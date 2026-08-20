// ===========================================================================
// net_config.h  -  Persistente Netzwerk-Konfiguration (Stufe B)
// ---------------------------------------------------------------------------
// Speichert IP-Modus (DHCP/statisch), statische IP-Felder und NTP-Server in
// den ESPHome-Preferences (Flash). Wird von timer_web.h (Web-Formular/JSON-API)
// gelesen/geschrieben und in timer-relais-c3.yaml angewendet:
//   - netcfg_load()        : beim Boot laden (frueh in on_boot)
//   - netcfg_apply_ntp()   : NTP-Server setzen (Boot + nach Speichern)
//   - netcfg_apply_static(): statische IP setzen (bei wifi on_connect)
//
// WLAN-Zugangsdaten laufen NICHT hierueber, sondern ueber ESPHomes eigenes
// save_wifi_sta() + Captive-Portal. Hostname bleibt compile-zeitlich.
// ===========================================================================
#pragma once
#include "esphome.h"
#include "esphome/components/wifi/wifi_component.h"
#include <cstring>
#include "esp_sntp.h"
#include "esp_netif.h"
#include <mdns.h>

namespace esphome {

struct NetCfg {
  uint8_t version;      // Layout-Version (aktuell 5)
  uint8_t use_static;   // 0 = DHCP, 1 = statisch
  char ip[16];
  char gw[16];
  char sn[16];          // Subnetzmaske
  char dns[16];
  char ntp[48];
  char host[32];        // Hostname (mDNS + DHCP)
  uint8_t roaming;      // 0 = aus (ESPHome-Scan-Roaming), 1 = 802.11k/v (BTM/RRM)
  char lang[4];         // UI-/OLED-Sprache: "de" | "en" | "fr"
  uint8_t led_bri;      // Status-LED-Helligkeit 0..100 % (WebUI-Regler)
};

static NetCfg g_netcfg;
static ESPPreferenceObject g_netcfg_pref;
static bool g_reboot_pending = false;
static bool g_reconnect_pending = false;
static bool g_prefs_save_pending = false;

inline void netcfg_defaults(NetCfg &c) {
  memset(&c, 0, sizeof(c));
  c.version = 5;
  c.use_static = 0;
  strncpy(c.ip,  "192.168.1.50",   sizeof(c.ip) - 1);
  strncpy(c.gw,  "192.168.1.1",    sizeof(c.gw) - 1);
  strncpy(c.sn,  "255.255.255.0",  sizeof(c.sn) - 1);
  strncpy(c.dns, "192.168.1.1",    sizeof(c.dns) - 1);
  strncpy(c.ntp, "de.pool.ntp.org", sizeof(c.ntp) - 1);
  strncpy(c.host, "feeder-relais", sizeof(c.host) - 1);
  c.roaming = 0;  // Default: kein k/v -> ESPHome-Scan-Roaming wie bisher
  strncpy(c.lang, "de", sizeof(c.lang) - 1);  // Default-Sprache Deutsch
  c.led_bri = 25;  // Status-LED-Default 25 %
}

inline void netcfg_load() {
  g_netcfg_pref = global_preferences->make_preference<NetCfg>((uint32_t) 0x4E657444);  // 'NetD'
  if (!g_netcfg_pref.load(&g_netcfg) || g_netcfg.version != 5)
    netcfg_defaults(g_netcfg);
}

// Erlaubte UI-/OLED-Sprachen in FESTER Reihenfolge; der Index ist zugleich die
// Spalte in allen Sprach-Tabellen (Web-Dictionary, OLED). Reihenfolge NICHT
// aendern. Unbekannt -> Index 0 (Deutsch).
static const char *const NETCFG_LANGS[] = {"de", "en", "fr", "nl", "es", "it"};
static const uint8_t NETCFG_LANG_N = 6;
inline uint8_t netcfg_lang_idx() {
  for (uint8_t i = 1; i < NETCFG_LANG_N; i++)
    if (strcmp(g_netcfg.lang, NETCFG_LANGS[i]) == 0) return i;
  return 0;
}
inline void netcfg_sanitize_lang() {
  for (uint8_t i = 0; i < NETCFG_LANG_N; i++)
    if (strcmp(g_netcfg.lang, NETCFG_LANGS[i]) == 0) return;
  strncpy(g_netcfg.lang, "de", sizeof(g_netcfg.lang) - 1);
}

// Auf ein gueltiges DNS-Label reduzieren (a-z 0-9 '-'), Rand-'-' entfernen.
inline void netcfg_sanitize_host(char *h) {
  for (size_t i = 0; h[i]; i++) {
    char c = h[i];
    if (c >= 'A' && c <= 'Z') c = (char) (c - 'A' + 'a');
    if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-')) c = '-';
    h[i] = c;
  }
  size_t len = strlen(h), s = 0;
  while (h[s] == '-') s++;
  while (len > s && h[len - 1] == '-') h[--len] = '\0';
  if (s > 0) memmove(h, h + s, len - s + 1);
  if (h[0] == '\0') strncpy(h, "feeder-relais", 31);
}

// Hostname zur Laufzeit anwenden: mDNS-Name (.local) sofort, DHCP-Name des
// STA-netif (Router) - der greift sauber nach Reconnect/Neustart.
inline void netcfg_apply_hostname() {
  if (g_netcfg.host[0] == '\0') return;
  mdns_hostname_set(g_netcfg.host);                 // mDNS (.local) sofort
  esp_netif_t *nif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
  if (nif == nullptr) return;
  // Compile-Default (feeder-relais) hat ESPHome bereits gesetzt -> nichts noetig.
  if (strcmp(g_netcfg.host, App.get_name().c_str()) == 0) return;
  if (g_netcfg.use_static) {
    esp_netif_set_hostname(nif, g_netcfg.host);
  } else {
    // DHCP-Client neu starten, damit der Router den neuen Namen (Option 12)
    // per frischem DISCOVER erhaelt. esp_netif_set_hostname verlangt DHCP=aus.
    esp_netif_dhcpc_stop(nif);
    esp_netif_set_hostname(nif, g_netcfg.host);
    esp_netif_dhcpc_start(nif);
  }
}

// ACHTUNG: Wird aus dem WEBSERVER-Task aufgerufen. ESPHomes Preferences
// (globale s_pending_save-Liste + NVS-Handle) sind NICHT threadsicher gegen den
// Main-Task -> save()/sync() hier direkt = Data-Race -> Panik/Neustart. Deshalb
// nur markieren; das eigentliche Schreiben macht netcfg_flush() im Main-Task
// (1s-Interval, dieselbe Task wie ESPHomes eigener Preferences-Sync).
inline void netcfg_save() { g_prefs_save_pending = true; }

// Nur im MAIN-Task aufrufen (Interval). Schreibt g_netcfg dauerhaft ins Flash.
inline void netcfg_flush() {
  g_netcfg_pref.save(&g_netcfg);
  global_preferences->sync();  // nvs_commit; sofort dauerhaft
}

// Nur den Servernamen aendern - erhaelt den von der ESPHome-sntp-Komponente
// gesetzten Sync-Callback (der die Uhr aktualisiert). Wirkt beim naechsten Sync.
inline void netcfg_apply_ntp() {
  if (g_netcfg.ntp[0] != '\0')
    esp_sntp_setservername(0, g_netcfg.ntp);
}

// Statische IP per ESP-IDF-netif setzen (nach jedem Verbinden aufrufen).
inline void netcfg_apply_static() {
  if (!g_netcfg.use_static)
    return;
  esp_netif_t *nif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
  if (nif == nullptr)
    return;
  esp_netif_dhcpc_stop(nif);
  esp_netif_ip_info_t info;
  memset(&info, 0, sizeof(info));
  esp_netif_str_to_ip4(g_netcfg.ip, &info.ip);
  esp_netif_str_to_ip4(g_netcfg.gw, &info.gw);
  esp_netif_str_to_ip4(g_netcfg.sn, &info.netmask);
  esp_netif_set_ip_info(nif, &info);
  esp_netif_dns_info_t dns;
  memset(&dns, 0, sizeof(dns));
  dns.ip.type = ESP_IPADDR_TYPE_V4;
  esp_netif_str_to_ip4(g_netcfg.dns, &dns.ip.u_addr.ip4);
  esp_netif_set_dns_info(nif, ESP_NETIF_DNS_MAIN, &dns);
}

// 802.11k/v-Roaming (BTM/RRM) zur Laufzeit schalten. Die *Faehigkeit* ist fest
// einkompiliert (enable_btm/enable_rrm in der YAML -> CONFIG_WPA_11KV_SUPPORT).
// btm_/rrm_ werden bei jedem (Re)Connect in die STA-Config uebernommen, wirken
// also voll ab dem naechsten Verbinden/Neustart. post_connect_roaming (ESPHomes
// eigenes Scan-Roaming) laeuft gegengleich: aus, wenn k/v aktiv ist (dann
// uebernimmt der Treiber die Roaming-Entscheidung).
inline void netcfg_apply_roaming() {
  auto *w = wifi::global_wifi_component;
  if (w == nullptr) return;
  bool on = g_netcfg.roaming != 0;
  w->set_btm(on);
  w->set_rrm(on);
  w->set_post_connect_roaming(!on);
}

// Sauberes WLAN-Neuverbinden: entspricht ESPHomes wifi.disable + wifi.enable.
// enable() ruft start() -> start_connecting(), das die STA-Config NEU aufbaut und
// dabei die aktuellen btm_/rrm_ (Roaming) uebernimmt -> Aenderung sofort aktiv.
// Wird verzoegert ueber das 1s-Interval aufgerufen, damit die HTTP-Antwort noch
// rausgeht, bevor die Verbindung kurz abreisst.
inline void netcfg_wifi_reconnect() {
  auto *w = wifi::global_wifi_component;
  if (w == nullptr) return;
  w->disable();
  w->enable();
}

}  // namespace esphome

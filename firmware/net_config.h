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
#include <cstring>
#include "esp_sntp.h"
#include "esp_netif.h"

namespace esphome {

struct NetCfg {
  uint8_t version;      // Layout-Version (aktuell 1)
  uint8_t use_static;   // 0 = DHCP, 1 = statisch
  char ip[16];
  char gw[16];
  char sn[16];          // Subnetzmaske
  char dns[16];
  char ntp[48];
};

static NetCfg g_netcfg;
static ESPPreferenceObject g_netcfg_pref;
static bool g_reboot_pending = false;

inline void netcfg_defaults(NetCfg &c) {
  memset(&c, 0, sizeof(c));
  c.version = 1;
  c.use_static = 0;
  strncpy(c.ip,  "192.168.1.50",   sizeof(c.ip) - 1);
  strncpy(c.gw,  "192.168.1.1",    sizeof(c.gw) - 1);
  strncpy(c.sn,  "255.255.255.0",  sizeof(c.sn) - 1);
  strncpy(c.dns, "192.168.1.1",    sizeof(c.dns) - 1);
  strncpy(c.ntp, "de.pool.ntp.org", sizeof(c.ntp) - 1);
}

inline void netcfg_load() {
  g_netcfg_pref = global_preferences->make_preference<NetCfg>((uint32_t) 0x4E657443);  // 'NetC'
  if (!g_netcfg_pref.load(&g_netcfg) || g_netcfg.version != 1)
    netcfg_defaults(g_netcfg);
}

inline void netcfg_save() { g_netcfg_pref.save(&g_netcfg); }

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

}  // namespace esphome

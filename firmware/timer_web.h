// ===========================================================================
// timer_web.h  –  Mobile Web-App + JSON-API für die Timer-Ersatzplatine
// ---------------------------------------------------------------------------
// Wird von timer-relais-c3.yaml über `esphome: includes:` eingebunden und in
// on_boot als AsyncWebHandler an web_server_base (Port 80) gehängt.
//
// Seiten (Single-Page, Tabs):  Bedienung · Einstellungen · Netzwerk · Status
// JSON-API (auch für ioBroker): GET /api/status, POST /api/trigger?button=N,
//                               POST /api/stop, POST /api/config?time1..3=
//
// Quelle der Wahrheit bleiben die ESPHome-Entitäten (time1/2/3, start_timer,
// shelly_trigger, remaining) – hier werden nur Zeiger darauf gehalten.
// ===========================================================================
#pragma once
#include "esphome.h"
#include <new>
#include <span>
#include <esp_system.h>
#include <esp_wifi.h>
#include "net_config.h"
#include "log_ring.h"
#include "esphome/components/wifi/wifi_component.h"

// Geflashte Firmware-Version (im Status oben angezeigt). Bei jedem Release
// mitziehen (siehe Release-Ablauf / github-repo-Memory).
#define FW_VERSION "0.0.15"

namespace esphome {

static const char TIMER_INDEX_HTML[] PROGMEM = R"HTMLPAGE(<!doctype html>
<html lang=de><head><meta charset=utf-8>
<meta name=viewport content="width=device-width,initial-scale=1,viewport-fit=cover">
<title>Feeder-Relais</title>
<style>
:root{--bg:#0f1420;--card:#1a2232;--line:#232d42;--mut:#8595ad;--fg:#eef2f8;
--acc:#3b82f6;--ok:#22c55e;--warn:#f59e0b}
*{box-sizing:border-box}
body{margin:0;font:15px/1.45 system-ui,-apple-system,sans-serif;background:var(--bg);color:var(--fg)}
.wrap{max-width:480px;margin:0 auto;padding:14px 14px 88px}
h1{font-size:18px;margin:8px 2px 12px;display:flex;align-items:center;gap:9px}
.dot{width:11px;height:11px;border-radius:50%;background:var(--warn);flex:0 0 auto}
.dot.on{background:var(--ok);box-shadow:0 0 10px var(--ok)}
.card{background:var(--card);border-radius:14px;padding:16px;margin:10px 0}
.state{text-align:center;padding:24px 12px}
.state .big{font-size:44px;font-weight:700;letter-spacing:.5px;line-height:1}
.state .sub{color:var(--mut);margin-top:8px;font-size:14px}
.btns{display:grid;grid-template-columns:1fr 1fr 1fr;gap:10px}
button{font:inherit;color:var(--fg);background:var(--acc);border:0;border-radius:12px;
padding:15px 8px;cursor:pointer;-webkit-tap-highlight-color:transparent}
button:active{filter:brightness(.9)}
button.stop{background:#ef4444;width:100%;margin-top:10px;padding:14px}
.tb{display:grid;place-items:center;gap:3px}.tb b{font-size:15px}.tb span{font-size:12px;color:#cfe0ff}
label{display:block;color:var(--mut);font-size:13px;margin:12px 0 5px}
input,select{width:100%;font:inherit;color:var(--fg);background:#0d1424;border:1px solid #2b3855;
border-radius:10px;padding:12px}
.row{display:flex;justify-content:space-between;gap:10px;padding:10px 2px;border-bottom:1px solid var(--line)}
.row:last-child{border:0}.row .k{color:var(--mut)}.row .v{text-align:right;word-break:break-all}
nav{position:fixed;left:0;right:0;bottom:0;background:#131a29;border-top:1px solid var(--line);
display:flex;padding-bottom:env(safe-area-inset-bottom)}
nav a{flex:1;text-align:center;padding:11px 4px;color:var(--mut);font-size:12px;text-decoration:none}
nav a.act{color:var(--fg);box-shadow:inset 0 2px 0 var(--acc)}
.hide{display:none}
.note{color:var(--mut);font-size:12px;display:block;margin-top:10px;line-height:1.4}
.toast{position:fixed;left:50%;bottom:78px;transform:translateX(-50%);background:#26304a;
padding:10px 18px;border-radius:22px;opacity:0;pointer-events:none;transition:.3s}
.toast.show{opacity:1}
</style></head><body>
<div class=wrap>
 <h1><span class=dot id=dot></span><span id=hdr>Feeder-Relais</span></h1>

 <section id=p_start>
  <div class="card state"><div class=big id=stBig>&ndash;</div><div class=sub id=stSub></div></div>
  <div class=btns>
   <button onclick="trig(1)"><span class=tb><b><span data-i18n=btn>Taster</span> 1</b><span id=t1s>&ndash;</span></span></button>
   <button onclick="trig(2)"><span class=tb><b><span data-i18n=btn>Taster</span> 2</b><span id=t2s>&ndash;</span></span></button>
   <button onclick="trig(3)"><span class=tb><b><span data-i18n=btn>Taster</span> 3</b><span id=t3s>&ndash;</span></span></button>
  </div>
  <button class=stop onclick="stop()" data-i18n=stop>Stopp</button>
 </section>

 <section id=p_cfg class=hide>
  <div class=card>
   <label data-i18n=lang_label>Sprache</label>
   <select id=langsel onchange="changeLang()">
    <option value=de>Deutsch</option>
    <option value=en>English</option>
    <option value=fr>Fran&ccedil;ais</option>
   </select>
  </div>
  <div class=card>
   <label data-i18n=cfg_t1>Zeit Taster 1 (Sekunden)</label><input id=c1 type=number min=1 max=600 inputmode=numeric>
   <label data-i18n=cfg_t2>Zeit Taster 2 (Sekunden)</label><input id=c2 type=number min=1 max=600 inputmode=numeric>
   <label data-i18n=cfg_t3>Zeit Taster 3 (Sekunden)</label><input id=c3 type=number min=1 max=600 inputmode=numeric>
   <button style="width:100%;margin-top:16px" onclick="save()" data-i18n=save>Speichern</button>
  </div>
 </section>

 <section id=p_net class=hide>
  <div class=card>
   <b data-i18n=wifi_t>WLAN</b>
   <div class=row><span class=k data-i18n=cur>Aktuell verbunden</span><span class=v id=cur_ssid>&ndash;</span></div>
   <label data-i18n=wifi_switch>Auf anderes WLAN wechseln &ndash; Netzwerkname (SSID)</label><input id=w_ssid autocomplete=off>
   <label data-i18n=pw>Passwort</label><input id=w_pw type=password autocomplete=off>
   <button style="width:100%;margin-top:12px" onclick="saveWifi()" data-i18n=wifi_save>WLAN speichern &amp; verbinden</button>
  </div>
  <div class=card>
   <b data-i18n=ipcfg>IP-Konfiguration</b>
   <label data-i18n=mode>Modus</label>
   <select id=n_static onchange="ipmode()">
    <option value=0 data-i18n=dhcp>DHCP (automatisch)</option>
    <option value=1 data-i18n=ipstatic>Statisch</option>
   </select>
   <div id=ipfields>
    <label data-i18n=ip>IP-Adresse</label><input id=n_ip inputmode=decimal>
    <label>Gateway</label><input id=n_gw inputmode=decimal>
    <label data-i18n=sn>Subnetzmaske</label><input id=n_sn inputmode=decimal>
    <label data-i18n=dns>DNS-Server</label><input id=n_dns inputmode=decimal>
   </div>
   <button style="width:100%;margin-top:12px" onclick="saveNet()" data-i18n=ip_save>IP-Konfig speichern</button>
  </div>
  <div class=card>
   <b data-i18n=ntp_t>NTP-Zeitserver</b>
   <label data-i18n=server>Server</label><input id=n_ntp autocomplete=off>
   <button style="width:100%;margin-top:12px" onclick="saveNtp()" data-i18n=ntp_save>NTP speichern</button>
  </div>
  <div class=card>
   <b data-i18n=host_t>Hostname</b>
   <label data-i18n=host_l>Gerätename (a–z, 0–9, „-")</label><input id=n_host autocomplete=off>
   <button style="width:100%;margin-top:12px" onclick="saveHost()" data-i18n=host_save>Hostname speichern</button>
   <span class=note data-i18n=host_note>Der mDNS-Name (…&#8203;.local) wird sofort umgestellt; der
   DHCP-Name (Router) und eine statische IP nach einem Neustart.</span>
   <button class=stop style="background:#b45309;margin-top:10px" onclick="reboot()" data-i18n=reboot>Neustart</button>
  </div>
  <div class=card>
   <b data-i18n=roam_t>WLAN-Roaming (802.11k/v)</b>
   <label style="display:flex;align-items:center;gap:8px;margin-top:8px">
    <input type=checkbox id=n_roam onchange="saveRoam()"> <span data-i18n=roam_chk>BTM/RRM aktivieren</span></label>
   <span class=note data-i18n=roam_note>Nur bei mehreren Access-Points mit gleicher SSID sinnvoll
   (z.&#8203;B. UniFi/Mesh): Der Router kann das Gerät gezielt auf den stärkeren
   AP umbuchen (802.11v BTM) und nutzt Nachbar-Listen (802.11k RRM). Aus =
   klassisches ESPHome-Scan-Roaming.</span>
   <button class=sec style="width:100%;background:#26304a;margin-top:10px" onclick="reconnect()" data-i18n=recon>Jetzt neu verbinden</button>
   <span class=note data-i18n=recon_note>Übernimmt die Roaming-Einstellung sofort. Das WLAN trennt
   dafür kurz &ndash; die Seite ist ein paar Sekunden nicht erreichbar.</span>
  </div>
 </section>

 <section id=p_stat class=hide><div class=card id=statbox></div></section>

 <section id=p_svc class=hide>
  <div class=card>
   <b data-i18n=log_t>Log / Debug</b>
   <label data-i18n=log_lvl>Anzeige-Stufe</label>
   <select id=lg_lvl onchange="logLevelChange()">
    <option value=1>ERROR</option>
    <option value=2>WARN</option>
    <option value=3 selected>INFO</option>
    <option value=5>DEBUG</option>
   </select>
   <label style="display:flex;align-items:center;gap:8px;margin-top:12px">
    <input type=checkbox id=lg_on onchange="logToggle()"> <span data-i18n=log_live>Live-Anzeige aktivieren</span></label>
   <pre id=lg_out style="margin:10px 0;max-height:240px;overflow:auto;background:#0d1424;border:1px solid #2b3855;border-radius:10px;padding:8px;font:11px/1.35 ui-monospace,monospace;white-space:pre-wrap;word-break:break-all"></pre>
   <button class=sec style="width:100%;background:#26304a" onclick="logClear()" data-i18n=log_clear>Anzeige leeren</button>
  </div>
  <div class=card>
   <b data-i18n=ota_t>Firmware-Update (OTA)</b>
   <span class=note data-i18n=ota_note>Kompilierte .bin hochladen (bei ESPHome die firmware.bin aus dem Build).
   Das Gerät startet danach neu. Alternativ per Netzwerk: esphome run (Port 3232).</span>
   <input type=file id=ota_file accept=".bin,application/octet-stream" style="margin-top:10px">
   <button style="width:100%;margin-top:10px" onclick="otaUpload()" data-i18n=ota_btn>Hochladen &amp; aktualisieren</button>
   <div id=ota_stat class=note></div>
  </div>
  <div class=card>
   <b data-i18n=device>Gerät</b>
   <button class=stop style="background:#b45309;margin-top:4px" onclick="reboot()" data-i18n=reboot>Neustart</button>
  </div>
 </section>
</div>

<nav>
 <a href="#" class=act data-p=start onclick="nav('start');return false" data-i18n=nav_start>Start</a>
 <a href="#" data-p=cfg  onclick="nav('cfg');return false" data-i18n=nav_cfg>Zeiten</a>
 <a href="#" data-p=net  onclick="nav('net');return false" data-i18n=nav_net>Netzwerk</a>
 <a href="#" data-p=stat onclick="nav('stat');return false" data-i18n=nav_stat>Status</a>
 <a href="#" data-p=svc  onclick="nav('svc');return false" data-i18n=nav_svc>Service</a>
</nav>
<div class=toast id=toast></div>

<script>
var $=function(i){return document.getElementById(i)};
var LANG='de';
var T={
 btn:{de:'Taster',en:'Button',fr:'Bouton'},
 stop:{de:'Stopp',en:'Stop',fr:'Arrêt'},
 lang_label:{de:'Sprache',en:'Language',fr:'Langue'},
 cfg_t1:{de:'Zeit Taster 1 (Sekunden)',en:'Time button 1 (seconds)',fr:'Durée bouton 1 (secondes)'},
 cfg_t2:{de:'Zeit Taster 2 (Sekunden)',en:'Time button 2 (seconds)',fr:'Durée bouton 2 (secondes)'},
 cfg_t3:{de:'Zeit Taster 3 (Sekunden)',en:'Time button 3 (seconds)',fr:'Durée bouton 3 (secondes)'},
 save:{de:'Speichern',en:'Save',fr:'Enregistrer'},
 wifi_t:{de:'WLAN',en:'Wi-Fi',fr:'Wi-Fi'},
 cur:{de:'Aktuell verbunden',en:'Currently connected',fr:'Connecté actuellement'},
 wifi_switch:{de:'Auf anderes WLAN wechseln – Netzwerkname (SSID)',en:'Switch to another Wi-Fi – network name (SSID)',fr:'Changer de Wi-Fi – nom du réseau (SSID)'},
 pw:{de:'Passwort',en:'Password',fr:'Mot de passe'},
 wifi_save:{de:'WLAN speichern & verbinden',en:'Save Wi-Fi & connect',fr:'Enregistrer le Wi-Fi et connecter'},
 ipcfg:{de:'IP-Konfiguration',en:'IP configuration',fr:'Configuration IP'},
 mode:{de:'Modus',en:'Mode',fr:'Mode'},
 dhcp:{de:'DHCP (automatisch)',en:'DHCP (automatic)',fr:'DHCP (automatique)'},
 ipstatic:{de:'Statisch',en:'Static',fr:'Statique'},
 ip:{de:'IP-Adresse',en:'IP address',fr:'Adresse IP'},
 sn:{de:'Subnetzmaske',en:'Subnet mask',fr:'Masque de sous-réseau'},
 dns:{de:'DNS-Server',en:'DNS server',fr:'Serveur DNS'},
 ip_save:{de:'IP-Konfig speichern',en:'Save IP config',fr:'Enregistrer la config IP'},
 ntp_t:{de:'NTP-Zeitserver',en:'NTP time server',fr:'Serveur de temps NTP'},
 server:{de:'Server',en:'Server',fr:'Serveur'},
 ntp_save:{de:'NTP speichern',en:'Save NTP',fr:'Enregistrer NTP'},
 host_t:{de:'Hostname',en:'Hostname',fr:'Nom d’hôte'},
 host_l:{de:'Gerätename (a–z, 0–9, „-")',en:'Device name (a–z, 0–9, "-")',fr:'Nom de l’appareil (a–z, 0–9, « - »)'},
 host_save:{de:'Hostname speichern',en:'Save hostname',fr:'Enregistrer le nom d’hôte'},
 host_note:{de:'Der mDNS-Name (….local) wird sofort umgestellt; der DHCP-Name (Router) und eine statische IP nach einem Neustart.',en:'The mDNS name (….local) changes immediately; the DHCP name (router) and a static IP after a restart.',fr:'Le nom mDNS (….local) change aussitôt ; le nom DHCP (routeur) et une IP statique après un redémarrage.'},
 reboot:{de:'Neustart',en:'Restart',fr:'Redémarrer'},
 roam_t:{de:'WLAN-Roaming (802.11k/v)',en:'Wi-Fi roaming (802.11k/v)',fr:'Itinérance Wi-Fi (802.11k/v)'},
 roam_chk:{de:'BTM/RRM aktivieren',en:'Enable BTM/RRM',fr:'Activer BTM/RRM'},
 roam_note:{de:'Nur bei mehreren Access-Points mit gleicher SSID sinnvoll (z. B. UniFi/Mesh): Der Router kann das Gerät gezielt auf den stärkeren AP umbuchen (802.11v BTM) und nutzt Nachbar-Listen (802.11k RRM). Aus = klassisches ESPHome-Scan-Roaming.',en:'Useful only with several access points sharing the same SSID (e.g. UniFi/Mesh): the router can steer the device to the stronger AP (802.11v BTM) and uses neighbor lists (802.11k RRM). Off = classic ESPHome scan roaming.',fr:'Utile seulement avec plusieurs points d’accès de même SSID (p. ex. UniFi/Mesh) : le routeur peut basculer l’appareil vers le point d’accès le plus fort (802.11v BTM) et utilise les listes de voisins (802.11k RRM). Désactivé = itinérance classique par scan d’ESPHome.'},
 recon:{de:'Jetzt neu verbinden',en:'Reconnect now',fr:'Reconnecter maintenant'},
 recon_note:{de:'Übernimmt die Roaming-Einstellung sofort. Das WLAN trennt dafür kurz – die Seite ist ein paar Sekunden nicht erreichbar.',en:'Applies the roaming setting immediately. Wi-Fi briefly disconnects – the page is unreachable for a few seconds.',fr:'Applique aussitôt le réglage d’itinérance. Le Wi-Fi se coupe brièvement – la page est injoignable quelques secondes.'},
 log_t:{de:'Log / Debug',en:'Log / Debug',fr:'Journal / Débogage'},
 log_lvl:{de:'Anzeige-Stufe',en:'Display level',fr:'Niveau d’affichage'},
 log_live:{de:'Live-Anzeige aktivieren',en:'Enable live view',fr:'Activer l’affichage en direct'},
 log_clear:{de:'Anzeige leeren',en:'Clear view',fr:'Effacer l’affichage'},
 ota_t:{de:'Firmware-Update (OTA)',en:'Firmware update (OTA)',fr:'Mise à jour du firmware (OTA)'},
 ota_note:{de:'Kompilierte .bin hochladen (bei ESPHome die firmware.bin aus dem Build). Das Gerät startet danach neu. Alternativ per Netzwerk: esphome run (Port 3232).',en:'Upload a compiled .bin (for ESPHome, the firmware.bin from the build). The device restarts afterwards. Alternatively over the network: esphome run (port 3232).',fr:'Téléverser un .bin compilé (pour ESPHome, le firmware.bin du build). L’appareil redémarre ensuite. Sinon par le réseau : esphome run (port 3232).'},
 ota_btn:{de:'Hochladen & aktualisieren',en:'Upload & update',fr:'Téléverser et mettre à jour'},
 device:{de:'Gerät',en:'Device',fr:'Appareil'},
 nav_start:{de:'Start',en:'Start',fr:'Accueil'},
 nav_cfg:{de:'Zeiten',en:'Times',fr:'Durées'},
 nav_net:{de:'Netzwerk',en:'Network',fr:'Réseau'},
 nav_stat:{de:'Status',en:'Status',fr:'État'},
 nav_svc:{de:'Service',en:'Service',fr:'Service'},
 st_ver:{de:'Version',en:'Version',fr:'Version'},
 st_fw:{de:'Firmware',en:'Firmware',fr:'Firmware'},
 st_uptime:{de:'Laufzeit',en:'Uptime',fr:'Durée de service'},
 st_heap:{de:'Freier Speicher',en:'Free memory',fr:'Mémoire libre'},
 st_wifi:{de:'WLAN',en:'Wi-Fi',fr:'Wi-Fi'},
 st_ssid:{de:'SSID',en:'SSID',fr:'SSID'},
 st_chansig:{de:'Kanal / Signal',en:'Channel / signal',fr:'Canal / signal'},
 st_host:{de:'Hostname',en:'Hostname',fr:'Nom d’hôte'},
 st_ip:{de:'IP-Adresse',en:'IP address',fr:'Adresse IP'},
 st_mac:{de:'MAC',en:'MAC',fr:'MAC'},
 st_ap:{de:'Setup-AP',en:'Setup AP',fr:'Point d’accès de config'},
 st_reset:{de:'Reset-Grund',en:'Reset reason',fr:'Cause du redémarrage'},
 st_relay:{de:'Relais',en:'Relay',fr:'Relais'},
 st_rem:{de:'Restzeit',en:'Remaining',fr:'Temps restant'},
 st_roam:{de:'WLAN-Roaming (802.11k/v)',en:'Wi-Fi roaming (802.11k/v)',fr:'Itinérance Wi-Fi (802.11k/v)'},
 chan_pfx:{de:'Kanal ',en:'Channel ',fr:'Canal '},
 on:{de:'AN',en:'ON',fr:'MARCHE'},
 off:{de:'AUS',en:'OFF',fr:'ARRÊT'},
 ein:{de:'EIN',en:'ON',fr:'MARCHE'},
 aus:{de:'AUS',en:'OFF',fr:'ARRÊT'},
 run:{de:'läuft – Taster',en:'running – button',fr:'actif – bouton'},
 ready:{de:'bereit',en:'ready',fr:'prêt'},
 notconn:{de:'nicht verbunden',en:'not connected',fr:'non connecté'},
 wifi_up:{de:'verbunden',en:'connected',fr:'connecté'},
 wifi_down:{de:'getrennt',en:'disconnected',fr:'déconnecté'},
 rst_poweron:{de:'Power-On',en:'Power-on',fr:'Mise sous tension'},
 rst_sw:{de:'Software',en:'Software',fr:'Logiciel'},
 rst_panic:{de:'Panik',en:'Panic',fr:'Panique'},
 rst_wdt:{de:'Watchdog',en:'Watchdog',fr:'Watchdog'},
 rst_brownout:{de:'Unterspannung',en:'Brownout',fr:'Sous-tension'},
 rst_deepsleep:{de:'Deep-Sleep',en:'Deep sleep',fr:'Veille profonde'},
 rst_unknown:{de:'unbekannt',en:'unknown',fr:'inconnu'},
 t_saved:{de:'Gespeichert',en:'Saved',fr:'Enregistré'},
 t_error:{de:'Fehler',en:'Error',fr:'Erreur'},
 t_wifi_saved:{de:'WLAN gespeichert',en:'Wi-Fi saved',fr:'Wi-Fi enregistré'},
 t_saved_reboot:{de:'Gespeichert – Neustart nötig',en:'Saved – restart required',fr:'Enregistré – redémarrage requis'},
 t_ntp_saved:{de:'NTP gespeichert',en:'NTP saved',fr:'NTP enregistré'},
 t_host_saved:{de:'Hostname gespeichert',en:'Hostname saved',fr:'Nom d’hôte enregistré'},
 t_roam_on:{de:'Roaming aktiviert',en:'Roaming enabled',fr:'Itinérance activée'},
 t_roam_off:{de:'Roaming aus',en:'Roaming off',fr:'Itinérance désactivée'},
 t_reboot:{de:'Neustart …',en:'Restarting …',fr:'Redémarrage …'},
 t_reconnect:{de:'Verbinde neu … (kurz offline)',en:'Reconnecting … (briefly offline)',fr:'Reconnexion … (hors ligne un instant)'},
 t_nofile:{de:'Keine Datei gewählt',en:'No file selected',fr:'Aucun fichier sélectionné'},
 t_uploading:{de:'Lade hoch … Gerät nicht trennen.',en:'Uploading … do not disconnect.',fr:'Téléversement … ne pas déconnecter.'},
 t_uploaded:{de:'Übertragen – Gerät startet neu.',en:'Transferred – device restarting.',fr:'Transféré – l’appareil redémarre.'},
 t_upload_disc:{de:'Verbindung getrennt (vermutlich Neustart nach Update).',en:'Connection lost (probably a restart after the update).',fr:'Connexion perdue (probablement un redémarrage après la mise à jour).'},
 c_reboot:{de:'Gerät jetzt neu starten?',en:'Restart the device now?',fr:'Redémarrer l’appareil maintenant ?'},
 c_reconnect:{de:'WLAN jetzt neu verbinden? Die Seite ist kurz offline.',en:'Reconnect Wi-Fi now? The page will be briefly offline.',fr:'Reconnecter le Wi-Fi maintenant ? La page sera hors ligne un instant.'}
};
function tr(k){var e=T[k];return e?(e[LANG]||e.de):k;}
function twifi(c){return tr('wifi_'+c);}
function treset(c){return tr('rst_'+c);}
function applyStatic(){document.documentElement.lang=LANG;
 var els=document.querySelectorAll('[data-i18n]');
 for(var i=0;i<els.length;i++)els[i].textContent=tr(els[i].getAttribute('data-i18n'));
 var ls=$('langsel');if(ls)ls.value=LANG;}
function setLang(l){if(l!='de'&&l!='en'&&l!='fr')l='de';LANG=l;applyStatic();}
function changeLang(){var l=$('langsel').value;setLang(l);api('/api/net?lang='+l,'POST');refresh();}
function nav(p){['start','cfg','net','stat','svc'].forEach(function(x){$('p_'+x).classList.toggle('hide',x!=p)});
 var a=document.querySelectorAll('nav a');for(var i=0;i<a.length;i++)a[i].classList.toggle('act',a[i].dataset.p==p);
 if(p=='net')loadNet();}
function loadNet(){api('/api/net').then(function(n){if(!n)return;
 $('n_static').value=n.static;$('n_ip').value=n.ip;$('n_gw').value=n.gw;$('n_sn').value=n.sn;
 $('n_dns').value=n.dns;$('n_ntp').value=n.ntp;$('n_host').value=n.hostname;$('n_roam').checked=!!n.roaming;ipmode();});}
function ipmode(){$('ipfields').style.display=($('n_static').value=='1')?'block':'none';}
function saveWifi(){api('/api/wifi?ssid='+encodeURIComponent($('w_ssid').value)+'&pw='+encodeURIComponent($('w_pw').value),'POST')
 .then(function(r){toast(r&&r.ok?tr('t_wifi_saved'):tr('t_error'));});}
function saveNet(){var q='static='+$('n_static').value+'&ip='+encodeURIComponent($('n_ip').value)
 +'&gw='+encodeURIComponent($('n_gw').value)+'&sn='+encodeURIComponent($('n_sn').value)+'&dns='+encodeURIComponent($('n_dns').value);
 api('/api/net?'+q,'POST').then(function(r){toast(($('n_static').value=='1')?tr('t_saved_reboot'):tr('t_saved'));});}
function saveNtp(){api('/api/net?ntp='+encodeURIComponent($('n_ntp').value),'POST').then(function(r){toast(r&&r.ok?tr('t_ntp_saved'):tr('t_error'));});}
function saveHost(){api('/api/net?host='+encodeURIComponent($('n_host').value),'POST').then(function(r){toast(tr('t_host_saved'));if(r&&r.hostname)$('n_host').value=r.hostname;});}
var roamHold=0;
function saveRoam(){roamHold=Date.now()+4000;  // kurz nicht vom Status ueberschreiben
 api('/api/net?roaming='+($('n_roam').checked?1:0),'POST').then(function(r){toast($('n_roam').checked?tr('t_roam_on'):tr('t_roam_off'));});}
function reboot(){if(confirm(tr('c_reboot')))api('/api/reboot','POST').then(function(){toast(tr('t_reboot'));});}
function reconnect(){if(confirm(tr('c_reconnect')))api('/api/reconnect','POST').then(function(){toast(tr('t_reconnect'));});}
var lgTimer=null,lgSeq=0,LVL={1:'E',2:'W',3:'I',4:'C',5:'D',6:'V'};
function logToggle(){if($('lg_on').checked){lgSeq=0;$('lg_out').textContent='';logPoll();lgTimer=setInterval(logPoll,1500);}
 else{if(lgTimer)clearInterval(lgTimer);lgTimer=null;}}
function logLevelChange(){if($('lg_on').checked){lgSeq=0;$('lg_out').textContent='';logPoll();}}
function logPoll(){api('/api/log?level='+$('lg_lvl').value+'&since='+lgSeq).then(function(d){if(!d||!d.lines)return;
 var o=$('lg_out');d.lines.forEach(function(x){if(x.s>lgSeq)lgSeq=x.s;o.textContent+='['+(LVL[x.l]||x.l)+'] '+x.t+'\n';});
 if(d.lines.length)o.scrollTop=o.scrollHeight;});}
function logClear(){$('lg_out').textContent='';}
function otaUpload(){var f=$('ota_file').files[0];if(!f){toast(tr('t_nofile'));return;}
 $('ota_stat').textContent=tr('t_uploading');
 var fd=new FormData();fd.append('file',f,f.name);
 fetch('/update',{method:'POST',body:fd}).then(function(r){return r.text();})
  .then(function(){$('ota_stat').textContent=tr('t_uploaded');})
  .catch(function(){$('ota_stat').textContent=tr('t_upload_disc');});}
function toast(m){var t=$('toast');t.textContent=m;t.classList.add('show');setTimeout(function(){t.classList.remove('show')},1600);}
function api(u,m){return fetch(u,{method:m||'GET'}).then(function(r){return r.json()}).catch(function(){return null});}
function trig(n){api('/api/trigger?button='+n,'POST').then(refresh);}
function stop(){api('/api/stop','POST').then(refresh);}
function save(){var q='time1='+$('c1').value+'&time2='+$('c2').value+'&time3='+$('c3').value;
 api('/api/config?'+q,'POST').then(function(r){toast(r&&r.ok?tr('t_saved'):tr('t_error'));refresh();});}
function up(s){var d=Math.floor(s/86400),h=Math.floor(s%86400/3600),m=Math.floor(s%3600/60);
 return (d?d+'d ':'')+('0'+h).slice(-2)+':'+('0'+m).slice(-2);}
function rows(box,arr){$(box).innerHTML=arr.map(function(kv){
 return '<div class=row><span class=k>'+kv[0]+'</span><span class=v>'+kv[1]+'</span></div>'}).join('');}
function bars(rssi){var n=rssi>=-55?4:(rssi>=-65?3:(rssi>=-75?2:1));
 var col=n>=3?'#22c55e':(n==2?'#f59e0b':'#ef4444');var h=[4,7,10,13];
 var s='<span style="display:inline-flex;align-items:flex-end;gap:2px;height:13px;vertical-align:-2px;margin:0 6px">';
 for(var i=0;i<4;i++)s+='<span style="width:3px;height:'+h[i]+'px;border-radius:1px;background:'+(i<n?col:'#333c52')+'"></span>';
 return s+'</span>';}
function refresh(){return api('/api/status').then(function(s){if(!s)return;
 if(s.lang&&s.lang!=LANG){LANG=s.lang;applyStatic();}
 var cs=$('cur_ssid');if(cs)cs.textContent=(s.wifi=='up'&&s.ssid)?s.ssid:tr('notconn');
 var dc=s.active?'#f59e0b':(s.fault?'#ef4444':'#22c55e');
 $('dot').style.background=dc;$('dot').style.boxShadow='0 0 8px '+dc;
 if(s.host){$('hdr').textContent=s.host;if(document.title!=s.host)document.title=s.host;}
 $('stBig').textContent=s.active?s.remaining+' s':(s.relay?tr('on'):tr('off'));
 $('stSub').textContent=s.active?(tr('run')+' '+(s.last||'?')):tr('ready');
 $('t1s').textContent=s.times[0]+' s';$('t2s').textContent=s.times[1]+' s';$('t3s').textContent=s.times[2]+' s';
 if(document.activeElement.tagName!='INPUT'){$('c1').value=s.times[0];$('c2').value=s.times[1];$('c3').value=s.times[2];}
 var rn=$('n_roam');if(rn&&rn!==document.activeElement&&Date.now()>roamHold)rn.checked=!!s.roaming;
 rows('statbox',[[tr('st_ver'),s.ver||'&ndash;'],[tr('st_fw'),s.fw],[tr('st_uptime'),up(s.uptime)],[tr('st_heap'),(s.heap/1024).toFixed(1)+' kB'],
  [tr('st_wifi'),twifi(s.wifi)],[tr('st_ssid'),s.ssid||'&ndash;'],
  [tr('st_chansig'),s.chan?(tr('chan_pfx')+s.chan+bars(s.rssi)+s.rssi+' dBm'):'&ndash;'],
  [tr('st_roam'),s.roaming?tr('ein'):tr('aus')],
  [tr('st_host'),s.host||'&ndash;'],
  [tr('st_ip'),s.ip||'&ndash;'],[tr('st_mac'),s.mac],[tr('st_ap'),s.ap],[tr('st_reset'),treset(s.reset)],
  [tr('st_relay'),s.relay?tr('on'):tr('off')],[tr('st_rem'),s.remaining+' s']]);
});}
refresh();setInterval(refresh,1000);
</script></body></html>)HTMLPAGE";

class TimerWebHandler : public AsyncWebHandler {
 public:
  number::Number *time1{nullptr}, *time2{nullptr}, *time3{nullptr};
  switch_::Switch *relay{nullptr};
  int *remaining{nullptr};
  int last_button{0};
  // Diagnose-Entitaeten (in on_boot gesetzt) fuer die Status-/Netzwerk-Seite
  sensor::Sensor *rssi{nullptr};
  sensor::Sensor *uptime{nullptr};
  text_sensor::TextSensor *ip{nullptr};
  text_sensor::TextSensor *ssid{nullptr};
  text_sensor::TextSensor *mac{nullptr};
  Component *oled{nullptr};   // fuer Stoerungs-Erkennung (is_failed)

  bool canHandle(AsyncWebServerRequest *req) const override {
    char urlbuf[AsyncWebServerRequest::URL_BUF_SIZE];
    const std::string u(req->url_to(urlbuf));
    return u == "/" || u.rfind("/api/", 0) == 0;
  }
  bool isRequestHandlerTrivial() const override { return false; }

  int qparam(AsyncWebServerRequest *req, const char *name, int def) {
    if (req->hasParam(name)) return atoi(req->getParam(name)->value().c_str());
    return def;
  }

  void copy_param(AsyncWebServerRequest *req, const char *name, char *dst, size_t n) {
    if (!req->hasParam(name)) return;
    std::string v = req->getParam(name)->value();
    strncpy(dst, v.c_str(), n - 1);
    dst[n - 1] = '\0';
  }

  void send_net(AsyncWebServerRequest *req) {
    // Heap statt Stack (httpd-Task-Stack ist knapp, siehe send_status).
    const size_t cap = 520;
    char *buf = new (std::nothrow) char[cap];
    if (buf == nullptr) { req->send(500, "application/json", "{\"ok\":false}"); return; }
    snprintf(buf, cap,
      "{\"ok\":true,\"static\":%d,\"ip\":\"%s\",\"gw\":\"%s\",\"sn\":\"%s\","
      "\"dns\":\"%s\",\"ntp\":\"%s\",\"hostname\":\"%s\",\"roaming\":%d,\"lang\":\"%s\"}",
      g_netcfg.use_static, g_netcfg.ip, g_netcfg.gw, g_netcfg.sn,
      g_netcfg.dns, g_netcfg.ntp, g_netcfg.host, g_netcfg.roaming, g_netcfg.lang);
    req->send(200, "application/json", buf);
    delete[] buf;
  }

  void apply_num(number::Number *n, int v) {
    if (n != nullptr && v >= 1 && v <= 600) n->make_call().set_value((float) v).perform();
  }

  // Stabiler Code (sprachneutral) - das Web-JS uebersetzt ihn (rst_*).
  const char *reset_reason() {
    switch (esp_reset_reason()) {
      case ESP_RST_POWERON:  return "poweron";
      case ESP_RST_SW:       return "sw";
      case ESP_RST_PANIC:    return "panic";
      case ESP_RST_INT_WDT:
      case ESP_RST_TASK_WDT:
      case ESP_RST_WDT:      return "wdt";
      case ESP_RST_BROWNOUT: return "brownout";
      case ESP_RST_DEEPSLEEP:return "deepsleep";
      default:               return "unknown";
    }
  }

  void send_status(AsyncWebServerRequest *req) {
    int rem = (remaining != nullptr) ? *remaining : 0;
    bool on = (relay != nullptr) ? relay->state : false;
    std::string ip_s   = (ip   != nullptr) ? ip->state   : std::string();
    std::string ssid_s = (ssid != nullptr) ? ssid->state : std::string();
    std::string mac_s  = (mac  != nullptr) ? mac->state  : std::string();
    bool connected = !ip_s.empty() && ip_s != "0.0.0.0";
    unsigned long up = (uptime != nullptr) ? (unsigned long) uptime->state
                                           : (unsigned long) (millis() / 1000UL);
    uint8_t chan = 0;
    wifi_second_chan_t sch;
    if (!connected || esp_wifi_get_channel(&chan, &sch) != ESP_OK) chan = 0;
    // Stoerung im Ruhezustand: OLED fehlerhaft oder kein WLAN.
    bool fault = (oled != nullptr && oled->is_failed()) || !connected;
    // JSON auf dem HEAP bauen, nicht auf dem knappen httpd-Task-Stack
    // (HTTPD_DEFAULT_CONFIG ~4 KB; hier laeuft zusaetzlich urlbuf[513]).
    const size_t cap = 960;
    char *buf = new (std::nothrow) char[cap];
    if (buf == nullptr) { req->send(500, "application/json", "{\"ok\":false}"); return; }
    snprintf(buf, cap,
      "{\"ok\":true,\"active\":%s,\"remaining\":%d,\"relay\":%s,\"last\":%d,\"fault\":%s,"
      "\"times\":[%d,%d,%d],\"host\":\"%s\",\"ip\":\"%s\",\"ssid\":\"%s\","
      "\"rssi\":%d,\"chan\":%d,\"mac\":\"%s\",\"ap\":\"%s\",\"fw\":\"%s\",\"uptime\":%lu,"
      "\"heap\":%u,\"wifi\":\"%s\",\"reset\":\"%s\",\"lang\":\"%s\",\"roaming\":%d,"
      "\"ver\":\"%s\"}",
      (rem > 0) ? "true" : "false", rem, on ? "true" : "false", last_button,
      fault ? "true" : "false",
      time1 ? (int) time1->state : 0, time2 ? (int) time2->state : 0, time3 ? (int) time3->state : 0,
      g_netcfg.host,
      ip_s.c_str(),
      ssid_s.c_str(),
      (rssi != nullptr) ? (int) rssi->state : 0,
      (int) chan,
      mac_s.c_str(),
      "Feeder-Relais Setup",
      (__DATE__ " " __TIME__),
      up,
      (unsigned) esp_get_free_heap_size(),
      connected ? "up" : "down",   // sprachneutraler Code -> JS uebersetzt (wifi_*)
      reset_reason(),
      g_netcfg.lang,
      g_netcfg.roaming,
      FW_VERSION);
    req->send(200, "application/json", buf);
    delete[] buf;   // send() kopiert synchron -> danach freigeben
  }

  void handleRequest(AsyncWebServerRequest *req) override {
    // URL dekodiert lesen. Puffer auf den HEAP: dieser Frame bleibt waehrend des
    // gesamten (tiefen) Requests aktiv; auf dem ~4-KB-httpd-Stack fuehrte ein
    // fester URL_BUF-Puffer zusammen mit send_* zu einem Stack-Overflow (Panik).
    constexpr size_t UB = AsyncWebServerRequest::URL_BUF_SIZE;
    char *ub = new (std::nothrow) char[UB];
    if (ub == nullptr) { req->send(500, "application/json", "{\"ok\":false}"); return; }
    const std::string u(req->url_to(std::span<char, UB>(ub, UB)));
    delete[] ub;   // u ist eine Kopie -> Puffer sofort freigeben
    if (u == "/") {
      req->send(200, "text/html", TIMER_INDEX_HTML);
      return;
    }
    if (u == "/api/trigger") {
      int b = qparam(req, "button", 0);
      int secs = qparam(req, "seconds", 0);
      if (b >= 1 && b <= 3) {
        number::Number *n = (b == 1) ? time1 : (b == 2) ? time2 : time3;
        if (n != nullptr) secs = (int) n->state;
        last_button = b;
      }
      if (secs > 0) {  // entspricht dem Script start_timer: Restzeit setzen + Relais an
        if (remaining != nullptr) *remaining = secs;
        if (relay != nullptr) relay->turn_on();
      }
      send_status(req);
      return;
    }
    if (u == "/api/stop") {
      if (remaining != nullptr) *remaining = 0;
      if (relay != nullptr) relay->turn_off();
      send_status(req);
      return;
    }
    if (u == "/api/config") {
      apply_num(time1, qparam(req, "time1", -1));
      apply_num(time2, qparam(req, "time2", -1));
      apply_num(time3, qparam(req, "time3", -1));
      send_status(req);
      return;
    }
    if (u == "/api/status") {
      send_status(req);
      return;
    }
    if (u == "/api/net") {                       // Netzwerk-Konfig lesen/speichern
      bool changed = false;
      if (req->hasParam("static")) { g_netcfg.use_static = qparam(req, "static", 0) ? 1 : 0; changed = true; }
      if (req->hasParam("ip"))  { copy_param(req, "ip",  g_netcfg.ip,  sizeof(g_netcfg.ip));  changed = true; }
      if (req->hasParam("gw"))  { copy_param(req, "gw",  g_netcfg.gw,  sizeof(g_netcfg.gw));  changed = true; }
      if (req->hasParam("sn"))  { copy_param(req, "sn",  g_netcfg.sn,  sizeof(g_netcfg.sn));  changed = true; }
      if (req->hasParam("dns")) { copy_param(req, "dns", g_netcfg.dns, sizeof(g_netcfg.dns)); changed = true; }
      if (req->hasParam("ntp")) { copy_param(req, "ntp", g_netcfg.ntp, sizeof(g_netcfg.ntp)); changed = true; }
      if (req->hasParam("host")) {
        copy_param(req, "host", g_netcfg.host, sizeof(g_netcfg.host));
        netcfg_sanitize_host(g_netcfg.host);
        changed = true;
      }
      bool roam_changed = false;
      if (req->hasParam("roaming")) {
        g_netcfg.roaming = qparam(req, "roaming", 0) ? 1 : 0;
        changed = true;
        roam_changed = true;
      }
      if (req->hasParam("lang")) {
        copy_param(req, "lang", g_netcfg.lang, sizeof(g_netcfg.lang));
        netcfg_sanitize_lang();
        changed = true;
      }
      if (changed) { netcfg_save(); netcfg_apply_ntp(); netcfg_apply_hostname(); }
      if (roam_changed) netcfg_apply_roaming();  // wirkt voll ab naechstem (Re)Connect
      send_net(req);
      return;
    }
    if (u == "/api/wifi") {                       // WLAN-Zugangsdaten setzen (nativ)
      if (req->hasParam("ssid")) {
        std::string s = req->getParam("ssid")->value();
        std::string p = req->hasParam("pw") ? req->getParam("pw")->value() : std::string();
        if (!s.empty()) wifi::global_wifi_component->save_wifi_sta(s, p);
      }
      req->send(200, "application/json", "{\"ok\":true}");
      return;
    }
    if (u == "/api/reboot") {                     // Neustart (verzoegert ueber Interval)
      g_reboot_pending = true;
      req->send(200, "application/json", "{\"ok\":true}");
      return;
    }
    if (u == "/api/reconnect") {                  // WLAN neu verbinden (verzoegert)
      g_reconnect_pending = true;                 // uebernimmt u.a. geaendertes Roaming
      req->send(200, "application/json", "{\"ok\":true}");
      return;
    }
    if (u == "/api/log") {                         // Log-Ringpuffer gefiltert lesen
      uint8_t sel = (uint8_t) qparam(req, "level", 3);      // Default INFO
      uint32_t since = (uint32_t) qparam(req, "since", 0);
      std::string j = log_ring_json(sel, since);
      req->send(200, "application/json", j.c_str());
      return;
    }
    req->send(404, "application/json", "{\"ok\":false,\"error\":\"not found\"}");
  }
};

}  // namespace esphome

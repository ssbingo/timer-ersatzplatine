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
#include <esp_system.h>
#include <esp_wifi.h>
#include "net_config.h"
#include "log_ring.h"
#include "esphome/components/wifi/wifi_component.h"

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
input{width:100%;font:inherit;color:var(--fg);background:#0d1424;border:1px solid #2b3855;
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
   <button onclick="trig(1)"><span class=tb><b>Taster 1</b><span id=t1s>&ndash;</span></span></button>
   <button onclick="trig(2)"><span class=tb><b>Taster 2</b><span id=t2s>&ndash;</span></span></button>
   <button onclick="trig(3)"><span class=tb><b>Taster 3</b><span id=t3s>&ndash;</span></span></button>
  </div>
  <button class=stop onclick="stop()">Stopp</button>
 </section>

 <section id=p_cfg class=hide>
  <div class=card>
   <label>Zeit Taster 1 (Sekunden)</label><input id=c1 type=number min=1 max=600 inputmode=numeric>
   <label>Zeit Taster 2 (Sekunden)</label><input id=c2 type=number min=1 max=600 inputmode=numeric>
   <label>Zeit Taster 3 (Sekunden)</label><input id=c3 type=number min=1 max=600 inputmode=numeric>
   <button style="width:100%;margin-top:16px" onclick="save()">Speichern</button>
  </div>
 </section>

 <section id=p_net class=hide>
  <div class=card>
   <b>WLAN</b>
   <div class=row><span class=k>Aktuell verbunden</span><span class=v id=cur_ssid>&ndash;</span></div>
   <label>Auf anderes WLAN wechseln &ndash; Netzwerkname (SSID)</label><input id=w_ssid autocomplete=off>
   <label>Passwort</label><input id=w_pw type=password autocomplete=off>
   <button style="width:100%;margin-top:12px" onclick="saveWifi()">WLAN speichern &amp; verbinden</button>
  </div>
  <div class=card>
   <b>IP-Konfiguration</b>
   <label>Modus</label>
   <select id=n_static onchange="ipmode()">
    <option value=0>DHCP (automatisch)</option>
    <option value=1>Statisch</option>
   </select>
   <div id=ipfields>
    <label>IP-Adresse</label><input id=n_ip inputmode=decimal>
    <label>Gateway</label><input id=n_gw inputmode=decimal>
    <label>Subnetzmaske</label><input id=n_sn inputmode=decimal>
    <label>DNS-Server</label><input id=n_dns inputmode=decimal>
   </div>
   <button style="width:100%;margin-top:12px" onclick="saveNet()">IP-Konfig speichern</button>
  </div>
  <div class=card>
   <b>NTP-Zeitserver</b>
   <label>Server</label><input id=n_ntp autocomplete=off>
   <button style="width:100%;margin-top:12px" onclick="saveNtp()">NTP speichern</button>
  </div>
  <div class=card>
   <b>Hostname</b>
   <label>Gerätename (a–z, 0–9, „-")</label><input id=n_host autocomplete=off>
   <button style="width:100%;margin-top:12px" onclick="saveHost()">Hostname speichern</button>
   <span class=note>Der mDNS-Name (…&#8203;.local) wird sofort umgestellt; der
   DHCP-Name (Router) und eine statische IP nach einem Neustart.</span>
   <button class=stop style="background:#b45309;margin-top:10px" onclick="reboot()">Neustart</button>
  </div>
  <div class=card>
   <b>WLAN-Roaming (802.11k/v)</b>
   <label style="display:flex;align-items:center;gap:8px;margin-top:8px">
    <input type=checkbox id=n_roam onchange="saveRoam()"> BTM/RRM aktivieren</label>
   <span class=note>Nur bei mehreren Access-Points mit gleicher SSID sinnvoll
   (z.&#8203;B. UniFi/Mesh): Der Router kann das Gerät gezielt auf den stärkeren
   AP umbuchen (802.11v BTM) und nutzt Nachbar-Listen (802.11k RRM). Aus =
   klassisches ESPHome-Scan-Roaming. Wirkt voll ab dem nächsten Verbinden/Neustart.</span>
  </div>
 </section>

 <section id=p_stat class=hide><div class=card id=statbox></div></section>

 <section id=p_svc class=hide>
  <div class=card>
   <b>Log / Debug</b>
   <label>Anzeige-Stufe</label>
   <select id=lg_lvl onchange="logLevelChange()">
    <option value=1>ERROR</option>
    <option value=2>WARN</option>
    <option value=3 selected>INFO</option>
    <option value=5>DEBUG</option>
   </select>
   <label style="display:flex;align-items:center;gap:8px;margin-top:12px">
    <input type=checkbox id=lg_on onchange="logToggle()"> Live-Anzeige aktivieren</label>
   <pre id=lg_out style="margin:10px 0;max-height:240px;overflow:auto;background:#0d1424;border:1px solid #2b3855;border-radius:10px;padding:8px;font:11px/1.35 ui-monospace,monospace;white-space:pre-wrap;word-break:break-all"></pre>
   <button class=sec style="width:100%;background:#26304a" onclick="logClear()">Anzeige leeren</button>
  </div>
  <div class=card>
   <b>Firmware-Update (OTA)</b>
   <span class=note>Kompilierte .bin hochladen (bei ESPHome die firmware.bin aus dem Build).
   Das Gerät startet danach neu. Alternativ per Netzwerk: <b>esphome run</b> (Port 3232).</span>
   <input type=file id=ota_file accept=".bin,application/octet-stream" style="margin-top:10px">
   <button style="width:100%;margin-top:10px" onclick="otaUpload()">Hochladen &amp; aktualisieren</button>
   <div id=ota_stat class=note></div>
  </div>
  <div class=card>
   <b>Gerät</b>
   <button class=stop style="background:#b45309;margin-top:4px" onclick="reboot()">Neustart</button>
  </div>
 </section>
</div>

<nav>
 <a href="#" class=act data-p=start onclick="nav('start');return false">Start</a>
 <a href="#" data-p=cfg  onclick="nav('cfg');return false">Zeiten</a>
 <a href="#" data-p=net  onclick="nav('net');return false">Netzwerk</a>
 <a href="#" data-p=stat onclick="nav('stat');return false">Status</a>
 <a href="#" data-p=svc  onclick="nav('svc');return false">Service</a>
</nav>
<div class=toast id=toast></div>

<script>
var $=function(i){return document.getElementById(i)};
function nav(p){['start','cfg','net','stat','svc'].forEach(function(x){$('p_'+x).classList.toggle('hide',x!=p)});
 var a=document.querySelectorAll('nav a');for(var i=0;i<a.length;i++)a[i].classList.toggle('act',a[i].dataset.p==p);
 if(p=='net')loadNet();}
function loadNet(){api('/api/net').then(function(n){if(!n)return;
 $('n_static').value=n.static;$('n_ip').value=n.ip;$('n_gw').value=n.gw;$('n_sn').value=n.sn;
 $('n_dns').value=n.dns;$('n_ntp').value=n.ntp;$('n_host').value=n.hostname;$('n_roam').checked=!!n.roaming;ipmode();});}
function ipmode(){$('ipfields').style.display=($('n_static').value=='1')?'block':'none';}
function saveWifi(){api('/api/wifi?ssid='+encodeURIComponent($('w_ssid').value)+'&pw='+encodeURIComponent($('w_pw').value),'POST')
 .then(function(r){toast(r&&r.ok?'WLAN gespeichert':'Fehler');});}
function saveNet(){var q='static='+$('n_static').value+'&ip='+encodeURIComponent($('n_ip').value)
 +'&gw='+encodeURIComponent($('n_gw').value)+'&sn='+encodeURIComponent($('n_sn').value)+'&dns='+encodeURIComponent($('n_dns').value);
 api('/api/net?'+q,'POST').then(function(r){toast(($('n_static').value=='1')?'Gespeichert - Neustart nötig':'Gespeichert');});}
function saveNtp(){api('/api/net?ntp='+encodeURIComponent($('n_ntp').value),'POST').then(function(r){toast(r&&r.ok?'NTP gespeichert':'Fehler');});}
function saveHost(){api('/api/net?host='+encodeURIComponent($('n_host').value),'POST').then(function(r){toast('Hostname gespeichert');if(r&&r.hostname)$('n_host').value=r.hostname;});}
function saveRoam(){api('/api/net?roaming='+($('n_roam').checked?1:0),'POST').then(function(r){toast($('n_roam').checked?'Roaming aktiviert':'Roaming aus');});}
function reboot(){if(confirm('Gerät jetzt neu starten?'))api('/api/reboot','POST').then(function(){toast('Neustart …');});}
var lgTimer=null,lgSeq=0,LVL={1:'E',2:'W',3:'I',4:'C',5:'D',6:'V'};
function logToggle(){if($('lg_on').checked){lgSeq=0;$('lg_out').textContent='';logPoll();lgTimer=setInterval(logPoll,1500);}
 else{if(lgTimer)clearInterval(lgTimer);lgTimer=null;}}
function logLevelChange(){if($('lg_on').checked){lgSeq=0;$('lg_out').textContent='';logPoll();}}
function logPoll(){api('/api/log?level='+$('lg_lvl').value+'&since='+lgSeq).then(function(d){if(!d||!d.lines)return;
 var o=$('lg_out');d.lines.forEach(function(x){if(x.s>lgSeq)lgSeq=x.s;o.textContent+='['+(LVL[x.l]||x.l)+'] '+x.t+'\n';});
 if(d.lines.length)o.scrollTop=o.scrollHeight;});}
function logClear(){$('lg_out').textContent='';}
function otaUpload(){var f=$('ota_file').files[0];if(!f){toast('Keine Datei gewählt');return;}
 $('ota_stat').textContent='Lade hoch … Gerät nicht trennen.';
 var fd=new FormData();fd.append('file',f,f.name);
 fetch('/update',{method:'POST',body:fd}).then(function(r){return r.text();})
  .then(function(){$('ota_stat').textContent='Übertragen – Gerät startet neu.';})
  .catch(function(){$('ota_stat').textContent='Verbindung getrennt (vermutlich Neustart nach Update).';});}
function toast(m){var t=$('toast');t.textContent=m;t.classList.add('show');setTimeout(function(){t.classList.remove('show')},1600);}
function api(u,m){return fetch(u,{method:m||'GET'}).then(function(r){return r.json()}).catch(function(){return null});}
function trig(n){api('/api/trigger?button='+n,'POST').then(refresh);}
function stop(){api('/api/stop','POST').then(refresh);}
function save(){var q='time1='+$('c1').value+'&time2='+$('c2').value+'&time3='+$('c3').value;
 api('/api/config?'+q,'POST').then(function(r){toast(r&&r.ok?'Gespeichert':'Fehler');refresh();});}
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
 var cs=$('cur_ssid');if(cs)cs.textContent=(s.wifi=='verbunden'&&s.ssid)?s.ssid:'nicht verbunden';
 var dc=s.active?'#f59e0b':(s.fault?'#ef4444':'#22c55e');
 $('dot').style.background=dc;$('dot').style.boxShadow='0 0 8px '+dc;
 if(s.host){$('hdr').textContent=s.host;if(document.title!=s.host)document.title=s.host;}
 $('stBig').textContent=s.active?s.remaining+' s':(s.relay?'AN':'AUS');
 $('stSub').textContent=s.active?('läuft – Taster '+(s.last||'?')):'bereit';
 $('t1s').textContent=s.times[0]+' s';$('t2s').textContent=s.times[1]+' s';$('t3s').textContent=s.times[2]+' s';
 if(document.activeElement.tagName!='INPUT'){$('c1').value=s.times[0];$('c2').value=s.times[1];$('c3').value=s.times[2];}
 rows('statbox',[['Firmware',s.fw],['Laufzeit',up(s.uptime)],['Freier Speicher',(s.heap/1024).toFixed(1)+' kB'],
  ['WLAN',s.wifi],['SSID',s.ssid||'&ndash;'],
  ['Kanal / Signal',s.chan?('Kanal '+s.chan+bars(s.rssi)+s.rssi+' dBm'):'&ndash;'],
  ['Hostname',s.host||'&ndash;'],
  ['IP-Adresse',s.ip||'&ndash;'],['MAC',s.mac],['Setup-AP',s.ap],['Reset-Grund',s.reset],
  ['Relais',s.relay?'AN':'AUS'],['Restzeit',s.remaining+' s']]);
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
    const std::string u = req->url();
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
    char buf[440];
    snprintf(buf, sizeof(buf),
      "{\"ok\":true,\"static\":%d,\"ip\":\"%s\",\"gw\":\"%s\",\"sn\":\"%s\","
      "\"dns\":\"%s\",\"ntp\":\"%s\",\"hostname\":\"%s\",\"roaming\":%d}",
      g_netcfg.use_static, g_netcfg.ip, g_netcfg.gw, g_netcfg.sn,
      g_netcfg.dns, g_netcfg.ntp, g_netcfg.host, g_netcfg.roaming);
    req->send(200, "application/json", buf);
  }

  void apply_num(number::Number *n, int v) {
    if (n != nullptr && v >= 1 && v <= 600) n->make_call().set_value((float) v).perform();
  }

  const char *reset_reason() {
    switch (esp_reset_reason()) {
      case ESP_RST_POWERON:  return "Power-On";
      case ESP_RST_SW:       return "Software";
      case ESP_RST_PANIC:    return "Panik";
      case ESP_RST_INT_WDT:
      case ESP_RST_TASK_WDT:
      case ESP_RST_WDT:      return "Watchdog";
      case ESP_RST_BROWNOUT: return "Unterspannung";
      case ESP_RST_DEEPSLEEP:return "Deep-Sleep";
      default:               return "unbekannt";
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
    char buf[820];
    snprintf(buf, sizeof(buf),
      "{\"ok\":true,\"active\":%s,\"remaining\":%d,\"relay\":%s,\"last\":%d,\"fault\":%s,"
      "\"times\":[%d,%d,%d],\"host\":\"%s\",\"ip\":\"%s\",\"ssid\":\"%s\","
      "\"rssi\":%d,\"chan\":%d,\"mac\":\"%s\",\"ap\":\"%s\",\"fw\":\"%s\",\"uptime\":%lu,"
      "\"heap\":%u,\"wifi\":\"%s\",\"reset\":\"%s\"}",
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
      connected ? "verbunden" : "getrennt",
      reset_reason());
    req->send(200, "application/json", buf);
  }

  void handleRequest(AsyncWebServerRequest *req) override {
    const std::string u = req->url();
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

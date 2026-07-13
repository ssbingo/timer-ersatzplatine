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

namespace esphome {

static const char TIMER_INDEX_HTML[] PROGMEM = R"HTMLPAGE(<!doctype html>
<html lang=de><head><meta charset=utf-8>
<meta name=viewport content="width=device-width,initial-scale=1,viewport-fit=cover">
<title>Timer-Relais</title>
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
 <h1><span class=dot id=dot></span>Timer-Relais</h1>

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
  <div class=card id=netbox></div>
  <span class=note>WLAN-Zugangsdaten werden über das Setup-AP &bdquo;Timer-Relais Setup&ldquo;
  (Captive-Portal) gesetzt. Hostname und feste IP sind derzeit in der Firmware
  festgelegt &ndash; Änderung per Neu-Flashen.</span>
 </section>

 <section id=p_stat class=hide><div class=card id=statbox></div></section>
</div>

<nav>
 <a href="#" class=act data-p=start onclick="nav('start');return false">Bedienung</a>
 <a href="#" data-p=cfg  onclick="nav('cfg');return false">Einstellungen</a>
 <a href="#" data-p=net  onclick="nav('net');return false">Netzwerk</a>
 <a href="#" data-p=stat onclick="nav('stat');return false">Status</a>
</nav>
<div class=toast id=toast></div>

<script>
var $=function(i){return document.getElementById(i)};
function nav(p){['start','cfg','net','stat'].forEach(function(x){$('p_'+x).classList.toggle('hide',x!=p)});
 var a=document.querySelectorAll('nav a');for(var i=0;i<a.length;i++)a[i].classList.toggle('act',a[i].dataset.p==p);}
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
function refresh(){return api('/api/status').then(function(s){if(!s)return;
 $('dot').classList.toggle('on',s.relay);
 $('stBig').textContent=s.active?s.remaining+' s':(s.relay?'AN':'AUS');
 $('stSub').textContent=s.active?('läuft – Taster '+(s.last||'?')):'bereit';
 $('t1s').textContent=s.times[0]+' s';$('t2s').textContent=s.times[1]+' s';$('t3s').textContent=s.times[2]+' s';
 if(document.activeElement.tagName!='INPUT'){$('c1').value=s.times[0];$('c2').value=s.times[1];$('c3').value=s.times[2];}
 rows('netbox',[['Hostname',s.host],['IP-Adresse',s.ip],['WLAN (SSID)',s.ssid||'&ndash;'],
  ['Signal',s.rssi+' dBm'],['MAC',s.mac],['Setup-AP',s.ap]]);
 rows('statbox',[['Firmware',s.fw],['Laufzeit',up(s.uptime)],['Freier Speicher',(s.heap/1024).toFixed(1)+' kB'],
  ['WLAN',s.wifi],['Reset-Grund',s.reset],['Relais',s.relay?'AN':'AUS'],['Restzeit',s.remaining+' s']]);
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

  bool canHandle(AsyncWebServerRequest *req) const override {
    const std::string u = req->url();
    return u == "/" || u.rfind("/api/", 0) == 0;
  }
  bool isRequestHandlerTrivial() const override { return false; }

  int qparam(AsyncWebServerRequest *req, const char *name, int def) {
    if (req->hasParam(name)) return atoi(req->getParam(name)->value().c_str());
    return def;
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
    char buf[760];
    snprintf(buf, sizeof(buf),
      "{\"ok\":true,\"active\":%s,\"remaining\":%d,\"relay\":%s,\"last\":%d,"
      "\"times\":[%d,%d,%d],\"host\":\"%s\",\"ip\":\"%s\",\"ssid\":\"%s\","
      "\"rssi\":%d,\"mac\":\"%s\",\"ap\":\"%s\",\"fw\":\"%s\",\"uptime\":%lu,"
      "\"heap\":%u,\"wifi\":\"%s\",\"reset\":\"%s\"}",
      (rem > 0) ? "true" : "false", rem, on ? "true" : "false", last_button,
      time1 ? (int) time1->state : 0, time2 ? (int) time2->state : 0, time3 ? (int) time3->state : 0,
      App.get_name().c_str(),
      ip_s.c_str(),
      ssid_s.c_str(),
      (rssi != nullptr) ? (int) rssi->state : 0,
      mac_s.c_str(),
      "Timer-Relais Setup",
      App.get_compilation_time().c_str(),
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
    req->send(404, "application/json", "{\"ok\":false,\"error\":\"not found\"}");
  }
};

}  // namespace esphome

// AUTO-GENERIERT von mk_help.py aus help_{de,en,fr}.html.
// NICHT von Hand editieren - stattdessen die .html anpassen und neu erzeugen.
#pragma once

static const char HELP_DE[] PROGMEM = R"HELP(
<!doctype html><html lang=de><head><meta charset=utf-8>
<meta name=viewport content="width=device-width,initial-scale=1,viewport-fit=cover">
<title>Feeder-Relais — Handbuch</title>
<style>
:root{--bg:#0f1420;--card:#1a2232;--line:#232d42;--mut:#8595ad;--fg:#eef2f8;--acc:#3b82f6;--ok:#22c55e;--warn:#f59e0b;--bad:#ef4444}
*{box-sizing:border-box}
body{margin:0;font:15px/1.55 system-ui,-apple-system,sans-serif;background:var(--bg);color:var(--fg)}
.wrap{max-width:760px;margin:0 auto;padding:14px 16px 60px}
.top{display:flex;align-items:center;gap:10px;flex-wrap:wrap;position:sticky;top:0;background:var(--bg);padding:8px 0;border-bottom:1px solid var(--line);z-index:5}
.top a{color:var(--acc);text-decoration:none;font-size:14px}
.top .sp{flex:1}
.lang a{color:var(--mut);padding:2px 6px;border-radius:6px}
.lang a.on{color:var(--fg);background:var(--card)}
h1{font-size:22px;margin:14px 0 4px}
h2{font-size:18px;margin:26px 0 8px;padding-top:6px;border-top:1px solid var(--line);color:#cfe0ff}
h3{font-size:15px;margin:16px 0 4px}
p,li{margin:7px 0}
code{background:#0d1424;border:1px solid #2b3855;border-radius:6px;padding:1px 6px;font-family:ui-monospace,monospace;font-size:.92em}
ol,ul{padding-left:22px}
a{color:var(--acc)}
.lead{color:var(--mut)}
.toc{background:var(--card);border-radius:12px;padding:12px 16px;margin:14px 0}
.toc ol{margin:4px 0;padding-left:20px}
.toc a{text-decoration:none}
.box{border-radius:10px;padding:10px 14px;margin:12px 0;border-left:4px solid}
.box b{display:block;margin-bottom:2px}
.hint{background:#0e2536;border-color:var(--acc)}
.tip{background:#0e2a1c;border-color:var(--ok)}
.warn{background:#2a2410;border-color:var(--warn)}
.dang{background:#2a1414;border-color:var(--bad)}
table{border-collapse:collapse;width:100%;margin:10px 0;font-size:14px}
th,td{border-bottom:1px solid var(--line);padding:7px 8px;text-align:left;vertical-align:top}
th{color:#cfe0ff}
figure{margin:12px 0;text-align:center}
svg{max-width:100%;height:auto}
.led{display:inline-block;width:11px;height:11px;border-radius:50%;vertical-align:middle;margin-right:6px}
.totop{font-size:13px;color:var(--mut);text-decoration:none}
kbd{background:#0d1424;border:1px solid #2b3855;border-radius:5px;padding:0 5px;font-family:ui-monospace,monospace;font-size:.9em}
</style></head><body>
<div class=wrap>

<div class=top>
 <a href="/">&larr; Zur App</a><span class=sp></span>
 <span class=lang><a class=on href="/help?lang=de">DE</a> <a href="/help?lang=en">EN</a> <a href="/help?lang=fr">FR</a></span>
</div>

<h1 id=oben>Feeder-Relais — Handbuch</h1>
<p class=lead>Installation, Einrichtung, Bedienung und Anbindung an ioBroker. Diese Seite liegt <b>im Gerät</b> und ist auch ohne Internet lesbar.</p>

<div class=toc>
<b>Inhalt</b>
<ol>
<li><a href="#was">Was das Gerät tut</a></li>
<li><a href="#flash">Firmware aufspielen (Erstflash)</a></li>
<li><a href="#wlan">WLAN einrichten</a></li>
<li><a href="#geraet">Bedienung am Gerät</a></li>
<li><a href="#webapp">Bedienung per Web-App</a></li>
<li><a href="#netz">Netzwerk, Zeit, Sprache, Updates</a></li>
<li><a href="#iobroker">Anbindung an ioBroker</a></li>
<li><a href="#fehler">Fehlersuche</a></li>
<li><a href="#sicher">Sicherheit &amp; ausführliches Handbuch</a></li>
</ol>
</div>

<h2 id=was>1. Was das Gerät tut</h2>
<p>Das Feeder-Relais schaltet eine 230-V-Last (z. B. einen Futterautomaten) auf Tastendruck für eine <b>einstellbare Zeit</b> ein und danach von allein wieder aus. Drei Taster lösen drei getrennt einstellbare Zeiten aus. Das eigentliche Schalten übernimmt ein <b>externer Shelly 1PM Mini Gen4</b>, den die Platine über ein PhotoMOS galvanisch getrennt ansteuert — die Kernfunktion läuft dadurch <b>ohne WLAN</b>.</p>
<figure><svg viewBox="0 0 620 60" role=img aria-label="Signalkette">
<style>.b{fill:#1a2232;stroke:#3b82f6}.t{fill:#eef2f8;font:12px sans-serif;text-anchor:middle}.a{stroke:#8595ad;stroke-width:2;marker-end:url(#ah)}</style>
<defs><marker id=ah markerWidth=8 markerHeight=8 refX=7 refY=3 orient=auto><path d="M0,0 L7,3 L0,6 z" fill="#8595ad"/></marker></defs>
<g>
<rect class=b x=4 y=16 width=86 height=28 rx=6/><text class=t x=47 y=34>Taste</text>
<line class=a x1=92 y1=30 x2=118 y2=30/>
<rect class=b x=120 y=16 width=96 height=28 rx=6/><text class=t x=168 y=34>ESP32-C3</text>
<line class=a x1=218 y1=30 x2=244 y2=30/>
<rect class=b x=246 y=16 width=96 height=28 rx=6/><text class=t x=294 y=34>PhotoMOS</text>
<line class=a x1=344 y1=30 x2=370 y2=30/>
<rect class=b x=372 y=16 width=110 height=28 rx=6/><text class=t x=427 y=34>Shelly 1PM</text>
<line class=a x1=484 y1=30 x2=510 y2=30/>
<rect class=b x=512 y=16 width=100 height=28 rx=6/><text class=t x=562 y=34>230-V-Last</text>
</g></svg><figcaption class=lead>Die Signalkette: Der ESP zählt die Zeit, der Shelly schaltet.</figcaption></figure>

<h2 id=flash>2. Firmware aufspielen (Erstflash)</h2>
<p>Beim ersten Mal wird der ESP über <b>USB und den Browser</b> beschrieben — ganz ohne Netzspannung. Am besten <b>bevor</b> er eingelötet ist.</p>
<div class=warn><b>⚠ Voraussetzungen</b>Ein <b>USB-C-Datenkabel</b> (kein reines Ladekabel!) und <b>Google Chrome</b> oder <b>Microsoft Edge</b> (Firefox/Safari können kein Web-Serial).</div>
<ol>
<li>Datei laden: <b>feeder-relais-vX.Y.Z.factory.bin</b> von der <a href="https://github.com/ssbingo/timer-ersatzplatine/releases/latest">Release-Seite</a> (Abschnitt „Assets"). Die <code>factory</code>-Datei ist das Komplett-Image für den Erstflash; die <code>ota</code>-Datei ist nur für spätere Updates.</li>
<li>ESP per USB-C anstecken. In <b>Chrome/Edge</b> das Flash-Tool öffnen: <code>https://espressif.github.io/esptool-js/</code></li>
<li><b>Connect</b> klicken, den ESP-Port wählen. Erfolg: „Connected to device: ESP32-C3".</li>
<li><b>Flash Address auf <code>0x0000</code> setzen</b> (der Vorgabewert <code>0x1000</code> ist falsch!). Als Datei die <code>factory.bin</code> wählen. Flash Mode/Frequency/Size auf <code>keep</code> lassen.</li>
<li><b>Program</b> klicken und warten, bis „Writing … (100 %)" und „Hard resetting…" erscheint.</li>
</ol>
<div class=hint><b>ℹ Warum 0x0000?</b><code>0</code>, <code>0x0</code> und <code>0x0000</code> sind dieselbe Stelle — der Anfang des Speichers. Das <code>factory</code>-Image ist komplett (Bootloader + Programm) und muss ganz vorne beginnen. Der Vorgabewert <code>0x1000</code> würde alles verschieben → der ESP startet nicht.</div>
<div class=warn><b>⚠ Kein Port / „Failed to connect"?</b>Den ESP in den Download-Modus bringen: <kbd>BOOT</kbd> gedrückt halten, kurz <kbd>RESET</kbd> drücken, <kbd>BOOT</kbd> loslassen — dann erneut „Connect". Bei anhaltenden Problemen erst <b>Erase Flash</b>, dann neu flashen.</div>
<div class=tip><b>✓ Stromtipp</b>Direkt nach dem Flashen zieht der Funk kurze Stromspitzen. An einem schwachen USB-Port kann der ESP dadurch neu starten. Nutze ein <b>kräftiges 5-V-Netzteil</b> oder einen Port direkt am PC mit kurzem, dickem Kabel.</div>

<h2 id=wlan>3. WLAN einrichten</h2>
<p>Nach dem ersten Start öffnet der ESP ein eigenes WLAN für die Einrichtung:</p>
<ol>
<li>Am Handy mit dem WLAN <b>Feeder-Relais Setup</b> verbinden (Passwort <code>feeder1234</code>).</li>
<li>Es öffnet sich eine Anmeldeseite (sonst <code>http://192.168.4.1</code> aufrufen).</li>
<li>Dein <b>Heim-WLAN wählen</b>, Passwort eingeben, speichern.</li>
</ol>
<p>Danach ist das Gerät im Heimnetz erreichbar unter <code>http://feeder-relais.local</code>.</p>
<div class=hint><b>ℹ Es kann kurz dauern</b>Der erste Verbindungsaufbau braucht manchmal ein paar Sekunden — das ist normal.</div>

<h2 id=geraet>4. Bedienung am Gerät</h2>
<table>
<tr><th>Taste</th><th>kurz</th><th>lang</th></tr>
<tr><td><b>S1</b> Down/Manual</td><td>Timer 1 auslösen</td><td>—</td></tr>
<tr><td><b>S2</b> SET</td><td>Timer 2 auslösen</td><td>≥ 3 s: Info-Menü (mit S1/S3 blättern)</td></tr>
<tr><td><b>S3</b> UP</td><td>Timer 3 auslösen</td><td>≥ 1,2 s: alle Timer stoppen</td></tr>
</table>
<p>Das <b>OLED</b> zeigt oben WLAN-Empfang, die große Uhr bzw. den Countdown und den Status (<b>Ruhe</b> / <b>Futter</b>); unten Datum und freien Speicher. Wochentag, Status und Menütitel folgen der eingestellten Sprache.</p>
<p><b>Status-Ampel</b> (kleine LED am ESP):</p>
<p><span class=led style="background:#22c55e"></span> grün = bereit &nbsp;·&nbsp; <span class=led style="background:#f59e0b"></span> gelb = Timer läuft &nbsp;·&nbsp; <span class=led style="background:#ef4444"></span> rot = Störung</p>

<h2 id=webapp>5. Bedienung per Web-App</h2>
<p>Im Browser <code>http://feeder-relais.local</code> öffnen. Unten wechselst du zwischen den Bereichen:</p>
<table>
<tr><th>Bereich</th><th>Funktion</th></tr>
<tr><td><b>Start</b></td><td>Status, Timer 1/2/3 auslösen, Stopp</td></tr>
<tr><td><b>Zeiten</b></td><td>die drei Schaltzeiten (1–600 s) einstellen und speichern</td></tr>
<tr><td><b>Netzwerk</b></td><td>WLAN wechseln, IP (DHCP/statisch), NTP-Zeitserver, Hostname, Roaming</td></tr>
<tr><td><b>Status</b></td><td>Version, Laufzeit, WLAN, IP, MAC, Reset-Grund, Relais</td></tr>
<tr><td><b>Service</b></td><td>Log/Debug, Firmware-Update (OTA), Neustart</td></tr>
</table>
<p>Die <b>Sprache</b> (Deutsch/English/Français) stellst du oben im Bereich „Zeiten" um — sie gilt für Web-App und OLED.</p>

<h2 id=netz>6. Netzwerk, Zeit, Sprache, Updates</h2>
<ul>
<li><b>Zeit:</b> Die Uhr wird per Internet-Zeitserver (NTP) gestellt; den Server änderst du im Bereich „Netzwerk".</li>
<li><b>IP:</b> Standard ist DHCP (automatisch). Eine feste IP wird nach einem Neustart aktiv.</li>
<li><b>Updates (OTA):</b> Neue Firmware ohne Kabel — Bereich <b>Service → Firmware-Update</b>, dort die <b>ota.bin</b> der neuen Version hochladen. Das Gerät startet danach neu.</li>
</ul>

<h2 id=iobroker>7. Anbindung an ioBroker</h2>
<p>Das Gerät ist die Hardware-Seite eines Futterautomaten und fügt sich gut in ioBroker ein:</p>
<ul>
<li><b>Shelly-Adapter:</b> Der externe Shelly 1PM Mini Gen4 wird über den ioBroker-Shelly-Adapter nativ eingebunden — Schaltzustand und Leistungsmessung sind dort direkt sichtbar und steuerbar.</li>
<li><b>JSON-API des Geräts:</b> per REST/Skript abfragbar und bedienbar:
<table>
<tr><th>Endpunkt</th><th>Zweck</th></tr>
<tr><td><code>GET /api/status</code></td><td>Status (Version, Relais, Restzeit, WLAN …)</td></tr>
<tr><td><code>POST /api/trigger?ch=1|2|3</code></td><td>Timer auslösen</td></tr>
<tr><td><code>POST /api/stop</code></td><td>alle Timer stoppen</td></tr>
<tr><td><code>POST /api/config?...</code></td><td>Zeiten setzen</td></tr>
</table></li>
</ul>
<p>Für Zeitplanung und ein fertiges Dashboard gibt es die passenden Adapter desselben Autors:</p>
<ul>
<li><a href="https://github.com/ssbingo/ioBroker.automatic-feeder">ioBroker.automatic-feeder</a> — Zeitplanung, Temperaturmodell, Sonnenauf-/-untergang, Pausen, Benachrichtigungen.</li>
<li><a href="https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder">ioBroker.vis-2-widgets-automatic-feeder</a> — fertige vis-2-Dashboard-Widgets (Anzeige + Fernbedienung).</li>
</ul>

<h2 id=fehler>8. Fehlersuche</h2>
<table>
<tr><th>Problem</th><th>Lösung</th></tr>
<tr><td>Beim Flashen <b>flappt der USB-Port</b> (verbindet/trennt ständig)</td><td>Die Firmware startet in einer Schleife → der USB meldet sich ständig neu an. In den Download-Modus zwingen: <kbd>BOOT</kbd> halten, <kbd>RESET</kbd> tippen, <kbd>BOOT</kbd> los. Dann „Connect", „Erase Flash", neu flashen.</td></tr>
<tr><td><b>Kein WLAN</b> „Feeder-Relais Setup" sichtbar</td><td>Meist zu wenig Strom → Neustart-Schleife. An ein <b>kräftiges 5-V-Netzteil</b> anschließen, ~15 s warten, am Handy erneut suchen (2,4 GHz). Prüfen, dass die <b>factory.bin</b> an <code>0x0000</code> geflasht wurde.</td></tr>
<tr><td><b>OLED bleibt schwarz</b></td><td>Display richtig aufgesteckt? Kontakte prüfen. (Beim Nachbau: SDA muss an ESP-Pad 7 liegen, siehe ausführliches Handbuch.)</td></tr>
<tr><td><b>Gerät nicht erreichbar</b></td><td>Im Router die IP suchen oder per IP statt <code>feeder-relais.local</code> zugreifen. Notfalls über <b>Service</b> neu starten.</td></tr>
</table>

<h2 id=sicher>9. Sicherheit &amp; ausführliches Handbuch</h2>
<div class=dang><b>✋ 230 Volt — Lebensgefahr</b>Aufbau und Anschluss der Netzspannung gehören in die Hände einer Elektrofachkraft. Arbeite nie am offenen, unter Spannung stehenden Gerät.</div>
<p>Die <b>vollständige Nachbau-Anleitung</b> (Bauteile, Platine, Löten, KiCad, Gehäusedruck) findest du online:</p>
<p><a href="https://ssbingo.github.io/timer-ersatzplatine/">ssbingo.github.io/timer-ersatzplatine</a> · <a href="https://github.com/ssbingo/timer-ersatzplatine">Projekt auf GitHub</a></p>

<p style="margin-top:26px"><a class=totop href="#oben">↑ nach oben</a> &nbsp;·&nbsp; <a class=totop href="/">← zur App</a></p>
<p class=lead style="font-size:12px">© 2026 S. Sternitzke · CC BY-NC-SA 4.0</p>

</div></body></html>
)HELP";

static const char HELP_EN[] PROGMEM = R"HELP(
<!doctype html><html lang=en><head><meta charset=utf-8>
<meta name=viewport content="width=device-width,initial-scale=1,viewport-fit=cover">
<title>Feeder-Relais — Manual</title>
<style>
:root{--bg:#0f1420;--card:#1a2232;--line:#232d42;--mut:#8595ad;--fg:#eef2f8;--acc:#3b82f6;--ok:#22c55e;--warn:#f59e0b;--bad:#ef4444}
*{box-sizing:border-box}
body{margin:0;font:15px/1.55 system-ui,-apple-system,sans-serif;background:var(--bg);color:var(--fg)}
.wrap{max-width:760px;margin:0 auto;padding:14px 16px 60px}
.top{display:flex;align-items:center;gap:10px;flex-wrap:wrap;position:sticky;top:0;background:var(--bg);padding:8px 0;border-bottom:1px solid var(--line);z-index:5}
.top a{color:var(--acc);text-decoration:none;font-size:14px}
.top .sp{flex:1}
.lang a{color:var(--mut);padding:2px 6px;border-radius:6px}
.lang a.on{color:var(--fg);background:var(--card)}
h1{font-size:22px;margin:14px 0 4px}
h2{font-size:18px;margin:26px 0 8px;padding-top:6px;border-top:1px solid var(--line);color:#cfe0ff}
h3{font-size:15px;margin:16px 0 4px}
p,li{margin:7px 0}
code{background:#0d1424;border:1px solid #2b3855;border-radius:6px;padding:1px 6px;font-family:ui-monospace,monospace;font-size:.92em}
ol,ul{padding-left:22px}
a{color:var(--acc)}
.lead{color:var(--mut)}
.toc{background:var(--card);border-radius:12px;padding:12px 16px;margin:14px 0}
.toc ol{margin:4px 0;padding-left:20px}
.toc a{text-decoration:none}
.box{border-radius:10px;padding:10px 14px;margin:12px 0;border-left:4px solid}
.box b{display:block;margin-bottom:2px}
.hint{background:#0e2536;border-color:var(--acc)}
.tip{background:#0e2a1c;border-color:var(--ok)}
.warn{background:#2a2410;border-color:var(--warn)}
.dang{background:#2a1414;border-color:var(--bad)}
table{border-collapse:collapse;width:100%;margin:10px 0;font-size:14px}
th,td{border-bottom:1px solid var(--line);padding:7px 8px;text-align:left;vertical-align:top}
th{color:#cfe0ff}
figure{margin:12px 0;text-align:center}
svg{max-width:100%;height:auto}
.led{display:inline-block;width:11px;height:11px;border-radius:50%;vertical-align:middle;margin-right:6px}
.totop{font-size:13px;color:var(--mut);text-decoration:none}
kbd{background:#0d1424;border:1px solid #2b3855;border-radius:5px;padding:0 5px;font-family:ui-monospace,monospace;font-size:.9em}
</style></head><body>
<div class=wrap>

<div class=top>
 <a href="/">&larr; To the app</a><span class=sp></span>
 <span class=lang><a href="/help?lang=de">DE</a> <a class=on href="/help?lang=en">EN</a> <a href="/help?lang=fr">FR</a></span>
</div>

<h1 id=oben>Feeder-Relais — Manual</h1>
<p class=lead>Installation, setup, operation and integration with ioBroker. This page is stored <b>on the device</b> and can be read even without an internet connection.</p>

<div class=toc>
<b>Contents</b>
<ol>
<li><a href="#was">What the device does</a></li>
<li><a href="#flash">Flashing the firmware (initial flash)</a></li>
<li><a href="#wlan">Setting up WiFi</a></li>
<li><a href="#geraet">Operating the device</a></li>
<li><a href="#webapp">Operating via the web app</a></li>
<li><a href="#netz">Network, time, language, updates</a></li>
<li><a href="#iobroker">Integration with ioBroker</a></li>
<li><a href="#fehler">Troubleshooting</a></li>
<li><a href="#sicher">Safety &amp; detailed manual</a></li>
</ol>
</div>

<h2 id=was>1. What the device does</h2>
<p>The Feeder-Relais switches a 230 V load (e.g. an automatic feeder) on at the press of a button for an <b>adjustable time</b>, then switches it back off by itself. Three buttons trigger three separately adjustable times. The actual switching is handled by an <b>external Shelly 1PM Mini Gen4</b>, which the board drives with galvanic isolation via a PhotoMOS — the core function therefore runs <b>without WiFi</b>.</p>
<figure><svg viewBox="0 0 620 60" role=img aria-label="Signal chain">
<style>.b{fill:#1a2232;stroke:#3b82f6}.t{fill:#eef2f8;font:12px sans-serif;text-anchor:middle}.a{stroke:#8595ad;stroke-width:2;marker-end:url(#ah)}</style>
<defs><marker id=ah markerWidth=8 markerHeight=8 refX=7 refY=3 orient=auto><path d="M0,0 L7,3 L0,6 z" fill="#8595ad"/></marker></defs>
<g>
<rect class=b x=4 y=16 width=86 height=28 rx=6/><text class=t x=47 y=34>Button</text>
<line class=a x1=92 y1=30 x2=118 y2=30/>
<rect class=b x=120 y=16 width=96 height=28 rx=6/><text class=t x=168 y=34>ESP32-C3</text>
<line class=a x1=218 y1=30 x2=244 y2=30/>
<rect class=b x=246 y=16 width=96 height=28 rx=6/><text class=t x=294 y=34>PhotoMOS</text>
<line class=a x1=344 y1=30 x2=370 y2=30/>
<rect class=b x=372 y=16 width=110 height=28 rx=6/><text class=t x=427 y=34>Shelly 1PM</text>
<line class=a x1=484 y1=30 x2=510 y2=30/>
<rect class=b x=512 y=16 width=100 height=28 rx=6/><text class=t x=562 y=34>230 V load</text>
</g></svg><figcaption class=lead>The signal chain: the ESP counts the time, the Shelly does the switching.</figcaption></figure>

<h2 id=flash>2. Flashing the firmware (initial flash)</h2>
<p>The first time, the ESP is programmed via <b>USB and the browser</b> — with no mains voltage involved at all. Ideally <b>before</b> it is soldered in.</p>
<div class=warn><b>⚠ Requirements</b>A <b>USB-C data cable</b> (not a charge-only cable!) and <b>Google Chrome</b> or <b>Microsoft Edge</b> (Firefox/Safari do not support Web Serial).</div>
<ol>
<li>Download the file: <b>feeder-relais-vX.Y.Z.factory.bin</b> from the <a href="https://github.com/ssbingo/timer-ersatzplatine/releases/latest">releases page</a> (the "Assets" section). The <code>factory</code> file is the complete image for the initial flash; the <code>ota</code> file is only for later updates.</li>
<li>Connect the ESP via USB-C. In <b>Chrome/Edge</b>, open the flashing tool: <code>https://espressif.github.io/esptool-js/</code></li>
<li>Click <b>Connect</b> and select the ESP's port. Success looks like: "Connected to device: ESP32-C3".</li>
<li><b>Set Flash Address to <code>0x0000</code></b> (the default value <code>0x1000</code> is wrong!). Choose <code>factory.bin</code> as the file. Leave Flash Mode/Frequency/Size at <code>keep</code>.</li>
<li>Click <b>Program</b> and wait until "Writing … (100 %)" and "Hard resetting…" appear.</li>
</ol>
<div class=hint><b>ℹ Why 0x0000?</b><code>0</code>, <code>0x0</code> and <code>0x0000</code> are the same location — the start of memory. The <code>factory</code> image is complete (bootloader + program) and must begin right at the start. The default value <code>0x1000</code> would shift everything → the ESP will not start.</div>
<div class=warn><b>⚠ No port / "Failed to connect"?</b>Put the ESP into download mode: hold <kbd>BOOT</kbd> down, briefly press <kbd>RESET</kbd>, release <kbd>BOOT</kbd> — then click "Connect" again. If problems persist, first run <b>Erase Flash</b>, then flash again.</div>
<div class=tip><b>✓ Power tip</b>Right after flashing, the radio draws brief current spikes. On a weak USB port this can cause the ESP to restart. Use a <b>robust 5 V power supply</b> or a port directly on the PC with a short, thick cable.</div>

<h2 id=wlan>3. Setting up WiFi</h2>
<p>After the first start, the ESP opens its own WiFi network for setup:</p>
<ol>
<li>On your phone, connect to the WiFi network <b>Feeder-Relais Setup</b> (password <code>feeder1234</code>).</li>
<li>A login page should open (otherwise go to <code>http://192.168.4.1</code>).</li>
<li>Select your <b>home WiFi</b>, enter the password, and save.</li>
</ol>
<p>After that, the device is reachable on your home network at <code>http://feeder-relais.local</code>.</p>
<div class=hint><b>ℹ It may take a moment</b>The first connection sometimes takes a few seconds to establish — this is normal.</div>

<h2 id=geraet>4. Operating the device</h2>
<table>
<tr><th>Button</th><th>short press</th><th>long press</th></tr>
<tr><td><b>S1</b> Down/Manual</td><td>Trigger timer 1</td><td>—</td></tr>
<tr><td><b>S2</b> SET</td><td>Trigger timer 2</td><td>≥ 3 s: info menu (scroll with S1/S3)</td></tr>
<tr><td><b>S3</b> UP</td><td>Trigger timer 3</td><td>≥ 1.2 s: stop all timers</td></tr>
</table>
<p>The <b>OLED</b> shows WiFi signal strength at the top, the large clock or countdown, and the status (<b>Idle</b> / <b>Feed</b>); at the bottom, the date and free memory. Weekday, status and menu titles follow the selected language.</p>
<p><b>Status LED</b> (small LED on the ESP):</p>
<p><span class=led style="background:#22c55e"></span> green = ready &nbsp;·&nbsp; <span class=led style="background:#f59e0b"></span> yellow = timer running &nbsp;·&nbsp; <span class=led style="background:#ef4444"></span> red = fault</p>

<h2 id=webapp>5. Operating via the web app</h2>
<p>Open <code>http://feeder-relais.local</code> in your browser. At the bottom, you can switch between the sections:</p>
<table>
<tr><th>Section</th><th>Function</th></tr>
<tr><td><b>Home</b></td><td>Status, trigger timer 1/2/3, stop</td></tr>
<tr><td><b>Times</b></td><td>set and save the three switching times (1–600 s)</td></tr>
<tr><td><b>Network</b></td><td>change WiFi, IP (DHCP/static), NTP time server, hostname, roaming</td></tr>
<tr><td><b>Status</b></td><td>version, uptime, WiFi, IP, MAC, reset reason, relay</td></tr>
<tr><td><b>Service</b></td><td>log/debug, firmware update (OTA), restart</td></tr>
</table>
<p>You change the <b>language</b> (Deutsch/English/Français) at the top of the "Times" section — it applies to both the web app and the OLED.</p>

<h2 id=netz>6. Network, time, language, updates</h2>
<ul>
<li><b>Time:</b> The clock is set via an internet time server (NTP); you can change the server in the "Network" section.</li>
<li><b>IP:</b> The default is DHCP (automatic). A static IP takes effect after a restart.</li>
<li><b>Updates (OTA):</b> New firmware without a cable — in the <b>Service → Firmware update</b> section, upload the <b>ota.bin</b> of the new version there. The device then restarts.</li>
</ul>

<h2 id=iobroker>7. Integration with ioBroker</h2>
<p>The device is the hardware side of an automatic feeder and integrates well with ioBroker:</p>
<ul>
<li><b>Shelly adapter:</b> The external Shelly 1PM Mini Gen4 is integrated natively via the ioBroker Shelly adapter — switch state and power measurement are directly visible and controllable there.</li>
<li><b>The device's JSON API:</b> can be queried and controlled via REST/scripts:
<table>
<tr><th>Endpoint</th><th>Purpose</th></tr>
<tr><td><code>GET /api/status</code></td><td>Status (version, relay, remaining time, WiFi …)</td></tr>
<tr><td><code>POST /api/trigger?ch=1|2|3</code></td><td>Trigger timer</td></tr>
<tr><td><code>POST /api/stop</code></td><td>Stop all timers</td></tr>
<tr><td><code>POST /api/config?...</code></td><td>Set times</td></tr>
</table></li>
</ul>
<p>For scheduling and a ready-made dashboard, there are matching adapters from the same author:</p>
<ul>
<li><a href="https://github.com/ssbingo/ioBroker.automatic-feeder">ioBroker.automatic-feeder</a> — scheduling, temperature model, sunrise/sunset, pauses, notifications.</li>
<li><a href="https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder">ioBroker.vis-2-widgets-automatic-feeder</a> — ready-made vis-2 dashboard widgets (display + remote control).</li>
</ul>

<h2 id=fehler>8. Troubleshooting</h2>
<table>
<tr><th>Problem</th><th>Solution</th></tr>
<tr><td>During flashing, the <b>USB port keeps flapping</b> (connects/disconnects constantly)</td><td>The firmware is starting in a loop → the USB keeps re-registering. Force it into download mode: hold <kbd>BOOT</kbd>, tap <kbd>RESET</kbd>, release <kbd>BOOT</kbd>. Then "Connect", "Erase Flash", flash again.</td></tr>
<tr><td><b>No WiFi</b> network "Feeder-Relais Setup" visible</td><td>Usually not enough power → restart loop. Connect a <b>robust 5 V power supply</b>, wait ~15 s, search again on your phone (2.4 GHz). Check that <b>factory.bin</b> was flashed at <code>0x0000</code>.</td></tr>
<tr><td><b>OLED stays black</b></td><td>Is the display plugged in correctly? Check the contacts. (When building your own: SDA must be on ESP pad 7, see the detailed manual.)</td></tr>
<tr><td><b>Device not reachable</b></td><td>Look up the IP in your router, or connect via IP instead of <code>feeder-relais.local</code>. As a last resort, restart via <b>Service</b>.</td></tr>
</table>

<h2 id=sicher>9. Safety &amp; detailed manual</h2>
<div class=dang><b>✋ 230 volts — danger to life</b>Assembly and connection of the mains voltage belong in the hands of a qualified electrician. Never work on the open device while it is live.</div>
<p>You can find the <b>complete build guide</b> (components, board, soldering, KiCad, case printing) online:</p>
<p><a href="https://ssbingo.github.io/timer-ersatzplatine/">ssbingo.github.io/timer-ersatzplatine</a> · <a href="https://github.com/ssbingo/timer-ersatzplatine">Project on GitHub</a></p>

<p style="margin-top:26px"><a class=totop href="#oben">↑ to top</a> &nbsp;·&nbsp; <a class=totop href="/">← to the app</a></p>
<p class=lead style="font-size:12px">© 2026 S. Sternitzke · CC BY-NC-SA 4.0</p>

</div></body></html>
)HELP";

static const char HELP_FR[] PROGMEM = R"HELP(
<!doctype html><html lang=fr><head><meta charset=utf-8>
<meta name=viewport content="width=device-width,initial-scale=1,viewport-fit=cover">
<title>Feeder-Relais — Manuel</title>
<style>
:root{--bg:#0f1420;--card:#1a2232;--line:#232d42;--mut:#8595ad;--fg:#eef2f8;--acc:#3b82f6;--ok:#22c55e;--warn:#f59e0b;--bad:#ef4444}
*{box-sizing:border-box}
body{margin:0;font:15px/1.55 system-ui,-apple-system,sans-serif;background:var(--bg);color:var(--fg)}
.wrap{max-width:760px;margin:0 auto;padding:14px 16px 60px}
.top{display:flex;align-items:center;gap:10px;flex-wrap:wrap;position:sticky;top:0;background:var(--bg);padding:8px 0;border-bottom:1px solid var(--line);z-index:5}
.top a{color:var(--acc);text-decoration:none;font-size:14px}
.top .sp{flex:1}
.lang a{color:var(--mut);padding:2px 6px;border-radius:6px}
.lang a.on{color:var(--fg);background:var(--card)}
h1{font-size:22px;margin:14px 0 4px}
h2{font-size:18px;margin:26px 0 8px;padding-top:6px;border-top:1px solid var(--line);color:#cfe0ff}
h3{font-size:15px;margin:16px 0 4px}
p,li{margin:7px 0}
code{background:#0d1424;border:1px solid #2b3855;border-radius:6px;padding:1px 6px;font-family:ui-monospace,monospace;font-size:.92em}
ol,ul{padding-left:22px}
a{color:var(--acc)}
.lead{color:var(--mut)}
.toc{background:var(--card);border-radius:12px;padding:12px 16px;margin:14px 0}
.toc ol{margin:4px 0;padding-left:20px}
.toc a{text-decoration:none}
.box{border-radius:10px;padding:10px 14px;margin:12px 0;border-left:4px solid}
.box b{display:block;margin-bottom:2px}
.hint{background:#0e2536;border-color:var(--acc)}
.tip{background:#0e2a1c;border-color:var(--ok)}
.warn{background:#2a2410;border-color:var(--warn)}
.dang{background:#2a1414;border-color:var(--bad)}
table{border-collapse:collapse;width:100%;margin:10px 0;font-size:14px}
th,td{border-bottom:1px solid var(--line);padding:7px 8px;text-align:left;vertical-align:top}
th{color:#cfe0ff}
figure{margin:12px 0;text-align:center}
svg{max-width:100%;height:auto}
.led{display:inline-block;width:11px;height:11px;border-radius:50%;vertical-align:middle;margin-right:6px}
.totop{font-size:13px;color:var(--mut);text-decoration:none}
kbd{background:#0d1424;border:1px solid #2b3855;border-radius:5px;padding:0 5px;font-family:ui-monospace,monospace;font-size:.9em}
</style></head><body>
<div class=wrap>

<div class=top>
 <a href="/">&larr; Vers l'appli</a><span class=sp></span>
 <span class=lang><a href="/help?lang=de">DE</a> <a href="/help?lang=en">EN</a> <a class=on href="/help?lang=fr">FR</a></span>
</div>

<h1 id=oben>Feeder-Relais — Manuel</h1>
<p class=lead>Installation, configuration, utilisation et intégration à ioBroker. Cette page est stockée <b>dans l'appareil</b> et reste lisible même sans Internet.</p>

<div class=toc>
<b>Sommaire</b>
<ol>
<li><a href="#was">Ce que fait l'appareil</a></li>
<li><a href="#flash">Installer le firmware (premier flashage)</a></li>
<li><a href="#wlan">Configurer le Wi-Fi</a></li>
<li><a href="#geraet">Utilisation sur l'appareil</a></li>
<li><a href="#webapp">Utilisation via l'appli web</a></li>
<li><a href="#netz">Réseau, heure, langue, mises à jour</a></li>
<li><a href="#iobroker">Intégration à ioBroker</a></li>
<li><a href="#fehler">Dépannage</a></li>
<li><a href="#sicher">Sécurité &amp; manuel complet</a></li>
</ol>
</div>

<h2 id=was>1. Ce que fait l'appareil</h2>
<p>Le Feeder-Relais met sous tension une charge 230 V (par ex. un distributeur de nourriture) sur simple pression d'un bouton, pendant une <b>durée réglable</b>, puis la coupe automatiquement. Trois boutons déclenchent trois durées réglables séparément. La commutation proprement dite est assurée par un <b>Shelly 1PM Mini Gen4 externe</b>, piloté par la carte via un PhotoMOS à isolation galvanique — la fonction principale fonctionne donc <b>sans Wi-Fi</b>.</p>
<figure><svg viewBox="0 0 620 60" role=img aria-label="Chaîne du signal">
<style>.b{fill:#1a2232;stroke:#3b82f6}.t{fill:#eef2f8;font:12px sans-serif;text-anchor:middle}.a{stroke:#8595ad;stroke-width:2;marker-end:url(#ah)}</style>
<defs><marker id=ah markerWidth=8 markerHeight=8 refX=7 refY=3 orient=auto><path d="M0,0 L7,3 L0,6 z" fill="#8595ad"/></marker></defs>
<g>
<rect class=b x=4 y=16 width=86 height=28 rx=6/><text class=t x=47 y=34>Bouton</text>
<line class=a x1=92 y1=30 x2=118 y2=30/>
<rect class=b x=120 y=16 width=96 height=28 rx=6/><text class=t x=168 y=34>ESP32-C3</text>
<line class=a x1=218 y1=30 x2=244 y2=30/>
<rect class=b x=246 y=16 width=96 height=28 rx=6/><text class=t x=294 y=34>PhotoMOS</text>
<line class=a x1=344 y1=30 x2=370 y2=30/>
<rect class=b x=372 y=16 width=110 height=28 rx=6/><text class=t x=427 y=34>Shelly 1PM</text>
<line class=a x1=484 y1=30 x2=510 y2=30/>
<rect class=b x=512 y=16 width=100 height=28 rx=6/><text class=t x=562 y=34>Charge 230 V</text>
</g></svg><figcaption class=lead>La chaîne du signal : l'ESP compte le temps, le Shelly commute.</figcaption></figure>

<h2 id=flash>2. Installer le firmware (premier flashage)</h2>
<p>La première fois, l'ESP est programmé via <b>USB et le navigateur</b> — sans aucune tension secteur. Idéalement <b>avant</b> qu'il ne soit soudé.</p>
<div class=warn><b>⚠ Prérequis</b>Un <b>câble de données USB-C</b> (pas un simple câble de charge !) et <b>Google Chrome</b> ou <b>Microsoft Edge</b> (Firefox/Safari ne prennent pas en charge Web Serial).</div>
<ol>
<li>Télécharger le fichier : <b>feeder-relais-vX.Y.Z.factory.bin</b> depuis la <a href="https://github.com/ssbingo/timer-ersatzplatine/releases/latest">page des versions</a> (section « Assets »). Le fichier <code>factory</code> est l'image complète pour le premier flashage ; le fichier <code>ota</code> ne sert que pour les mises à jour ultérieures.</li>
<li>Brancher l'ESP en USB-C. Dans <b>Chrome/Edge</b>, ouvrir l'outil de flashage : <code>https://espressif.github.io/esptool-js/</code></li>
<li>Cliquer sur <b>Connect</b>, sélectionner le port de l'ESP. Succès : « Connected to device: ESP32-C3 ».</li>
<li><b>Régler Flash Address sur <code>0x0000</code></b> (la valeur par défaut <code>0x1000</code> est incorrecte !). Choisir le fichier <code>factory.bin</code>. Laisser Flash Mode/Frequency/Size sur <code>keep</code>.</li>
<li>Cliquer sur <b>Program</b> et attendre l'affichage de « Writing … (100 %) » puis « Hard resetting… ».</li>
</ol>
<div class=hint><b>ℹ Pourquoi 0x0000 ?</b><code>0</code>, <code>0x0</code> et <code>0x0000</code> désignent le même emplacement — le début de la mémoire. L'image <code>factory</code> est complète (bootloader + programme) et doit commencer tout au début. La valeur par défaut <code>0x1000</code> décalerait tout → l'ESP ne démarre pas.</div>
<div class=warn><b>⚠ Pas de port / « Failed to connect » ?</b>Mettre l'ESP en mode téléchargement : maintenir <kbd>BOOT</kbd> enfoncé, appuyer brièvement sur <kbd>RESET</kbd>, relâcher <kbd>BOOT</kbd> — puis refaire « Connect ». En cas de problème persistant, faire d'abord <b>Erase Flash</b>, puis reflasher.</div>
<div class=tip><b>✓ Astuce alimentation</b>Juste après le flashage, la radio provoque de brefs pics de courant. Sur un port USB trop faible, cela peut redémarrer l'ESP. Utilisez une <b>alimentation 5 V robuste</b> ou un port directement sur le PC avec un câble court et épais.</div>

<h2 id=wlan>3. Configurer le Wi-Fi</h2>
<p>Au premier démarrage, l'ESP ouvre son propre réseau Wi-Fi pour la configuration :</p>
<ol>
<li>Sur le téléphone, se connecter au réseau Wi-Fi <b>Feeder-Relais Setup</b> (mot de passe <code>feeder1234</code>).</li>
<li>Une page de connexion s'ouvre (sinon, ouvrir <code>http://192.168.4.1</code>).</li>
<li>Choisir son <b>réseau Wi-Fi domestique</b>, saisir le mot de passe, enregistrer.</li>
</ol>
<p>L'appareil est ensuite accessible sur le réseau domestique à l'adresse <code>http://feeder-relais.local</code>.</p>
<div class=hint><b>ℹ Cela peut prendre un instant</b>La première connexion peut parfois prendre quelques secondes — c'est normal.</div>

<h2 id=geraet>4. Utilisation sur l'appareil</h2>
<table>
<tr><th>Bouton</th><th>court</th><th>long</th></tr>
<tr><td><b>S1</b> Down/Manual</td><td>Déclencher le minuteur 1</td><td>—</td></tr>
<tr><td><b>S2</b> SET</td><td>Déclencher le minuteur 2</td><td>≥ 3 s : menu d'informations (naviguer avec S1/S3)</td></tr>
<tr><td><b>S3</b> UP</td><td>Déclencher le minuteur 3</td><td>≥ 1,2 s : arrêter tous les minuteurs</td></tr>
</table>
<p>L'<b>OLED</b> affiche en haut la réception Wi-Fi, en grand l'horloge ou le compte à rebours, ainsi que le statut (<b>Repos</b> / <b>Repas</b>) ; en bas la date et la mémoire libre. Le jour de la semaine, le statut et les titres de menu suivent la langue configurée.</p>
<p><b>Voyant de statut</b> (petite LED sur l'ESP) :</p>
<p><span class=led style="background:#22c55e"></span> vert = prêt &nbsp;·&nbsp; <span class=led style="background:#f59e0b"></span> jaune = minuteur en cours &nbsp;·&nbsp; <span class=led style="background:#ef4444"></span> rouge = anomalie</p>

<h2 id=webapp>5. Utilisation via l'appli web</h2>
<p>Ouvrir <code>http://feeder-relais.local</code> dans le navigateur. En bas, vous basculez entre les sections :</p>
<table>
<tr><th>Section</th><th>Fonction</th></tr>
<tr><td><b>Accueil</b></td><td>statut, déclencher les minuteurs 1/2/3, arrêt</td></tr>
<tr><td><b>Durées</b></td><td>régler et enregistrer les trois durées de commutation (1–600 s)</td></tr>
<tr><td><b>Réseau</b></td><td>changer de Wi-Fi, IP (DHCP/statique), serveur de temps NTP, nom d'hôte, itinérance</td></tr>
<tr><td><b>Statut</b></td><td>version, temps de fonctionnement, Wi-Fi, IP, MAC, cause du redémarrage, relais</td></tr>
<tr><td><b>Service</b></td><td>journal/débogage, mise à jour du firmware (OTA), redémarrage</td></tr>
</table>
<p>La <b>langue</b> (Deutsch/English/Français) se change en haut dans la section « Durées » — elle s'applique à l'appli web et à l'OLED.</p>

<h2 id=netz>6. Réseau, heure, langue, mises à jour</h2>
<ul>
<li><b>Heure :</b> l'horloge est réglée via un serveur de temps Internet (NTP) ; vous changez le serveur dans la section « Réseau ».</li>
<li><b>IP :</b> le réglage par défaut est DHCP (automatique). Une IP fixe devient active après un redémarrage.</li>
<li><b>Mises à jour (OTA) :</b> nouveau firmware sans câble — section <b>Service → Mise à jour du firmware</b>, y téléverser le fichier <b>ota.bin</b> de la nouvelle version. L'appareil redémarre ensuite.</li>
</ul>

<h2 id=iobroker>7. Intégration à ioBroker</h2>
<p>L'appareil constitue le côté matériel d'un distributeur de nourriture et s'intègre bien à ioBroker :</p>
<ul>
<li><b>Adaptateur Shelly :</b> le Shelly 1PM Mini Gen4 externe s'intègre nativement via l'adaptateur ioBroker Shelly — l'état de commutation et la mesure de puissance y sont directement visibles et commandables.</li>
<li><b>API JSON de l'appareil :</b> interrogeable et pilotable via REST/script :
<table>
<tr><th>Point d'accès</th><th>Objectif</th></tr>
<tr><td><code>GET /api/status</code></td><td>statut (version, relais, temps restant, Wi-Fi …)</td></tr>
<tr><td><code>POST /api/trigger?ch=1|2|3</code></td><td>déclencher un minuteur</td></tr>
<tr><td><code>POST /api/stop</code></td><td>arrêter tous les minuteurs</td></tr>
<tr><td><code>POST /api/config?...</code></td><td>régler les durées</td></tr>
</table></li>
</ul>
<p>Pour la planification horaire et un tableau de bord prêt à l'emploi, il existe les adaptateurs correspondants du même auteur :</p>
<ul>
<li><a href="https://github.com/ssbingo/ioBroker.automatic-feeder">ioBroker.automatic-feeder</a> — planification horaire, modèle de température, lever/coucher du soleil, pauses, notifications.</li>
<li><a href="https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder">ioBroker.vis-2-widgets-automatic-feeder</a> — widgets de tableau de bord vis-2 prêts à l'emploi (affichage + télécommande).</li>
</ul>

<h2 id=fehler>8. Dépannage</h2>
<table>
<tr><th>Problème</th><th>Solution</th></tr>
<tr><td>Pendant le flashage, <b>le port USB clignote</b> (se connecte/déconnecte sans arrêt)</td><td>Le firmware redémarre en boucle → l'USB se réannonce sans cesse. Forcer le mode téléchargement : maintenir <kbd>BOOT</kbd>, appuyer sur <kbd>RESET</kbd>, relâcher <kbd>BOOT</kbd>. Puis « Connect », « Erase Flash », reflasher.</td></tr>
<tr><td><b>Aucun Wi-Fi</b> « Feeder-Relais Setup » visible</td><td>Généralement un manque de courant → boucle de redémarrage. Brancher une <b>alimentation 5 V robuste</b>, attendre ~15 s, rechercher à nouveau sur le téléphone (2,4 GHz). Vérifier que le <b>factory.bin</b> a bien été flashé à l'adresse <code>0x0000</code>.</td></tr>
<tr><td><b>L'OLED reste noir</b></td><td>L'écran est-il correctement enfiché ? Vérifier les contacts. (Pour l'auto-construction : SDA doit être relié au pad 7 de l'ESP, voir le manuel complet.)</td></tr>
<tr><td><b>Appareil injoignable</b></td><td>Chercher l'IP dans le routeur, ou y accéder par l'IP plutôt que par <code>feeder-relais.local</code>. En dernier recours, redémarrer via <b>Service</b>.</td></tr>
</table>

<h2 id=sicher>9. Sécurité &amp; manuel complet</h2>
<div class=dang><b>✋ 230 volts — danger de mort</b>Le montage et le raccordement à la tension secteur doivent être confiés à un électricien qualifié. Ne travaillez jamais sur l'appareil ouvert sous tension.</div>
<p>Le <b>guide complet d'auto-construction</b> (composants, carte, soudure, KiCad, impression du boîtier) est disponible en ligne :</p>
<p><a href="https://ssbingo.github.io/timer-ersatzplatine/">ssbingo.github.io/timer-ersatzplatine</a> · <a href="https://github.com/ssbingo/timer-ersatzplatine">Projet sur GitHub</a></p>

<p style="margin-top:26px"><a class=totop href="#oben">↑ haut de page</a> &nbsp;·&nbsp; <a class=totop href="/">← vers l'appli</a></p>
<p class=lead style="font-size:12px">© 2026 S. Sternitzke · CC BY-NC-SA 4.0</p>

</div></body></html>
)HELP";


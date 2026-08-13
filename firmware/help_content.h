// AUTO-GENERIERT von mk_help.py aus help_<lang>.html.
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
 <span class=lang><a class=on href="/help?lang=de">🇩🇪 DE</a> <a href="/help?lang=en">🇬🇧 EN</a> <a href="/help?lang=fr">🇫🇷 FR</a> <a href="/help?lang=nl">🇳🇱 NL</a> <a href="/help?lang=es">🇪🇸 ES</a> <a href="/help?lang=it">🇮🇹 IT</a></span>
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
 <span class=lang><a href="/help?lang=de">🇩🇪 DE</a> <a class=on href="/help?lang=en">🇬🇧 EN</a> <a href="/help?lang=fr">🇫🇷 FR</a> <a href="/help?lang=nl">🇳🇱 NL</a> <a href="/help?lang=es">🇪🇸 ES</a> <a href="/help?lang=it">🇮🇹 IT</a></span>
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
 <span class=lang><a href="/help?lang=de">🇩🇪 DE</a> <a href="/help?lang=en">🇬🇧 EN</a> <a class=on href="/help?lang=fr">🇫🇷 FR</a> <a href="/help?lang=nl">🇳🇱 NL</a> <a href="/help?lang=es">🇪🇸 ES</a> <a href="/help?lang=it">🇮🇹 IT</a></span>
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

static const char HELP_NL[] PROGMEM = R"HELP(
<!doctype html><html lang=nl><head><meta charset=utf-8>
<meta name=viewport content="width=device-width,initial-scale=1,viewport-fit=cover">
<title>Feeder-Relais — Handleiding</title>
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
 <a href="/">&larr; Naar de app</a><span class=sp></span>
 <span class=lang><a href="/help?lang=de">🇩🇪 DE</a> <a href="/help?lang=en">🇬🇧 EN</a> <a href="/help?lang=fr">🇫🇷 FR</a> <a class=on href="/help?lang=nl">🇳🇱 NL</a> <a href="/help?lang=es">🇪🇸 ES</a> <a href="/help?lang=it">🇮🇹 IT</a></span>
</div>

<h1 id=oben>Feeder-Relais — Handleiding</h1>
<p class=lead>Installatie, instelling, bediening en koppeling met ioBroker. Deze pagina staat <b>in het apparaat</b> en is ook zonder internet leesbaar.</p>

<div class=toc>
<b>Inhoud</b>
<ol>
<li><a href="#was">Wat het apparaat doet</a></li>
<li><a href="#flash">Firmware installeren (eerste keer flashen)</a></li>
<li><a href="#wlan">Wifi instellen</a></li>
<li><a href="#geraet">Bediening op het apparaat</a></li>
<li><a href="#webapp">Bediening via de web-app</a></li>
<li><a href="#netz">Netwerk, tijd, taal, updates</a></li>
<li><a href="#iobroker">Koppeling met ioBroker</a></li>
<li><a href="#fehler">Problemen oplossen</a></li>
<li><a href="#sicher">Veiligheid &amp; uitgebreide handleiding</a></li>
</ol>
</div>

<h2 id=was>1. Wat het apparaat doet</h2>
<p>De Feeder-Relais schakelt een 230 V-belasting (bijv. een voerautomaat) op knopdruk voor een <b>instelbare tijd</b> in en daarna vanzelf weer uit. Drie knoppen activeren drie afzonderlijk instelbare tijden. Het eigenlijke schakelen doet een <b>externe Shelly 1PM Mini Gen4</b>, die de printplaat via een PhotoMOS galvanisch gescheiden aanstuurt — de kernfunctie werkt daardoor <b>zonder wifi</b>.</p>
<figure><svg viewBox="0 0 620 60" role=img aria-label="Signalkette">
<style>.b{fill:#1a2232;stroke:#3b82f6}.t{fill:#eef2f8;font:12px sans-serif;text-anchor:middle}.a{stroke:#8595ad;stroke-width:2;marker-end:url(#ah)}</style>
<defs><marker id=ah markerWidth=8 markerHeight=8 refX=7 refY=3 orient=auto><path d="M0,0 L7,3 L0,6 z" fill="#8595ad"/></marker></defs>
<g>
<rect class=b x=4 y=16 width=86 height=28 rx=6/><text class=t x=47 y=34>Knop</text>
<line class=a x1=92 y1=30 x2=118 y2=30/>
<rect class=b x=120 y=16 width=96 height=28 rx=6/><text class=t x=168 y=34>ESP32-C3</text>
<line class=a x1=218 y1=30 x2=244 y2=30/>
<rect class=b x=246 y=16 width=96 height=28 rx=6/><text class=t x=294 y=34>PhotoMOS</text>
<line class=a x1=344 y1=30 x2=370 y2=30/>
<rect class=b x=372 y=16 width=110 height=28 rx=6/><text class=t x=427 y=34>Shelly 1PM</text>
<line class=a x1=484 y1=30 x2=510 y2=30/>
<rect class=b x=512 y=16 width=100 height=28 rx=6/><text class=t x=562 y=34>230 V-belasting</text>
</g></svg><figcaption class=lead>De signaalketen: de ESP telt de tijd, de Shelly schakelt.</figcaption></figure>

<h2 id=flash>2. Firmware installeren (eerste keer flashen)</h2>
<p>De eerste keer wordt de ESP via <b>USB en de browser</b> beschreven — helemaal zonder netspanning. Het beste <b>voordat</b> hij ingesoldeerd is.</p>
<div class=warn><b>⚠ Vereisten</b>Een <b>USB-C-datakabel</b> (geen kaal laadkabeltje!) en <b>Google Chrome</b> of <b>Microsoft Edge</b> (Firefox/Safari ondersteunen geen Web Serial).</div>
<ol>
<li>Bestand downloaden: <b>feeder-relais-vX.Y.Z.factory.bin</b> van de <a href="https://github.com/ssbingo/timer-ersatzplatine/releases/latest">releasepagina</a> (sectie „Assets"). Het <code>factory</code>-bestand is het complete image voor de eerste keer flashen; het <code>ota</code>-bestand is alleen voor latere updates.</li>
<li>ESP via USB-C aansluiten. In <b>Chrome/Edge</b> de flashtool openen: <code>https://espressif.github.io/esptool-js/</code></li>
<li>Op <b>Connect</b> klikken en de ESP-poort kiezen. Succes: „Connected to device: ESP32-C3".</li>
<li><b>Flash Address op <code>0x0000</code> zetten</b> (de standaardwaarde <code>0x1000</code> is fout!). Als bestand de <code>factory.bin</code> kiezen. Flash Mode/Frequency/Size op <code>keep</code> laten staan.</li>
<li>Op <b>Program</b> klikken en wachten tot „Writing … (100 %)" en „Hard resetting…" verschijnt.</li>
</ol>
<div class=hint><b>ℹ Waarom 0x0000?</b><code>0</code>, <code>0x0</code> en <code>0x0000</code> zijn dezelfde plek — het begin van het geheugen. Het <code>factory</code>-image is compleet (bootloader + programma) en moet helemaal vooraan beginnen. De standaardwaarde <code>0x1000</code> zou alles verschuiven → de ESP start dan niet.</div>
<div class=warn><b>⚠ Geen poort / „Failed to connect"?</b>De ESP in de download-modus zetten: <kbd>BOOT</kbd> ingedrukt houden, kort op <kbd>RESET</kbd> drukken, <kbd>BOOT</kbd> loslaten — daarna opnieuw op „Connect". Bij aanhoudende problemen eerst <b>Erase Flash</b>, dan opnieuw flashen.</div>
<div class=tip><b>✓ Stroomtip</b>Direct na het flashen trekt de radio korte stroompieken. Bij een zwakke USB-poort kan de ESP daardoor opnieuw opstarten. Gebruik een <b>krachtige 5 V-voeding</b> of een poort rechtstreeks op de pc met een kort, dik kabeltje.</div>

<h2 id=wlan>3. Wifi instellen</h2>
<p>Na de eerste start opent de ESP een eigen wifinetwerk voor de instelling:</p>
<ol>
<li>Verbind je telefoon met het wifinetwerk <b>Feeder-Relais Setup</b> (wachtwoord <code>feeder1234</code>).</li>
<li>Er opent zich een aanmeldpagina (anders <code>http://192.168.4.1</code> openen).</li>
<li>Je <b>eigen wifinetwerk kiezen</b>, wachtwoord invoeren, opslaan.</li>
</ol>
<p>Daarna is het apparaat in je thuisnetwerk bereikbaar via <code>http://feeder-relais.local</code>.</p>
<div class=hint><b>ℹ Het kan even duren</b>De eerste verbinding kan soms een paar seconden duren — dat is normaal.</div>

<h2 id=geraet>4. Bediening op het apparaat</h2>
<table>
<tr><th>Knop</th><th>kort</th><th>lang</th></tr>
<tr><td><b>S1</b> Down/Manual</td><td>Timer 1 starten</td><td>—</td></tr>
<tr><td><b>S2</b> SET</td><td>Timer 2 starten</td><td>≥ 3 s: infomenu (bladeren met S1/S3)</td></tr>
<tr><td><b>S3</b> UP</td><td>Timer 3 starten</td><td>≥ 1,2 s: alle timers stoppen</td></tr>
</table>
<p>De <b>OLED</b> toont bovenaan de wifi-ontvangst, de grote klok resp. de countdown en de status (<b>Rust</b> / <b>Voer</b>); onderaan de datum en het vrije geheugen. Weekdag, status en menutitels volgen de ingestelde taal.</p>
<p><b>Statuslampje</b> (kleine LED op de ESP):</p>
<p><span class=led style="background:#22c55e"></span> groen = klaar &nbsp;·&nbsp; <span class=led style="background:#f59e0b"></span> geel = timer actief &nbsp;·&nbsp; <span class=led style="background:#ef4444"></span> rood = storing</p>

<h2 id=webapp>5. Bediening via de web-app</h2>
<p>Open in de browser <code>http://feeder-relais.local</code>. Onderaan wissel je tussen de onderdelen:</p>
<table>
<tr><th>Onderdeel</th><th>Functie</th></tr>
<tr><td><b>Start</b></td><td>status, timer 1/2/3 starten, stoppen</td></tr>
<tr><td><b>Tijden</b></td><td>de drie schakeltijden (1–600 s) instellen en opslaan</td></tr>
<tr><td><b>Netwerk</b></td><td>wifi wisselen, IP (DHCP/statisch), NTP-tijdserver, hostnaam, roaming</td></tr>
<tr><td><b>Status</b></td><td>versie, looptijd, wifi, IP, MAC, resetoorzaak, relais</td></tr>
<tr><td><b>Service</b></td><td>log/debug, firmware-update (OTA), herstart</td></tr>
</table>
<p>De <b>taal</b> (Deutsch/English/Français) stel je bovenaan bij het onderdeel „Tijden" in — deze geldt voor web-app en OLED.</p>

<h2 id=netz>6. Netwerk, tijd, taal, updates</h2>
<ul>
<li><b>Tijd:</b> De klok wordt via een internet-tijdserver (NTP) gelijkgezet; de server wijzig je bij het onderdeel „Netwerk".</li>
<li><b>IP:</b> Standaard is DHCP (automatisch). Een vast IP-adres wordt na een herstart actief.</li>
<li><b>Updates (OTA):</b> Nieuwe firmware zonder kabel — onderdeel <b>Service → Firmware-update</b>, daar de <b>ota.bin</b> van de nieuwe versie uploaden. Het apparaat herstart daarna.</li>
</ul>

<h2 id=iobroker>7. Koppeling met ioBroker</h2>
<p>Het apparaat is de hardwarekant van een voerautomaat en past goed in ioBroker:</p>
<ul>
<li><b>Shelly-adapter:</b> De externe Shelly 1PM Mini Gen4 wordt via de ioBroker-Shelly-adapter native ingebonden — schakelstatus en vermogensmeting zijn daar direct zichtbaar en te bedienen.</li>
<li><b>JSON-API van het apparaat:</b> op te vragen en te bedienen via REST/script:
<table>
<tr><th>Eindpunt</th><th>Doel</th></tr>
<tr><td><code>GET /api/status</code></td><td>status (versie, relais, resttijd, wifi …)</td></tr>
<tr><td><code>POST /api/trigger?ch=1|2|3</code></td><td>timer starten</td></tr>
<tr><td><code>POST /api/stop</code></td><td>alle timers stoppen</td></tr>
<tr><td><code>POST /api/config?...</code></td><td>tijden instellen</td></tr>
</table></li>
</ul>
<p>Voor tijdplanning en een kant-en-klaar dashboard zijn er passende adapters van dezelfde auteur:</p>
<ul>
<li><a href="https://github.com/ssbingo/ioBroker.automatic-feeder">ioBroker.automatic-feeder</a> — tijdplanning, temperatuurmodel, zonsopgang/-ondergang, pauzes, meldingen.</li>
<li><a href="https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder">ioBroker.vis-2-widgets-automatic-feeder</a> — kant-en-klare vis-2-dashboardwidgets (weergave + afstandsbediening).</li>
</ul>

<h2 id=fehler>8. Problemen oplossen</h2>
<table>
<tr><th>Probleem</th><th>Oplossing</th></tr>
<tr><td>Tijdens het flashen <b>flikkert de USB-poort</b> (verbindt/verbreekt steeds)</td><td>De firmware start in een lus → de USB meldt zich steeds opnieuw aan. Dwing de download-modus af: <kbd>BOOT</kbd> vasthouden, <kbd>RESET</kbd> tikken, <kbd>BOOT</kbd> los. Dan „Connect", „Erase Flash", opnieuw flashen.</td></tr>
<tr><td><b>Geen wifi</b> „Feeder-Relais Setup" zichtbaar</td><td>Meestal te weinig stroom → herstartlus. Sluit een <b>krachtige 5 V-voeding</b> aan, wacht ~15 s, zoek opnieuw op de telefoon (2,4 GHz). Controleer of de <b>factory.bin</b> op <code>0x0000</code> geflasht is.</td></tr>
<tr><td><b>OLED blijft zwart</b></td><td>Display goed opgestoken? Contacten controleren. (Bij zelfbouw: SDA moet op ESP-pad 7 liggen, zie de uitgebreide handleiding.)</td></tr>
<tr><td><b>Apparaat niet bereikbaar</b></td><td>Zoek het IP-adres in de router op of gebruik het IP-adres in plaats van <code>feeder-relais.local</code>. Zo nodig via <b>Service</b> herstarten.</td></tr>
</table>

<h2 id=sicher>9. Veiligheid &amp; uitgebreide handleiding</h2>
<div class=dang><b>✋ 230 volt — levensgevaar</b>Opbouw en aansluiting van de netspanning horen in handen van een elektricien. Werk nooit aan een open, onder spanning staand apparaat.</div>
<p>De <b>volledige bouwhandleiding</b> (onderdelen, printplaat, solderen, KiCad, behuizing printen) vind je online:</p>
<p><a href="https://ssbingo.github.io/timer-ersatzplatine/">ssbingo.github.io/timer-ersatzplatine</a> · <a href="https://github.com/ssbingo/timer-ersatzplatine">Project op GitHub</a></p>

<p style="margin-top:26px"><a class=totop href="#oben">↑ naar boven</a> &nbsp;·&nbsp; <a class=totop href="/">← naar de app</a></p>
<p class=lead style="font-size:12px">© 2026 S. Sternitzke · CC BY-NC-SA 4.0</p>

</div></body></html>
)HELP";

static const char HELP_ES[] PROGMEM = R"HELP(
<!doctype html><html lang=es><head><meta charset=utf-8>
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
 <a href="/">&larr; A la app</a><span class=sp></span>
 <span class=lang><a href="/help?lang=de">🇩🇪 DE</a> <a href="/help?lang=en">🇬🇧 EN</a> <a href="/help?lang=fr">🇫🇷 FR</a> <a href="/help?lang=nl">🇳🇱 NL</a> <a class=on href="/help?lang=es">🇪🇸 ES</a> <a href="/help?lang=it">🇮🇹 IT</a></span>
</div>

<h1 id=oben>Feeder-Relais — Manual</h1>
<p class=lead>Instalación, configuración, manejo e integración con ioBroker. Esta página está guardada <b>en el aparato</b> y se puede leer también sin conexión a Internet.</p>

<div class=toc>
<b>Contenido</b>
<ol>
<li><a href="#was">Qué hace el aparato</a></li>
<li><a href="#flash">Instalar el firmware (primer flasheo)</a></li>
<li><a href="#wlan">Configurar el Wi-Fi</a></li>
<li><a href="#geraet">Manejo del aparato</a></li>
<li><a href="#webapp">Manejo mediante la aplicación web</a></li>
<li><a href="#netz">Red, hora, idioma, actualizaciones</a></li>
<li><a href="#iobroker">Integración con ioBroker</a></li>
<li><a href="#fehler">Solución de problemas</a></li>
<li><a href="#sicher">Seguridad &amp; manual completo</a></li>
</ol>
</div>

<h2 id=was>1. Qué hace el aparato</h2>
<p>El Feeder-Relais enciende una carga de 230 V (p. ej. un alimentador automático) al pulsar un botón durante un <b>tiempo ajustable</b> y después la apaga de nuevo por sí solo. Tres botones activan tres tiempos ajustables por separado. La conmutación propiamente dicha la realiza un <b>Shelly 1PM Mini Gen4 externo</b>, al que la placa controla con aislamiento galvánico mediante un PhotoMOS — la función principal funciona así <b>sin Wi-Fi</b>.</p>
<figure><svg viewBox="0 0 620 60" role=img aria-label="Cadena de señal">
<style>.b{fill:#1a2232;stroke:#3b82f6}.t{fill:#eef2f8;font:12px sans-serif;text-anchor:middle}.a{stroke:#8595ad;stroke-width:2;marker-end:url(#ah)}</style>
<defs><marker id=ah markerWidth=8 markerHeight=8 refX=7 refY=3 orient=auto><path d="M0,0 L7,3 L0,6 z" fill="#8595ad"/></marker></defs>
<g>
<rect class=b x=4 y=16 width=86 height=28 rx=6/><text class=t x=47 y=34>Botón</text>
<line class=a x1=92 y1=30 x2=118 y2=30/>
<rect class=b x=120 y=16 width=96 height=28 rx=6/><text class=t x=168 y=34>ESP32-C3</text>
<line class=a x1=218 y1=30 x2=244 y2=30/>
<rect class=b x=246 y=16 width=96 height=28 rx=6/><text class=t x=294 y=34>PhotoMOS</text>
<line class=a x1=344 y1=30 x2=370 y2=30/>
<rect class=b x=372 y=16 width=110 height=28 rx=6/><text class=t x=427 y=34>Shelly 1PM</text>
<line class=a x1=484 y1=30 x2=510 y2=30/>
<rect class=b x=512 y=16 width=100 height=28 rx=6/><text class=t x=562 y=34>Carga 230 V</text>
</g></svg><figcaption class=lead>La cadena de señal: el ESP cuenta el tiempo, el Shelly conmuta.</figcaption></figure>

<h2 id=flash>2. Instalar el firmware (primer flasheo)</h2>
<p>La primera vez, el ESP se programa mediante <b>USB y el navegador</b> — sin tensión de red en absoluto. Lo mejor es hacerlo <b>antes</b> de soldarlo.</p>
<div class=warn><b>⚠ Requisitos</b>Un <b>cable de datos USB-C</b> (¡no un simple cable de carga!) y <b>Google Chrome</b> o <b>Microsoft Edge</b> (Firefox/Safari no admiten Web Serial).</div>
<ol>
<li>Descargar el archivo: <b>feeder-relais-vX.Y.Z.factory.bin</b> desde la <a href="https://github.com/ssbingo/timer-ersatzplatine/releases/latest">página de versiones</a> (apartado «Assets»). El archivo <code>factory</code> es la imagen completa para el primer flasheo; el archivo <code>ota</code> solo sirve para actualizaciones posteriores.</li>
<li>Conectar el ESP por USB-C. En <b>Chrome/Edge</b>, abrir la herramienta de flasheo: <code>https://espressif.github.io/esptool-js/</code></li>
<li>Hacer clic en <b>Connect</b> y elegir el puerto del ESP. Éxito: «Connected to device: ESP32-C3».</li>
<li><b>Poner Flash Address en <code>0x0000</code></b> (¡el valor predeterminado <code>0x1000</code> es incorrecto!). Como archivo, elegir <code>factory.bin</code>. Dejar Flash Mode/Frequency/Size en <code>keep</code>.</li>
<li>Hacer clic en <b>Program</b> y esperar hasta que aparezcan «Writing … (100 %)» y «Hard resetting…».</li>
</ol>
<div class=hint><b>ℹ ¿Por qué 0x0000?</b><code>0</code>, <code>0x0</code> y <code>0x0000</code> son el mismo lugar — el comienzo de la memoria. La imagen <code>factory</code> está completa (bootloader + programa) y debe empezar justo al principio. El valor predeterminado <code>0x1000</code> desplazaría todo → el ESP no arranca.</div>
<div class=warn><b>⚠ ¿Sin puerto / «Failed to connect»?</b>Poner el ESP en modo de descarga: mantener pulsado <kbd>BOOT</kbd>, pulsar brevemente <kbd>RESET</kbd>, soltar <kbd>BOOT</kbd> — después repetir «Connect». Si el problema persiste, hacer primero <b>Erase Flash</b> y luego flashear de nuevo.</div>
<div class=tip><b>✓ Consejo de alimentación</b>Justo después de flashear, la radio provoca breves picos de corriente. En un puerto USB débil esto puede hacer que el ESP se reinicie. Usa una <b>fuente de 5 V robusta</b> o un puerto directamente en el PC con un cable corto y grueso.</div>

<h2 id=wlan>3. Configurar el Wi-Fi</h2>
<p>Tras el primer arranque, el ESP abre su propia red Wi-Fi para la configuración:</p>
<ol>
<li>En el móvil, conectarse a la red Wi-Fi <b>Feeder-Relais Setup</b> (contraseña <code>feeder1234</code>).</li>
<li>Se abre una página de acceso (si no, entrar en <code>http://192.168.4.1</code>).</li>
<li>Elegir tu <b>Wi-Fi doméstico</b>, introducir la contraseña y guardar.</li>
</ol>
<p>Después, el aparato está accesible en la red doméstica en <code>http://feeder-relais.local</code>.</p>
<div class=hint><b>ℹ Puede tardar un momento</b>La primera conexión a veces tarda unos segundos en establecerse — es normal.</div>

<h2 id=geraet>4. Manejo del aparato</h2>
<table>
<tr><th>Botón</th><th>corto</th><th>largo</th></tr>
<tr><td><b>S1</b> Down/Manual</td><td>Activar temporizador 1</td><td>—</td></tr>
<tr><td><b>S2</b> SET</td><td>Activar temporizador 2</td><td>≥ 3 s: menú de información (navegar con S1/S3)</td></tr>
<tr><td><b>S3</b> UP</td><td>Activar temporizador 3</td><td>≥ 1,2 s: detener todos los temporizadores</td></tr>
</table>
<p>La <b>pantalla OLED</b> muestra arriba la recepción Wi-Fi, el reloj grande o la cuenta atrás y el estado (<b>Reposo</b> / <b>Comida</b>); abajo la fecha y la memoria libre. El día de la semana, el estado y los títulos del menú siguen el idioma configurado.</p>
<p><b>LED de estado</b> (LED pequeño en el ESP):</p>
<p><span class=led style="background:#22c55e"></span> verde = listo &nbsp;·&nbsp; <span class=led style="background:#f59e0b"></span> amarillo = temporizador en marcha &nbsp;·&nbsp; <span class=led style="background:#ef4444"></span> rojo = fallo</p>

<h2 id=webapp>5. Manejo mediante la aplicación web</h2>
<p>Abrir <code>http://feeder-relais.local</code> en el navegador. Abajo puedes cambiar entre las secciones:</p>
<table>
<tr><th>Sección</th><th>Función</th></tr>
<tr><td><b>Inicio</b></td><td>Estado, activar temporizador 1/2/3, parar</td></tr>
<tr><td><b>Tiempos</b></td><td>configurar y guardar los tres tiempos de conmutación (1–600 s)</td></tr>
<tr><td><b>Red</b></td><td>cambiar de Wi-Fi, IP (DHCP/estática), servidor de tiempo NTP, nombre de host, itinerancia</td></tr>
<tr><td><b>Estado</b></td><td>versión, tiempo de actividad, Wi-Fi, IP, MAC, motivo de reinicio, relé</td></tr>
<tr><td><b>Servicio</b></td><td>registro/depuración, actualización de firmware (OTA), reinicio</td></tr>
</table>
<p>El <b>idioma</b> (Deutsch/English/Français) se cambia arriba, en la sección «Tiempos» — se aplica tanto a la aplicación web como al OLED.</p>

<h2 id=netz>6. Red, hora, idioma, actualizaciones</h2>
<ul>
<li><b>Hora:</b> El reloj se ajusta mediante un servidor de tiempo de Internet (NTP); el servidor se cambia en la sección «Red».</li>
<li><b>IP:</b> Por defecto es DHCP (automático). Una IP fija se activa después de un reinicio.</li>
<li><b>Actualizaciones (OTA):</b> Firmware nuevo sin cable — sección <b>Servicio → Actualización de firmware</b>, sube ahí la <b>ota.bin</b> de la nueva versión. El aparato se reinicia después.</li>
</ul>

<h2 id=iobroker>7. Integración con ioBroker</h2>
<p>El aparato es el lado hardware de un alimentador automático y se integra bien en ioBroker:</p>
<ul>
<li><b>Adaptador Shelly:</b> El Shelly 1PM Mini Gen4 externo se integra de forma nativa mediante el adaptador Shelly de ioBroker — el estado de conmutación y la medición de potencia son directamente visibles y controlables ahí.</li>
<li><b>API JSON del aparato:</b> consultable y controlable por REST/script:
<table>
<tr><th>Endpoint</th><th>Función</th></tr>
<tr><td><code>GET /api/status</code></td><td>Estado (versión, relé, tiempo restante, Wi-Fi …)</td></tr>
<tr><td><code>POST /api/trigger?ch=1|2|3</code></td><td>Activar temporizador</td></tr>
<tr><td><code>POST /api/stop</code></td><td>detener todos los temporizadores</td></tr>
<tr><td><code>POST /api/config?...</code></td><td>configurar tiempos</td></tr>
</table></li>
</ul>
<p>Para la planificación horaria y un panel de control ya preparado existen los adaptadores correspondientes del mismo autor:</p>
<ul>
<li><a href="https://github.com/ssbingo/ioBroker.automatic-feeder">ioBroker.automatic-feeder</a> — planificación horaria, modelo de temperatura, amanecer/atardecer, pausas, notificaciones.</li>
<li><a href="https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder">ioBroker.vis-2-widgets-automatic-feeder</a> — widgets de panel vis-2 ya preparados (visualización + control remoto).</li>
</ul>

<h2 id=fehler>8. Solución de problemas</h2>
<table>
<tr><th>Problema</th><th>Solución</th></tr>
<tr><td>Al flashear, <b>el puerto USB parpadea</b> (se conecta/desconecta constantemente)</td><td>El firmware arranca en bucle → el USB se registra una y otra vez. Forzar el modo de descarga: mantener <kbd>BOOT</kbd>, pulsar brevemente <kbd>RESET</kbd>, soltar <kbd>BOOT</kbd>. Luego «Connect», «Erase Flash», flashear de nuevo.</td></tr>
<tr><td><b>No aparece la red Wi-Fi</b> «Feeder-Relais Setup»</td><td>Normalmente falta de corriente → bucle de reinicio. Conectar a una <b>fuente de 5 V robusta</b>, esperar ~15 s, buscar de nuevo en el móvil (2,4 GHz). Comprobar que el <b>factory.bin</b> se flasheó en <code>0x0000</code>.</td></tr>
<tr><td><b>La pantalla OLED permanece en negro</b></td><td>¿Está la pantalla bien conectada? Revisar los contactos. (Al construirlo tú mismo: SDA debe ir al pad 7 del ESP, ver el manual completo.)</td></tr>
<tr><td><b>El aparato no responde</b></td><td>Buscar la IP en el router o acceder por IP en lugar de <code>feeder-relais.local</code>. Como último recurso, reiniciar desde <b>Servicio</b>.</td></tr>
</table>

<h2 id=sicher>9. Seguridad &amp; manual completo</h2>
<div class=dang><b>✋ 230 voltios — peligro de muerte</b>El montaje y la conexión de la tensión de red deben quedar en manos de un electricista cualificado. No trabajes nunca en el aparato abierto y bajo tensión.</div>
<p>La <b>guía completa de reconstrucción</b> (componentes, placa, soldadura, KiCad, impresión de la carcasa) la encuentras en línea:</p>
<p><a href="https://ssbingo.github.io/timer-ersatzplatine/">ssbingo.github.io/timer-ersatzplatine</a> · <a href="https://github.com/ssbingo/timer-ersatzplatine">Proyecto en GitHub</a></p>

<p style="margin-top:26px"><a class=totop href="#oben">↑ arriba</a> &nbsp;·&nbsp; <a class=totop href="/">← a la app</a></p>
<p class=lead style="font-size:12px">© 2026 S. Sternitzke · CC BY-NC-SA 4.0</p>

</div></body></html>
)HELP";

static const char HELP_IT[] PROGMEM = R"HELP(
<!doctype html><html lang=it><head><meta charset=utf-8>
<meta name=viewport content="width=device-width,initial-scale=1,viewport-fit=cover">
<title>Feeder-Relais — Manuale</title>
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
 <a href="/">&larr; All'app</a><span class=sp></span>
 <span class=lang><a href="/help?lang=de">🇩🇪 DE</a> <a href="/help?lang=en">🇬🇧 EN</a> <a href="/help?lang=fr">🇫🇷 FR</a> <a href="/help?lang=nl">🇳🇱 NL</a> <a href="/help?lang=es">🇪🇸 ES</a> <a class=on href="/help?lang=it">🇮🇹 IT</a></span>
</div>

<h1 id=oben>Feeder-Relais — Manuale</h1>
<p class=lead>Installazione, configurazione, utilizzo e integrazione con ioBroker. Questa pagina si trova <b>nel dispositivo</b> ed è leggibile anche senza Internet.</p>

<div class=toc>
<b>Indice</b>
<ol>
<li><a href="#was">Cosa fa il dispositivo</a></li>
<li><a href="#flash">Caricare il firmware (primo flash)</a></li>
<li><a href="#wlan">Configurare il Wi-Fi</a></li>
<li><a href="#geraet">Uso del dispositivo</a></li>
<li><a href="#webapp">Uso tramite l'app web</a></li>
<li><a href="#netz">Rete, ora, lingua, aggiornamenti</a></li>
<li><a href="#iobroker">Integrazione con ioBroker</a></li>
<li><a href="#fehler">Risoluzione dei problemi</a></li>
<li><a href="#sicher">Sicurezza &amp; manuale completo</a></li>
</ol>
</div>

<h2 id=was>1. Cosa fa il dispositivo</h2>
<p>Il Feeder-Relais accende un carico a 230 V (ad es. un distributore automatico di cibo) alla pressione di un pulsante per un <b>tempo regolabile</b> e poi lo spegne da solo. Tre pulsanti attivano tre tempi regolabili separatamente. La commutazione vera e propria è affidata a uno <b>Shelly 1PM Mini Gen4 esterno</b>, pilotato dalla scheda tramite un PhotoMOS a isolamento galvanico — la funzione principale funziona quindi <b>senza Wi-Fi</b>.</p>
<figure><svg viewBox="0 0 620 60" role=img aria-label="Catena del segnale">
<style>.b{fill:#1a2232;stroke:#3b82f6}.t{fill:#eef2f8;font:12px sans-serif;text-anchor:middle}.a{stroke:#8595ad;stroke-width:2;marker-end:url(#ah)}</style>
<defs><marker id=ah markerWidth=8 markerHeight=8 refX=7 refY=3 orient=auto><path d="M0,0 L7,3 L0,6 z" fill="#8595ad"/></marker></defs>
<g>
<rect class=b x=4 y=16 width=86 height=28 rx=6/><text class=t x=47 y=34>Pulsante</text>
<line class=a x1=92 y1=30 x2=118 y2=30/>
<rect class=b x=120 y=16 width=96 height=28 rx=6/><text class=t x=168 y=34>ESP32-C3</text>
<line class=a x1=218 y1=30 x2=244 y2=30/>
<rect class=b x=246 y=16 width=96 height=28 rx=6/><text class=t x=294 y=34>PhotoMOS</text>
<line class=a x1=344 y1=30 x2=370 y2=30/>
<rect class=b x=372 y=16 width=110 height=28 rx=6/><text class=t x=427 y=34>Shelly 1PM</text>
<line class=a x1=484 y1=30 x2=510 y2=30/>
<rect class=b x=512 y=16 width=100 height=28 rx=6/><text class=t x=562 y=34>Carico 230 V</text>
</g></svg><figcaption class=lead>La catena del segnale: l'ESP conta il tempo, lo Shelly commuta.</figcaption></figure>

<h2 id=flash>2. Caricare il firmware (primo flash)</h2>
<p>La prima volta l'ESP viene programmato tramite <b>USB e il browser</b> — senza alcuna tensione di rete. Meglio farlo <b>prima</b> di saldarlo.</p>
<div class=warn><b>⚠ Requisiti</b>Un <b>cavo dati USB-C</b> (non un semplice cavo di ricarica!) e <b>Google Chrome</b> oppure <b>Microsoft Edge</b> (Firefox/Safari non supportano Web Serial).</div>
<ol>
<li>Scaricare il file: <b>feeder-relais-vX.Y.Z.factory.bin</b> dalla <a href="https://github.com/ssbingo/timer-ersatzplatine/releases/latest">pagina delle release</a> (sezione «Assets»). Il file <code>factory</code> è l'immagine completa per il primo flash; il file <code>ota</code> serve solo per gli aggiornamenti successivi.</li>
<li>Collegare l'ESP tramite USB-C. In <b>Chrome/Edge</b> aprire lo strumento di flash: <code>https://espressif.github.io/esptool-js/</code></li>
<li>Fare clic su <b>Connect</b> e selezionare la porta dell'ESP. Esito positivo: «Connected to device: ESP32-C3».</li>
<li><b>Impostare Flash Address su <code>0x0000</code></b> (il valore predefinito <code>0x1000</code> è sbagliato!). Come file scegliere <code>factory.bin</code>. Lasciare Flash Mode/Frequency/Size su <code>keep</code>.</li>
<li>Fare clic su <b>Program</b> e attendere la comparsa di «Writing … (100 %)» e «Hard resetting…».</li>
</ol>
<div class=hint><b>ℹ Perché 0x0000?</b><code>0</code>, <code>0x0</code> e <code>0x0000</code> indicano la stessa posizione — l'inizio della memoria. L'immagine <code>factory</code> è completa (bootloader + programma) e deve iniziare proprio all'inizio. Il valore predefinito <code>0x1000</code> sposterebbe tutto → l'ESP non si avvia.</div>
<div class=warn><b>⚠ Nessuna porta / «Failed to connect»?</b>Portare l'ESP in modalità download: tenere premuto <kbd>BOOT</kbd>, premere brevemente <kbd>RESET</kbd>, rilasciare <kbd>BOOT</kbd> — quindi fare di nuovo clic su «Connect». Se il problema persiste, eseguire prima <b>Erase Flash</b>, poi flashare di nuovo.</div>
<div class=tip><b>✓ Consiglio sull'alimentazione</b>Subito dopo il flash, il modulo radio assorbe brevi picchi di corrente. Su una porta USB debole questo può causare il riavvio dell'ESP. Usare un <b>alimentatore da 5 V robusto</b> oppure una porta direttamente sul PC con un cavo corto e spesso.</div>

<h2 id=wlan>3. Configurare il Wi-Fi</h2>
<p>Dopo il primo avvio, l'ESP apre una propria rete Wi-Fi per la configurazione:</p>
<ol>
<li>Sul telefono collegarsi alla rete Wi-Fi <b>Feeder-Relais Setup</b> (password <code>feeder1234</code>).</li>
<li>Si apre una pagina di accesso (in alternativa aprire <code>http://192.168.4.1</code>).</li>
<li>Selezionare la propria <b>rete Wi-Fi domestica</b>, inserire la password, salvare.</li>
</ol>
<p>Dopo di che il dispositivo è raggiungibile nella rete domestica all'indirizzo <code>http://feeder-relais.local</code>.</p>
<div class=hint><b>ℹ Può richiedere un momento</b>Il primo collegamento a volte richiede qualche secondo — è normale.</div>

<h2 id=geraet>4. Uso del dispositivo</h2>
<table>
<tr><th>Pulsante</th><th>breve</th><th>lungo</th></tr>
<tr><td><b>S1</b> Down/Manual</td><td>Attivare il timer 1</td><td>—</td></tr>
<tr><td><b>S2</b> SET</td><td>Attivare il timer 2</td><td>≥ 3 s: menu informazioni (scorrere con S1/S3)</td></tr>
<tr><td><b>S3</b> UP</td><td>Attivare il timer 3</td><td>≥ 1,2 s: fermare tutti i timer</td></tr>
</table>
<p>L'<b>OLED</b> mostra in alto la ricezione Wi-Fi, al centro l'orologio grande o il conto alla rovescia e lo stato (<b>Riposo</b> / <b>Cibo</b>); in basso la data e la memoria libera. Il giorno della settimana, lo stato e i titoli dei menu seguono la lingua impostata.</p>
<p><b>Semaforo di stato</b> (piccolo LED sull'ESP):</p>
<p><span class=led style="background:#22c55e"></span> verde = pronto &nbsp;·&nbsp; <span class=led style="background:#f59e0b"></span> giallo = timer in corso &nbsp;·&nbsp; <span class=led style="background:#ef4444"></span> rosso = guasto</p>

<h2 id=webapp>5. Uso tramite l'app web</h2>
<p>Aprire <code>http://feeder-relais.local</code> nel browser. In basso si passa da una sezione all'altra:</p>
<table>
<tr><th>Sezione</th><th>Funzione</th></tr>
<tr><td><b>Home</b></td><td>stato, attivazione timer 1/2/3, stop</td></tr>
<tr><td><b>Durate</b></td><td>impostare e salvare i tre tempi di commutazione (1–600 s)</td></tr>
<tr><td><b>Rete</b></td><td>cambiare Wi-Fi, IP (DHCP/statico), server orario NTP, nome host, roaming</td></tr>
<tr><td><b>Stato</b></td><td>versione, tempo di funzionamento, Wi-Fi, IP, MAC, causa del riavvio, relè</td></tr>
<tr><td><b>Service</b></td><td>log/debug, aggiornamento firmware (OTA), riavvio</td></tr>
</table>
<p>La <b>lingua</b> (Deutsch/English/Français) si imposta in alto nella sezione «Durate» — vale per l'app web e per l'OLED.</p>

<h2 id=netz>6. Rete, ora, lingua, aggiornamenti</h2>
<ul>
<li><b>Ora:</b> l'orologio viene sincronizzato tramite un server orario Internet (NTP); il server si cambia nella sezione «Rete».</li>
<li><b>IP:</b> l'impostazione predefinita è DHCP (automatico). Un IP fisso diventa attivo dopo un riavvio.</li>
<li><b>Aggiornamenti (OTA):</b> nuovo firmware senza cavo — sezione <b>Service → Aggiornamento firmware</b>, dove caricare la <b>ota.bin</b> della nuova versione. Il dispositivo si riavvia poi automaticamente.</li>
</ul>

<h2 id=iobroker>7. Integrazione con ioBroker</h2>
<p>Il dispositivo è il lato hardware di un distributore automatico di cibo e si integra bene con ioBroker:</p>
<ul>
<li><b>Adattatore Shelly:</b> lo Shelly 1PM Mini Gen4 esterno viene integrato nativamente tramite l'adattatore Shelly di ioBroker — lo stato di commutazione e la misurazione di potenza sono lì direttamente visibili e controllabili.</li>
<li><b>API JSON del dispositivo:</b> interrogabile e controllabile via REST/script:
<table>
<tr><th>Endpoint</th><th>Scopo</th></tr>
<tr><td><code>GET /api/status</code></td><td>stato (versione, relè, tempo rimanente, Wi-Fi …)</td></tr>
<tr><td><code>POST /api/trigger?ch=1|2|3</code></td><td>attivare un timer</td></tr>
<tr><td><code>POST /api/stop</code></td><td>fermare tutti i timer</td></tr>
<tr><td><code>POST /api/config?...</code></td><td>impostare le durate</td></tr>
</table></li>
</ul>
<p>Per la pianificazione oraria e una dashboard già pronta esistono gli adattatori corrispondenti dello stesso autore:</p>
<ul>
<li><a href="https://github.com/ssbingo/ioBroker.automatic-feeder">ioBroker.automatic-feeder</a> — pianificazione oraria, modello di temperatura, alba/tramonto, pause, notifiche.</li>
<li><a href="https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder">ioBroker.vis-2-widgets-automatic-feeder</a> — widget dashboard vis-2 già pronti (visualizzazione + telecomando).</li>
</ul>

<h2 id=fehler>8. Risoluzione dei problemi</h2>
<table>
<tr><th>Problema</th><th>Soluzione</th></tr>
<tr><td>Durante il flash <b>la porta USB sfarfalla</b> (si connette/disconnette di continuo)</td><td>Il firmware si avvia in un ciclo continuo → l'USB si ripresenta di continuo. Forzare la modalità download: tenere premuto <kbd>BOOT</kbd>, premere <kbd>RESET</kbd>, rilasciare <kbd>BOOT</kbd>. Poi «Connect», «Erase Flash», flashare di nuovo.</td></tr>
<tr><td><b>Nessuna rete Wi-Fi</b> «Feeder-Relais Setup» visibile</td><td>Di solito corrente insufficiente → ciclo di riavvio. Collegare un <b>alimentatore da 5 V robusto</b>, attendere ~15 s, cercare di nuovo sul telefono (2,4 GHz). Verificare che il <b>factory.bin</b> sia stato flashato su <code>0x0000</code>.</td></tr>
<tr><td><b>L'OLED resta nero</b></td><td>Il display è inserito correttamente? Controllare i contatti. (Per l'autocostruzione: SDA deve essere collegato al pad 7 dell'ESP, vedere il manuale completo.)</td></tr>
<tr><td><b>Dispositivo non raggiungibile</b></td><td>Cercare l'IP nel router oppure accedere tramite l'IP invece di <code>feeder-relais.local</code>. In caso estremo riavviare tramite <b>Service</b>.</td></tr>
</table>

<h2 id=sicher>9. Sicurezza &amp; manuale completo</h2>
<div class=dang><b>✋ 230 volt — pericolo di morte</b>Il montaggio e il collegamento alla tensione di rete devono essere affidati a un elettricista qualificato. Non lavorare mai sul dispositivo aperto e sotto tensione.</div>
<p>La <b>guida completa all'autocostruzione</b> (componenti, scheda, saldatura, KiCad, stampa del case) è disponibile online:</p>
<p><a href="https://ssbingo.github.io/timer-ersatzplatine/">ssbingo.github.io/timer-ersatzplatine</a> · <a href="https://github.com/ssbingo/timer-ersatzplatine">Progetto su GitHub</a></p>

<p style="margin-top:26px"><a class=totop href="#oben">↑ su</a> &nbsp;·&nbsp; <a class=totop href="/">← all'app</a></p>
<p class=lead style="font-size:12px">© 2026 S. Sternitzke · CC BY-NC-SA 4.0</p>

</div></body></html>
)HELP";


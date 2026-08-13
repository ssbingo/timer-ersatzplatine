# Feeder-Relais

**230-V-Timer-Steuerung zum Selbstbau — ESP32-C3 · OLED · PhotoMOS · externer Shelly 1PM Mini Gen4**

Das Feeder-Relais ist eine selbstgebaute Steuerplatine, die eine 230-Volt-Last
auf Knopfdruck für eine **einstellbare Zeit** einschaltet und danach von allein
wieder abschaltet. Der Name stammt aus dem ursprünglichen Einsatz: Sie ersetzt
die defekte Zeitschaltplatine eines **Futterautomaten** (englisch *feeder*).
Weil sie im Kern nur „einen Schalter für eine gewisse Zeit drückt“, eignet sie
sich für jede Last, die zeitgesteuert geschaltet werden soll — Pumpe,
Futtermotor, Lüfter, Licht.

Drei Taster lösen drei getrennt einstellbare Zeiten aus (Standard 5/10/15 s),
ein OLED zeigt WLAN, Uhrzeit und den Countdown, und eine für Handys optimierte
Weboberfläche erlaubt Bedienung und Konfiguration im Heimnetz — **ohne App und
ohne Cloud**. Das eigentliche Schalten und die Leistungsmessung übernimmt ein
**externer Shelly 1PM Mini Gen4**; die Platine steuert dessen SW-Eingang über ein
**PhotoMOS-Relais galvanisch getrennt** an. Dadurch ist die Kernfunktion
**WLAN-unabhängig**.

> ### ⚠️ 230 Volt — Lebensgefahr
> Netzspannung kann tödlich sein. Aufbau, Prüfung und Inbetriebnahme der
> 230-V-Seite gehören in die Hände einer **Elektrofachkraft** oder unterwiesenen
> Person. Alle Tests, die ohne Fachkraft möglich sind, laufen **ausschließlich
> über USB und ohne jede Netzspannung**. Bitte zuerst Kapitel 2 des Handbuchs
> lesen.

---

## 🌍 Sprachen · Languages

| Sprache | README | Handbuch (PDF) |
|--------|--------|----------------|
| 🇩🇪 **Deutsch** (Original) | [README.md](README.md) | [docs/handbuch/Feeder-Relais-Handbuch.pdf](docs/handbuch/Feeder-Relais-Handbuch.pdf) |
| 🇬🇧 English | [docs/en/README.md](docs/en/README.md) | [docs/en/Feeder-Relais-Manual.pdf](docs/en/Feeder-Relais-Manual.pdf) |
| 🇫🇷 Français | [docs/fr/README.md](docs/fr/README.md) | [docs/fr/Feeder-Relais-Manuel.pdf](docs/fr/Feeder-Relais-Manuel.pdf) |
| 🇳🇱 Nederlands | [docs/nl/README.md](docs/nl/README.md) | [docs/nl/Feeder-Relais-Handleiding.pdf](docs/nl/Feeder-Relais-Handleiding.pdf) |
| 🇪🇸 Español | [docs/es/README.md](docs/es/README.md) | [docs/es/Feeder-Relais-Manual.pdf](docs/es/Feeder-Relais-Manual.pdf) |
| 🇮🇹 Italiano | [docs/it/README.md](docs/it/README.md) | [docs/it/Feeder-Relais-Manuale.pdf](docs/it/Feeder-Relais-Manuale.pdf) |

---

## Inhalt

1. [Überblick](#überblick)
2. [Die Signalkette](#die-signalkette)
3. [Die Platine (Hardware v2)](#die-platine-hardware-v2)
4. [Die Firmware](#die-firmware)
5. [Bedienung](#bedienung)
6. [Das Gehäuse (3D-Druck)](#das-gehäuse-3d-druck)
7. [Anbindung an ioBroker](#anbindung-an-iobroker)
8. [Nachbau & Handbuch](#nachbau--handbuch)
9. [Projektstruktur](#projektstruktur)
10. [Status](#status)
11. [Lizenz](#lizenz)

---

## Überblick

Das Gerät ersetzt eine originale Timer-Platine hinter einer vorhandenen
Frontplatte. Es besteht aus vier gut trennbaren Bausteinen:

- **Platine** (`kicad-v2/`) — ESP32-C3, Netzteil, PhotoMOS und die 230-V-Klemmen,
  vierlagig, gesamte Elektronik auf der Rückseite.
- **Firmware** (`firmware/`) — ESPHome-Projekt mit eigener Mobil-Web-App,
  JSON-Schnittstelle, NTP-Uhr, OLED-Anzeige, Status-LED und mehrsprachiger
  Bedienung.
- **Gehäuse** (`box/`) — 3D-gedrucktes Rückteil (35 mm tief), das Platine *und*
  den externen Shelly aufnimmt; das Vorderteil ist die vorhandene Frontplatte.
- **Externer Shelly 1PM Mini Gen4** — das zertifizierte Schaltrelais mit
  Leistungsmessung, außerhalb der Platine verdrahtet.

Die **Aufgabenteilung** ist der Kern des Konzepts: Der ESP misst die Zeit und
gibt ein galvanisch getrenntes Hardware-Signal an den Shelly; der Shelly schaltet
die Last und misst die Leistung. Fällt das WLAN aus, laufen Tasten, Timer und
Schalten trotzdem weiter — nur die Fernbedienung ruht.

## Die Signalkette

Vom Tastendruck bis zur geschalteten Last durchläuft das Signal fünf Stationen,
jede mit genau einer Aufgabe:

```
Taste  ─►  ESP32-C3  ─►  330 Ω  ─►  PhotoMOS  ─►  Shelly 1PM  ─►  Last
S1–S3      zählt die     begrenzt    schaltet      schaltet und     (Pumpe,
           Zeit, malt    den LED-    galvanisch     misst die        Futter-
           das OLED      Strom       getrennt       230-V-Last       motor …)
```

Der ESP arbeitet mit ungefährlichen 3,3 V und darf 230 V niemals direkt berühren.
Der **PhotoMOS** ist die Brücke: Er trennt Klein- und Netzspannung vollständig
durch *Licht*. Der Shelly wird auf **Switch/Follow** gestellt — sein Relais ist
genau so lange an, wie unser Signal anliegt; das gesamte Timing bleibt beim ESP.

## Die Platine (Hardware v2)

Die aktuelle Version 2 liegt fertig als KiCad-Projekt unter `kicad-v2/`.

- **Außenmaß** 101,6 × 77,5 mm, **vierlagig** (1,6 mm).
- **Gesamte Elektronik auf der Rückseite** — vorne bleiben nur die drei Taster
  und die OLED-Buchse (alles, was bedient oder gesehen wird).
- Die beiden **Innenlagen sind durchgehende Masseflächen** im
  Kleinspannungsbereich → störungsarm, stabiles WLAN.
- **Netzspannung nur außen:** Die fünf 230-V-Netze liegen ausschließlich auf den
  Außenlagen, unten links, in einer eigenen Netzklasse mit breiteren Bahnen.
- **6-mm-Kriechstrecke** zwischen jedem 230-V-Netz und jeder Kleinspannung — als
  feste KiCad-Prüfregel (`.kicad_dru`) hinterlegt. Einzige Ausnahme ist das
  PhotoMOS K1: Sein Gehäuse *ist* die zertifizierte Trennstelle.

### GPIO-Belegung — verbindlicher Abgleich Platine ↔ Firmware

Diese Zuordnung muss auf beiden Seiten exakt übereinstimmen, sonst funktioniert
das Gerät nicht:

| ESP-Pin | Firmware | Platine / Netz | Funktion |
|---------|----------|----------------|----------|
| **GPIO3** | `btn_s1` (Eingang, Pull-up, invertiert) | Pad 3 → `/BTN1` | Taster **S1 Down/Manual** (T1) → Timer 1 |
| **GPIO4** | `btn_s2` | Pad 4 → `/BTN2` | Taster **S2 SET** (T2) → Timer 2 / lang: Menü |
| **GPIO5** | `btn_s3` | Pad 5 → `/BTN3` | Taster **S3 UP** (T3) → Timer 3 / lang: Stop |
| **GPIO6** | `shelly_trigger` (Ausgang) | Pad 6 → `/PMOS_DRV` → R1 330 Ω → K1-LED | PhotoMOS-Treiber: HIGH = Last ein |
| **GPIO7** | `i2c: sda` (400 kHz) | Pad 7 → `/SDA` → OLED J2.4 | I²C-Datenleitung zum OLED |
| **GPIO8** | `status_led` (WS2812, GRB) | modulintern (Pad 8 frei) | Onboard-RGB-Status-LED (Ampel) |
| **GPIO9** | `i2c: scl` (400 kHz) | Pad 9 → `/SCL` → OLED J2.3 | I²C-Taktleitung zum OLED (Adresse 0x3C) |
| **5V / GND** | Modulversorgung | `/+5V` / `GND` vom Netzteil | Versorgung + gemeinsame Masse |
| **3V3** | Onboard-Regler | `/+3V3` → OLED-VCC | 3,3 V für das OLED |

> **Wichtig:** SDA liegt bewusst auf **GPIO7**, nicht GPIO8 — auf GPIO8 sitzt die
> Onboard-WS2812. Läge dort I²C, bliebe das OLED schwarz und der Datenverkehr
> würde die LED stören.

### Anschlussklemmen und Netze

| Klemme | Anschluss | Belegung |
|--------|-----------|----------|
| **X1** | Netzeingang | 1 = N, 2 = L_IN (230 V herein) |
| **X2** | Lastabgang | 1 = O (geschaltet), 2 = N |
| **X3** | Snubber | 1 = O, 2 = N — optionales RC-Glied für induktive Lasten |
| **J1** | Shelly (extern) | 1 = SW, 2 = O, 3 = L, 4 = N |
| **J2** | OLED | GND / VCC / SCL / SDA (aufgesteckt) |

Die fünf 230-V-Netze der Netzklasse „230V“: `L_IN` (ungesichert, X1→F1),
`L_F` (abgesichert, F1→RV1/PS1/K1.3/Shelly-L), `N` (Neutral), `SW_SHELLY`
(geschaltet, K1.4→Shelly-SW) und `O_LAST` (geschaltet, Shelly-O→X2/X3).

### Wichtige Bauteile

| Kennung | Bauteil | Funktion |
|---------|---------|----------|
| **U1** | ESP32-C3 Super Mini | Mikrocontroller mit WLAN, 5 V→3,3 V; trägt die WS2812 auf GPIO8 |
| **K1** | PhotoMOS G3VM-601AY2 (o. -601BY / AQY216) | Galvanische Trennung 3,3 V ↔ 230 V, **≥ 400 V** |
| **PS1** | AC/DC-Modul TSP-05 (5 V / 3 W) | Netzteil aus L_F + N |
| **R1** | 330 Ω | Vorwiderstand der K1-LED (~6 mA) |
| **C1 / C2** | 220 µF / 100 nF | 5-V-Puffer (WLAN-Spitzen) + Abblockung |
| **F1** | 1 A träge, 5×20 mm | primärseitige Feinsicherung (X1→F1→L_F) |
| **RV1** | Varistor S14K275 | Überspannungsschutz zwischen L_F und N |
| **SW1–3** | Taster 6×6 mm | die drei Kurzhubtaster (Position fix, Frontplatte) |

## Die Firmware

Die Firmware ist ein **ESPHome**-Projekt (`firmware/timer-relais-c3.yaml`) mit
eigenen C++-Erweiterungen. Gerätename/Hostname: **`feeder-relais`**
(→ `http://feeder-relais.local`).

- **Timer-Logik:** drei unabhängige Zeiten (1–600 s), im laufenden Betrieb per
  Web änderbar; kurzer Tastendruck startet, langer Druck auf UP stoppt alles.
- **Eigene Mobil-Web-App + JSON-API** (`firmware/timer_web.h`) auf Port 80 —
  kein Cloud-Dienst. Endpunkte: `/api/status`, `/api/trigger`, `/api/stop`,
  `/api/config`, `/api/net`, `/api/wifi`, `/api/reboot`.
- **OLED-Anzeige** (SSD1306 128×32): WLAN-Empfang, große NTP-Uhr, Datum, freier
  Speicher; im Timerlauf der Sekunden-Countdown. Anzeige um 180° gedreht (an die
  Einbaulage angepasst).
- **Status-Ampel** über die Onboard-WS2812 (GPIO8): **grün** = bereit,
  **gelb** = Timer läuft, **rot** = Störung.
- **Netzwerk-Konfiguration zur Laufzeit** (`firmware/net_config.h`): IP-Modus
  DHCP/statisch, NTP-Server, Hostname, 802.11k/v-Roaming.
- **Mehrsprachig** (Web + OLED): Deutsch / Englisch / Französisch, geräteweit
  umschaltbar.
- **Provisioning per Captive-Portal** — kein WLAN-Passwort einkompiliert; die
  Zugangsdaten überstehen ein Update.
- **Drahtlose Updates (OTA)** über `web_server`-Plattform (`POST /update`) sowie
  ein Log-/Debug-Ringpuffer (`/api/log`).

Fertige Flash-Images (factory + OTA) liegen unter `firmware/build/`.

## Bedienung

**Am Gerät** — drei Taster:

| Taste | kurz | lang |
|-------|------|------|
| **S1** Down/Manual | Timer 1 auslösen | — |
| **S2** SET | Timer 2 auslösen | ≥ 3 s: Info-Menü (mit S1/S3 blättern) |
| **S3** UP | Timer 3 auslösen | ≥ 1,2 s: alle Timer stoppen |

**Mobil** — im Browser `http://feeder-relais.local`: Timer auslösen, die drei
Zeiten einstellen, Netzwerk- und Statuswerte einsehen, Sprache wählen.

## Das Gehäuse (3D-Druck)

Das Gehäuse besteht aus dem vorhandenen **Vorderteil** (Originalfrontplatte mit
Sichtfenster und Tast-Stößeln) und einem selbst gedruckten **Rückteil**:

- **Produktionsgehäuse:** `box/feeder_back_Shelly_35mm.stl` — das zu druckende
  Rückteil **mit integrierten Halterungen für den Shelly und den Snubber**.
- Basis-/Parametervariante: `box/feeder_back.scad` (OpenSCAD) → `box/feeder_back_35mm.stl`
  (ohne Shelly-/Snubber-Halter), zum Anpassen der Maße.
- **35 mm tief** (statt originaler 5,7 mm), damit Platine *und* Shelly hineinpassen;
  Außenmaß 109,8 × 90,8 mm.
- Wandaufbau: Dichtkante oben **1,3 mm**, verstärkte Außenwand darunter **2,5 mm**,
  Boden **2,5 mm**. Sechs Schraubdome (Raster 45 × 70 mm) mit tiefem Senkkanal für
  die kurzen Originalschrauben; Aufhängelasche mit Schlüsselloch.
- `box/Timer-Ersatzplatine-v2-BOARD.stl` ist eine **1:1-Attrappe** der Platine —
  flach drucken und einlegen, um die Passung zu prüfen, **bevor** die echte
  Platine bestellt wird.

## Anbindung an ioBroker

Das Feeder-Relais ist die **Hardware-Seite** eines Futterautomaten und lässt sich
gut in eine Hausautomatisierung einbinden:

- Der **externe Shelly 1PM Mini Gen4** wird in ioBroker über den
  **Shelly-Adapter** nativ eingebunden — Schaltzustand und Leistungsmessung sind
  dort direkt sichtbar und steuerbar.
- Die **eigene JSON-API** des Geräts (`/api/status | trigger | stop | config`)
  lässt sich per REST/Skript (z. B. `simple-api`, JavaScript-Adapter) auslesen
  und bedienen — für Timer-Auslösung und Statusabfrage.

Im selben „Smart-Pond/Feeder“-Umfeld gibt es zwei passende Adapter desselben
Autors, die die **Software-Seite** bilden:

- **[ioBroker.automatic-feeder](https://github.com/ssbingo/ioBroker.automatic-feeder)**
  — Zeitplanung, Temperaturmodell, Sonnenauf-/-untergang, Pausen und
  Benachrichtigungen für einen Fisch-/Koi-/Teichfutterautomaten.
- **[ioBroker.vis-2-widgets-automatic-feeder](https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder)**
  — fertige vis-2-Dashboard-Widgets (Live-Ansicht und Fernbedienung) für den
  Adapter oben.

So bildet die Hardware (dieses Gerät + Shelly) zusammen mit den beiden Adaptern
eine durchgängige Kette von der Taste bis zum Dashboard.

## Nachbau & Handbuch

Ein **vollständiges, anfängertaugliches Handbuch** führt Schritt für Schritt vom
leeren Board bis zum fertigen Gerät — mit Sicherheit, Einkaufsliste,
Platinenfertigung, Bestückung, Firmware-Flashen und Inbetriebnahme, inklusive
klickbarem Inhaltsverzeichnis:

**➡️ [docs/handbuch/Feeder-Relais-Handbuch.pdf](docs/handbuch/Feeder-Relais-Handbuch.pdf)**
(Übersetzungen siehe [Sprachen-Tabelle](#-sprachen--languages) oben.)

Firmware flashen (ESP per USB-C):

```bash
esphome run firmware/timer-relais-c3.yaml
```

## Projektstruktur

```
kicad-v2/     Platine v2 (KiCad: Schaltplan, Layout, 6-mm-Regel, Footprints, 3D-Modelle)
box/          Gehäuse-Rückteil (OpenSCAD-Quelle + STL) und Platinen-Attrappe
firmware/     ESPHome-Firmware (.yaml + .h), fertige Flash-Images in build/
docs/         Handbuch-PDF (deutsch) und Übersetzungen unter docs/<sprache>/
README.md     dieses Dokument (deutsch; Übersetzungen unter docs/<sprache>/)
```

## Status

**Version 2 fertig entwickelt — vor der Fertigung.** Platine 4-lagig geroutet
(DRC ohne echte Fehler), Board ↔ Firmware abgeglichen (OLED-SDA auf GPIO7),
Gehäuse und Dokumentation fertig. Offen: Gerber frisch erzeugen, Passprobe der
Attrappe, 4-Lagen-Bestellung, Aufbau und Funktionstest.

## Lizenz

Dieses Projekt (Hardware, Firmware, Gehäuse und Dokumentation) steht unter der
Lizenz **Creative Commons Namensnennung – Nicht kommerziell – Weitergabe unter
gleichen Bedingungen 4.0 International (CC BY-NC-SA 4.0)**.

© 2026 Silvio Sternitzke

Es steht dir frei:

- **Teilen** — das Material vervielfältigen und weiterverbreiten,
- **Bearbeiten** — es umgestalten und darauf aufbauen,

unter den folgenden Bedingungen:

- **Namensnennung (BY)** — nenne den Urheber, verlinke die Lizenz und gib an, ob
  Änderungen vorgenommen wurden.
- **Nicht kommerziell (NC)** — nicht für kommerzielle Zwecke.
- **Weitergabe unter gleichen Bedingungen (SA)** — Bearbeitungen müssen unter
  derselben Lizenz weitergegeben werden.
- **Keine weiteren Einschränkungen** — keine zusätzlichen Klauseln oder
  technischen Maßnahmen, die anderen etwas rechtlich Erlaubtes verwehren.

Lizenztext: <https://creativecommons.org/licenses/by-nc-sa/4.0/deed.de> ·
vollständiger Rechtstext siehe [LICENSE](LICENSE).

> **Haftungsausschluss:** Der Nachbau erfolgt auf eigene Verantwortung.
> 230 Volt sind lebensgefährlich. Das Material wird ohne Gewähr bereitgestellt;
> jede Haftung für Schäden ist ausgeschlossen. Im Zweifel eine Elektrofachkraft
> hinzuziehen.

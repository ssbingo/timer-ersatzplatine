# Timer-Ersatzplatine — Vollständige Dokumentation

**Projekt:** Ersatz einer defekten/veralteten Timer-Steuerplatine durch eine
Eigenentwicklung mit ESP32-C3, OLED-Display, WLAN-Konfiguration und
Shelly 1PM Mini Gen4 als Leistungsschalter.

**Stand:** 2026-07-13 · Vorlagenversion v8 · Phase: Verifikation vor Layout
**Autor:** Silvio (Hardware/Messung) + Claude (Auswertung/Konstruktion)

---

## 1. Was das Gerät tut (Funktionsbeschreibung)

Das Gerät hat drei Taster an der Frontseite. Ein Druck auf einen Taster
schaltet eine 230-V-Last für eine einstellbare Zeit ein:

| Taster | Standardzeit | einstellbar |
|--------|--------------|-------------|
| T1     | 5 Sekunden   | 1–600 s über WLAN |
| T2     | 10 Sekunden  | 1–600 s über WLAN |
| T3     | 15 Sekunden  | 1–600 s über WLAN |

Ein kleines OLED-Display hinter der Sichtscheibe zeigt im Ruhezustand
**„ON"** und während eines Laufs den **Sekunden-Countdown**. Ein erneuter
Tastendruck während des Laufs startet die zugehörige Zeit neu.

Die drei Zeiten werden **ohne App und ohne Cloud** über eine Webseite
eingestellt, die der ESP32 selbst bereitstellt (im Browser
`http://timer-relais.local` aufrufen). Optional kann das Gerät in
Home Assistant oder ioBroker (esphome-Adapter) eingebunden werden.

### 1.1 Die Signalkette (so fließt das Signal)

```
Taster ──> ESP32-C3 ──> Vorwiderstand 330 Ω ──> PhotoMOS-Relais ──> Shelly
(T1–T3)    (zählt die     (begrenzt den           (schaltet 230-V-      SW-Eingang
            Zeit, steuert  LED-Strom im            Signal galvanisch     │
            das OLED)      PhotoMOS)               getrennt)             ▼
                                                                    Shelly-Relais
                                                                    schaltet Last (O)
```

**Warum ein Shelly?** Der Shelly 1PM Mini Gen4 übernimmt das eigentliche
Schalten der Last, misst dabei die Leistung und ist zusätzlich per
WLAN/App erreichbar. Unsere Platine „drückt" für den Shelly nur den
Schalter — als echtes Hardware-Signal, **ohne WLAN-Abhängigkeit** für die
Kernfunktion.

**Was ist ein PhotoMOS?** Ein winziges Halbleiterrelais: Auf der einen
Seite eine LED (die der ESP mit 3,3 V ansteuert), auf der anderen Seite
ein lichtgesteuerter Schalter, der Netzspannung schalten darf. Dazwischen
liegt nur Licht — also eine vollständige galvanische Trennung zwischen
Kleinspannung und 230 V. Der SW-Eingang des Shelly ist netzspannungs-
bezogen (erwartet geschaltetes L), deshalb **zwingend ein Typ mit
≥ 400 V Sperrspannung** (z. B. Omron G3VM-601BY oder Panasonic AQY216).
Ein gewöhnlicher Optokoppler (PC817) ist hier **nicht** zulässig.

Der Shelly wird auf Eingangsmodus **„Schalter/Follow"** konfiguriert:
sein Relais ist genau so lange an, wie der ESP das Signal hält. Das
Timing liegt vollständig beim ESP.

---

## 2. Sicherheit — bitte zuerst lesen

- Das Gerät arbeitet mit **230 V Netzspannung. Lebensgefahr!** Aufbau,
  Prüfung und Inbetriebnahme gehören in die Hände einer Person mit
  entsprechender Qualifikation (Elektrofachkraft oder unterwiesen).
- Erste Funktionstests von ESP, Tastern und OLED erfolgen **ausschließlich
  über USB** — dabei ist keinerlei Netzspannung verbunden (siehe Testplan
  im Projektplan).
- Der erste 230-V-Test erfolgt hinter einem **RCD/PRCD (Personenschutz-
  stecker)**, Gehäuse geschlossen, niemals unter Spannung im offenen
  Gerät hantieren.
- Auf der Platine gilt: zwischen allen 230-V-Netzen und der Kleinspannung
  **mindestens 6 mm Abstand** (Kriechstrecke), Details in Kap. 7.6.
- Sicherung (1 A träge) und Varistor vor dem Netzteilmodul sind Pflicht —
  die Module (TSP-05/HLK) bringen beides nicht selbst mit.

---

## 3. Stückliste (BOM)

| Ref | Bauteil | Wert / Typ | Bemerkung |
|-----|---------|-----------|-----------|
| U1  | ESP32-C3 Super Mini | 18 × 24 mm, USB-C | Controller, WLAN |
| U2  | PhotoMOS-Relais | Omron G3VM-601BY **oder** Panasonic AQY216 | ≥ 400 V! SOP-4/DIP-4 |
| PS1 | AC/DC-Modul | TENSTAR TSP-05 (5 V / 3 W) | HLK-PM05-Klon, 34,7 × 20,5 × 15,05 mm, **Pinabstände nachmessen!** |
| —   | Shelly 1PM Mini Gen4 | S4SW-001P8EU | 29 × 34 × 16 mm, max. 8 A/240 V |
| —   | OLED-Display | 0,91" SSD1306, 128 × 32, I2C | Modul 38 × 12 mm, Pins: GND VCC SCL SDA, Adresse 0x3C |
| SW1–3 | Kurzhubtaster | 6 × 6 mm, Hub 1,5 mm | Pinbild 6,9 × 4,4 mm (aus Original vermessen) |
| R1  | Widerstand | 330 Ω, axial | LED-Vorwiderstand PhotoMOS |
| F1  | Feinsicherung | 1 A träge, 5 × 20 mm + Halter | primärseitig |
| RV1 | Varistor | S14K275 | primärseitig parallel |
| C1  | Elko | 220 µF / 10 V | 5-V-Puffer für WLAN-Stromspitzen |
| C2  | Kerko | 100 nF | 5-V-Abblockung |
| J1  | Netzklemme | 2-polig (L, N) | Schraubklemme oder Lötpads |
| J2  | Shelly-Anschluss | 4 Lötpads/Stifte | L, N, SW, O — kurze Litzen zu den Shelly-Schraubklemmen |
| J3  | Lastabgang | 2-polig | O (geschaltet), N |
| J4  | OLED-Buchse | Buchsenleiste 1 × 4, RM 2,54 | Bauhöhe nach Stackmessung (~11 mm), Kap. 5.6 |
| —   | Stiftleiste 1 × 4 | RM 2,54 | wird ans OLED gelötet (nach hinten) |
| —   | Montagematerial | 3M-VHB-Klebeband o. 3D-Clip | Befestigung Shelly + TSP |

---

## 4. Gehäuse und Mechanik

### 4.1 Das Koordinatensystem (wichtig für alles Weitere!)

Alle Maße beziehen sich auf die **obere linke Ecke der ORIGINALPLATINE**,
x nach rechts, **y nach unten**, Blick auf die **Bestückungsseite**
(Taster oben). Die neue, größere Platine ragt über diesen Ursprung
hinaus — deshalb gibt es **negative Koordinaten**. Vorteil: Alle je
gemessenen Werte bleiben für immer gültig, egal wie die Kontur wächst.

### 4.2 Randbedingungen aus dem Gehäuse (gemessen/abgeleitet)

| Größe | Wert | Quelle |
|-------|------|--------|
| Innere Gesamthöhe | 19,9 mm | Messung Silvio |
| Rahmenhöhe (Frontplatte) | 2 mm | Messung Silvio |
| Bauraum **über** der Platine | **16,5 mm** | Messung Silvio (Platine ↔ Front) |
| Platinenstärke | 1,6 mm | Standard |
| Raum **unter** der Platine | **≈ 1,8 mm** | 19,9 − 16,5 − 1,6 → nichts darf nach unten ragen! |
| Höhenlimit im Fensterbereich | **≈ 12 mm** | Glas + davor gestecktes OLED |
| Platinenbefestigung | 4 Schrauben auf 16,5-mm-Domen an der Frontplatte | mit Stabilisierungsstegen zum Rand |
| Gehäuseverschraubung | 6 Schrauben außenliegend | Platine braucht ⌀10-Durchführungen |

### 4.3 Finale Platinengeometrie (Vorlage v8)

Alle Werte stehen **maschinenlesbar** in `hardware/platine_template.py`
(die einzige Quelle der Wahrheit!). Zusammenfassung:

| Element | Koordinaten (mm) | Genauigkeit |
|---------|------------------|-------------|
| Kontur | x −14,2…91,1 / y −11,8…67,6 → **105,3 × 79,4**, Eckenradius 4 | ±1 (links ±1,5) |
| 4 Befestigungslöcher ⌀3,0 | (3,8/4,1) (73,1/4,0) (3,7/39,6) (73,4/50,7) | ±0,3 |
| 6 Dom-Ausschnitte ⌀10 | B1 (82,7/−7,9) · B2 (37,9/−8,6) · B3 (−6,5/−6,9) · B4 (82,7/61,7) · B5 (38,8/62,8) · B6 (−7,0/62,3) | ±1,5 → **anprobieren** |
| Taster T1/T2/T3 (Zentren) | (13,2/12,3) (38,8/12,2) (64,1/12,0) | ±0,3 |
| Sichtfenster (Referenz) | x 18,4…53,6 / y 23,3…40,0 | ±1 |
| J4 OLED-Buchse (4 Pins senkr.) | Pins bei x = 15,0, y = 27,84 / 30,38 / 32,92 / 35,46 | Annahmen prüfen, Kap. 5.6 |
| Stellfläche Shelly | x 56…90 / y 16,5…45,5 (liegend) | — |
| Stellfläche ESP32-C3 | x 8,5…32,5 / y −10…8 (quer, USB nach oben) | — |
| Stellfläche TSP-05 | x −1,5…33,2 / y 44,2…64,7 (AC-Seite nach links) | — |
| Keepouts (Referenz) | ⌀8 um die 4 Schraubenköpfe + 5 Steg-Bänder | Stegrichtungen = Annahme! |

**Woher stammen die Werte?** Lötseiten-Scan der Originalplatine (300 dpi,
entdreht, gespiegelt) für Taster/Löcher/Kontur; Gehäusescan, registriert
über die 4 Rahmenschrauben (Spiegel-Transformation
`x_platine = 110,5 − x_gehäuse`, `y_platine = y_gehäuse − 16,4`, ±0,4 mm);
Fensterposition aus dem perspektivisch entzerrten Foto.

### 4.4 Die alte Aussparung

Die trapezförmige Aussparung an der Unterkante der Originalplatine war
die Freistellung des mittleren unteren Schraubdoms (B5). Sie ist in der
neuen Platine **durch den ⌀10-Kreisausschnitt B5 ersetzt** und entfällt.

---

## 5. Elektrik im Detail

### 5.1 Übersicht der Netze (Verbindungen)

| Netzname | führt | verbindet |
|----------|-------|-----------|
| L_IN | 230 V | Netzklemme J1.L → Sicherung F1 |
| L_F | 230 V (abgesichert) | F1 → Varistor, TSP-05 AC, PhotoMOS OUT1, Shelly L |
| N | 230 V Neutral | J1.N → Varistor, TSP-05 AC, Shelly N, Last J3 |
| SW_SHELLY | 230 V geschaltet | PhotoMOS OUT2 → Shelly SW |
| O_LAST | 230 V geschaltet | Shelly O → Lastabgang J3 |
| +5V | Kleinspannung | TSP-05 +Vo → ESP 5V, C1, C2 |
| GND | Kleinspannung | TSP-05 −Vo → ESP GND, Taster, PhotoMOS K, OLED |
| +3V3 | Kleinspannung | ESP-3V3-Ausgang → OLED VCC |
| BTN1/2/3 | Signal | Taster → GPIO3/4/5 (interne Pullups) |
| PMOS_DRV → PMOS_A | Signal | GPIO6 → R1 330 Ω → PhotoMOS-Anode |
| SDA / SCL | I2C | GPIO8 / GPIO9 → OLED |

### 5.2 ESP32-C3-Super-Mini-Pinbelegung

| Pin | Funktion | Anmerkung |
|-----|----------|-----------|
| 5V / G | Versorgung | vom TSP-05 |
| 3V3 | Ausgang des Onboard-LDO | versorgt das OLED |
| GPIO3 | Taster T1 | Pullup intern, Taster nach GND |
| GPIO4 | Taster T2 | dito |
| GPIO5 | Taster T3 | dito |
| GPIO6 | PhotoMOS-Treiber | high = Shelly ein |
| GPIO8 | SDA | auf dem Modul so beschriftet |
| GPIO9 | SCL | dito |

Bewusst vermieden: GPIO2/8/9 als Taster (Strapping-Pins — GPIO8/9 sind
mit I2C-Pullups bootkompatibel, als Tastereingänge wären sie riskant).

### 5.3 Shelly 1PM Mini Gen4

- Klemmen: **SW** (Schalteingang), **O** (Lastausgang), **L**, **N**.
- Versorgung 110–240 V~, Relais max. 8 A / 2000 W @ 240 V.
- Konfiguration nach Inbetriebnahme: *Input Mode = Switch (Follow)*,
  damit das Relais dem SW-Signal 1:1 folgt.
- Montage: liegend auf der Stellfläche, VHB-Klebeband oder 3D-Clip.
  Vier kurze Litzen (z. B. 0,75 mm², 6–7 mm abisoliert) von den
  Schraubklemmen zu den J2-Pads.

### 5.4 Netzteil TSP-05

100–240 V~ → 5 V DC / 3 W (= 600 mA). Reicht für ESP-WLAN-Spitzen
(~350 mA) plus OLED mit Reserve. **Offen: Pinabstände mit Messschieber
gegen den KiCad-Footprint `Converter_ACDC_HiLink_HLK-PMxx` prüfen**
(Klon ist üblicherweise pinkompatibel — bei 230 V nichts annehmen).

### 5.5 Taster

Die drei 6×6-Kurzhubtaster (1,5 mm Hub) werden von Stößeln in der
Frontplatte betätigt — ihre Position ist deshalb **nicht verhandelbar**
(auf ±0,2 mm bestücken). Pinbild je Taster: 6,9 mm × 4,4 mm.

### 5.6 OLED — Steckmontage („Stack")

Das OLED wird **nicht verlötet**, sondern **auf J4 aufgesteckt**:
Buchsenleiste 1×4 auf der Platine, Stiftleiste am OLED nach hinten,
Display-Face liegt (mit dünnem Schaumstoffpad) an der Glasscheibe an.

- Belegung J4 von oben nach unten: **GND, VCC (3V3), SCL, SDA** —
  identisch mit der Beschriftung des vorhandenen Moduls.
- **Benötigte Stackhöhe** = 16,5 mm − Glaseinstand − Modulstärke (≈ 2,8 mm)
  ≈ **13–14 mm**. Realisierung z. B. Buchsenleiste 11 mm + Stiftleisten-
  kragen 2,5 mm. Buchsenleisten gibt es in 8,5/11/13/15 mm.
- **Vor dem Einfrieren am realen Modul messen** (Hersteller streuen ±1 mm):
  1. Abstand Modul-Linkskante → Pinreihe (Annahme 2,5 mm),
  2. Abstand Modul-Linkskante → Zentrum aktive Fläche (Annahme 23,5 mm),
  3. Glaseinstand (Front-Innenfläche → Glasunterseite).
  Praktisch: Modul in den Rahmen legen, Display mittig im Fenster,
  Pinlöcher relativ zu zwei Dom-Schrauben messen → das ist J4.

---

## 6. Firmware (ESPHome)

Datei: `firmware/timer-relais-c3.yaml`. Enthält komplett: WLAN mit
Fallback-Hotspot („Timer-Relais Setup"), Webserver zum Einstellen der
drei Zeiten (gespeichert über Neustart hinweg), Tasterlogik mit
Entprellung, Countdown-Anzeige, „ON" im Ruhezustand.

**Erstinstallation (einmalig, vor dem Einbau!):**
1. ESPHome installieren (Home-Assistant-Add-on **oder**
   `pip install esphome` auf dem PC).
2. Datei `secrets.yaml` neben die YAML legen:
   ```yaml
   wifi_ssid: "DeinWLAN"
   wifi_password: "DeinPasswort"
   ```
3. ESP per USB-C anschließen und flashen:
   `esphome run firmware/timer-relais-c3.yaml`
4. Danach gehen Updates kabellos (OTA) — deshalb darf die USB-Buchse
   im eingebauten Zustand ruhig schlecht erreichbar sein.

**Bedienung:** Zeiten ändern unter `http://timer-relais.local`
(drei Zahlenfelder „Zeit Taster 1/2/3").

---

## 7. KiCad — Schritt für Schritt (auch für Einsteiger)

Getestet gegen KiCad 8/9/10; Menünamen können minimal abweichen.

### 7.1 Projekt anlegen und Schaltplan übernehmen
1. KiCad starten → **Datei → Neues Projekt** → Name `timer_ersatzplatine`,
   Ordner z. B. `hardware/kicad/`.
2. KiCad erzeugt eine leere `timer_ersatzplatine.kicad_sch`. Diese Datei
   **im Explorer durch unsere Datei ersetzen** (gleicher Name!):
   `hardware/timer_ersatzplatine.kicad_sch` hineinkopieren.
3. Projekt öffnen, Schaltplan-Editor starten. KiCad konvertiert die Datei
   ggf. ins aktuelle Format — das ist normal, einfach speichern.
4. **Werkzeuge → Elektrische Regeln prüfen (ERC)** laufen lassen.
   Warnungen über „nicht angeschlossene Power-Pins" sind bekannt und
   unkritisch (unsere Symbole haben bewusst keine Power-Pin-Typen);
   optional mit PWR_FLAG-Symbolen auf +5V und GND stilllegen.

### 7.2 Footprints prüfen/zuordnen
**Werkzeuge → Footprints zuweisen.** Vorbelegt sind:

| Ref | Footprint | Aktion |
|-----|-----------|--------|
| SW1–3 | `Button_Switch_THT:SW_PUSH_6mm` | prüfen (Pinbild 6,9 × 4,4) |
| PS1 | `Converter_ACDC:Converter_ACDC_HiLink_HLK-PMxx` | **gegen TSP-05-Messung prüfen!** |
| U2 | `Package_SO:SOP-4_4.4x2.6mm_P1.27mm` | bei DIP-Variante (AQY216 DIP): `Package_DIP:DIP-4_W7.62mm` |
| F1 | `Fuse:Fuse_5x20mm_Horizontal_ReferenceFuseHolder` | oder gewählter Halter |
| RV1 | `Varistor:RV_Disc_D12mm_W3.9mm_P7.5mm` | S14K275 passt |
| R1, C1, C2 | Standard-THT | ok |
| J1–J3 | Pinheader/Klemme | J2 alternativ als 4 große Lötpads |
| J4 | `Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical` | **Buchsen**leiste! |
| U1 | — (leer) | **selbst anlegen**, siehe 7.3 |

### 7.3 Footprint für den ESP32-C3 Super Mini anlegen
1. Footprint-Editor öffnen → neue Bibliothek `timer_project.pretty`
   (im Projektordner, Tabelle „projektspezifisch").
2. Neuer Footprint `ESP32-C3_SuperMini`: zwei Padreihen 1×8, RM 2,54,
   Reihenabstand 15,24 mm (= 6 × 2,54), Pads ⌀1,7/Bohrung 1,0.
   Umriss 18 × 24 mm auf F.Fab, USB-Seite markieren.
3. Padnummern gemäß Pinout-Bild vergeben (linke Reihe 5V, G, 3.3, 4, 3,
   2, 1, 0 / rechte Reihe 5, 6, 7, 8, 9, 10, 20, 21) und im Schaltplan
   dem Symbol U1 zuweisen (die Symbol-Pinnamen 5V/G/3V3/3/4/5/6/8/9
   müssen auf die richtigen Padnummern zeigen).

### 7.4 Platine aus dem Schaltplan erzeugen
Schaltplan-Editor → **Werkzeuge → Schaltplan mit Platine abgleichen**
(„Update PCB from Schematic"). Alle Footprints landen als Haufen neben
der (noch leeren) Platine.

### 7.5 Kontur und Referenzen importieren
1. PCB-Editor → **Datei → Importieren → Grafik** →
   `hardware/platine_original_geometrie.dxf`.
2. Einheit steht dank DXF-Header automatisch auf **mm**; Import zunächst
   auf Layer **User.Drawings**, Position (0,0), Maßstab 1.
3. **Maßkontrolle:** Mit dem Messwerkzeug T1→T2 messen — muss
   **25,6 mm** ergeben. Stimmt es, weiter; sonst Import-Einstellungen
   prüfen.
4. Die Konturlinien (Außenkontur + 6 ⌀10-Kreise) markieren →
   Eigenschaften → Layer auf **Edge.Cuts** ändern. Alles andere
   (Taster-Kreuze, Stellflächen, Fenster, Keepouts, Texte) bleibt auf
   User-Layern; die Stellflächen-Rahmen samt Beschriftung optional
   zusätzlich auf **F.Silkscreen** kopieren (hilft beim Bestücken).
5. Die 4 Befestigungslöcher als Footprints setzen:
   `MountingHole:MountingHole_3.2mm` exakt auf die grünen Kreuze
   (Position per **E** → Koordinaten aus Kap. 4.3 eintippen).

### 7.6 Platzieren und Routen
1. **Taster zuerst**: SW1–SW3 exakt auf (13,2/12,3), (38,8/12,2),
   (64,1/12,0) — Position numerisch eingeben, nicht schieben.
2. J4 auf die Pinkreuze (erster Pin = GND auf x 15,0 / y 27,84).
3. PS1/TSP aufs Stellflächen-Rechteck (AC-Pins Richtung linker Rand),
   U1/ESP auf seine Fläche (USB zur Oberkante), J2-Pads an den Rand der
   Shelly-Stellfläche, J1 + F1 + RV1 in die 230-V-Ecke unten links,
   U2/PhotoMOS zwischen ESP-Bereich und Shelly-Pads, R1 daneben,
   C1/C2 an die 5-V-Leitung nahe U1.
4. **Netzklassen** anlegen (Datei → Platineneinstellungen → Netzklassen):
   - `HV` (Netze L_IN, L_F, N, SW_SHELLY, O_LAST): Leiterbahn ≥ 0,8 mm
     (Versorgungspfad des Shelly-Ausgangs O ≥ 2 mm bei 8-A-Last!),
     Abstand innerhalb HV ≥ 1,0 mm.
   - Standard (Kleinspannung): 0,25/0,2 mm.
5. **Die goldene Regel:** Zwischen jedem HV-Netz und jedem
   Kleinspannungs-Netz **≥ 6,0 mm Abstand** — am einfachsten per
   benutzerdefinierter Regel (Platineneinstellungen → Benutzerdefinierte
   Regeln):
   ```
   (version 1)
   (rule HV_zu_LV
     (condition "A.NetClass == 'HV' && B.NetClass != 'HV'")
     (constraint clearance (min 6.0mm)))
   ```
   Einzige erlaubte „Annäherung" ist der PhotoMOS selbst — dessen
   Gehäuse ist die Trennstelle (Pins 1/2 = LV, Pins 3/4 = HV).
6. Keine Masseflächen/Zonen im HV-Bereich; unter dem TSP-Modul keine
   Fremdleiterbahnen.
7. **DRC** (Design Rules Check) fehlerfrei bekommen.

### 7.7 Fertigungsdaten und Bestellung
1. **Datei → Fertigungsdaten → Gerber** (Standardlayer) + Bohrdateien.
2. 3D-Ansicht (Alt+3) als letzte Sichtprüfung.
3. Hersteller (JLCPCB/PCBWay/Aisler): 2 Lagen, 1,6 mm FR4, HASL bleifrei
   oder ENIG, Farbe egal. Die ⌀10-Kreise und die Außenkontur kommen
   automatisch aus Edge.Cuts.
4. **Vor dem Absenden:** 1:1-Papierdruck der Platine (Datei → Plotten →
   PDF, Maßstab 1:1) ausschneiden und im Gehäuse anprobieren!

---

## 8. Montage und Inbetriebnahme

1. **Kleinteile bestücken** (Reihenfolge flach → hoch): R1, C2, U2,
   Taster (exakt!), J4-Buchsenleiste, C1, F1-Halter, RV1, Klemmen.
2. **ESP32-C3 vorbereiten:** per USB flashen (Kap. 6), WLAN-Verbindung
   testen, dann auf die Platine löten (Stiftleisten oder direkt).
3. **Nur-USB-Test:** ESP über USB versorgen (kein Netz!) — Taster müssen
   Countdown starten, OLED auf J4 aufgesteckt muss anzeigen, GPIO6
   muss schalten (Messgerät/LED am PhotoMOS-Eingang).
4. **TSP-05 einlöten**, Shelly mit VHB auf die Stellfläche kleben,
   vier Litzen zu J2 (L, N, SW, O), Litze zum Lastabgang.
5. **Sichtprüfung + Durchgangsprüfung:** kein Schluss zwischen L/N/PE,
   ≥ 6 mm Abstände eingehalten, keine Lötspritzer.
6. **Erster Netztest:** Gehäuse geschlossen, über PRCD/RCD einschalten.
   OLED zeigt „ON" → Shelly per Knopf/App einrichten (WLAN, Input Mode
   „Switch") → Tastertest mit Last.
7. Zeiten nach Wunsch über `http://timer-relais.local` einstellen.

---

## 9. Dateiübersicht

| Datei | Inhalt | Regenerierbar? |
|-------|--------|----------------|
| `hardware/platine_template.py` | **Quelle der Wahrheit** für alle Geometrie; parametrisch | Quelle |
| `hardware/platine_original_geometrie.dxf` | daraus erzeugte DXF für KiCad | ja: `python3 platine_template.py` (benötigt `pip install ezdxf`) |
| `hardware/platine_vorschau.png` | Render der DXF | ja (Renderskript siehe CLAUDE.md) |
| `hardware/timer_ersatzplatine.kicad_sch` | kompletter Schaltplan (KiCad 8+) | Hand-gepflegt |
| `firmware/timer-relais-c3.yaml` | ESPHome-Konfiguration | Hand-gepflegt |
| `docs/DOKUMENTATION.md` | dieses Dokument | Hand-gepflegt |
| `docs/PROJEKTPLAN.md` | Phasen, Status, Checklisten | Hand-gepflegt |
| `CLAUDE.md` | Arbeitsanweisung für Claude Code | Hand-gepflegt |
| `docs/DOKUMENTATION.pdf`, `docs/PROJEKTPLAN.pdf` | PDF-Fassungen (**Pflicht bei jeder Änderung**) | ja: `python3 tools/md2pdf.py docs/*.md` |
| `tools/md2pdf.py` | Markdown→PDF-Generator | Quelle |

## 10. Änderungshistorie der Geometrie-Vorlage

| Version | Änderung |
|---------|----------|
| v1 | Erste Koordinaten aus perspektivisch entzerrten Fotos (±1–2 mm) |
| v2 | Scanner-Vermessung: 76,7 × 66,1, Taster/Löcher/Aussparung präzise (Lötseiten-Scan) |
| v3 | Gehäuse-Einpassung 105,3 × 79,4, 6 Dom-Ausschnitte ⌀10, alte Aussparung entfällt (= B5) |
| v4 | Korrektur: kein Versenken möglich (unten nur 1,8 mm) — Fenster raus, Shelly auf Stellfläche rechts, 4. Loch zurück, Steg-Keepouts |
| v5 | TSP-05 statt HLK eingeplant (unten links), ESP nach oben links |
| v6 | OLED rahmenmontiert: Fensterbereich freigegeben, J4-Anschluss |
| v7 | Beschriftete Platzhalter (DXF-Texte) |
| v8 | OLED-Steckmontage: J4 senkrecht auf Fensterzentrierung konstruiert |

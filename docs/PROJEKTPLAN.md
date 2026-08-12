# Feeder-Relais (Timer-Ersatzplatine) — Projektplan

**Stand:** 2026-08-12 · Aktuelle Phase: **v2 fertig entwickelt — vor der Fertigung**
Pflegehinweis: Erledigtes abhaken (`[x]`), neue Erkenntnisse mit Datum
ergänzen, niemals Messwerte ohne neue Messung ändern (siehe CLAUDE.md).

> **Produktstand:** Version 2 (Elektronik auf der Rückseite, Shelly extern) ist
> die maßgebliche Hardware. Version 1 wurde aus dem Repo entfernt (bleibt in der
> Git-Historie). Die alten v1-Geometrie-Phasen (DXF-Template, Papier-Anprobe)
> sind damit historisch — die v2-Geometrie steckt in `kicad-v2/` und `box/`.

---

## Phase 0–3 — Analyse, Konzept, v1-Entwurf ✅ abgeschlossen (historisch)

- [x] Originalgerät vermessen (Kontur, Taster, Dome, Höhenbudget)
- [x] Architektur: Taster → ESP32-C3 → PhotoMOS → Shelly-SW (Follow-Mode)
- [x] Firmware `timer-relais-c3.yaml` (ESPHome), Web-App + JSON-API, NTP,
      OLED, Status-LED, Netzwerk-Laufzeitkonfig, Mehrsprachigkeit DE/EN/FR
- [x] v1-Platine (Shelly on-board) entworfen — durch v2 abgelöst

## Phase 4 — v2-Layout ✅ abgeschlossen

- [x] v2 aus v1 abgeleitet: Elektronik komplett auf die **Rückseite**,
      Shelly + Snubber **extern** (J1/X3), Außenmaß **101,6 × 77,5 mm**
- [x] **4-lagig**: F/B tragen die Signale, In1/In2 = GND-Masseflächen nur im
      Kleinspannungsbereich; Netzspannung ausschließlich auf F/B
- [x] Netzklassen aus v1 übernommen (Default 0,2/0,2, 230V 1,0/1,0)
- [x] **6-mm-Kriechstrecke** als `.kicad_dru` (K1-Barriere ausgenommen)
- [x] Routing (Freerouting + Handarbeit), GND-Zonen-Outlines mit 6-mm-Rückzug
- [x] DRC sauber (0 clearance / 0 creepage / 0 unrouted; nur harmlose
      lib_footprint-Warnungen, weil Wago/G3VM-Libs nicht in der User-Lib-Table)
- [x] **Board↔Firmware-Audit (2026-08-12):** alle ESP-GPIO abgeglichen
- [x] **KRITISCHER FIX (2026-08-12):** OLED-SDA lag auf v2 fälschlich auf
      **GPIO8** (= Onboard-WS2812) → auf **GPIO7** korrigiert (Schaltplan-Pin
      8→7, Layout, Zonen neu gefüllt; verifiziert per Netzliste + DRC). GPIO8
      bleibt frei für die Status-LED. Firmware unverändert.

## Phase 5 — Gehäuse ✅ abgeschlossen

- [x] Rückteil `box/feeder_back.scad` (3D-Druck, 35 mm tief, 6 Schraubdome
      Raster 45×70, Aufhängelasche mit Schlüsselloch) → `feeder_back_35mm.stl`
- [x] Platinen-Attrappe `Timer-Ersatzplatine-v2-BOARD.stl` für die Anprobe

## Phase 6 — Dokumentation ✅ abgeschlossen

- [x] Handbuch `docs/handbuch/` (HTML→PDF via WeasyPrint, nach asksin-Regelwerk:
      Deckblatt, klickbares Inhaltsverzeichnis, Fußsteg „↑ Inhaltsverzeichnis",
      Umbruchregeln, 45 Seiten) — anfängertaugliche Nachbau-Anleitung
- [x] Technische Referenz `DOKUMENTATION.md` auf v2 (penibel-genaue GPIO- und
      Bauteil-Tabellen, Board↔Firmware, Netze, Steckverbinder)
- [x] Projektplan (diese Datei) auf v2

## Phase 7 — Fertigung & Beschaffung ⬜ offen

- [x] **SW4/X4 aus Schaltplan entfernt** (2026-08-12); J3–J6 bleiben als OLED-Header-Alternativen und werden noch aufs PCB platziert
- [ ] **Vor Bestellung:** (ehem. Altlast) — noch offen: J3–J6 platzieren, F1-Drehung (GUI), Aussparungen ggf. +1&nbsp;mm
      stehen noch im Schaltplan, nicht auf dem PCB)
- [ ] Testdruck der Platinen-Attrappe im gedruckten Rückteil (Passprobe)
- [ ] Gerber + Bohrdaten final prüfen, bestellen (**4 Lagen**, 1,6 mm)
- [ ] BOM-Teile bestellen: PhotoMOS ≥ 400 V, TSP-05, Buchsen-/Stiftleisten,
      Sicherungshalter, Varistor, Kleinteile, Shelly 1PM Mini Gen4

## Phase 8 — Aufbau & Test ⬜ offen

- [ ] Bestückung (flach → hoch), Taster exakt
- [ ] ESP vorab per USB flashen + WLAN-Test
- [ ] **Nur-USB-Funktionstest** (Taster, OLED, GPIO6) — ohne Netz!
- [ ] PS1 einlöten, Shelly an J1 verdrahten (SW/O/L/N), Last an X2, ggf. X3
- [ ] Sicht- & Durchgangsprüfung, Abstandskontrolle (≥ 6 mm)
- [ ] Erster Netztest über PRCD/RCD, Gehäuse geschlossen
- [ ] Shelly einrichten (WLAN, Input Mode „Switch/Follow")
- [ ] Lasttest, Zeitentest, OTA-Update-Test

## Phase 9 — Abschluss ⬜ offen

- [ ] „as built"-Abweichungen + Fotos in die Doku
- [ ] EN/FR-Handbuch je Release nachziehen (DE führend)
- [ ] Release/Tag + Firmware-Images

---

## Risiken & offene Punkte

| # | Risiko | Auswirkung | Gegenmaßnahme | Status |
|---|--------|-----------|---------------|--------|
| 1 | Schaltplan-Altlast (J3–J6, SW4, X4) | „Update PCB from Schematic" fügt Phantom-Footprints ein | vor Release aus Schaltplan löschen | offen |
| 2 | Passprobe Platine ↔ gedrucktes Rückteil | Platine sitzt nicht satt | Attrappe drucken + einlegen vor Bestellung | offen |
| 3 | TSP-05 Pinabstände vs. Footprint | Netzteil passt nicht | Messschieber-Check; Footprint ist HLK-Klasse | offen |
| 4 | Kriechstrecken im Layout | Sicherheit! | 6-mm-DRC-Regel aktiv, DRC sauber, Review vor Bestellung | erledigt (Review offen) |
| 5 | Board↔Firmware-Pinabgleich | Gerät unbrauchbar | vollständiger Audit 2026-08-12; SDA-Fix angewandt + verifiziert | erledigt |
| 6 | Shelly-Wärme im Gehäuse | Derating | extern + 35 mm tiefes Rückteil; Last ≤ 8 A | Beobachtung |

## Entscheidungslog (warum ist etwas so?)

| Datum | Entscheidung | Begründung |
|-------|--------------|------------|
| 2026-07-13 | Shelly schaltet, eigene Platine steuert nur SW | PM + Fernzugriff erhalten, Timing bleibt WLAN-unabhängig |
| 2026-07-13 | PhotoMOS ≥ 400 V statt Optokoppler/Relais | SW-Eingang ist netzspannungsbezogen; winzig; galvanische Trennung |
| 2026-07-13 | 1PM **Mini** Gen4 statt 1PM Gen4 | 42 × 38 des großen passt flächig nicht |
| 2026-07-13 | OLED gesteckt statt verdrahtet | Montage/Service; von Fensterzentrierung rückwärts konstruiert |
| 2026-07-16 | **I2C-SDA GPIO8 → GPIO7**; Onboard-RGB-LED (GPIO8) als Status-LED | GPIO8 trägt die WS2812 des Super Mini; I2C-Verkehr trieb sie hell/warm. SDA daher auf GPIO7 (Schaltplan-Pin `GPIO8/SDA`→`GPIO7/SDA` inkl. Instanz-Nr.). WS2812 als `light: esp32_rmt_led_strip`: grün=OK/gelb=Timer/rot=Störung |
| 2026-07-16 | Kein einkompiliertes WLAN – Provisioning nur per Captive-Portal | kein fremder SSID/PW in Auslieferung; Portal-Daten unter festem Prefs-Key → überstehen OTA |
| 2026-07-16 | Panik-/Stack-Fixes: keine großen Puffer/Prefs-Writes im httpd-Task | Preferences aus Webserver-Task = Data-Race; große Stack-Puffer = httpd-Stack-Overflow → alles single-threaded / auf den Heap |
| 2026-07-16 | Mehrsprachigkeit DE/EN/FR (Web + OLED) | Sprache geräteweit in `g_netcfg.lang`; Web-Wörterbuch + neutrale Statuscodes; OLED-Sprachtabellen (akzentfrei) |
| **2026-08-12** | **v2 = v1 mit Elektronik auf der Rückseite, Shelly extern** | Höhenbudget zur Front zu knapp für Module vorne; externer Shelly hält Platine klein und 230-V-Wege kurz; 4-lagig mit GND-Flächen (nur Kleinspannung) für Störfestigkeit; Steckverbinder umbenannt (X1 Netz, X2 Last, X3 Snubber, J1 Shelly, J2 OLED) |
| **2026-08-12** | **v2-Board: OLED-SDA von GPIO8 auf GPIO7 korrigiert** | Beim Ableiten von v1 war die 2026-07-16-Korrektur verloren gegangen — v2 hatte SDA wieder auf GPIO8 (= WS2812). Ohne Fix: OLED tot + LED/I²C-Konflikt. Headless behoben (Schaltplan Pin 8→7, Layout pad8→pad7, Zonen neu gefüllt), verifiziert (Netzliste `/SDA→U1.7`, DRC sauber). Firmware war stets korrekt (SDA=GPIO7) |
| **2026-08-12** | **Doku nach asksin-Regelwerk (HTML-Handbuch)** | anfängertaugliches Handbuch `docs/handbuch/` (WeasyPrint-PDF, Inhaltsverzeichnis mit Sprungmarken, Fußsteg zurück zum Inhalt, feste Umbruchregeln); `DOKUMENTATION.md` bleibt technische Quelle der Wahrheit |

# CLAUDE.md — Arbeitsanweisung für dieses Projekt

Dieses Repository enthält das **Feeder-Relais** (Board-/Repo-Name
„Timer-Ersatzplatine"): eine 230-V-Timer-/Schaltplatine mit ESP32-C3, OLED,
PhotoMOS und **externem** Shelly 1PM Mini Gen4. Maßgeblich ist **Version 2**
(Elektronik auf der Rückseite, Shelly extern).

**Repo-Policy (Nutzervorgabe 2026-08-13):** Im Repo verbleiben als Doku **nur die
fertigen `README.md`s und die Handbuch-PDFs**. `docs/DOKUMENTATION.md` (technische
Quelle der Wahrheit) und `docs/PROJEKTPLAN.md` sind **lokale Arbeitsdokumente**
(nicht mehr eingecheckt, per `.gitignore` ausgenommen) — weiter pflegen, aber
nicht committen. Ebenso lokal: das gesamte Handbuch-Bauwerkzeug
(`docs/handbuch/handbuch*.html`, `build.sh`, `direktziele.py`, `pruefe_*.py`,
`umbrueche.py`, `img/`) und `tools/md2pdf.py`. **Vollständiger Kontext** steht
weiterhin lokal in `docs/DOKUMENTATION.md` + `docs/PROJEKTPLAN.md`; diese bei
jeder Änderung mitpflegen (Changelog Doku Kap. 11, Entscheidungslog Projektplan).

**Lizenz:** Das Projekt steht unter **CC BY-NC-SA 4.0** (`LICENSE`); der
Lizenzabschnitt steht am Ende jeder `README.md`.

## Grundregeln

1. **Board↔Firmware-Pinbelegung ist heilig (Konsistenz-Viereck).** Schaltplan/
   Layout (`kicad-v2/`), Firmware (`firmware/timer-relais-c3.yaml`), Handbuch und
   `DOKUMENTATION.md` müssen **dieselbe** Belegung tragen:
   - Taster T1/T2/T3 = **GPIO3/4/5**, PhotoMOS = **GPIO6** (über 330 Ω),
   - **I²C-SDA = GPIO7, SCL = GPIO9**, OLED J2 = GND/VCC/SCL/SDA,
   - **RGB-Status-LED (WS2812, onboard Super Mini) = GPIO8.**
   **SDA MUSS auf GPIO7 liegen, NIE auf GPIO8** — auf GPIO8 sitzt die WS2812;
   SDA auf GPIO8 macht das OLED tot und das Gerät unbrauchbar (genau dieser
   Fehler steckte in v2 und wurde 2026-08-12 behoben). Wer eine Seite ändert,
   ändert alle vier und **gleicht Board gegen Firmware programmatisch ab**
   (pcbnew-Pad-Dump ↔ YAML).

2. **Sicherheit:** Alle Netze L_IN, L_F, N, SW_SHELLY, O_LAST führen 230 V.
   Kriechstrecke **≥ 6 mm** zu Kleinspannung — als DRC-Regel
   `kicad-v2/Timer-Ersatzplatine-v2.kicad_dru` hinterlegt (K1/PhotoMOS als
   zertifizierte Barriere ausgenommen). **Keine Vorschläge machen, die diese
   Regel aufweichen.** Netzspannung nur auf F.Cu/B.Cu, kein Innenkupfer.

3. **Netzklassen nicht ändern.** `Default` (0,2/0,2 mm) und `230V` (1,0/1,0 mm,
   Netze L_IN/L_F/N/SW_SHELLY/O_LAST) sind aus v1 übernommen und fix.

4. **Geometrie/Layout v2 lebt in `kicad-v2/` und `box/`.** Die Platine ist
   fertig geroutet (4-lagig, DRC sauber). Änderungen am Board headless mit
   pcbnew (KiCad 10, `~/kicad10/kcli` + `~/kicad10/squashfs-root/usr/bin/python3.11`,
   `LD_LIBRARY_PATH=$HOME/kicad10/squashfs-root/usr/lib`); **immer Sicherung
   anlegen**, danach DRC + Netzliste prüfen. GND-Zonen nach Track-Änderungen neu
   füllen (6-mm-Rückzug steckt in der Zonen-Outline). Das Gehäuse-Rückteil ist
   parametrisch in `box/feeder_back.scad`.

5. **Höhenbudget** (nicht verletzen): über der Platine ~16,5 mm, zur Front
   praktisch nichts — deshalb liegt in v2 die gesamte Elektronik auf der
   **Rückseite**; vorne nur Taster (SW1–3) und OLED-Buchse (J2).

6. **Handbuch-PDFs (committet) bei Handbuch-Änderungen neu erzeugen:**
   ```bash
   # Deutsch (Standard)
   docs/handbuch/build.sh
   # eine Übersetzung: build.sh <quelle.html> <ziel.pdf> <Fußsteg-Wort>
   docs/handbuch/build.sh handbuch.en.html ../en/Feeder-Relais-Manual.pdf Contents
   ```
   `build.sh` prüft Nummerierung + Fußsteg, baut mit **WeasyPrint** und macht die
   Sprungmarken via `direktziele.py` **klickbar in jedem Viewer** (benannte →
   direkte Ziele). Lokal (nicht committet) bleiben `DOKUMENTATION.md`/
   `PROJEKTPLAN.md`; deren PDFs via `python3 tools/md2pdf.py …` nur für den
   Eigengebrauch.
   **Sprachpolitik:** Das **deutsche** `README.md` (Root) und das deutsche
   Handbuch sind die **Quelle der Wahrheit**. Übersetzungen von **README + Handbuch**
   liegen unter `docs/<sprache>/` für **EN/FR/NL/ES/IT** und werden **je Release**
   nachgezogen (DE führend). Im Repo landen nur die fertigen `README.md`s +
   Handbuch-PDFs; die `handbuch.<sprache>.html`-Quellen bleiben lokal.

7. **Doku-Regelwerk (aus ioBroker.asksinanalyzer übernommen):** Das Handbuch
   `docs/handbuch/handbuch.html` wird mit **WeasyPrint** gebaut (nicht Chromium)
   und muss: ein **Inhaltsverzeichnis mit Sprungmarken** am Anfang, auf **jeder
   Seite** einen **Fußsteg mit „↑ Inhaltsverzeichnis"** und feste **Umbruchregeln**
   tragen. Durchgesetzt von `pruefe_nummerierung.py`, `pruefe_fusssteg.py`,
   `umbrueche.py`; `direktziele.py` macht die Sprungmarken universell klickbar.
   Diese Skripte sind **sprachparametriert** (Pfad/Fußsteg-Wort als Argument), so
   dass `build.sh` jede Übersetzung prüft. Jedes `h2` trägt eine fortlaufende
   Nummer `N.M` mit passender `id="kN-M"`; **Übersetzungen halten Struktur, IDs
   und Nummern byte-identisch** — nur der sichtbare Text wird übersetzt.
   Ziel: **jeder Anfänger kann das Projekt vollständig nachbauen.**

   Gehäuse-Beschriftung der Taster: **S1 = Down/Manual (T1), S2 = SET (T2),
   S3 = UP (T3)**. Gerätename/Default-Hostname **`feeder-relais`**.

## Dateikarte

| Pfad | Rolle |
|------|-------|
| `kicad-v2/Timer-Ersatzplatine-v2.kicad_pcb/.sch/.pro` | Platine v2 (Layout, Schaltplan, Projekt) — 4-lagig, geroutet |
| `kicad-v2/…​.kicad_dru` | 6-mm-Kriechstrecken-Regel (K1 ausgenommen) |
| `kicad-v2/Timer-Ersatz-Gerber(.zip)` | Fertigungsdaten (aus KiCad) |
| `kicad-v2/…​-BOARD.stl` | Platinen-Attrappe für die Passprobe |
| `box/feeder_back.scad` + `…​_35mm.stl` | Gehäuse-Rückteil (OpenSCAD-Quelle + Druck) |
| `firmware/timer-relais-c3.yaml` | ESPHome; `secrets.yaml` lokal, nicht einchecken |
| `firmware/timer_web.h` | Mobile Web-App + JSON-API (`AsyncWebHandler` auf `web_server_base`, Port 80) |
| `firmware/net_config.h` | Persistente Netzwerk-Konfig (IP DHCP/statisch, NTP, Hostname, 802.11k/v, Sprache) |
| `firmware/log_ring.h` | Log-/Debug-Ringpuffer + Web-OTA |
| `firmware/build/*.bin` | Flash-Images (factory + ota) — bewusst getrackt |
| `README.md` | **committet** — Projektüberblick (deutsch, Quelle der Wahrheit) + Sprachen-Links + Lizenz |
| `docs/<sprache>/README.md` | **committet** — README-Übersetzungen EN/FR/NL/ES/IT |
| `docs/handbuch/Feeder-Relais-Handbuch.pdf` | **committet** — deutsches Handbuch-PDF |
| `docs/<sprache>/Feeder-Relais-*.pdf` | **committet** — Handbuch-PDFs EN/FR/NL/ES/IT |
| `LICENSE` | **committet** — CC BY-NC-SA 4.0 |
| `docs/handbuch/handbuch*.html`, `build.sh`, `direktziele.py`, `pruefe_*.py`, `umbrueche.py`, `img/` | **lokal** — Handbuch-Bauwerkzeug (nicht committet) |
| `docs/DOKUMENTATION.md` (+ `.pdf`) | **lokal** — technische Referenz (deutsche Quelle der Wahrheit) |
| `docs/PROJEKTPLAN.md` (+ `.pdf`) | **lokal** — Phasen, Risiken, Entscheidungslog (nur Deutsch) |
| `tools/md2pdf.py` | **lokal** — Markdown → PDF für DOKUMENTATION/PROJEKTPLAN |

## Board↔Firmware programmatisch abgleichen (Kurzrezept)

```bash
export LD_LIBRARY_PATH=$HOME/kicad10/squashfs-root/usr/lib
# U1-Pads (GPIO ↔ Netz) aus dem PCB
$HOME/kicad10/squashfs-root/usr/bin/python3.11 -c "import pcbnew; b=pcbnew.LoadBoard('kicad-v2/Timer-Ersatzplatine-v2.kicad_pcb'); \
[print(p.GetName(), p.GetNetname()) for fp in b.GetFootprints() if fp.GetReference()=='U1' for p in fp.Pads()]"
# Firmware-Pins gegenlesen
grep -nE 'GPIO|sda|scl|pin' firmware/timer-relais-c3.yaml
```

## Nächste Schritte (Details im Projektplan)

Vor der Fertigung: Schaltplan-Altlast (Phantom-Symbole **J3–J6, SW4, X4**, nicht
auf dem PCB) entfernen, Passprobe der Platinen-Attrappe im gedruckten Rückteil,
Gerber final prüfen → **4 Lagen** bestellen → Aufbau/Test (Phase 8).

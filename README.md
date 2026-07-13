# Timer-Ersatzplatine (ESP32-C3 + OLED + Shelly 1PM Mini Gen4)

Ersatz einer Timer-Steuerplatine: 3 Taster schalten eine 230-V-Last für
je eine per WLAN einstellbare Zeit (Standard 5/10/15 s); das OLED zeigt
WLAN-Status, Uhrzeit und bei Lauf den Countdown. Der vorhandene Shelly
1PM Mini Gen4 übernimmt das
Schalten und die Leistungsmessung; die Platine steuert seinen SW-Eingang
galvanisch getrennt über ein PhotoMOS-Relais an — die Kernfunktion ist
dadurch WLAN-unabhängig.

**⚠️ 230 V — Lebensgefahr. Sicherheitshinweise in `docs/DOKUMENTATION.md`
Kap. 2 zuerst lesen.**

## Bedienung

**Am Gerät:** drei Tasten **S1 Down/Manual · S2 SET · S3 UP** — kurz löst
Timer 1/2/3 aus, langer Druck auf **UP** stoppt alles, langer Druck auf
**SET** (≥3 s) öffnet ein Info-Menü (mit S1/S3 blättern). Das OLED zeigt
WLAN-Status, Uhr bzw. Countdown (Doku Kap. 6.5).

**Mobil:** Web-App auf **Port 80** (`http://feeder-relais.local`): Taster
auslösen, Zeiten einstellen, Netzwerk-/Statuswerte. Für die Anbindung
(z. B. ioBroker) gibt es eine JSON-API (`/api/status|trigger|stop|config`,
siehe Doku Kap. 6.4).

## Einstieg

1. `docs/DOKUMENTATION.md` — vollständige, laienverständliche Doku
   (Konzept, Maße, Schaltung, ESPHome, KiCad-Anleitung, Montage)
2. `docs/PROJEKTPLAN.md` — Phasen, Checklisten, Risiken, Entscheidungen
3. `CLAUDE.md` — Arbeitsregeln für die Fortführung (auch mit Claude Code)

## Status

Phase 3 (Verifikation): Vorlagen fertig (Geometrie v8, Schaltplan,
Firmware) — vor dem Layout stehen die Realwelt-Checks aus
(Papier-Anprobe, Stegrichtungen, TSP-Pins, OLED-Maße, Stackhöhe).

## Schnellbefehle

```bash
pip install ezdxf pillow
cd hardware
python3 platine_template.py        # DXF neu erzeugen
```

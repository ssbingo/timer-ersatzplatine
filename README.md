# Feeder-Relais (Timer-Ersatzplatine v2 · ESP32-C3 + OLED + Shelly 1PM Mini Gen4)

Ersatz einer 230-V-Timer-Steuerplatine: 3 Taster schalten eine 230-V-Last für
je eine per WLAN einstellbare Zeit (Standard 5/10/15 s); das OLED zeigt
WLAN-Status, Uhrzeit und bei Lauf den Countdown. Ein **externer** Shelly 1PM
Mini Gen4 übernimmt das Schalten und die Leistungsmessung; die Platine steuert
seinen SW-Eingang galvanisch getrennt über ein PhotoMOS-Relais an — die
Kernfunktion ist dadurch WLAN-unabhängig.

**⚠️ 230 V — Lebensgefahr. Sicherheitshinweise in `docs/DOKUMENTATION.md` Kap. 2
bzw. Handbuch Kap. 2 zuerst lesen.**

## Version 2

- Gesamte Elektronik auf der **Rückseite**, Shelly + Snubber **extern** (J1/X3).
- **4-lagig** mit GND-Masseflächen (nur Kleinspannung), Netzspannung nur auf F/B,
  6-mm-Kriechstrecke als DRC-Regel.
- Gehäuse-Rückteil 3D-gedruckt (`box/`), Außenmaß Platine 101,6 × 77,5 mm.

## Bedienung

**Am Gerät:** drei Tasten **S1 Down/Manual · S2 SET · S3 UP** — kurz löst
Timer 1/2/3 aus, langer Druck auf **UP** stoppt alles, langer Druck auf **SET**
(≥ 3 s) öffnet ein Info-Menü (mit S1/S3 blättern).

**Mobil:** Web-App auf **Port 80** (`http://feeder-relais.local`): Taster
auslösen, Zeiten einstellen, Netzwerk-/Statuswerte. Für die Anbindung (z. B.
ioBroker) gibt es eine JSON-API (`/api/status|trigger|stop|config`).

## Einstieg

1. **Handbuch** `docs/handbuch/` (HTML + PDF) — anfängertaugliche
   Schritt-für-Schritt-Nachbauanleitung mit Inhaltsverzeichnis.
2. `docs/DOKUMENTATION.md` — technische Referenz (GPIO-/Bauteil-/Netz-Tabellen,
   Board↔Firmware, KiCad/Fertigung).
3. `docs/PROJEKTPLAN.md` — Phasen, Risiken, Entscheidungslog.
4. `CLAUDE.md` — Arbeitsregeln für die Fortführung.

## Status

**v2 fertig entwickelt — vor der Fertigung.** Platine geroutet (4-lagig, DRC
sauber), Board↔Firmware abgeglichen (SDA=GPIO7-Fix angewandt), Gehäuse und
Dokumentation fertig. Offen: Schaltplan-Altlast entfernen, Passprobe,
4-Lagen-Bestellung, Aufbau/Test.

## Schnellbefehle

```bash
# Handbuch-PDF bauen (WeasyPrint-venv, prüft Nummerierung + Fußsteg)
docs/handbuch/build.sh

# Doku/Projektplan als PDF
python3 tools/md2pdf.py docs/DOKUMENTATION.md docs/PROJEKTPLAN.md

# Firmware flashen (ESP per USB-C)
esphome run firmware/timer-relais-c3.yaml
```

# <img src="../../logo.svg" alt="Feeder-Relais Logo" height="30" align="top"> Feeder-Relais

<p align="center">
  <a href="https://www.buymeacoffee.com/ssbingo"><img src="https://img.buymeacoffee.com/button-api/?text=Buy%20me%20a%20coffee&emoji=&slug=ssbingo&button_colour=FFDD00&font_colour=000000&font_family=Cookie&outline_colour=000000&coffee_colour=ffffff" alt="Buy me a coffee" /></a>
</p>

**A DIY 230 V timer controller — ESP32-C3 · OLED · PhotoMOS · external Shelly 1PM Mini Gen4**

The Feeder-Relais is a DIY control board that switches on a 230 V load at
the press of a button for an **adjustable time** and then switches itself
off again automatically. The name comes from its original use case: it
replaces the defective timer board of an automatic **feeder** — hence the
product name. Because at its core it just "presses a switch for a certain
time," it is suitable for any load that needs to be switched on a timer —
pump, feed motor, fan, light.

Three buttons trigger three independently adjustable times (default
5/10/15 s), an OLED shows the Wi-Fi status, the time, and the countdown, and
a mobile-optimized web interface allows operation and configuration on the
home network — **without an app and without the cloud**. The actual
switching and power measurement are handled by an **external Shelly 1PM Mini
Gen4**; the board drives its SW input via a **galvanically isolated PhotoMOS
relay**. This makes the core function **independent of Wi-Fi**.

> ### ⚠️ 230 Volts — Danger to Life
> Mains voltage can be fatal. Building, testing, and commissioning the 230 V
> side must be done by a **qualified electrician** or a person trained and
> instructed in electrical safety. All tests that are possible without a
> qualified electrician are carried out in this project **exclusively via
> USB and without any mains voltage**. Please read Chapter 2 of the manual
> first.

---

## 🌍 Sprachen · Languages

| Sprache | README | Handbuch (PDF) | 🌐 Online |
|--------|--------|----------------|--------|
| 🇩🇪 **Deutsch** (Original) | [README.md](README.md) | [docs/handbuch/Feeder-Relais-Handbuch.pdf](docs/handbuch/Feeder-Relais-Handbuch.pdf) | [Online](https://ssbingo.github.io/timer-ersatzplatine/) |
| 🇬🇧 English | [docs/en/README.md](docs/en/README.md) | [docs/en/Feeder-Relais-Manual.pdf](docs/en/Feeder-Relais-Manual.pdf) | [Online](https://ssbingo.github.io/timer-ersatzplatine/en.html) |
| 🇫🇷 Français | [docs/fr/README.md](docs/fr/README.md) | [docs/fr/Feeder-Relais-Manuel.pdf](docs/fr/Feeder-Relais-Manuel.pdf) | [Online](https://ssbingo.github.io/timer-ersatzplatine/fr.html) |
| 🇳🇱 Nederlands | [docs/nl/README.md](docs/nl/README.md) | [docs/nl/Feeder-Relais-Handleiding.pdf](docs/nl/Feeder-Relais-Handleiding.pdf) | [Online](https://ssbingo.github.io/timer-ersatzplatine/nl.html) |
| 🇪🇸 Español | [docs/es/README.md](docs/es/README.md) | [docs/es/Feeder-Relais-Manual.pdf](docs/es/Feeder-Relais-Manual.pdf) | [Online](https://ssbingo.github.io/timer-ersatzplatine/es.html) |
| 🇮🇹 Italiano | [docs/it/README.md](docs/it/README.md) | [docs/it/Feeder-Relais-Manuale.pdf](docs/it/Feeder-Relais-Manuale.pdf) | [Online](https://ssbingo.github.io/timer-ersatzplatine/it.html) |

---

## Contents

1. [Overview](#overview)
2. [The Signal Chain](#the-signal-chain)
3. [The PCB (Hardware v2)](#the-pcb-hardware-v2)
4. [The Firmware](#the-firmware)
5. [Operation](#operation)
6. [The Enclosure (3D Printing)](#the-enclosure-3d-printing)
7. [Integration with ioBroker](#integration-with-iobroker)
8. [Building Your Own & Manual](#building-your-own--manual)
9. [Project Structure](#project-structure)
10. [Status](#status)
11. [License](#license)

---

## Overview

The device replaces an original timer board behind an existing front panel.
It consists of four cleanly separable building blocks:

- **PCB** (`kicad-v2/`) — ESP32-C3, power supply, PhotoMOS, and the 230 V
  terminal blocks; four layers, all electronics on the back.
- **Firmware** (`firmware/`) — an ESPHome project with its own mobile web
  app, JSON interface, NTP clock, OLED display, status LED, and
  multilingual operation.
- **Enclosure** (`box/`) — a 3D-printed back piece (35 mm deep) that houses
  the board *and* the external Shelly; the front piece is the existing
  front panel.
- **External Shelly 1PM Mini Gen4** — the certified switching relay with
  power measurement, wired outside the board.

This **division of labor** is at the core of the concept: the ESP measures
the time and sends a galvanically isolated hardware signal to the Shelly;
the Shelly switches the load and measures the power. If Wi-Fi goes down,
the buttons, timer, and switching keep working regardless — only remote
control is paused.

## The Signal Chain

From the button press to the switched load, the signal passes through five
stages, each with exactly one job:

```
Button ─►  ESP32-C3  ─►  330 Ω  ─►  PhotoMOS  ─►  Shelly 1PM  ─►  Load
S1–S3      counts the    limits      switches       switches and     (pump,
           time, draws   the LED     galvanically   measures the      feed
           the OLED      current     isolated       230 V load        motor …)
```

The ESP operates at a safe 3,3 V and must never touch 230 V directly. The
**PhotoMOS** is the bridge: it completely isolates low voltage from mains
voltage using *light*. The Shelly is set to **Switch/Follow** — its relay is
on for exactly as long as our signal is present; all the timing stays with
the ESP.

## The PCB (Hardware v2)

The current version 2 is complete as a KiCad project under `kicad-v2/`.

- **Outer dimensions** 101,6 × 77,5 mm, **four layers** (1,6 mm).
- **All electronics on the back** — only the three buttons and the OLED
  socket remain on the front (everything that is operated or seen).
- Both **inner layers are continuous ground planes** in the low-voltage
  area → low interference, stable Wi-Fi.
- **Mains voltage only on the outer layers:** the five 230 V nets are
  located exclusively on the outer layers, in the bottom left, in their own
  net class with wider traces.
- **6 mm creepage distance** between every 230 V net and every low-voltage
  net — enforced as a fixed KiCad design rule (`.kicad_dru`). The only
  exception is the PhotoMOS K1: its package *is* the certified isolation
  barrier.

### GPIO Assignment — Mandatory PCB ↔ Firmware Alignment

This mapping must match exactly on both sides, or the device will not work:

| ESP Pin | Firmware | Board / Net | Function |
|---------|----------|----------------|----------|
| **GPIO3** | `btn_s1` (input, pull-up, inverted) | Pad 3 → `/BTN1` | Button **S1 Down/Manual** (T1) → Timer 1 |
| **GPIO4** | `btn_s2` | Pad 4 → `/BTN2` | Button **S2 SET** (T2) → Timer 2 / long press: menu |
| **GPIO5** | `btn_s3` | Pad 5 → `/BTN3` | Button **S3 UP** (T3) → Timer 3 / long press: stop |
| **GPIO6** | `shelly_trigger` (output) | Pad 6 → `/PMOS_DRV` → R1 330 Ω → K1-LED | PhotoMOS driver: HIGH = load on |
| **GPIO7** | `i2c: sda` (400 kHz) | Pad 7 → `/SDA` → OLED J2.4 | I²C data line to the OLED |
| **GPIO8** | `status_led` (WS2812, GRB) | on-module (Pad 8 unused) | Onboard RGB status LED (traffic light) |
| **GPIO9** | `i2c: scl` (400 kHz) | Pad 9 → `/SCL` → OLED J2.3 | I²C clock line to the OLED (address 0x3C) |
| **5V / GND** | Module supply | `/+5V` / `GND` from the power supply | Supply + common ground |
| **3V3** | Onboard regulator | `/+3V3` → OLED-VCC | 3,3 V for the OLED |

> **Important:** SDA is deliberately on **GPIO7**, not GPIO8 — the onboard
> WS2812 sits on GPIO8. If I²C were there instead, the OLED would stay black
> and the data traffic would interfere with the LED.

### Terminal Blocks and Nets

| Terminal | Connection | Pinout |
|--------|-----------|------------------|
| **X1** | Mains input | 1 = N, 2 = L_IN (230 V in) |
| **X2** | Load output | 1 = O (switched), 2 = N |
| **X3** | Snubber | 1 = O, 2 = N — optional RC network for inductive loads |
| **J1** | Shelly (external) | 1 = SW, 2 = O, 3 = L, 4 = N |
| **J2** | OLED | GND / VCC / SCL / SDA (plugged on) |

The five 230 V nets in the "230V" net class: `L_IN` (unfused, X1→F1), `L_F`
(fused, F1→RV1/PS1/K1.3/Shelly-L), `N` (neutral), `SW_SHELLY` (switched,
K1.4→Shelly-SW), and `O_LAST` (switched, Shelly-O→X2/X3).

### Key Components

| Reference | Component | Function |
|---------|---------|------------------|
| **U1** | ESP32-C3 Super Mini | Microcontroller with Wi-Fi, 5 V→3,3 V; carries the WS2812 on GPIO8 |
| **K1** | PhotoMOS G3VM-601AY2 (or -601BY / AQY216) | Galvanic isolation 3,3 V ↔ 230 V, **≥ 400 V** |
| **PS1** | AC/DC module TSP-05 (5 V / 3 W) | Power supply from L_F + N |
| **R1** | 330 Ω | Series resistor for the K1 LED (~6 mA) |
| **C1 / C2** | 220 µF / 100 nF | 5 V buffer (Wi-Fi peaks) + decoupling |
| **F1** | 1 A slow-blow, 5×20 mm | Primary-side fine fuse (X1→F1→L_F) |
| **RV1** | Varistor S14K275 | Overvoltage protection between L_F and N |
| **SW1–3** | Push button 6×6 mm | the three tactile switches (fixed position, front panel) |

## The Firmware

The firmware is an **ESPHome** project (`firmware/timer-relais-c3.yaml`)
with custom C++ extensions. Device name/hostname: **`feeder-relais`**
(→ `http://feeder-relais.local`).

- **Timer logic:** three independent times (1–600 s), changeable via the
  web while running; a short button press starts, a long press on UP stops
  everything.
- **Own mobile web app + JSON API** (`firmware/timer_web.h`) on port 80 —
  no cloud service. Endpoints: `/api/status`, `/api/trigger`, `/api/stop`,
  `/api/config`, `/api/net`, `/api/wifi`, `/api/reboot`.
- **OLED display** (SSD1306 128×32): Wi-Fi reception, a large NTP clock,
  date, free memory; a seconds countdown while a timer is running. Display
  rotated 180° (adapted to the installed orientation).
- **Status traffic light** via the onboard WS2812 (GPIO8): **green** =
  ready, **yellow** = timer running, **red** = fault.
- **Runtime network configuration** (`firmware/net_config.h`): IP mode
  DHCP/static, NTP server, hostname, 802.11k/v roaming.
- **Multilingual** (web + OLED): German / English / French, switchable
  device-wide.
- **Provisioning via captive portal** — no Wi-Fi password compiled in; the
  credentials survive an update.
- **Wireless updates (OTA)** via the `web_server` platform (`POST
  /update`), plus a log/debug ring buffer (`/api/log`).

Ready-made flash images (factory + OTA) are located under `firmware/build/`.

## Operation

**On the device** — three buttons:

| Button | short press | long press |
|-------|------|--------------|
| **S1** Down/Manual | trigger timer 1 | — |
| **S2** SET | trigger timer 2 | ≥ 3 s: info menu (scroll with S1/S3) |
| **S3** UP | trigger timer 3 | ≥ 1,2 s: stop all timers |

**On mobile** — in the browser at `http://feeder-relais.local`: trigger
timers, set the three times, view network and status values, choose the
language.

## The Enclosure (3D Printing)

The enclosure consists of the existing **front piece** (original front
panel with viewing window and button plungers) and a self-printed **back
piece**:

- Source `box/feeder_back.scad` (OpenSCAD), ready-made
  `box/feeder_back_35mm.stl`.
- **35 mm deep** (instead of the original 5,7 mm), so that the board *and*
  the Shelly fit inside.
- Six screw bosses (45 × 70 mm grid), a mounting tab with a keyhole slot.
- `box/Timer-Ersatzplatine-v2-BOARD.stl` is a **1:1 mock-up** of the board
  — print it flat and insert it to check the fit **before** ordering the
  real board.

## Integration with ioBroker

The Feeder-Relais is the **hardware side** of an automatic feeder and
integrates well into a home automation system:

- The **external Shelly 1PM Mini Gen4** is integrated natively into
  ioBroker via the **Shelly adapter** — switch state and power measurement
  are directly visible and controllable there.
- The device's **own JSON API** (`/api/status | trigger | stop | config`)
  can be read and operated via REST/script (e.g. `simple-api`, JavaScript
  adapter) — for triggering timers and querying status.

In the same "smart pond/feeder" ecosystem there are two matching adapters
by the same author that form the **software side**:

- **[ioBroker.automatic-feeder](https://github.com/ssbingo/ioBroker.automatic-feeder)**
  — scheduling, temperature model, sunrise/sunset, pauses, and
  notifications for a fish/koi/pond feeder.
- **[ioBroker.vis-2-widgets-automatic-feeder](https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder)**
  — ready-made vis-2 dashboard widgets (live view and remote control) for
  the adapter above.

Together, the hardware (this device + Shelly) and the two adapters form an
unbroken chain from the button to the dashboard.

## Building Your Own & Manual

A **complete, beginner-friendly manual** guides you step by step from a
blank board to a finished device — covering safety, the shopping list, PCB
fabrication, assembly, flashing the firmware, and commissioning, including
a clickable table of contents:

**➡️ [docs/en/Feeder-Relais-Manual.pdf](docs/en/Feeder-Relais-Manual.pdf)**
(For other translations, see the [language table](#-sprachen--languages) above.)

Flashing the firmware (ESP via USB-C):

```bash
esphome run firmware/timer-relais-c3.yaml
```

## Project Structure

```
kicad-v2/     PCB v2 (KiCad: schematic, layout, 6 mm rule, footprints, 3D models)
box/          Enclosure back (OpenSCAD source + STL) and PCB mock-up
firmware/     ESPHome firmware (.yaml + .h), ready-made flash images in build/
docs/         Manual PDF (German) and translations under docs/<language>/
README.md     this document (German; translations under docs/<language>/)
```

## Status

**Version 2 fully developed — ready for production.** Board routed in 4
layers (DRC with no real errors), board ↔ firmware aligned (OLED SDA on
GPIO7), enclosure and documentation complete. Remaining: regenerate the
Gerber files, fit-check the mock-up, order in 4 layers, assembly, and
functional testing.

## License

This project (hardware, firmware, enclosure, and documentation) is
licensed under **Creative Commons Attribution-NonCommercial-ShareAlike 4.0
International (CC BY-NC-SA 4.0)**.

© 2026 Silvio Sternitzke

You are free to:

- **Share** — copy and redistribute the material,
- **Adapt** — remix, transform, and build upon it,

under the following terms:

- **Attribution (BY)** — you must give appropriate credit, provide a link
  to the license, and indicate if changes were made.
- **NonCommercial (NC)** — you may not use the material for commercial
  purposes.
- **ShareAlike (SA)** — if you remix, transform, or build upon the
  material, you must distribute your contributions under the same license.
- **No additional restrictions** — you may not apply legal terms or
  technological measures that legally restrict others from doing anything
  the license permits.

License summary: <https://creativecommons.org/licenses/by-nc-sa/4.0/deed.en> ·
for the full legal text see [LICENSE](LICENSE).

> **Disclaimer:** Building this project is at your own risk. 230 volts can
> be fatal. The material is provided without warranty; any liability for
> damages is excluded. When in doubt, consult a qualified electrician.

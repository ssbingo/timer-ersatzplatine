# <img src="../../logo.svg" alt="Feeder-Relais Logo" height="30" align="top"> Feeder-Relais

<p align="center">
  <a href="https://www.buymeacoffee.com/ssbingo"><img src="https://img.buymeacoffee.com/button-api/?text=Buy%20me%20a%20coffee&emoji=&slug=ssbingo&button_colour=FFDD00&font_colour=000000&font_family=Cookie&outline_colour=000000&coffee_colour=ffffff" alt="Buy me a coffee" /></a>
</p>

> **Herkomst:** Dit project is een ombouw van een **SuperFish / Koi-Pro Fish Feeder** (voederautomaat van Aquadistri — [productlijn](https://aquadistri.com/de/brands/koi-pro/einrichtung-zubehoer/zubehoer/) · [originele handleiding (PDF)](../Koi-Pro-FishFeeder-Original-Manual.pdf)) — het vervangt de defecte originele timerprint. **De achterkant van de behuizing en de print volgen de afmetingen van de originele besturing**, zodat beide precies in de bestaande behuizing passen.

**230V-timerbesturing om zelf te bouwen — ESP32-C3 · OLED · PhotoMOS · externe Shelly 1PM Mini Gen4**

Het Feeder-Relais is een zelfgebouwde stuurprintplaat die een 230-volt-last op
knopdruk voor een **instelbare tijd** inschakelt en daarna vanzelf weer
uitschakelt. De naam komt van de oorspronkelijke toepassing: het vervangt de
defecte tijdschakelprintplaat van een **voederautomaat** (Engels *feeder*).
Omdat het in de kern alleen „een schakelaar voor een bepaalde tijd indrukt”,
is het geschikt voor elke last die tijdgestuurd geschakeld moet worden — pomp,
voedermotor, ventilator, licht.

Drie drukknoppen activeren drie afzonderlijk instelbare tijden (standaard
5/10/15 s), een OLED toont wifi, tijd en de aftelling, en een voor mobiele
telefoons geoptimaliseerde webinterface maakt bediening en configuratie in
het thuisnetwerk mogelijk — **zonder app en zonder cloud**. Het eigenlijke
schakelen en het meten van het vermogen gebeurt door een **externe Shelly
1PM Mini Gen4**; de printplaat stuurt de SW-ingang daarvan **galvanisch
gescheiden** aan via een **PhotoMOS-relais**. Daardoor is de kernfunctie
**wifi-onafhankelijk**.

> ### ⚠️ 230 volt — levensgevaar
> Netspanning kan dodelijk zijn. Opbouw, controle en inbedrijfstelling van de
> 230-V-zijde horen in handen van een **elektromonteur** of een onderrichte
> persoon. Alle tests die zonder vakman mogelijk zijn, verlopen **uitsluitend
> via USB en zonder enige netspanning**. Lees eerst hoofdstuk 2 van de
> handleiding.

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

## Inhoud

1. [Overzicht](#overzicht)
2. [De signaalketen](#de-signaalketen)
3. [De printplaat (hardware v2)](#de-printplaat-hardware-v2)
4. [De firmware](#de-firmware)
5. [Bediening](#bediening)
6. [De behuizing (3D-print)](#de-behuizing-3d-print)
7. [Aansluiting op ioBroker](#aansluiting-op-iobroker)
8. [Nabouw & handleiding](#nabouw--handleiding)
9. [Projectstructuur](#projectstructuur)
10. [Status](#status)
11. [Licentie](#licentie)

---

## Overzicht

Het apparaat vervangt een originele timerprintplaat achter een bestaande
frontplaat. Het bestaat uit vier goed te scheiden bouwstenen:

- **Printplaat** (`kicad-v2/`) — ESP32-C3, voeding, PhotoMOS en de
  230-V-klemmen, vierlaags, alle elektronica op de achterzijde.
- **Firmware** (`firmware/`) — ESPHome-project met eigen mobiele webapp,
  JSON-interface, NTP-klok, OLED-weergave, statusled en meertalige
  bediening.
- **Behuizing** (`box/`) — 3D-geprint achterstuk (35 mm diep), dat printplaat
  *en* de externe Shelly opneemt; het voorstuk is de bestaande frontplaat.
- **Externe Shelly 1PM Mini Gen4** — het gecertificeerde schakelrelais met
  vermogensmeting, buiten de printplaat bedraad.

De **taakverdeling** vormt de kern van het concept: de ESP meet de tijd en
geeft een galvanisch gescheiden hardwaresignaal aan de Shelly; de Shelly
schakelt de last en meet het vermogen. Valt de wifi uit, dan blijven
knoppen, timer en schakelen gewoon werken — alleen de afstandsbediening
ligt stil.

## De signaalketen

Van de knopdruk tot de geschakelde last doorloopt het signaal vijf stations,
elk met precies één taak:

```
Knop   ─►  ESP32-C3  ─►  330 Ω  ─►  PhotoMOS  ─►  Shelly 1PM  ─►  Last
S1–S3      telt de       begrenst    schakelt      schakelt en      (pomp,
           tijd, tekent  de LED-     galvanisch    meet de          voeder-
           het OLED      stroom      gescheiden    230-V-last       motor …)
```

De ESP werkt met ongevaarlijke 3,3 V en mag 230 V nooit rechtstreeks
aanraken. De **PhotoMOS** is de brug: hij scheidt laag- en netspanning
volledig door *licht*. De Shelly wordt op **Switch/Follow** ingesteld — het
relais ervan staat precies zo lang aan als ons signaal actief is; de
volledige timing blijft bij de ESP.

## De printplaat (hardware v2)

De huidige versie 2 is klaar als KiCad-project onder `kicad-v2/`.

- **Buitenmaat** 101,6 × 77,5 mm, **vierlaags** (1,6 mm).
- **Alle elektronica op de achterzijde** — aan de voorzijde blijven alleen de
  drie drukknoppen en de OLED-connector (alles wat bediend of gezien wordt).
- De beide **binnenlagen zijn doorlopende massavlakken** in het
  laagspanningsgebied → storingsarm, stabiele wifi.
- **Netspanning alleen aan de buitenzijde:** de vijf 230-V-netten liggen
  uitsluitend op de buitenlagen, linksonder, in een eigen netklasse met
  bredere banen.
- **6-mm-kruipweg** tussen elk 230-V-net en elke laagspanning — vastgelegd
  als vaste KiCad-controleregel (`.kicad_dru`). Enige uitzondering is de
  PhotoMOS K1: de behuizing daarvan *is* het gecertificeerde scheidingspunt.

### GPIO-toewijzing — bindende afstemming printplaat ↔ firmware

Deze toewijzing moet aan beide kanten exact overeenkomen, anders werkt het
apparaat niet:

| ESP-pin | Firmware | Printplaat / net | Functie |
|---------|----------|----------------|----------|
| **GPIO3** | `btn_s1` (ingang, pull-up, geïnverteerd) | Pad 3 → `/BTN1` | Drukknop **S1 Down/Manual** (T1) → timer 1 |
| **GPIO4** | `btn_s2` | Pad 4 → `/BTN2` | Drukknop **S2 SET** (T2) → timer 2 / lang: menu |
| **GPIO5** | `btn_s3` | Pad 5 → `/BTN3` | Drukknop **S3 UP** (T3) → timer 3 / lang: stop |
| **GPIO6** | `shelly_trigger` (uitgang) | Pad 6 → `/PMOS_DRV` → R1 330 Ω → K1-LED | PhotoMOS-driver: HIGH = last aan |
| **GPIO7** | `i2c: sda` (400 kHz) | Pad 7 → `/SDA` → OLED J2.4 | I²C-datalijn naar het OLED |
| **GPIO8** | `status_led` (WS2812, GRB) | module-intern (pad 8 vrij) | Onboard rgb-statusled (verkeerslicht) |
| **GPIO9** | `i2c: scl` (400 kHz) | Pad 9 → `/SCL` → OLED J2.3 | I²C-kloklijn naar het OLED (adres 0x3C) |
| **5V / GND** | Modulvoeding | `/+5V` / `GND` van de voeding | Voeding + gemeenschappelijke massa |
| **3V3** | Onboard-regelaar | `/+3V3` → OLED-VCC | 3,3 V voor het OLED |

> **Belangrijk:** SDA ligt bewust op **GPIO7**, niet GPIO8 — op GPIO8 zit de
> onboard WS2812. Lag I²C daar, dan zou het OLED zwart blijven en het
> dataverkeer de led verstoren.

### Aansluitklemmen en netten

| Klem | Aansluiting | Bezetting |
|--------|-----------|------------------|
| **X1** | Netingang | 1 = N, 2 = L_IN (230 V binnenkomend) |
| **X2** | Lastafgang | 1 = O (geschakeld), 2 = N |
| **X3** | Snubber | 1 = O, 2 = N — optioneel RC-lid voor inductieve lasten |
| **J1** | Shelly (extern) | 1 = SW, 2 = O, 3 = L, 4 = N |
| **J2** | OLED | GND / VCC / SCL / SDA (opgestoken) |

De vijf 230-V-netten van de netklasse „230V": `L_IN` (onbeveiligd, X1→F1),
`L_F` (beveiligd, F1→RV1/PS1/K1.3/Shelly-L), `N` (nul), `SW_SHELLY`
(geschakeld, K1.4→Shelly-SW) en `O_LAST` (geschakeld, Shelly-O→X2/X3).

### Belangrijke componenten

| Aanduiding | Component | Functie |
|---------|---------|------------------|
| **U1** | ESP32-C3 Super Mini | Microcontroller met wifi, 5 V→3,3 V; draagt de WS2812 op GPIO8 |
| **K1** | PhotoMOS G3VM-601AY2 (of -601BY / AQY216) | Galvanische scheiding 3,3 V ↔ 230 V, **≥ 400 V** |
| **PS1** | AC/DC-module TSP-05 (5 V / 3 W) | Voeding uit L_F + N |
| **R1** | 330 Ω | Voorweerstand van de K1-led (~6 mA) |
| **C1 / C2** | 220 µF / 100 nF | 5-V-buffer (wifipieken) + afblokking |
| **F1** | 1 A traag, 5×20 mm | fijnzekering aan de primaire zijde (X1→F1→L_F) |
| **RV1** | Varistor S14K275 | Overspanningsbeveiliging tussen L_F en N |
| **SW1–3** | Drukknop 6×6 mm | de drie korteslagdrukknoppen (positie vast, frontplaat) |

## De firmware

De firmware is een **ESPHome**-project (`firmware/timer-relais-c3.yaml`) met
eigen C++-uitbreidingen. Apparaatnaam/hostnaam: **`feeder-relais`**
(→ `http://feeder-relais.local`).

- **Timerlogica:** drie onafhankelijke tijden (1–600 s), tijdens bedrijf via
  het web te wijzigen; korte druk op de knop start, lange druk op UP stopt
  alles.
- **Eigen mobiele webapp + JSON-API** (`firmware/timer_web.h`) op poort 80 —
  geen clouddienst. Endpoints: `/api/status`, `/api/trigger`, `/api/stop`,
  `/api/config`, `/api/net`, `/api/wifi`, `/api/reboot`.
- **OLED-weergave** (SSD1306 128×32): wifi-ontvangst, grote NTP-klok, datum,
  vrij geheugen; tijdens de timerloop de secondenaftelling. Weergave 180°
  gedraaid (aangepast aan de inbouwpositie).
- **Statusverkeerslicht** via de onboard WS2812 (GPIO8): **groen** = klaar,
  **geel** = timer loopt, **rood** = storing.
- **Netwerkconfiguratie tijdens bedrijf** (`firmware/net_config.h`): IP-modus
  DHCP/statisch, NTP-server, hostnaam, 802.11k/v-roaming.
- **Meertalig** (web + OLED): Duits / Engels / Frans, apparaatbreed
  omschakelbaar.
- **Provisioning via captive portal** — geen wifiwachtwoord ingecompileerd;
  de toegangsgegevens overleven een update.
- **Draadloze updates (OTA)** via het `web_server`-platform (`POST /update`)
  plus een log-/debug-ringbuffer (`/api/log`).

Kant-en-klare flashimages (factory + OTA) staan onder `firmware/build/`.

## Bediening

**Op het apparaat** — drie drukknoppen:

| Knop | kort | lang |
|-------|------|--------------|
| **S1** Down/Manual | Timer 1 activeren | — |
| **S2** SET | Timer 2 activeren | ≥ 3 s: info-menu (bladeren met S1/S3) |
| **S3** UP | Timer 3 activeren | ≥ 1,2 s: alle timers stoppen |

**Mobiel** — in de browser `http://feeder-relais.local`: timer activeren, de
drie tijden instellen, netwerk- en statuswaarden bekijken, taal kiezen.

## De behuizing (3D-print)

De behuizing bestaat uit het bestaande **voorstuk** (originele frontplaat met
kijkvenster en druktaster-stoterpennen) en een zelf geprint **achterstuk**:

- Bron `box/feeder_back.scad` (OpenSCAD), kant-en-klare `box/feeder_back_35mm.stl`.
- **35 mm diep** (in plaats van de originele 5,7 mm), zodat printplaat *en*
  Shelly erin passen.
- Zes schroefdomes (raster 45 × 70 mm), ophanglipje met sleutelgat.
- `box/Timer-Ersatzplatine-v2-BOARD.stl` is een **1:1-attrappe** van de
  printplaat — plat printen en erin leggen om de pasvorm te controleren,
  **voordat** de echte printplaat wordt besteld.

## Aansluiting op ioBroker

Het Feeder-Relais is de **hardwarezijde** van een voederautomaat en laat zich
goed inbinden in een huisautomatisering:

- De **externe Shelly 1PM Mini Gen4** wordt in ioBroker via de
  **Shelly-adapter** native ingebonden — schakeltoestand en vermogensmeting
  zijn daar direct zichtbaar en bestuurbaar.
- De **eigen JSON-API** van het apparaat (`/api/status | trigger | stop |
  config`) is via REST/script (bijv. `simple-api`, JavaScript-adapter) uit
  te lezen en te bedienen — voor het activeren van timers en het opvragen
  van de status.

In dezelfde „Smart-Pond/Feeder"-omgeving zijn er twee passende adapters van
dezelfde auteur, die de **softwarezijde** vormen:

- **[ioBroker.automatic-feeder](https://github.com/ssbingo/ioBroker.automatic-feeder)**
  — planning, temperatuurmodel, zonsopgang/-ondergang, pauzes en
  meldingen voor een vis-/koi-/vijvervoederautomaat.
- **[ioBroker.vis-2-widgets-automatic-feeder](https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder)**
  — kant-en-klare vis-2-dashboardwidgets (live weergave en
  afstandsbediening) voor bovenstaande adapter.

Zo vormt de hardware (dit apparaat + Shelly) samen met de twee adapters een
doorlopende keten van de knop tot het dashboard.

## Nabouw & handleiding

Een **volledige, voor beginners geschikte handleiding** leidt je stap voor
stap van de lege printplaat tot het kant-en-klare apparaat — met
veiligheid, inkooplijst, printplaatproductie, montage, firmware flashen en
inbedrijfstelling, inclusief klikbare inhoudsopgave:

**➡️ [docs/nl/Feeder-Relais-Handleiding.pdf](docs/nl/Feeder-Relais-Handleiding.pdf)**
(voor andere talen zie de [talentabel](#-sprachen--languages) hierboven.)

Firmware flashen (ESP via USB-C):

```bash
esphome run firmware/timer-relais-c3.yaml
```

## Projectstructuur

```
kicad-v2/     Printplaat v2 (KiCad: schema, layout, 6-mm-regel, footprints, 3D-modellen)
box/          Behuizing-achterstuk (OpenSCAD-bron + STL) en printplaat-attrappe
firmware/     ESPHome-firmware (.yaml + .h), kant-en-klare flashimages in build/
docs/         Handleiding-PDF (Duits) en vertalingen onder docs/<taal>/
README.md     dit document (Duits; vertalingen onder docs/<taal>/)
```

## Status

**Versie 2 volledig ontwikkeld — vóór de productie.** Printplaat 4-laags
gerouteerd (DRC zonder echte fouten), board ↔ firmware afgestemd (OLED-SDA
op GPIO7), behuizing en documentatie klaar. Nog te doen: Gerberbestanden
opnieuw genereren, pasproef van de attrappe, bestelling van de 4 lagen,
opbouw en functietest.

## Licentie

Dit project (hardware, firmware, behuizing en documentatie) staat onder de
licentie **Creative Commons Naamsvermelding – Niet-commercieel – Gelijk
delen 4.0 Internationaal (CC BY-NC-SA 4.0)**.

© 2026 Silvio Sternitzke

Het staat je vrij om:

- **Te delen** — het materiaal te kopiëren en verder te verspreiden,
- **Te bewerken** — het te hervormen en erop voort te bouwen,

onder de volgende voorwaarden:

- **Naamsvermelding (BY)** — vermeld de maker, koppel naar de licentie en
  geef aan of er wijzigingen zijn aangebracht.
- **Niet-commercieel (NC)** — niet voor commerciële doeleinden.
- **Gelijk delen (SA)** — bewerkingen moeten onder dezelfde licentie worden
  verspreid.
- **Geen aanvullende restricties** — geen extra clausules of technische
  maatregelen die anderen iets wettelijk toegestaans ontzeggen.

Licentietekst: <https://creativecommons.org/licenses/by-nc-sa/4.0/deed.nl> ·
volledige juridische tekst zie [LICENSE](LICENSE).

> **Aansprakelijkheidsuitsluiting:** de nabouw gebeurt op eigen
> verantwoordelijkheid. 230 volt is levensgevaarlijk. Het materiaal wordt
> zonder garantie beschikbaar gesteld; alle aansprakelijkheid voor schade
> is uitgesloten. Raadpleeg bij twijfel een elektromonteur.
</content>

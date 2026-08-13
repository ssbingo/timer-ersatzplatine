# <img src="../../logo.svg" alt="Feeder-Relais Logo" height="30" align="top"> Feeder-Relais

<p align="center">
  <a href="https://www.buymeacoffee.com/ssbingo"><img src="https://img.buymeacoffee.com/button-api/?text=Buy%20me%20a%20coffee&emoji=&slug=ssbingo&button_colour=FFDD00&font_colour=000000&font_family=Cookie&outline_colour=000000&coffee_colour=ffffff" alt="Buy me a coffee" /></a>
</p>

> **Origine:** Questo progetto è la conversione di un **SuperFish / Koi-Pro Fish Feeder** (mangiatoia automatica di Aquadistri — [gamma prodotti](https://aquadistri.com/de/brands/koi-pro/einrichtung-zubehoer/zubehoer/) · [manuale originale (PDF)](https://c6f4t2c9.delivery.rocketcdn.me/wp-content/uploads/2023/01/Manual-Koi-ProFishFeeder.pdf)) — sostituisce la scheda timer originale difettosa. **Il retro del contenitore e la scheda seguono le dimensioni del controller originale**, così entrambi entrano esattamente nell’alloggiamento esistente.

**Centralina timer 230 V da autocostruire — ESP32-C3 · OLED · PhotoMOS · Shelly 1PM Mini Gen4 esterno**

Il Feeder-Relais è una scheda di controllo autocostruita che accende un carico
a 230 volt alla pressione di un pulsante per un **tempo impostabile** e poi si
spegne da sola. Il nome deriva dall'impiego originario: sostituisce la scheda
timer difettosa di un **distributore automatico di mangime** (in inglese
*feeder*). Poiché in sostanza si limita a «premere un interruttore per un
certo tempo», si presta a qualsiasi carico che debba essere commutato in modo
temporizzato — pompa, motore del mangime, ventola, luce.

Tre pulsanti attivano tre tempi impostabili separatamente (valore predefinito
5/10/15 s), un display OLED mostra Wi-Fi, ora e conto alla rovescia, e
un'interfaccia web ottimizzata per smartphone consente l'uso e la
configurazione nella rete domestica — **senza app e senza cloud**. La
commutazione vera e propria e la misura della potenza sono affidate a uno
**Shelly 1PM Mini Gen4 esterno**; la scheda pilota il suo ingresso SW tramite
un **relè PhotoMOS con isolamento galvanico**. Grazie a questo, la funzione
principale è **indipendente dal Wi-Fi**.

> ### ⚠️ 230 volt — Pericolo di morte
> La tensione di rete può essere letale. La realizzazione, il collaudo e la
> messa in servizio del lato a 230 V vanno affidati a un **elettricista
> qualificato** o a una persona istruita. Tutti i test possibili senza
> personale qualificato avvengono in questo manuale **esclusivamente via USB
> e senza alcuna tensione di rete**. Leggere prima il capitolo 2 del manuale.

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

## Indice

1. [Panoramica](#panoramica)
2. [La catena di segnale](#la-catena-di-segnale)
3. [La scheda (hardware v2)](#la-scheda-hardware-v2)
4. [Il firmware](#il-firmware)
5. [Utilizzo](#utilizzo)
6. [L'involucro (stampa 3D)](#linvolucro-stampa-3d)
7. [Integrazione con ioBroker](#integrazione-con-iobroker)
8. [Autocostruzione e manuale](#autocostruzione-e-manuale)
9. [Struttura del progetto](#struttura-del-progetto)
10. [Stato](#stato)
11. [Licenza](#licenza)

---

## Panoramica

Il dispositivo sostituisce una scheda timer originale dietro un pannello
frontale esistente. È composto da quattro moduli ben separabili:

- **Scheda** (`kicad-v2/`) — ESP32-C3, alimentatore, PhotoMOS e i morsetti a
  230 V, quattro strati, tutta l'elettronica sul retro.
- **Firmware** (`firmware/`) — progetto ESPHome con una propria app web
  mobile, interfaccia JSON, orologio NTP, display OLED, LED di stato e
  interfaccia multilingue.
- **Involucro** (`box/`) — parte posteriore stampata in 3D (35 mm di
  profondità) che accoglie la scheda *e* lo Shelly esterno; la parte
  anteriore è il pannello frontale esistente.
- **Shelly 1PM Mini Gen4 esterno** — il relè di commutazione certificato con
  misura della potenza, cablato al di fuori della scheda.

La **divisione dei compiti** è il cuore del concetto: l'ESP misura il tempo e
invia allo Shelly un segnale hardware isolato galvanicamente; lo Shelly
commuta il carico e ne misura la potenza. Se il Wi-Fi si interrompe,
pulsanti, timer e commutazione continuano comunque a funzionare — solo il
comando remoto resta fermo.

## La catena di segnale

Dalla pressione del pulsante al carico commutato, il segnale attraversa
cinque stazioni, ciascuna con un solo compito:

```
Tasto  ─►  ESP32-C3  ─►  330 Ω  ─►  PhotoMOS  ─►  Shelly 1PM  ─►  Carico
S1–S3      misura il     limita     isola          commuta e        (pompa,
           tempo,        corrente   galvanica-      misura la         motore
           pilota        del LED    mente           potenza           mangime,
           l'OLED                                   230 V             luce …)
```

L'ESP lavora con i 3,3 V innocui e non deve mai toccare direttamente i
230 V. Il **PhotoMOS** è il ponte: separa completamente bassa tensione e
tensione di rete tramite la *luce*. Lo Shelly viene impostato su
**Switch/Follow** — il suo relè resta acceso esattamente per tutto il tempo
in cui è presente il nostro segnale; l'intera temporizzazione resta all'ESP.

## La scheda (hardware v2)

L'attuale versione 2 è disponibile come progetto KiCad completo in
`kicad-v2/`.

- **Dimensioni esterne** 101,6 × 77,5 mm, **quattro strati** (1,6 mm).
- **Tutta l'elettronica sul retro** — davanti restano solo i tre pulsanti e
  il connettore OLED (tutto ciò che si usa o si vede).
- I due **strati interni sono piani di massa continui** nella zona a bassa
  tensione → poche interferenze, Wi-Fi stabile.
- **Tensione di rete solo esterna:** le cinque reti a 230 V si trovano
  esclusivamente sugli strati esterni, in basso a sinistra, in una classe di
  rete propria con piste più larghe.
- **Distanza di dispersione di 6 mm** tra ogni rete a 230 V e ogni bassa
  tensione — definita come regola di verifica fissa in KiCad (`.kicad_dru`).
  L'unica eccezione è il PhotoMOS K1: il suo involucro *è* il punto di
  isolamento certificato.

### Assegnazione GPIO — corrispondenza vincolante scheda ↔ firmware

Questa assegnazione deve corrispondere esattamente su entrambi i lati,
altrimenti il dispositivo non funziona:

| Pin ESP | Firmware | Scheda / rete | Funzione |
|---------|----------|----------------|----------|
| **GPIO3** | `btn_s1` (ingresso, pull-up, invertito) | Pad 3 → `/BTN1` | Pulsante **S1 Down/Manual** (T1) → Timer 1 |
| **GPIO4** | `btn_s2` | Pad 4 → `/BTN2` | Pulsante **S2 SET** (T2) → Timer 2 / pressione lunga: menu |
| **GPIO5** | `btn_s3` | Pad 5 → `/BTN3` | Pulsante **S3 UP** (T3) → Timer 3 / pressione lunga: Stop |
| **GPIO6** | `shelly_trigger` (uscita) | Pad 6 → `/PMOS_DRV` → R1 330 Ω → LED K1 | Pilotaggio PhotoMOS: HIGH = carico acceso |
| **GPIO7** | `i2c: sda` (400 kHz) | Pad 7 → `/SDA` → OLED J2.4 | Linea dati I²C verso l'OLED |
| **GPIO8** | `status_led` (WS2812, GRB) | interno al modulo (Pad 8 libero) | LED RGB di stato integrato (semaforo) |
| **GPIO9** | `i2c: scl` (400 kHz) | Pad 9 → `/SCL` → OLED J2.3 | Linea di clock I²C verso l'OLED (indirizzo 0x3C) |
| **5V / GND** | Alimentazione del modulo | `/+5V` / `GND` dall'alimentatore | Alimentazione + massa comune |
| **3V3** | Regolatore integrato | `/+3V3` → OLED-VCC | 3,3 V per l'OLED |

> **Importante:** SDA si trova intenzionalmente su **GPIO7**, non GPIO8 — su
> GPIO8 si trova il WS2812 integrato. Se lì ci fosse l'I²C, l'OLED
> rimarrebbe nero e il traffico dati disturberebbe il LED.

### Morsetti di collegamento e reti

| Morsetto | Collegamento | Assegnazione |
|--------|-----------|------------------|
| **X1** | Ingresso rete | 1 = N, 2 = L_IN (230 V in ingresso) |
| **X2** | Uscita carico | 1 = O (commutato), 2 = N |
| **X3** | Snubber | 1 = O, 2 = N — rete RC opzionale per carichi induttivi |
| **J1** | Shelly (esterno) | 1 = SW, 2 = O, 3 = L, 4 = N |
| **J2** | OLED | GND / VCC / SCL / SDA (a innesto) |

Le cinque reti a 230 V della classe di rete «230V»: `L_IN` (non protetta,
X1→F1), `L_F` (protetta, F1→RV1/PS1/K1.3/Shelly-L), `N` (neutro),
`SW_SHELLY` (commutata, K1.4→Shelly-SW) e `O_LAST` (commutata,
Shelly-O→X2/X3).

### Componenti principali

| Sigla | Componente | Funzione |
|---------|---------|------------------|
| **U1** | ESP32-C3 Super Mini | Microcontrollore con Wi-Fi, 5 V→3,3 V; porta il WS2812 su GPIO8 |
| **K1** | PhotoMOS G3VM-601AY2 (o -601BY / AQY216) | Isolamento galvanico 3,3 V ↔ 230 V, **≥ 400 V** |
| **PS1** | Modulo AC/DC TSP-05 (5 V / 3 W) | Alimentatore da L_F + N |
| **R1** | 330 Ω | Resistenza di limitazione del LED di K1 (~6 mA) |
| **C1 / C2** | 220 µF / 100 nF | Buffer 5 V (picchi Wi-Fi) + disaccoppiamento |
| **F1** | 1 A ritardato, 5×20 mm | fusibile primario (X1→F1→L_F) |
| **RV1** | Varistore S14K275 | Protezione da sovratensione tra L_F e N |
| **SW1–3** | Pulsante 6×6 mm | i tre micropulsanti (posizione fissa, pannello frontale) |

## Il firmware

Il firmware è un progetto **ESPHome** (`firmware/timer-relais-c3.yaml`) con
estensioni C++ proprie. Nome del dispositivo/hostname: **`feeder-relais`**
(→ `http://feeder-relais.local`).

- **Logica del timer:** tre tempi indipendenti (1–600 s), modificabili via
  web durante il funzionamento; una pressione breve avvia, una pressione
  lunga su UP arresta tutto.
- **App web mobile propria + API JSON** (`firmware/timer_web.h`) sulla
  porta 80 — nessun servizio cloud. Endpoint: `/api/status`,
  `/api/trigger`, `/api/stop`, `/api/config`, `/api/net`, `/api/wifi`,
  `/api/reboot`.
- **Display OLED** (SSD1306 128×32): ricezione Wi-Fi, orologio NTP grande,
  data, memoria libera; durante il timer, il conto alla rovescia in
  secondi. Visualizzazione ruotata di 180° (adattata alla posizione di
  montaggio).
- **Semaforo di stato** tramite il WS2812 integrato (GPIO8): **verde** =
  pronto, **giallo** = timer in corso, **rosso** = anomalia.
- **Configurazione di rete a runtime** (`firmware/net_config.h`): modalità
  IP DHCP/statica, server NTP, hostname, roaming 802.11k/v.
- **Multilingue** (web + OLED): tedesco / inglese / francese, selezionabile
  per l'intero dispositivo.
- **Provisioning tramite captive portal** — nessuna password Wi-Fi
  compilata nel firmware; le credenziali sopravvivono a un aggiornamento.
- **Aggiornamenti via etere (OTA)** tramite la piattaforma `web_server`
  (`POST /update`), oltre a un buffer circolare di log/debug (`/api/log`).

Le immagini flash già pronte (factory + OTA) si trovano in
`firmware/build/`.

## Utilizzo

**Sul dispositivo** — tre pulsanti:

| Pulsante | breve | lungo |
|-------|------|--------------|
| **S1** Down/Manual | Avvia Timer 1 | — |
| **S2** SET | Avvia Timer 2 | ≥ 3 s: menu informazioni (scorrere con S1/S3) |
| **S3** UP | Avvia Timer 3 | ≥ 1,2 s: arresta tutti i timer |

**Da mobile** — nel browser `http://feeder-relais.local`: avviare i timer,
impostare i tre tempi, consultare i valori di rete e di stato, scegliere la
lingua.

## L'involucro (stampa 3D)

L'involucro è composto dalla **parte anteriore** esistente (pannello
frontale originale con finestrella e pulsanti a stantuffo) e da una **parte
posteriore** stampata in proprio:

- Sorgente `box/feeder_back.scad` (OpenSCAD), file pronto
  `box/feeder_back_35mm.stl`.
- **Profondità 35 mm** (invece dei 5,7 mm originali), per far entrare
  scheda *e* Shelly.
- Sei colonnette filettate (passo 45 × 70 mm), linguetta di sospensione con
  foro a serratura.
- `box/Timer-Ersatzplatine-v2-BOARD.stl` è una **sagoma in scala 1:1**
  della scheda — stamparla piatta e inserirla per verificare
  l'accoppiamento **prima** di ordinare la scheda vera.

## Integrazione con ioBroker

Il Feeder-Relais è il **lato hardware** di un distributore automatico di
mangime e si integra bene in un sistema di domotica:

- Lo **Shelly 1PM Mini Gen4 esterno** viene integrato in ioBroker in modo
  nativo tramite l'**adattatore Shelly** — stato di commutazione e misura
  della potenza sono direttamente visibili e controllabili.
- La **API JSON propria** del dispositivo (`/api/status | trigger | stop |
  config`) può essere letta e comandata via REST/script (ad es.
  `simple-api`, adattatore JavaScript) — per l'avvio dei timer e
  l'interrogazione dello stato.

Nello stesso ambito «Smart-Pond/Feeder» esistono due adattatori dello
stesso autore che costituiscono il **lato software**:

- **[ioBroker.automatic-feeder](https://github.com/ssbingo/ioBroker.automatic-feeder)**
  — pianificazione oraria, modello di temperatura, alba/tramonto, pause e
  notifiche per un distributore automatico di mangime per pesci/koi/laghetto.
- **[ioBroker.vis-2-widgets-automatic-feeder](https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder)**
  — widget dashboard vis-2 già pronti (vista in tempo reale e comando
  remoto) per l'adattatore sopra indicato.

In questo modo l'hardware (questo dispositivo + Shelly), insieme ai due
adattatori, forma una catena continua dal pulsante alla dashboard.

## Autocostruzione e manuale

Un **manuale completo, adatto ai principianti** guida passo dopo passo
dalla scheda vuota al dispositivo finito — con sicurezza, lista della
spesa, produzione della scheda, montaggio dei componenti, flashing del
firmware e messa in servizio, con indice cliccabile incluso:

**➡️ [docs/it/Feeder-Relais-Manuale.pdf](docs/it/Feeder-Relais-Manuale.pdf)**
(per le altre lingue vedi la [tabella delle lingue](#-sprachen--languages)
qui sopra.)

Flashing del firmware (ESP via USB-C):

```bash
esphome run firmware/timer-relais-c3.yaml
```

## Struttura del progetto

```
kicad-v2/     Scheda v2 (KiCad: schema elettrico, layout, regola dei 6 mm, footprint, modelli 3D)
box/          Parte posteriore dell'involucro (sorgente OpenSCAD + STL) e sagoma della scheda
firmware/     Firmware ESPHome (.yaml + .h), immagini flash già pronte in build/
docs/         PDF del manuale (tedesco) e traduzioni in docs/<lingua>/
README.md     questo documento (tedesco; traduzioni in docs/<lingua>/)
```

## Stato

**Versione 2 con sviluppo completato — prima della produzione.** Scheda
instradata a 4 strati (DRC senza errori reali), scheda e firmware allineati
(OLED-SDA su GPIO7), involucro e documentazione completi. Da fare:
rigenerare i Gerber, prova di accoppiamento della sagoma, ordine a 4
strati, montaggio e collaudo funzionale.

## Licenza

Questo progetto (hardware, firmware, involucro e documentazione) è
distribuito con la licenza **Creative Commons Attribuzione – Non
commerciale – Condividi allo stesso modo 4.0 Internazionale (CC
BY-NC-SA 4.0)**.

© 2026 Silvio Sternitzke

Sei libero di:

- **Condividere** — riprodurre e ridistribuire il materiale con qualsiasi
  mezzo e formato,
- **Modificare** — remixare, trasformare il materiale e crearne altri a
  partire da esso,

alle seguenti condizioni:

- **Attribuzione (BY)** — devi indicare l'autore, fornire un link alla
  licenza e segnalare se sono state effettuate modifiche.
- **Non commerciale (NC)** — non puoi utilizzare il materiale per scopi
  commerciali.
- **Condividi allo stesso modo (SA)** — se remixi, trasformi o sviluppi il
  materiale, devi distribuire i tuoi contributi con la stessa licenza
  dell'originale.
- **Nessuna restrizione aggiuntiva** — non puoi applicare termini legali o
  misure tecnologiche che impediscano legalmente ad altri di fare ciò che
  la licenza consente.

Testo della licenza:
<https://creativecommons.org/licenses/by-nc-sa/4.0/deed.it> · per il testo
legale completo vedi [LICENSE](LICENSE).

> **Esclusione di responsabilità:** l'autocostruzione avviene sotto la
> propria responsabilità. 230 volt sono pericolosi per la vita. Il
> materiale viene fornito senza alcuna garanzia; è esclusa qualsiasi
> responsabilità per danni. In caso di dubbio, rivolgersi a un elettricista
> qualificato.

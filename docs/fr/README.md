# <img src="../../logo.svg" alt="Feeder-Relais Logo" height="30" align="top"> Feeder-Relais

<p align="center">
  <a href="https://www.buymeacoffee.com/ssbingo"><img src="https://img.buymeacoffee.com/button-api/?text=Buy%20me%20a%20coffee&emoji=&slug=ssbingo&button_colour=FFDD00&font_colour=000000&font_family=Cookie&outline_colour=000000&coffee_colour=ffffff" alt="Buy me a coffee" /></a>
</p>

**Commande de minuterie 230 V à construire soi-même — ESP32-C3 · OLED · PhotoMOS · Shelly 1PM Mini Gen4 externe**

Le Feeder-Relais est une carte de commande faite maison qui met sous tension
une charge 230 volts sur simple pression d'un bouton, pour une
**durée réglable**, puis la coupe automatiquement. Son nom vient de son
usage d'origine : elle remplace la carte de programmation horaire
défectueuse d'un **distributeur de nourriture automatique** (*feeder* en
anglais). Comme elle se contente, au fond, d'« actionner un interrupteur
pendant un certain temps », elle convient à toute charge que l'on souhaite
commander de façon temporisée — pompe, moteur de distribution de
nourriture, ventilateur, éclairage.

Trois boutons déclenchent trois durées réglables séparément (par défaut
5/10/15 s), un OLED affiche le Wi-Fi, l'heure et le compte à rebours, et une
interface web optimisée pour mobile permet la commande et la configuration
sur le réseau domestique — **sans application et sans cloud**. La
commutation proprement dite et la mesure de puissance sont assurées par un
**Shelly 1PM Mini Gen4 externe** ; la carte pilote son entrée SW via un
**relais PhotoMOS à isolation galvanique**. La fonction principale est
ainsi **indépendante du Wi-Fi**.

> ### ⚠️ 230 volts — danger de mort
> La tension secteur peut être mortelle. Le montage, le contrôle et la mise
> en service du côté 230 V doivent être confiés à un(e)
> **électricien(ne) qualifié(e)** ou à une personne formée. Tous les tests
> réalisables sans professionnel se déroulent **exclusivement via USB et
> sans aucune tension secteur**. Merci de lire d'abord le chapitre 2 du
> manuel.

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

## Sommaire

1. [Aperçu](#aperçu)
2. [La chaîne de signal](#la-chaîne-de-signal)
3. [La carte (matériel v2)](#la-carte-matériel-v2)
4. [Le firmware](#le-firmware)
5. [Utilisation](#utilisation)
6. [Le boîtier (impression 3D)](#le-boîtier-impression-3d)
7. [Intégration avec ioBroker](#intégration-avec-iobroker)
8. [Reproduction et manuel](#reproduction-et-manuel)
9. [Structure du projet](#structure-du-projet)
10. [Statut](#statut)
11. [Licence](#licence)

---

## Aperçu

L'appareil remplace une carte de minuterie d'origine derrière une façade
existante. Il se compose de quatre blocs bien séparables :

- **Carte** (`kicad-v2/`) — ESP32-C3, alimentation, PhotoMOS et les bornes
  230 V, quatre couches, électronique entièrement au dos.
- **Firmware** (`firmware/`) — projet ESPHome avec sa propre application
  web mobile, interface JSON, horloge NTP, affichage OLED, LED d'état et
  commande multilingue.
- **Boîtier** (`box/`) — partie arrière imprimée en 3D (35 mm de
  profondeur) qui accueille la carte *et* le Shelly externe ; la partie
  avant est la façade existante.
- **Shelly 1PM Mini Gen4 externe** — le relais de commutation certifié avec
  mesure de puissance, câblé à l'extérieur de la carte.

La **répartition des tâches** est au cœur du concept : l'ESP mesure le
temps et envoie un signal matériel isolé galvaniquement au Shelly ; le
Shelly commute la charge et mesure la puissance. Si le Wi-Fi tombe en
panne, les boutons, la minuterie et la commutation continuent malgré tout
de fonctionner — seule la télécommande est alors au repos.

## La chaîne de signal

De la pression du bouton jusqu'à la charge commutée, le signal traverse
cinq étapes, chacune avec exactement une tâche :

```
Bouton ─►  ESP32-C3  ─►  330 Ω  ─►  PhotoMOS  ─►  Shelly 1PM  ─►  Charge
S1–S3      compte le     limite      commute       commute et       (pompe,
           temps, dessine le courant   isolation    mesure la        moteur
           l'OLED         de la LED   galvanique     charge 230 V     d'aliment. …)
```

L'ESP fonctionne avec des 3,3 V sans danger et ne doit jamais toucher
directement 230 V. Le **PhotoMOS** est le pont entre les deux mondes : il
isole complètement basse tension et tension secteur par la *lumière*. Le
Shelly est réglé sur **Switch/Follow** — son relais reste activé exactement
aussi longtemps que notre signal est présent ; tout le minutage reste du
côté de l'ESP.

## La carte (matériel v2)

La version 2 actuelle est disponible, terminée, sous forme de projet KiCad
dans `kicad-v2/`.

- **Dimensions extérieures** 101,6 × 77,5 mm, **quatre couches** (1,6 mm).
- **Électronique entièrement au dos** — à l'avant ne restent que les trois
  boutons et le connecteur OLED (tout ce qui est actionné ou visible).
- Les deux **couches internes sont des plans de masse continus** dans la
  zone basse tension → peu de perturbations, Wi-Fi stable.
- **Tension secteur uniquement à l'extérieur :** les cinq nets 230 V se
  trouvent exclusivement sur les couches externes, en bas à gauche, dans
  une classe de réseau dédiée avec des pistes plus larges.
- **Ligne de fuite de 6 mm** entre chaque net 230 V et chaque basse
  tension — inscrite comme règle de contrôle KiCad fixe (`.kicad_dru`). La
  seule exception est le PhotoMOS K1 : son boîtier *est* le point de
  séparation certifié.

### Brochage GPIO — correspondance obligatoire carte ↔ firmware

Cette correspondance doit être exactement identique des deux côtés, sinon
l'appareil ne fonctionne pas :

| Broche ESP | Firmware | Carte / net | Fonction |
|---------|----------|----------------|----------|
| **GPIO3** | `btn_s1` (entrée, pull-up, inversé) | Pad 3 → `/BTN1` | Bouton **S1 Down/Manual** (T1) → minuterie 1 |
| **GPIO4** | `btn_s2` | Pad 4 → `/BTN2` | Bouton **S2 SET** (T2) → minuterie 2 / long : menu |
| **GPIO5** | `btn_s3` | Pad 5 → `/BTN3` | Bouton **S3 UP** (T3) → minuterie 3 / long : arrêt |
| **GPIO6** | `shelly_trigger` (sortie) | Pad 6 → `/PMOS_DRV` → R1 330 Ω → LED K1 | Pilote du PhotoMOS : HIGH = charge activée |
| **GPIO7** | `i2c: sda` (400 kHz) | Pad 7 → `/SDA` → OLED J2.4 | Ligne de données I²C vers l'OLED |
| **GPIO8** | `status_led` (WS2812, GRB) | interne au module (pad 8 libre) | LED RVB d'état embarquée (voyant) |
| **GPIO9** | `i2c: scl` (400 kHz) | Pad 9 → `/SCL` → OLED J2.3 | Ligne d'horloge I²C vers l'OLED (adresse 0x3C) |
| **5V / GND** | alimentation du module | `/+5V` / `GND` depuis l'alimentation | Alimentation + masse commune |
| **3V3** | régulateur embarqué | `/+3V3` → OLED-VCC | 3,3 V pour l'OLED |

> **Important :** SDA se trouve délibérément sur **GPIO7**, pas GPIO8 — sur
> GPIO8 se trouve la WS2812 embarquée. Si l'I²C s'y trouvait, l'OLED
> resterait noir et le trafic de données perturberait la LED.

### Bornes de raccordement et nets

| Borne | Raccordement | Brochage |
|--------|-----------|------------------|
| **X1** | Entrée secteur | 1 = N, 2 = L_IN (230 V entrant) |
| **X2** | Sortie de charge | 1 = O (commuté), 2 = N |
| **X3** | Snubber | 1 = O, 2 = N — circuit RC optionnel pour charges inductives |
| **J1** | Shelly (externe) | 1 = SW, 2 = O, 3 = L, 4 = N |
| **J2** | OLED | GND / VCC / SCL / SDA (enfiché) |

Les cinq nets 230 V de la classe de réseau « 230V » : `L_IN` (non protégé,
X1→F1), `L_F` (protégé, F1→RV1/PS1/K1.3/Shelly-L), `N` (neutre),
`SW_SHELLY` (commuté, K1.4→Shelly-SW) et `O_LAST` (commuté,
Shelly-O→X2/X3).

### Composants importants

| Repère | Composant | Fonction |
|---------|---------|------------------|
| **U1** | ESP32-C3 Super Mini | Microcontrôleur Wi-Fi, 5 V→3,3 V ; porte la WS2812 sur GPIO8 |
| **K1** | PhotoMOS G3VM-601AY2 (ou -601BY / AQY216) | Isolation galvanique 3,3 V ↔ 230 V, **≥ 400 V** |
| **PS1** | Module AC/DC TSP-05 (5 V / 3 W) | Alimentation à partir de L_F + N |
| **R1** | 330 Ω | Résistance de limitation de la LED de K1 (~6 mA) |
| **C1 / C2** | 220 µF / 100 nF | Tampon 5 V (pics Wi-Fi) + découplage |
| **F1** | 1 A temporisé, 5×20 mm | fusible fin côté primaire (X1→F1→L_F) |
| **RV1** | Varistance S14K275 | Protection contre les surtensions entre L_F et N |
| **SW1–3** | Boutons 6×6 mm | les trois boutons-poussoirs (position fixe, façade) |

## Le firmware

Le firmware est un projet **ESPHome** (`firmware/timer-relais-c3.yaml`)
avec ses propres extensions C++. Nom de l'appareil/hôte :
**`feeder-relais`** (→ `http://feeder-relais.local`).

- **Logique de minuterie :** trois durées indépendantes (1–600 s),
  modifiables via le web en cours de fonctionnement ; une pression brève
  démarre, une pression longue sur UP arrête tout.
- **Application web mobile et API JSON propres**
  (`firmware/timer_web.h`) sur le port 80 — aucun service cloud. Points
  d'accès : `/api/status`, `/api/trigger`, `/api/stop`, `/api/config`,
  `/api/net`, `/api/wifi`, `/api/reboot`.
- **Affichage OLED** (SSD1306 128×32) : réception Wi-Fi, grande horloge
  NTP, date, mémoire libre ; pendant la minuterie, le compte à rebours en
  secondes. Affichage pivoté à 180° (adapté à la position de montage).
- **Voyant d'état** via la WS2812 embarquée (GPIO8) : **vert** = prêt,
  **jaune** = minuterie en cours, **rouge** = anomalie.
- **Configuration réseau en temps réel** (`firmware/net_config.h`) : mode
  IP DHCP/statique, serveur NTP, nom d'hôte, itinérance 802.11k/v.
- **Multilingue** (web + OLED) : allemand / anglais / français,
  commutable pour tout l'appareil.
- **Provisioning par portail captif** — aucun mot de passe Wi-Fi compilé en
  dur ; les identifiants survivent à une mise à jour.
- **Mises à jour sans fil (OTA)** via la plateforme `web_server`
  (`POST /update`), ainsi qu'un tampon circulaire de journal/débogage
  (`/api/log`).

Des images de flashage prêtes (factory + OTA) se trouvent sous
`firmware/build/`.

## Utilisation

**Sur l'appareil** — trois boutons :

| Bouton | court | long |
|-------|------|--------------|
| **S1** Down/Manual | déclencher la minuterie 1 | — |
| **S2** SET | déclencher la minuterie 2 | ≥ 3 s : menu d'info (naviguer avec S1/S3) |
| **S3** UP | déclencher la minuterie 3 | ≥ 1,2 s : arrêter toutes les minuteries |

**Mobile** — dans le navigateur `http://feeder-relais.local` : déclencher
une minuterie, régler les trois durées, consulter les valeurs réseau et
d'état, choisir la langue.

## Le boîtier (impression 3D)

Le boîtier se compose de la **partie avant** existante (façade d'origine
avec vitre et poussoirs) et d'une **partie arrière** imprimée soi-même :

- Source `box/feeder_back.scad` (OpenSCAD), STL prêt
  `box/feeder_back_35mm.stl`.
- **35 mm de profondeur** (au lieu des 5,7 mm d'origine), afin que la carte
  *et* le Shelly y trouvent leur place.
- Six colonnettes de vissage (pas 45 × 70 mm), patte de suspension à trou
  en serrure.
- `box/Timer-Ersatzplatine-v2-BOARD.stl` est une **maquette 1:1** de la
  carte — à imprimer à plat et à poser à l'intérieur pour vérifier
  l'ajustement **avant** de commander la vraie carte.

## Intégration avec ioBroker

Le Feeder-Relais constitue le **côté matériel** d'un distributeur de
nourriture automatique et s'intègre bien dans une domotique :

- Le **Shelly 1PM Mini Gen4 externe** s'intègre nativement dans ioBroker
  via l'**adaptateur Shelly** — l'état de commutation et la mesure de
  puissance y sont directement visibles et pilotables.
- La **propre API JSON** de l'appareil
  (`/api/status | trigger | stop | config`) peut être lue et pilotée par
  REST/script (par ex. `simple-api`, adaptateur JavaScript) — pour
  déclencher la minuterie et interroger l'état.

Dans le même environnement « Smart-Pond/Feeder », il existe deux
adaptateurs correspondants du même auteur, qui constituent le **côté
logiciel** :

- **[ioBroker.automatic-feeder](https://github.com/ssbingo/ioBroker.automatic-feeder)**
  — planification horaire, modèle de température, lever/coucher du soleil,
  pauses et notifications pour un distributeur de nourriture pour
  poissons/koïs/bassin.
- **[ioBroker.vis-2-widgets-automatic-feeder](https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder)**
  — widgets de tableau de bord vis-2 prêts à l'emploi (vue en direct et
  télécommande) pour l'adaptateur ci-dessus.

Ainsi, le matériel (cet appareil + le Shelly), associé aux deux
adaptateurs, forme une chaîne continue depuis le bouton jusqu'au tableau de
bord.

## Reproduction et manuel

Un **manuel complet, accessible aux débutants**, guide pas à pas de la
carte vierge à l'appareil fini — avec sécurité, liste d'achats,
fabrication de la carte, soudure des composants, flashage du firmware et
mise en service, avec un sommaire cliquable :

**➡️ [docs/fr/Feeder-Relais-Manuel.pdf](docs/fr/Feeder-Relais-Manuel.pdf)**
(traductions : voir le [tableau des langues](#-sprachen--languages) ci-dessus.)

Flasher le firmware (ESP via USB-C) :

```bash
esphome run firmware/timer-relais-c3.yaml
```

## Structure du projet

```
kicad-v2/     carte v2 (KiCad : schéma, routage, règle des 6 mm, empreintes, modèles 3D)
box/          partie arrière du boîtier (source OpenSCAD + STL) et maquette de la carte
firmware/     firmware ESPHome (.yaml + .h), images de flashage prêtes dans build/
docs/         PDF du manuel (allemand) et traductions sous docs/<langue>/
README.md     ce document (allemand ; traductions sous docs/<langue>/)
```

## Statut

**Version 2 entièrement développée — avant la fabrication.** Carte routée
en 4 couches (DRC sans erreur réelle), carte et firmware alignés
(OLED-SDA sur GPIO7), boîtier et documentation terminés. Restant à
faire : régénérer les fichiers Gerber, essayage de la maquette, commande
en 4 couches, montage et test fonctionnel.

## Licence

Ce projet (matériel, firmware, boîtier et documentation) est placé sous la
licence **Creative Commons Attribution – Pas d'utilisation commerciale –
Partage dans les mêmes conditions 4.0 International (CC BY-NC-SA 4.0)**.

© 2026 Silvio Sternitzke

Vous êtes libre de :

- **Partager** — reproduire et redistribuer le matériel,
- **Adapter** — le remixer et vous en inspirer,

selon les conditions suivantes :

- **Attribution (BY)** — vous devez créditer l'auteur, fournir un lien vers
  la licence et indiquer si des modifications ont été apportées.
- **Pas d'utilisation commerciale (NC)** — non destiné à des fins
  commerciales.
- **Partage dans les mêmes conditions (SA)** — les adaptations doivent être
  diffusées sous la même licence.
- **Pas de restrictions supplémentaires** — vous n'êtes pas autorisé(e) à
  appliquer des clauses juridiques ou des mesures techniques qui
  restreindraient légalement autrui à faire ce que la licence autorise.

Texte de la licence :
<https://creativecommons.org/licenses/by-nc-sa/4.0/deed.fr> · texte
juridique complet dans [LICENSE](LICENSE).

> **Avertissement :** la reproduction se fait sous votre propre
> responsabilité. 230 volts sont mortels. Le matériel est fourni sans
> aucune garantie ; toute responsabilité pour des dommages est exclue. En
> cas de doute, faites appel à un(e) électricien(ne) qualifié(e).

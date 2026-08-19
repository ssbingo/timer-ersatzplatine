# <img src="../../logo.svg" alt="Feeder-Relais Logo" height="30" align="top"> Feeder-Relais

<p align="center">
  <a href="https://www.buymeacoffee.com/ssbingo"><img src="https://img.buymeacoffee.com/button-api/?text=Buy%20me%20a%20coffee&emoji=&slug=ssbingo&button_colour=FFDD00&font_colour=000000&font_family=Cookie&outline_colour=000000&coffee_colour=ffffff" alt="Buy me a coffee" /></a>
</p>

> **Origen:** Este proyecto es una conversión de un **SuperFish / Koi-Pro Fish Feeder** (comedero automático de Aquadistri — [gama de productos](https://aquadistri.com/de/brands/koi-pro/einrichtung-zubehoer/zubehoer/) · [manual original (PDF)](../Koi-Pro-FishFeeder-Original-Manual.pdf)) — sustituye la placa de temporizador original defectuosa. **La parte trasera de la carcasa y la placa siguen las dimensiones del controlador original**, de modo que ambas encajan exactamente en la carcasa existente.

**Control de temporizador de 230 V para autoconstrucción — ESP32-C3 · OLED · PhotoMOS · Shelly 1PM Mini Gen4 externo**

El Feeder-Relais es una placa de control autoconstruida que enciende una carga
de 230 voltios pulsando un botón durante un **tiempo ajustable** y luego se
apaga sola. El nombre proviene de su uso original: sustituye la placa
temporizadora defectuosa de un **comedero automático** (en inglés *feeder*).
Como en el fondo solo «pulsa un interruptor durante un tiempo determinado»,
sirve para cualquier carga que deba conmutarse de forma temporizada — bomba,
motor de alimentación, ventilador, luz.

Tres pulsadores activan tres tiempos ajustables por separado (por defecto
5/10/15 s), una pantalla OLED muestra el WiFi, la hora y la cuenta atrás, y
una interfaz web optimizada para móviles permite el manejo y la configuración
en la red doméstica — **sin app y sin nube**. La conmutación propiamente
dicha y la medición de potencia las realiza un **Shelly 1PM Mini Gen4
externo**; la placa controla su entrada SW mediante un **relé PhotoMOS con
aislamiento galvánico**. Gracias a ello, la función principal es
**independiente del WiFi**.

> ### ⚠️ 230 voltios — Peligro de muerte
> La tensión de red puede ser mortal. El montaje, la comprobación y la
> puesta en marcha del lado de 230 V deben quedar en manos de un
> **electricista cualificado** o una persona instruida. Todas las pruebas
> que se pueden realizar sin personal cualificado se llevan a cabo
> **exclusivamente por USB y sin ninguna tensión de red**. Por favor, lee
> primero el capítulo 2 del manual.

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

## Contenido

1. [Descripción general](#descripción-general)
2. [La cadena de señal](#la-cadena-de-señal)
3. [La placa (hardware v3)](#la-placa-hardware-v3)
4. [El firmware](#el-firmware)
5. [Manejo](#manejo)
6. [La carcasa (impresión 3D)](#la-carcasa-impresión-3d)
7. [Conexión con ioBroker](#conexión-con-iobroker)
8. [Réplica y manual](#réplica-y-manual)
9. [Estructura del proyecto](#estructura-del-proyecto)
10. [Estado](#estado)
11. [Licencia](#licencia)

---

## Descripción general

El dispositivo sustituye una placa temporizadora original detrás de un panel
frontal existente. Consta de cuatro módulos claramente separables:

- **Placa** (`kicad-v3/`) — ESP32-C3, fuente de alimentación, PhotoMOS y los
  bornes de 230 V, de cuatro capas, con toda la electrónica en la cara
  posterior.
- **Firmware** (`firmware/`) — proyecto ESPHome con su propia aplicación web
  móvil, interfaz JSON, reloj NTP, pantalla OLED, LED de estado y manejo
  multilingüe.
- **Carcasa** (`box/`) — parte trasera impresa en 3D (35 mm de profundidad)
  que aloja la placa *y* el Shelly externo; la parte delantera es el panel
  frontal existente.
- **Shelly 1PM Mini Gen4 externo** — el relé de conmutación certificado con
  medición de potencia, cableado fuera de la placa.

El núcleo del concepto es la **división de tareas**: el ESP mide el tiempo y
envía una señal de hardware con aislamiento galvánico al Shelly; el Shelly
conmuta la carga y mide la potencia. Si falla el WiFi, los botones, el
temporizador y la conmutación siguen funcionando — solo el control remoto
queda inactivo.

## La cadena de señal

Desde que se pulsa el botón hasta que se conmuta la carga, la señal recorre
cinco etapas, cada una con una única función:

```
Botón  ─►  ESP32-C3  ─►  330 Ω  ─►  PhotoMOS  ─►  Shelly 1PM  ─►  Carga
S1–S3      cuenta el     limita la   conmuta con    conmuta y        (bomba,
           tiempo,       corriente   aislamiento    mide la carga    motor de
           dibuja el     del LED     galvánico      de 230 V         alimentación,
           OLED                                                      ventilador …)
```

El ESP trabaja con unos inofensivos 3,3 V y no debe «tocar» nunca 230 V
directamente. El **PhotoMOS** es el puente: separa por completo la baja
tensión y la tensión de red mediante *luz*. El Shelly se configura en
**Switch/Follow**: su relé permanece encendido exactamente el tiempo que
nuestra señal esté activa; toda la temporización sigue en manos del ESP.

## La placa (hardware v3)

La versión 2 actual está terminada como proyecto KiCad en `kicad-v3/`.

- **Medida exterior** 101,6 × 77,5 mm, **cuatro capas** (1,6 mm).
- **Toda la electrónica en la cara posterior** — en la parte delantera solo
  quedan los tres pulsadores y el conector OLED (todo lo que se maneja o se
  ve).
- Las dos **capas internas son planos de masa continuos** en la zona de baja
  tensión → bajo nivel de interferencias, WiFi estable.
- **Tensión de red solo en el exterior:** las cinco redes de 230 V se
  encuentran exclusivamente en las capas externas, abajo a la izquierda, en
  una clase de red propia con pistas más anchas.
- **Distancia de fuga de 6 mm** entre cada red de 230 V y cada baja tensión —
  establecida como regla de comprobación fija de KiCad (`.kicad_dru`). La
  única excepción es el PhotoMOS K1: su encapsulado *es* el punto de
  aislamiento certificado.

### Asignación de GPIO — correspondencia vinculante placa ↔ firmware

Esta asignación debe coincidir exactamente en ambos lados; de lo contrario,
el dispositivo no funcionará:

| Pin ESP | Firmware | Placa / red | Función |
|---------|----------|----------------|----------|
| **GPIO3** | `btn_s1` (entrada, pull-up, invertido) | Pad 3 → `/BTN1` | Pulsador **S1 Down/Manual** (T1) → temporizador 1 |
| **GPIO4** | `btn_s2` | Pad 4 → `/BTN2` | Pulsador **S2 SET** (T2) → temporizador 2 / pulsación larga: menú |
| **GPIO5** | `btn_s3` | Pad 5 → `/BTN3` | Pulsador **S3 UP** (T3) → temporizador 3 / pulsación larga: parada |
| **GPIO6** | `shelly_trigger` (salida) | Pad 6 → `/PMOS_DRV` → R1 330 Ω → K1-LED | Excitador del PhotoMOS: HIGH = carga encendida |
| **GPIO7** | `i2c: sda` (400 kHz) | Pad 7 → `/SDA` → OLED J2.4 | Línea de datos I²C hacia el OLED |
| **GPIO8** | `status_led` (WS2812, GRB) | interno al módulo (Pad 8 libre) | LED RGB de estado integrado (semáforo) |
| **GPIO9** | `i2c: scl` (400 kHz) | Pad 9 → `/SCL` → OLED J2.3 | Línea de reloj I²C hacia el OLED (dirección 0x3C) |
| **5V / GND** | Alimentación del módulo | `/+5V` / `GND` de la fuente de alimentación | Alimentación + masa común |
| **3V3** | Regulador integrado | `/+3V3` → OLED-VCC | 3,3 V para el OLED |

> **Importante:** SDA se ha colocado deliberadamente en **GPIO7**, no en
> GPIO8 — en GPIO8 está el WS2812 integrado. Si ahí estuviera el I²C, el
> OLED se quedaría en negro y el tráfico de datos interferiría con el LED.

### Bornes de conexión y redes

| Borne | Conexión | Asignación |
|--------|-----------|------------------|
| **X1** | Entrada de red | 1 = N, 2 = L_IN (230 V entrante) |
| **X2** | Salida de carga | 1 = O (conmutado), 2 = N |
| **X3** | Snubber | 1 = O, 2 = N — red RC opcional para cargas inductivas |
| **J1** | Shelly (externo) | 1 = SW, 2 = O, 3 = L, 4 = N |
| **J2** | OLED | GND / VCC / SCL / SDA (enchufable) |

Las cinco redes de 230 V de la clase de red «230V»: `L_IN` (sin proteger,
X1→F1), `L_F` (protegida, F1→RV1/PS1/K1.3/Shelly-L), `N` (neutro),
`SW_SHELLY` (conmutado, K1.4→Shelly-SW) y `O_LAST` (conmutado,
Shelly-O→X2/X3).

### Componentes principales

| Referencia | Componente | Función |
|---------|---------|------------------|
| **U1** | ESP32-C3 Super Mini | Microcontrolador con WiFi, 5 V→3,3 V; incorpora el WS2812 en GPIO8 |
| **K1** | PhotoMOS G3VM-601AY2 (o -601BY / AQY216) | Aislamiento galvánico 3,3 V ↔ 230 V, **≥ 400 V** |
| **PS1** | Módulo AC/DC TSP-05 (5 V / 3 W) | Fuente de alimentación a partir de L_F + N |
| **R1** | 330 Ω | Resistencia limitadora del LED de K1 (~6 mA) |
| **C1 / C2** | 220 µF / 100 nF | Amortiguación de 5 V (picos de WiFi) + desacoplo |
| **F1** | 1 A lento, 5×20 mm | fusible de precisión del lado primario (X1→F1→L_F) |
| **RV1** | Varistor S14K275 | Protección contra sobretensión entre L_F y N |
| **SW1–3** | Pulsador 6×6 mm | los tres micropulsadores (posición fija, panel frontal) |

## El firmware

El firmware es un proyecto **ESPHome** (`firmware/timer-relais-c3.yaml`) con
extensiones propias en C++. Nombre del dispositivo/hostname:
**`feeder-relais`** (→ `http://feeder-relais.local`).

- **Lógica del temporizador:** tres tiempos independientes (1–600 s),
  modificables por web durante el funcionamiento; una pulsación corta
  inicia, una pulsación larga en UP detiene todo.
- **Aplicación web móvil propia + API JSON** (`firmware/timer_web.h`) en el
  puerto 80 — sin servicio en la nube. Puntos finales: `/api/status`,
  `/api/trigger`, `/api/stop`, `/api/config`, `/api/net`, `/api/wifi`,
  `/api/reboot`.
- **Pantalla OLED** (SSD1306 128×32): recepción WiFi, reloj NTP grande,
  fecha, memoria libre; durante el temporizador, la cuenta atrás en
  segundos. Pantalla girada 180° (adaptada a la posición de montaje).
- **Semáforo de estado** mediante el WS2812 integrado (GPIO8): **verde** =
  listo, **amarillo** = temporizador en marcha, **rojo** = fallo.
- **Configuración de red en tiempo de ejecución** (`firmware/net_config.h`):
  modo IP DHCP/estático, servidor NTP, hostname, roaming 802.11k/v.
- **Multilingüe** (web + OLED): alemán / inglés / francés, conmutable para
  todo el dispositivo.
- **Aprovisionamiento mediante portal cautivo** — ninguna contraseña WiFi
  está precompilada; las credenciales sobreviven a una actualización.
- **Actualizaciones inalámbricas (OTA)** a través de la plataforma
  `web_server` (`POST /update`), además de un búfer circular de
  registro/depuración (`/api/log`).

Las imágenes de flasheo ya preparadas (factory + OTA) se encuentran en
`firmware/build/`.

## Manejo

**En el dispositivo** — tres pulsadores:

| Botón | corta | larga |
|-------|------|--------------|
| **S1** Down/Manual | Activa el temporizador 1 | — |
| **S2** SET | Activa el temporizador 2 | ≥ 3 s: menú de información (navegar con S1/S3) |
| **S3** UP | Activa el temporizador 3 | ≥ 1,2 s: detiene todos los temporizadores |

**Móvil** — en el navegador `http://feeder-relais.local`: activar el
temporizador, ajustar los tres tiempos, consultar los valores de red y
estado, elegir el idioma.

## La carcasa (impresión 3D)

La carcasa consta de la **parte delantera** existente (panel frontal
original con ventana y varillas pulsadoras) y una **parte trasera** impresa
por uno mismo:

- Fuente `box/feeder_back.scad` (OpenSCAD), archivo listo
  `box/feeder_back_35mm.stl`.
- **35 mm de profundidad** (en lugar de los 5,7 mm originales), para que
  quepan la placa *y* el Shelly.
- Seis columnas de tornillo (retícula 45 × 70 mm), lengüeta de suspensión
  con ojo de cerradura.
- `box/Timer-Ersatzplatine-v3-BOARD.stl` es una **maqueta 1:1** de la placa —
  imprímela plana y colócala dentro para comprobar el ajuste **antes** de
  encargar la placa real.

## Conexión con ioBroker

El Feeder-Relais es el **lado del hardware** de un comedero automático y se
integra bien en una domótica:

- El **Shelly 1PM Mini Gen4 externo** se integra de forma nativa en
  ioBroker mediante el **adaptador Shelly** — el estado de conmutación y la
  medición de potencia son directamente visibles y controlables ahí.
- La **API JSON propia** del dispositivo (`/api/status | trigger | stop |
  config`) puede leerse y manejarse mediante REST/script (p. ej.
  `simple-api`, adaptador JavaScript) — para activar el temporizador y
  consultar el estado.

En el mismo entorno «Smart-Pond/Feeder» existen dos adaptadores adecuados
del mismo autor, que constituyen el **lado del software**:

- **[ioBroker.automatic-feeder](https://github.com/ssbingo/ioBroker.automatic-feeder)**
  — planificación horaria, modelo de temperatura, salida/puesta de sol,
  pausas y notificaciones para un comedero automático de peces/koi/estanque.
- **[ioBroker.vis-2-widgets-automatic-feeder](https://github.com/ssbingo/ioBroker.vis-2-widgets-automatic-feeder)**
  — widgets de panel vis-2 ya preparados (vista en vivo y control remoto)
  para el adaptador anterior.

Así, el hardware (este dispositivo + Shelly) forma junto con los dos
adaptadores una cadena continua desde el botón hasta el panel de control.

## Réplica y manual

Un **manual completo apto para principiantes** guía paso a paso desde la
placa vacía hasta el dispositivo terminado — con seguridad, lista de
compras, fabricación de la placa, montaje, flasheo del firmware y puesta en
marcha, incluyendo un índice con enlaces:

**➡️ [docs/es/Feeder-Relais-Manual.pdf](docs/es/Feeder-Relais-Manual.pdf)**
(para otras traducciones, véase la [tabla de idiomas](#-sprachen--languages)
más arriba.)

Flashear el firmware (ESP por USB-C):

```bash
esphome run firmware/timer-relais-c3.yaml
```

## Estructura del proyecto

```
kicad-v3/     Placa v3 (KiCad: esquemático, layout, regla de 6 mm, footprints, modelos 3D)
box/          Parte trasera de la carcasa (fuente OpenSCAD + STL) y maqueta de la placa
firmware/     Firmware ESPHome (.yaml + .h), imágenes de flasheo listas en build/
docs/         PDF del manual (alemán) y traducciones en docs/<idioma>/
README.md     este documento (alemán; traducciones en docs/<idioma>/)
```

## Estado

**Versión 2 desarrollada por completo — antes de la fabricación.** Placa
enrutada en 4 capas (DRC sin errores reales), placa y firmware coordinados
(OLED-SDA en GPIO7), carcasa y documentación terminadas. Pendiente: generar
los Gerber de nuevo, prueba de ajuste de la maqueta, pedido de 4 capas,
montaje y prueba funcional.

## Licencia

Este proyecto (hardware, firmware, carcasa y documentación) está bajo la
licencia **Creative Commons Reconocimiento – NoComercial – CompartirIgual
4.0 Internacional (CC BY-NC-SA 4.0)**.

© 2026 Silvio Sternitzke

Eres libre de:

- **Compartir** — copiar y redistribuir el material,
- **Adaptar** — remezclarlo y construir a partir de él,

bajo las siguientes condiciones:

- **Reconocimiento (BY)** — debes citar al autor, enlazar la licencia e
  indicar si se han realizado cambios.
- **NoComercial (NC)** — no puede utilizarse con fines comerciales.
- **CompartirIgual (SA)** — las obras derivadas deben distribuirse bajo la
  misma licencia.
- **Sin restricciones adicionales** — no se pueden aplicar cláusulas
  adicionales ni medidas tecnológicas que restrinjan legalmente a otros
  hacer lo que la licencia permite.

Texto de la licencia:
<https://creativecommons.org/licenses/by-nc-sa/4.0/deed.es> · el texto
legal completo se encuentra en [LICENSE](LICENSE).

> **Exención de responsabilidad:** la réplica se realiza bajo la
> responsabilidad propia de cada persona. 230 voltios son mortales. El
> material se ofrece sin garantía; se excluye toda responsabilidad por
> daños. En caso de duda, consulta a un electricista cualificado.

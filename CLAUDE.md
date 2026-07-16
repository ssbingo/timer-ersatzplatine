# CLAUDE.md — Arbeitsanweisung für dieses Projekt

Dieses Repository enthält die Entwicklung einer 230-V-Timer-Ersatzplatine
(ESP32-C3 + OLED + Shelly 1PM Mini Gen4). Vollständiger Kontext:
`docs/DOKUMENTATION.md`. Aufgaben und Status: `docs/PROJEKTPLAN.md`.
**Beide Dokumente sind bei jeder Änderung mitzupflegen** (Changelog in
der Doku Kap. 10, Checkboxen/Entscheidungslog im Projektplan).

## Grundregeln

1. **Quelle der Wahrheit für alle Geometrie ist `hardware/platine_template.py`.**
   Die DXF wird niemals von Hand editiert, sondern regeneriert:
   ```bash
   pip install ezdxf
   cd hardware && python3 platine_template.py
   ```
2. **Koordinatensystem:** Ursprung = obere linke Ecke der ORIGINALPLATINE,
   x rechts, y nach UNTEN, Blick auf die Bestückungsseite. Die neue Kontur
   hat negative Koordinaten (x −14,2…91,1 / y −11,8…67,6). Niemals das
   Bezugssystem verschieben — alle Messwerte hängen daran.
3. **Messwerte sind heilig.** Werte mit Herkunft „Scan"/„Messung Silvio"
   nur ändern, wenn eine neue, bessere Messung vorliegt. Werte, die als
   ANNAHME kommentiert sind (WALL_T, RIBS-Richtungen, OLED-Offsets,
   Dompositionen ±1,5), warten auf Verifikation — siehe Projektplan
   Phase 3.
4. **Höhenbudget** (nicht verletzen): 16,5 mm über der Platine,
   ~1,8 mm darunter (nichts darf nach unten ragen!), ~12 mm im
   Fensterbereich (Glas + gestecktes OLED).
5. **Sicherheit:** Alle Netze L_IN, L_F, N, SW_SHELLY, O_LAST führen
   230 V. Kriechstrecke ≥ 6 mm zu Kleinspannung, DRC-Regel in Doku
   Kap. 7.6. Keine Vorschläge machen, die diese Regel aufweichen.
6. **PDF-Pflicht (zwingend):** `docs/DOKUMENTATION.md` und
   `docs/PROJEKTPLAN.md` werden bei JEDER Änderung auch als PDF neu
   erzeugt und mitgeliefert:
   ```bash
   pip install markdown weasyprint
   python3 tools/md2pdf.py docs/DOKUMENTATION.md docs/PROJEKTPLAN.md
   ```
   Ein Commit/Abgabestand ohne aktuelle PDFs ist unvollständig.
   **Sprachpolitik Doku:** Die **deutsche** `DOKUMENTATION.md` ist die
   **Quelle der Wahrheit** und wird bei jeder Änderung gepflegt. Die
   Übersetzungen `DOKUMENTATION.en.md` / `DOKUMENTATION.fr.md` werden **je
   Release** nachgezogen (nicht bei jeder Mini-Änderung); beim Release-Build
   dann alle drei Handbuch-PDFs + Projektplan-PDF erzeugen:
   ```bash
   python3 tools/md2pdf.py docs/DOKUMENTATION.md docs/DOKUMENTATION.en.md \
     docs/DOKUMENTATION.fr.md docs/PROJEKTPLAN.md
   ```
   `PROJEKTPLAN.md` bleibt nur Deutsch.
7. **Konsistenz-Dreieck:** Schaltplan (`timer_ersatzplatine.kicad_sch`),
   Firmware (`firmware/timer-relais-c3.yaml`) und Doku müssen dieselbe
   Pinbelegung tragen: T1/T2/T3 = GPIO3/4/5, PhotoMOS = GPIO6 (über
   330 Ω), SDA = GPIO7, SCL = GPIO9 (SDA war GPIO8 — dort sitzt die
   Onboard-RGB-LED WS2812, siehe unten), J4 = GND/VCC/SCL/SDA von oben.
   RGB-Status-LED (WS2812, onboard Super Mini) = GPIO8.
   Wer eine Seite ändert, ändert alle drei.
   Gehäuse-Beschriftung der Taster (Firmware/Doku): **S1 = Down/Manual
   (T1), S2 = SET (T2), S3 = UP (T3)**. Firmware-Gerätename/Default-
   Hostname ist **`feeder-relais`** (Produktname Feeder-Relais); der
   Board-/Repo-Name „timer-ersatzplatine" bleibt davon unberührt.

## Dateikarte

| Pfad | Rolle |
|------|-------|
| `hardware/platine_template.py` | parametrischer Generator (Geometrie v8) |
| `hardware/platine_original_geometrie.dxf` | generiert; KiCad-Import (Edge.Cuts + Referenzlayer) |
| `hardware/platine_vorschau.png` | generierter Render (Skript unten) |
| `hardware/timer_ersatzplatine.kicad_sch` | Schaltplan, KiCad-8-Format, eingebettete Symbole, Verbindungen über Netzlabels |
| `firmware/timer-relais-c3.yaml` | ESPHome; `secrets.yaml` wird lokal ergänzt, nicht einchecken |
| `firmware/timer_web.h` | Mobile Web-App + JSON-API (`AsyncWebHandler` auf `web_server_base`, Port 80); Endpunkte `/api/status\|trigger\|stop\|config\|net\|wifi\|reboot` |
| `firmware/net_config.h` | Persistente Netzwerk-Konfig (Prefs, NetCfg v4): IP-Modus DHCP/statisch (ESP-IDF-netif bei `wifi.on_connect`), NTP-Server (`esp_sntp_setservername`), Hostname zur Laufzeit (`mdns_hostname_set` + `esp_netif_set_hostname`), 802.11k/v-Roaming (`set_btm/set_rrm`), UI-Sprache `lang` (de/en/fr, `netcfg_lang_idx()`) |
| `firmware/log_ring.h` | Log-/Debug-Ringpuffer (`logger: on_message:` → `/api/log`); Web-OTA via `ota: platform: web_server` (`POST /update`) |
| `docs/DOKUMENTATION.md` | Gesamtdoku inkl. KiCad-Anleitung (deutsche **Quelle der Wahrheit**) |
| `docs/DOKUMENTATION.en.md` / `.fr.md` | Handbuch-Übersetzungen EN/FR (je Release nachgezogen; DE führend) |
| `docs/PROJEKTPLAN.md` | Phasen, Checklisten, Risiken, Entscheidungslog (nur Deutsch) |
| `docs/*.pdf` | generierte PDF-Fassungen (Pflichtabgabe, nie von Hand editieren) |
| `tools/md2pdf.py` | erzeugt die PDFs aus den Markdown-Quellen |

## Vorschau-Render (nach jeder Template-Änderung ausführen)

```python
# hardware/render_vorschau.py — bei Bedarf als Datei anlegen
import ezdxf
from PIL import Image, ImageDraw, ImageFont
doc = ezdxf.readfile('platine_original_geometrie.dxf')
msp = doc.modelspace()
S, OX, OY = 9, 16, 14
img = Image.new('RGB', (int(111*S), int(85.5*S)), (255,255,255))
d = ImageDraw.Draw(img)
colors = {'Edge_Cuts':(200,0,0),'Holes':(0,140,0),'Buttons':(0,0,200),
          'Display_alt':(150,150,150),'OLED_neu':(180,0,180),
          'Module_Ref':(0,150,200),'Keepout_Ref':(255,140,0)}
def P(x,y): return ((x+OX+2)*S, (67.6-y+OY-11.8+2)*S)
for e in msp:
    c = colors.get(e.dxf.layer,(0,0,0))
    if e.dxftype()=='LINE':
        d.line([P(e.dxf.start.x,e.dxf.start.y),P(e.dxf.end.x,e.dxf.end.y)],fill=c,width=2)
    elif e.dxftype()=='CIRCLE':
        x,y,r=e.dxf.center.x,e.dxf.center.y,e.dxf.radius
        p1=P(x-r,y+r);p2=P(x+r,y-r);d.ellipse([*p1,*p2],outline=c,width=2)
    elif e.dxftype()=='ARC':
        x,y,r=e.dxf.center.x,e.dxf.center.y,e.dxf.radius
        p1=P(x-r,y+r);p2=P(x+r,y-r)
        d.arc([*p1,*p2],-e.dxf.end_angle,-e.dxf.start_angle,fill=c,width=2)
    elif e.dxftype()=='LWPOLYLINE':
        d.polygon([P(p[0],p[1]) for p in e.get_points()],outline=c)
    elif e.dxftype()=='TEXT':
        try: f=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf',int(e.dxf.height*S))
        except: f=None
        d.text(P(e.dxf.insert.x,e.dxf.insert.y),e.dxf.text,
               fill=colors.get(e.dxf.layer,(0,0,0)),font=f,anchor='mm')
img.save('platine_vorschau.png')
```

## Nächste Schritte (Kurzfassung, Details im Projektplan)

Phase 3 abarbeiten: Papier-Anprobe, Stegrichtungen, TSP-Pinabstände,
OLED-Modulmaße, Glaseinstand/Stackhöhe → korrigierte Werte ins Template
→ regenerieren → Kontur einfrieren → dann Phase 4 (KiCad-Layout nach
Doku Kap. 7).

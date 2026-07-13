#!/usr/bin/env python3
# ============================================================================
# Ersatzplatine Timer - DXF-Generator fuer KiCad (Version 2)
# ----------------------------------------------------------------------------
# Masse in mm, Ursprung = obere linke Ecke der ORIGINALPLATINE, y nach unten.
# Der Umriss kann ueber EXT_* nach aussen wachsen (Gehaeuse-Innenraum!),
# der Ursprung und alle Originalkoordinaten bleiben dabei unveraendert.
#
# Messbasis: Loetseiten-Scan der Platine + Gehaeusescan, beide 300 dpi.
# Registrierung Gehaeuse->Platine ueber die 4 Rahmenschrauben (+/-0.4 mm).
# Kontur = Rahmenaussenkante - WALL_T (Wandstaerke, ANNAHME 2.0) - 1.0 Spiel.
# Genauigkeit: Kontur +/-1 mm (links +/-1.5). Schraubdome direkt vermessen
# (Messschieber, Silvio 2026-07-13) und als randoffene Schlitze ausgefuehrt.
# VOR BESTELLUNG: DXF 1:1 auf Papier drucken und im Gehaeuse anprobieren!
# ============================================================================

import ezdxf

# ---- Originalkontur ---------------------------------------------------------
BOARD_W = 76.7
BOARD_H = 66.1
CORNER_R = 4.0

# ---- Erweiterung ueber das Originalmass hinaus (aus Gehaeusescan) -----------
WALL_T = 2.0    # angenommene Wandstaerke Gehaeuseschale (Rand = Aussenkante-WALL_T)
EXT_L = 14.2
EXT_R = 14.4
EXT_T = 11.8
EXT_B = 1.5

# ---- Alte Aussparung: ENTFAELLT ---------------------------------------------
# Sie stellte nur den mittleren unteren Schraubdom frei; das uebernimmt
# jetzt der Kreis-Ausschnitt B5 in BOSS_CUTS.

# ---- Befestigungsloecher (Original) -----------------------------------------
HOLE_DIA = 3.0
HOLES = [
    ( 3.8,  4.1),   # oben links
    (73.1,  4.0),   # oben rechts
    ( 3.7, 39.6),   # mitte links
    (73.4, 50.7),   # mitte rechts
]
# Sperrzonen ueber der Platine (Referenzlayer Keepout_Ref):
# Schraubenkoepfe ~d8 an allen 4 Loechern + Stabilisierungsstege der
# 16.5-mm-Dome zum Plattenrand. Stegrichtungen = ANNAHME (nachsehen!):
#   Dom oben links/rechts -> Oberkante, Dom mitte links -> linker Rand,
#   Dom mitte rechts -> Unterkante (+ Variante rechter Rand mitgesperrt)
RIB_W = 4.0
RIBS = [   # (x0, y0, x1, y1) je Steg-Band
    ( 1.8, -11.8,  5.8,  4.1),   # h1 oben links -> Oberkante
    (71.1, -11.8, 75.1,  4.0),   # h2 oben rechts -> Oberkante
    (-14.2, 37.6,  3.7, 41.6),   # h3 mitte links -> linker Rand
    (71.4, 50.7, 75.4, 67.6),    # h4 mitte rechts -> Unterkante
    (73.4, 48.7, 91.1, 52.7),    # h4 Variante -> rechter Rand
]

# ---- Gehaeuse-Schraubdome: RANDOFFENE U-Ausschnitte (Edge.Cuts) --------------
# Statt geschlossener Bohrungen randoffene Schlitze -> toleranter beim Einsetzen,
# verzeiht Dom-Streuung entlang der Schlitzachse (Wunsch Silvio 2026-07-13).
# Messung Silvio 2026-07-13 (Messschieber, bis Dom-Mitte):
#   Rasterabstand je Reihe 45 mm, Reihenabstand 70 mm,
#   obere Dom-Linie 6 mm ueber Platinen-Oberkante      -> y = -6.0
#   linke Dom-Spalte  6 mm links der Platinen-Linkskante -> x = -6.0
# Absolut verankert; loest die Scan-Werte (v3, in y bis 2.6 mm daneben) ab.
DOME_D = 10.0                       # Schlitzbreite (klart Dom mit Reserve)
DOME_TOP_Y = -6.0                   # obere Reihe, oeffnet zur Oberkante
DOME_BOT_Y = DOME_TOP_Y + 70.0      # untere Reihe (Reihenabstand 70), zur Unterkante
DOME_X = [-6.0, -6.0 + 45.0, -6.0 + 90.0]   # 3 Spalten, Pitch 45, oben=unten
DOMES_TOP = [(x, DOME_TOP_Y) for x in DOME_X]   # B3, B2, B1
DOMES_BOT = [(x, DOME_BOT_Y) for x in DOME_X]   # B6, B5, B4

# ---- Kurzhubtaster 6x6 (Zentren) ---------------------------------------------
BTN_SIZE = 6.0
BUTTONS = [(13.2, 12.3), (38.8, 12.2), (64.1, 12.0)]

# ---- Sichtfenster (nur Referenz) / OLED-Anschluss -----------------------------
# Das OLED sitzt IM RAHMEN plan an der Glasscheibe - NICHT auf der Platine.
# Fensterbereich = Hoehenlimit ~12 mm (Glas + OLED-Modul darueber),
# ansonsten frei bestueckbar.
OLD_DISP = (18.4, 23.3, 53.6, 40.0)
# OLED wird DIREKT AUFGESTECKT: Buchsenleiste J4 auf der Platine, Stift-
# leiste am OLED (nach hinten), Display-Face liegt an der Glasscheibe an.
# J4-Position ist damit die Fensterzentrierung! Rueckwaerts konstruiert:
#   Fensterzentrum (36.0, 31.65), Modul 38x12 -> Modul bei x 12.5..50.5,
#   Pinreihe senkrecht, Pins bei x=15.0, y=27.84/30.38/32.92/35.46
#   (Belegung von oben: GND, VCC, SCL, SDA - wie J4 im Schaltplan)
# ANNAHMEN (am eigenen Modul nachmessen, Hersteller streuen +/-1 mm!):
#   - Pinreihe 2.5 mm von Modul-Linkskante
#   - Zentrum der aktiven Flaeche 23.5 mm von Modul-Linkskante
# Stackhoehe: 16.5 - Glaseinstand - Modulstaerke (~2.8) => ca. 13-14 mm,
# z.B. Buchsenleiste 11 mm + Stiftleistenkragen 2.5 mm. Vorher messen!
J4_REF = (13.7, 26.6, 2.6, 10.2)      # Buchsenleiste 1x4 senkrecht
OLED_HOVER = (12.5, 25.65, 38.0, 12.0)  # aufgestecktes Modul (schwebt auf Stack)

# ---- Shelly 1PM Mini Gen4: FLACH AUF der Platine (nur 1.8 mm darunter!) ------
# 16 mm Bauhoehe passt in die 16.5 mm ueber der Platine. Befestigung: VHB-
# Klebeband oder 3D-Clip, Anschluesse L/N/SW/O per kurzer Litze auf Pads.
SHELLY_CUT_ENABLE = False            # KEIN Ausschnitt mehr
SHELLY_TOL = 0.5
SHELLY_CUT = (56.0, 16.5, 34.0, 29.0)  # Stellflaeche (liegend), Referenz

# ---- ESP32-C3 Super Mini: flach AUF der Platine, oben links -------------------
ESP_CUT_ENABLE = False               # kein Einlassen (unten nur 1.8 mm)
ESP_TOL = 0.3
ESP_CUT = (8.5, -10.0, 24.0, 18.0)     # quer liegend, USB-C zeigt zur Oberkante

# ---- Netzteil TENSTAR TSP-05 (HLK-PM05-Klon, 34.7 x 20.5 x 15.05) -------------
# Stellflaeche unten links, AC-Seite zeigt zum linken Platinenrand (230V-Zone).
# ACHTUNG nach Dom-Neuvermessung: B6-Schlitz reicht bis x=-1.0 und ueberlappt
# die PSU-Linkskante (-1.5) um ~0.5 mm; B5-Schlitz ab x=34.0 (0.8 mm Luft).
# -> PSU im Layout ~1 mm nach rechts/oben ruecken. 0.6 mm ueber Kopf Schraube h3.
PSU_REF = (-1.5, 44.2, 34.7, 20.5)

# ============================================================================

def Y(y): return (BOARD_H + EXT_B) - y - 0  # DXF y nach oben, Nullpunkt unten

doc = ezdxf.new('R2010')
doc.units = ezdxf.units.MM
doc.header['$MEASUREMENT'] = 1
doc.layers.add('Edge_Cuts', color=1)
doc.layers.add('Holes', color=3)
doc.layers.add('Buttons', color=5)
doc.layers.add('Display_alt', color=8)
doc.layers.add('OLED_neu', color=6)
doc.layers.add('Module_Ref', color=4)
doc.layers.add('Keepout_Ref', color=2)
msp = doc.modelspace()

L, Rt, Tp, Bt = -EXT_L, BOARD_W + EXT_R, -EXT_T, BOARD_H + EXT_B
r = CORNER_R

def seg(x1, y1, x2, y2, layer='Edge_Cuts'):
    msp.add_line((x1, Y(y1)), (x2, Y(y2)), dxfattribs={'layer': layer})

def rect(x, y, w, h, layer):
    msp.add_lwpolyline([(x, Y(y)), (x+w, Y(y)), (x+w, Y(y+h)), (x, Y(y+h))],
                       close=True, dxfattribs={'layer': layer})

# Aussenkontur mit randoffenen Dom-Schlitzen (Ecken gerundet).
# Eckradien schrumpfen lokal, falls ein Schlitz bis in die Ecke reicht (die
# aeusseren Dome sitzen dicht am Rand). Kleinerer Eckradius = spitzere
# Platinenecke = passt mit MEHR Spiel in die gerundete Gehaeuseecke -> unkritisch.
rr = DOME_D / 2
xs_top = sorted(x for x, _ in DOMES_TOP)
xs_bot = sorted(x for x, _ in DOMES_BOT)
r_tl = max(0.0, min(r, (xs_top[0]  - rr) - L))
r_tr = max(0.0, min(r, Rt - (xs_top[-1] + rr)))
r_bl = max(0.0, min(r, (xs_bot[0]  - rr) - L))
r_br = max(0.0, min(r, Rt - (xs_bot[-1] + rr)))

def arc(cx, cy, radius, a0, a1):
    msp.add_arc((cx, Y(cy)), radius, a0, a1, dxfattribs={'layer': 'Edge_Cuts'})

# Oberkante (links -> rechts) mit nach unten gerundeten U-Schlitzen
cx_ = L + r_tl
for (dx, dy) in sorted(DOMES_TOP):
    if dx - rr > cx_:
        seg(cx_, Tp, dx - rr, Tp)     # Kantenstueck bis zum Schlitz
    seg(dx - rr, Tp, dx - rr, dy)     # linke Schlitzwand
    arc(dx, dy, rr, 180, 360)         # gerundetes Schlitzende (nach unten)
    seg(dx + rr, dy, dx + rr, Tp)     # rechte Schlitzwand
    cx_ = dx + rr
if Rt - r_tr > cx_:
    seg(cx_, Tp, Rt - r_tr, Tp)

# rechte obere Ecke, rechte Kante, rechte untere Ecke
arc(Rt - r_tr, Tp + r_tr, r_tr, 0, 90)
seg(Rt, Tp + r_tr, Rt, Bt - r_br)
arc(Rt - r_br, Bt - r_br, r_br, 270, 360)

# Unterkante (rechts -> links) mit nach oben gerundeten U-Schlitzen
cx_ = Rt - r_br
for (dx, dy) in sorted(DOMES_BOT, reverse=True):
    if dx + rr < cx_:
        seg(cx_, Bt, dx + rr, Bt)     # Kantenstueck bis zum Schlitz
    seg(dx + rr, Bt, dx + rr, dy)     # rechte Schlitzwand
    arc(dx, dy, rr, 0, 180)           # gerundetes Schlitzende (nach oben)
    seg(dx - rr, dy, dx - rr, Bt)     # linke Schlitzwand
    cx_ = dx - rr
if L + r_bl < cx_:
    seg(cx_, Bt, L + r_bl, Bt)

# linke untere Ecke, linke Kante, linke obere Ecke
arc(L + r_bl, Bt - r_bl, r_bl, 180, 270)
seg(L, Bt - r_bl, L, Tp + r_tl)
arc(L + r_tl, Tp + r_tl, r_tl, 90, 180)

# Loecher
for (x, y) in HOLES:
    msp.add_circle((x, Y(y)), HOLE_DIA/2, dxfattribs={'layer': 'Holes'})
    seg(x-2, y, x+2, y, 'Holes'); seg(x, y-2, x, y+2, 'Holes')

# Taster
for (x, y) in BUTTONS:
    s = BTN_SIZE/2
    rect(x-s, y-s, BTN_SIZE, BTN_SIZE, 'Buttons')
    seg(x-3, y, x+3, y, 'Buttons'); seg(x, y-3, x, y+3, 'Buttons')

# Sichtfenster-Referenz + OLED-Anschluss J4
x1,y1,x2,y2 = OLD_DISP
rect(x1, y1, x2-x1, y2-y1, 'Display_alt')
rect(*J4_REF[:2], J4_REF[2], J4_REF[3], 'OLED_neu')
rect(*OLED_HOVER[:2], OLED_HOVER[2], OLED_HOVER[3], 'OLED_neu')
for i in range(4):  # Pin-Kreuze
    py = 27.84 + i*2.54
    seg(15.0-1, py, 15.0+1, py, 'OLED_neu'); seg(15.0, py-1, 15.0, py+1, 'OLED_neu')

# Beschriftete Platzhalter
from ezdxf.enums import TextEntityAlignment
def label(text, x, y, w, h, layer, th=2.5):
    t = msp.add_text(text, dxfattribs={'layer': layer, 'height': th})
    t.set_placement((x + w/2, Y(y + h/2)), align=TextEntityAlignment.MIDDLE_CENTER)

label('SHELLY 1PM MINI G4', *SHELLY_CUT, 'Module_Ref', 2.8)
label('ESP32-C3', *ESP_CUT, 'Module_Ref', 2.8)
label('TSP-05', *PSU_REF, 'Module_Ref', 2.8)
label('J4', 9.5, 29.2, 4, 3, 'OLED_neu', 2.0)
label('OLED (gesteckt)', 20.0, 25.8, 30, 3.5, 'OLED_neu', 2.0)
label('FENSTER (max. 12mm)', x1, y1, x2-x1, y2-y1, 'Display_alt', 2.2)
for i, (bx, by) in enumerate(BUTTONS, 1):
    label(f'T{i}', bx-3, by+4.5, 6, 3, 'Buttons', 2.0)

# Modul-Stellflaechen (Referenz) bzw. optional Fenster
for enable, tol, cut in [(SHELLY_CUT_ENABLE, SHELLY_TOL, SHELLY_CUT),
                         (ESP_CUT_ENABLE, ESP_TOL, ESP_CUT),
                         (False, 0.0, PSU_REF)]:
    x,y,w,h = cut
    if enable:
        rect(x-tol, y-tol, w+2*tol, h+2*tol, 'Edge_Cuts')
    rect(x, y, w, h, 'Module_Ref')

# Sperrzonen: Schraubenkoepfe + Dome-Stege
for (x, y) in HOLES:
    msp.add_circle((x, Y(y)), 4.0, dxfattribs={'layer': 'Keepout_Ref'})
for (rx0, ry0, rx1, ry1) in RIBS:
    rect(rx0, ry0, rx1-rx0, ry1-ry0, 'Keepout_Ref')

doc.saveas('platine_original_geometrie.dxf')
print(f'DXF geschrieben: Kontur {L}..{Rt} x {Tp}..{Bt} '
      f'({Rt-L:.1f} x {Bt-Tp:.1f} mm), Dom-Schlitze D{DOME_D} '
      f'oben y={DOME_TOP_Y} / unten y={DOME_BOT_Y}, '
      f'Eckradien TL{r_tl:.1f}/TR{r_tr:.1f}/BR{r_br:.1f}/BL{r_bl:.1f}')

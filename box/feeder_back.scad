// ============================================================
//  SuperFish Fish Feeder - Gehaeusehinterteil (tiefere Variante)
//  Parametrisch. Alle Passflaechen wie am Original gemessen;
//  nur die Tiefe (H_OUT) ist geaendert.
//  Datum z=0 = Aussenseite Rueckwand (Wand-Montageflaeche)
//  Rim/Dichtebene (Wandoberkante) = z = H_OUT
//  Einheiten: mm
// ============================================================

/* ---------- Passflaechen (gemessen, NICHT aendern) ---------- */
OUT_W      = 109.8;   // Aussenmass X (Breite)
OUT_Y      = 90.8;    // Aussenmass Y (Hoehe des Korpus, ohne Lasche)
CORNER_R   = 5.0;     // Eckradius aussen
WALL       = 1.3;     // Wandstaerke (Dichtkante gegen Dichtung im Oberteil)
FLOOR      = 1.3;     // Rueckwandstaerke

BOSS_OD    = 8.0;     // Dom-Aussendurchmesser
BOSS_ID    = 3.2;     // Schraubloch (Durchgang, Schraube von hinten)
BOSS_PROUD = 1.75;    // Ueberstand Domoberkante ueber Dichtebene (aus E=6.15)
CS_D       = 6.0;     // Senkung fuer Schraubenkopf hinten (Durchmesser)
CS_DEPTH   = 2.0;     // Senkungstiefe hinten

COL_PITCH  = 45.0;    // Domraster X
ROW_PITCH  = 70.0;    // Domraster Y

// Aufhaengelasche (mittig obere Kante)
TAB_W      = 22.0;    // Laschenbreite
TAB_OUT    = 19.0;    // Ueberstand ueber Korpuskante
TAB_T      = 3.0;     // Laschendicke (an Rueckflaeche)
KEY_HEAD_D = 9.0;     // Schluesselloch: grosse Bohrung
KEY_SLOT_W = 4.5;     // Schluesselloch: Schlitzbreite
KEY_SLOT_L = 9.0;     // Schlitzlaenge (Richtung Korpus)

/* ---------- Variabel ---------- */
H_OUT      = 35.0;    // NEUE Gesamttiefe (Original war 5.7)

$fn = 96;
EPS = 0.01;
BOSS_TOP = H_OUT + BOSS_PROUD;

// runde-Rechteck-Prisma (Ecke bei Radius r), Basis bei z0
module rrect_prism(w, d, r, h, z0=0){
    translate([0,0,z0])
    linear_extrude(height=h)
        offset(r=r) offset(r=-r)
            square([w,d], center=false);
}

// Body-Footprint-Zentrum
cx = OUT_W/2;  cy = OUT_Y/2;

// Dompositionen (zentriertes 3x2 Raster)
col = [cx-COL_PITCH, cx, cx+COL_PITCH];
row = [cy-ROW_PITCH/2, cy+ROW_PITCH/2];

module bosses_solid(){
    for(x=col) for(y=row)
        translate([x,y,FLOOR-EPS])
            cylinder(d=BOSS_OD, h=BOSS_TOP-FLOOR+EPS);
}
REAR_COUNTERSINK = false;   // Boden geschlossen: nur reine Schraubenbohrung

module boss_holes(){
    for(x=col) for(y=row){
        // Durchgangsloch komplett durch (reine Schraubenbohrung Ø BOSS_ID)
        translate([x,y,-1]) cylinder(d=BOSS_ID, h=BOSS_TOP+2);
        // optionale Senkung hinten (standardmaessig AUS)
        if(REAR_COUNTERSINK)
            translate([x,y,-EPS]) cylinder(d1=CS_D, d2=BOSS_ID, h=CS_DEPTH);
    }
}

module tab(){
    // flache Lasche an +Y-Kante, an der Rueckflaeche (z=0..TAB_T)
    ty0 = OUT_Y - 6;                 // Ueberlappung in den Korpus
    ty1 = OUT_Y + TAB_OUT;
    translate([cx - TAB_W/2, ty0, 0])
        linear_extrude(height=TAB_T)
            offset(r=6) offset(r=-6)
                square([TAB_W, ty1-ty0], center=false);
}
module keyhole(){
    kx = cx;
    ky = OUT_Y + TAB_OUT - KEY_HEAD_D/2 - 2;  // grosse Bohrung nahe Aussenende
    translate([kx, ky, -1]) cylinder(d=KEY_HEAD_D, h=TAB_T+2);
    // Schlitz Richtung Korpus (-Y)
    translate([kx-KEY_SLOT_W/2, ky-KEY_SLOT_L, -1])
        cube([KEY_SLOT_W, KEY_SLOT_L, TAB_T+2]);
}

module feeder_back(){
    difference(){
        union(){
            // Aussen-Tray
            difference(){
                rrect_prism(OUT_W, OUT_Y, CORNER_R, H_OUT, 0);
                // Kavitaet (offen nach oben), um WALL nach innen versetzt
                translate([WALL, WALL, 0])
                    rrect_prism(OUT_W-2*WALL, OUT_Y-2*WALL,
                                max(CORNER_R-WALL,0.5), H_OUT, FLOOR);
            }
            bosses_solid();
            tab();
        }
        boss_holes();
        keyhole();
    }
}
feeder_back();

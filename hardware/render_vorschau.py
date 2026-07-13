#!/usr/bin/env python3
# Render der generierten DXF als PNG-Vorschau (Skript aus CLAUDE.md).
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
print('platine_vorschau.png geschrieben')

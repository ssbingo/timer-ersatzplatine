#!/usr/bin/env python3
# Baut firmware/help_content.h aus help_<lang>.html (DE/EN/FR/NL/ES/IT) als
# PROGMEM-Rohstrings HELP_DE..HELP_IT. Setzt zugleich in jede Seite:
#  - den einheitlichen 6-Sprachen-Umschalter mit INLINE-SVG-Flaggen (die auf
#    jedem System erscheinen; Emoji-Flaggen fehlen z. B. unter Windows),
#  - Favicon (/favicon.svg) und ein bisschen CSS fuer die Flaggen.
# Aufruf:  python3 firmware/mk_help.py
import pathlib
import re

D = pathlib.Path(__file__).resolve().parent
LANGS = ["de", "en", "fr", "nl", "es", "it"]
SW_RE = re.compile(r"<span class=lang>.*?</span>", re.S)

# Kompakte Inline-SVG-Landesflaggen (en = Union Jack fuer Englisch).
FLAGS = {
 "de": '<svg class=fl viewBox="0 0 3 2"><rect width="3" height="2" fill="#000"/><rect y="0.667" width="3" height="0.667" fill="#D00"/><rect y="1.333" width="3" height="0.667" fill="#FFCE00"/></svg>',
 "en": '<svg class=fl viewBox="0 0 60 30"><rect width="60" height="30" fill="#012169"/><path d="M0,0 60,30 M60,0 0,30" stroke="#fff" stroke-width="6"/><path d="M0,0 60,30 M60,0 0,30" stroke="#C8102E" stroke-width="2"/><path d="M30,0 V30 M0,15 H60" stroke="#fff" stroke-width="10"/><path d="M30,0 V30 M0,15 H60" stroke="#C8102E" stroke-width="6"/></svg>',
 "fr": '<svg class=fl viewBox="0 0 3 2"><rect width="3" height="2" fill="#fff"/><rect width="1" height="2" fill="#0055A4"/><rect x="2" width="1" height="2" fill="#EF4135"/></svg>',
 "nl": '<svg class=fl viewBox="0 0 3 2"><rect width="3" height="2" fill="#fff"/><rect width="3" height="0.667" fill="#AE1C28"/><rect y="1.333" width="3" height="0.667" fill="#21468B"/></svg>',
 "es": '<svg class=fl viewBox="0 0 3 2"><rect width="3" height="2" fill="#AA151B"/><rect y="0.5" width="3" height="1" fill="#F1BF00"/></svg>',
 "it": '<svg class=fl viewBox="0 0 3 2"><rect width="3" height="2" fill="#fff"/><rect width="1" height="2" fill="#009246"/><rect x="2" width="1" height="2" fill="#CE2B37"/></svg>',
}
HEAD_EXTRA = (
 '<link rel=icon type="image/svg+xml" href="/favicon.svg">'
 '<style>.fl{height:.82em;width:auto;border-radius:2px;vertical-align:-.1em;'
 'margin-right:.34em;box-shadow:0 0 0 .5px rgba(0,0,0,.28);display:inline-block}</style>'
)


def switcher(cur: str) -> str:
    links = []
    for lg in LANGS:
        cls = " class=on" if lg == cur else ""
        links.append(f'<a{cls} href="/help?lang={lg}">{FLAGS[lg]} {lg.upper()}</a>')
    return "<span class=lang>" + " ".join(links) + "</span>"


def build(lang: str) -> str:
    p = D / f"help_{lang}.html"
    if not p.exists():
        p = D / "help_de.html"
    html = p.read_text(encoding="utf8").rstrip("\n")
    html = SW_RE.sub(switcher(lang), html, count=1)
    html = html.replace("</head>", HEAD_EXTRA + "</head>", 1)
    return html


out = [
    "// AUTO-GENERIERT von mk_help.py aus help_<lang>.html.",
    "// NICHT von Hand editieren - stattdessen die .html anpassen und neu erzeugen.",
    "#pragma once",
    "",
]
for lang in LANGS:
    html = build(lang)
    assert ')HELP"' not in html, f"Delimiter-Kollision in help_{lang}.html"
    out.append(f'static const char HELP_{lang.upper()}[] PROGMEM = R"HELP(')
    out.append(html)
    out.append(')HELP";')
    out.append("")

dst = D / "help_content.h"
dst.write_text("\n".join(out) + "\n", encoding="utf8")
print(f"help_content.h geschrieben: {dst.stat().st_size} Bytes ({len(LANGS)} Sprachen)")

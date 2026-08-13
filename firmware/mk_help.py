#!/usr/bin/env python3
# Baut firmware/help_content.h aus help_<lang>.html (DE/EN/FR/NL/ES/IT) als
# PROGMEM-Rohstrings HELP_DE..HELP_IT. Setzt zugleich den einheitlichen
# 6-Sprachen-Umschalter (Flagge + Kuerzel) in jede Seite, mit 'on' fuer die
# jeweilige Sprache. Aufruf:  python3 firmware/mk_help.py
# Fehlt eine Uebersetzung noch, wird vorlaeufig die deutsche Fassung genutzt.
import pathlib
import re

D = pathlib.Path(__file__).resolve().parent
LANGS = ["de", "en", "fr", "nl", "es", "it"]
FLAG = {"de": "🇩🇪", "en": "🇬🇧", "fr": "🇫🇷", "nl": "🇳🇱", "es": "🇪🇸", "it": "🇮🇹"}
SW_RE = re.compile(r"<span class=lang>.*?</span>", re.S)


def switcher(cur: str) -> str:
    links = []
    for lg in LANGS:
        cls = " class=on" if lg == cur else ""
        links.append(f'<a{cls} href="/help?lang={lg}">{FLAG[lg]} {lg.upper()}</a>')
    return "<span class=lang>" + " ".join(links) + "</span>"


def build(lang: str) -> str:
    p = D / f"help_{lang}.html"
    if not p.exists():
        p = D / "help_de.html"
    html = p.read_text(encoding="utf8").rstrip("\n")
    html = SW_RE.sub(switcher(lang), html, count=1)
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

#!/usr/bin/env python3
# Baut firmware/help_content.h aus help_de/en/fr.html als PROGMEM-Rohstrings
# (HELP_DE/HELP_EN/HELP_FR). Aufruf:  python3 firmware/mk_help.py
# Fehlt eine Uebersetzung noch, wird vorlaeufig die deutsche Fassung genutzt.
import pathlib

D = pathlib.Path(__file__).resolve().parent


def load(lang: str) -> str:
    p = D / f"help_{lang}.html"
    if not p.exists():
        p = D / "help_de.html"
    return p.read_text(encoding="utf8").rstrip("\n")


out = [
    "// AUTO-GENERIERT von mk_help.py aus help_{de,en,fr}.html.",
    "// NICHT von Hand editieren - stattdessen die .html anpassen und neu erzeugen.",
    "#pragma once",
    "",
]
for lang in ("de", "en", "fr"):
    html = load(lang)
    assert ')HELP"' not in html, f"Delimiter-Kollision in help_{lang}.html"
    out.append(f'static const char HELP_{lang.upper()}[] PROGMEM = R"HELP(')
    out.append(html)
    out.append(')HELP";')
    out.append("")

dst = D / "help_content.h"
dst.write_text("\n".join(out) + "\n", encoding="utf8")
print(f"help_content.h geschrieben: {dst.stat().st_size} Bytes")

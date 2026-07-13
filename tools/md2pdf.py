#!/usr/bin/env python3
"""Markdown -> PDF fuer Projektdokumente (Regel: Doku+Plan immer auch als PDF).
Aufruf: python3 tools/md2pdf.py docs/DOKUMENTATION.md docs/PROJEKTPLAN.md"""
import sys, markdown
from pathlib import Path
from weasyprint import HTML

CSS = """
@page { size: A4; margin: 22mm 18mm 20mm 18mm;
        @bottom-right { content: counter(page) " / " counter(pages); font-size: 8pt; color: #666; } }
body { font-family: "DejaVu Sans", sans-serif; font-size: 9.5pt; line-height: 1.45; color: #1a1a1a; }
h1 { font-size: 17pt; border-bottom: 2px solid #2c5f8a; padding-bottom: 4px; color: #2c5f8a; }
h2 { font-size: 13pt; color: #2c5f8a; margin-top: 18px; border-bottom: 1px solid #ccd; padding-bottom: 2px; }
h3 { font-size: 11pt; color: #333; margin-top: 14px; }
table { border-collapse: collapse; width: 100%; margin: 8px 0; font-size: 8.5pt; }
th, td { border: 1px solid #bbb; padding: 3px 6px; text-align: left; vertical-align: top; }
th { background: #e8eef5; }
code { font-family: "DejaVu Sans Mono", monospace; font-size: 8.5pt; background: #f2f2f2; padding: 0 2px; }
pre { background: #f5f5f5; border: 1px solid #ddd; padding: 6px 8px; font-size: 8pt;
      white-space: pre-wrap; word-wrap: break-word; }
pre code { background: none; }
blockquote { border-left: 3px solid #2c5f8a; margin-left: 0; padding-left: 10px; color: #444; }
li { margin: 2px 0; }
img { max-width: 100%; height: auto; display: block; margin: 8px auto; border: 1px solid #ddd; border-radius: 4px; }
"""

for src in sys.argv[1:]:
    p = Path(src)
    html = markdown.markdown(p.read_text(encoding="utf-8"),
                             extensions=["tables", "fenced_code", "sane_lists"])
    out = p.with_suffix(".pdf")
    HTML(string=f"<html><head><style>{CSS}</style></head><body>{html}</body></html>",
         base_url=str(p.parent.resolve())).write_pdf(out)
    print(f"{out} geschrieben")

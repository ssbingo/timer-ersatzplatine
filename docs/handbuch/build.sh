#!/usr/bin/env bash
# Baut das Feeder-Relais-Handbuch (PDF) aus handbuch.html.
#
# Regelwerk uebernommen aus ioBroker.asksinanalyzer: gebaut wird mit
# WeasyPrint (nicht Chromium), weil nur WeasyPrint den fest positionierten
# Fusssteg sauber in den unteren Seitenrand setzt. Chromium zwingt fest
# positionierte Elemente in den Satzspiegel — dort verdeckte der Steg Text.
#
# Voraussetzungen: python3 (bringt venv mit). Fuer --bilder zusaetzlich das
# KiCad-10-CLI (~/kicad10/kcli).
set -euo pipefail
cd "$(dirname "$0")"

# --bilder: Platinen-Renders neu erzeugen (sonst bleiben die vorhandenen).
if [[ "${1:-}" == "--bilder" ]]; then
  B=../../kicad-v2/Timer-Ersatzplatine-v2.kicad_pcb
  KCLI="${KCLI:-$HOME/kicad10/kcli}"
  export LD_LIBRARY_PATH="${LD_LIBRARY_PATH:-}:$HOME/kicad10/squashfs-root/usr/lib"
  "$KCLI" pcb render --output img/platine-oben.png  --side top    --zoom 1.05 --width 1500 --height 1150 --quality high "$B"
  "$KCLI" pcb render --output img/platine-unten.png --side bottom --zoom 1.05 --width 1500 --height 1150 --quality high "$B"
fi

# 1) Nummerierung MUSS stimmen, bevor gedruckt wird: doppelte oder falsche
#    Sprungmarken lassen Verweise aus dem Inhaltsverzeichnis ins falsche
#    Kapitel springen. Faellt beim Lesen kaum auf, im PDF aber sofort.
python3 pruefe_nummerierung.py

# 2) WeasyPrint aus einer eigenen Umgebung neben diesem Skript — kein
#    Systempaket, kein sudo. Die noetigen Bibliotheken (Pango, Cairo) bringt
#    jedes Desktop-Debian ohnehin mit.
UMGEBUNG="$PWD/.venv"
if [ ! -x "$UMGEBUNG/bin/weasyprint" ]; then
  echo "==> Richte WeasyPrint ein (einmalig)..."
  python3 -m venv "$UMGEBUNG"
  "$UMGEBUNG/bin/pip" install --quiet --upgrade pip
  "$UMGEBUNG/bin/pip" install --quiet weasyprint \
    || { echo "WeasyPrint liess sich nicht einrichten." >&2; exit 1; }
fi

"$UMGEBUNG/bin/weasyprint" handbuch.html Feeder-Relais-Handbuch.pdf \
  2>&1 | grep -vE "print-color-adjust|overflow-x" || true

pdfinfo Feeder-Relais-Handbuch.pdf | grep -E "Pages|Page size"

# 3) Der Fusssteg darf keinen Text verdecken — die Vorgabe, an der die
#    Chromium-Fassung gescheitert ist. Deshalb bei jedem Bau nachgerechnet.
python3 pruefe_fusssteg.py

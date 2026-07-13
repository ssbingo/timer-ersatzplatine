#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# Kompiliert die feeder-relais-Firmware und legt die fertigen Images unter
# stabilen Namen in firmware/build/ ab (immer der aktuelle Stand):
#   feeder-relais.factory.bin  - Voll-Image fuer den ERSTflash (Adresse 0x0)
#   feeder-relais.ota.bin      - App-Image fuer OTA / Web-Update
#
# Aufruf aus der Projektwurzel:  ./firmware/build_images.sh
# Fuer ein GitHub-Release die Dateien versioniert hochladen, z. B.:
#   gh release create v0.0.1 \
#     firmware/build/feeder-relais.factory.bin#feeder-relais-v0.0.1.factory.bin \
#     firmware/build/feeder-relais.ota.bin#feeder-relais-v0.0.1.ota.bin
# ---------------------------------------------------------------------------
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

# venv mit esphome aktivieren, falls vorhanden
[ -f .venv/bin/activate ] && source .venv/bin/activate

esphome compile firmware/timer-relais-c3.yaml

SRC="firmware/.esphome/build/feeder-relais/.pioenvs/feeder-relais"
mkdir -p firmware/build
cp "$SRC/firmware.factory.bin" firmware/build/feeder-relais.factory.bin
cp "$SRC/firmware.bin"         firmware/build/feeder-relais.ota.bin

echo "Fertige Images in firmware/build/:"
ls -la firmware/build/*.bin

#!/usr/bin/env bash
# Build local do Slowduino (firmware ou simulador), sem precisar de venv
# no PATH nem variavel nenhuma. Cria o venv na primeira vez se faltar.
#
# Uso:
#   ./build.sh uno          -> firmware normal (raiz do projeto)
#   ./build.sh uno_debug    -> firmware com log serial (DEBUG_ENABLED)
#   ./build.sh sim          -> simulador de roda fonica (simulator/)
#   ./build.sh mega2560     -> firmware para Mega2560
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VENV="$ROOT/.pio_venv"
PIO="$VENV/bin/pio"

if [ ! -x "$PIO" ]; then
  echo "Criando venv do PlatformIO em $VENV ..."
  python3 -m venv "$VENV"
  "$VENV/bin/pip" install -q platformio
fi

TARGET="${1:-uno}"

if [ "$TARGET" = "sim" ]; then
  cd "$ROOT/simulator"
  rm -f ".pio/build/uno/firmware.hex" ".pio/build/uno/firmware.elf"
  "$PIO" run -e uno
  echo "-> simulator/.pio/build/uno/firmware.hex"
else
  cd "$ROOT"
  rm -f ".pio/build/$TARGET/firmware.hex" ".pio/build/$TARGET/firmware.elf"
  "$PIO" run -e "$TARGET"
  echo "-> .pio/build/$TARGET/firmware.hex"
fi

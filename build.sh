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
  # Remove o diretorio de build inteiro (nao so hex/elf) - garante que nao
  # sobra .o intermediario de uma build anterior mascarando o resultado.
  rm -rf ".pio/build/uno"
  "$PIO" run -e uno
  HEX=".pio/build/uno/firmware.hex"
  echo "-> simulator/$HEX"
else
  cd "$ROOT"
  rm -rf ".pio/build/$TARGET"
  "$PIO" run -e "$TARGET"
  HEX=".pio/build/$TARGET/firmware.hex"
  echo "-> $HEX"
fi

# Hash do .hex gerado - compara com o build anterior pra confirmar que o
# binario realmente mudou (util quando o simulador/gravador tem cache de
# firmware e nao recarrega sozinho, ex: Auto_Load="false" no SimulIDE).
if command -v sha256sum >/dev/null 2>&1; then
  echo "sha256: $(sha256sum "$HEX" | cut -d' ' -f1)"
fi

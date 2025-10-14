#!/bin/bash
# banner.sh — exibe o banner do Enzo Linux com efeito no terminal

BANNER_FILE="Source/banner/enzo-banner.txt"

# Verifica se o arquivo existe
if [ ! -f "$BANNER_FILE" ]; then
    echo "[banner.sh] ERRO: banner não encontrado em $BANNER_FILE"
    exit 1
fi

# Exibe o banner com efeito de digitação
while IFS= read -r line; do
    echo "$line"
    sleep 0.05  # tempo entre cada linha (ajuste para mais rápido/lento)
done < "$BANNER_FILE"

echo ""
echo ">>> Enzo Linux iniciado com sucesso!"
echo ">>> Digite 'help' para comandos do sistema."
echo ""

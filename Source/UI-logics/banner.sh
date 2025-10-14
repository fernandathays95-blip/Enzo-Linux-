#!/bin/bash
# banner.sh — exibe o banner do Enzo Linux com cores e boot dinâmico

BANNER_FILE="Source/banner/enzo-banner.txt"

# ANSI colors
GREEN="\033[0;32m"
CYAN="\033[0;36m"
YELLOW="\033[1;33m"
RESET="\033[0m"

# Verifica se o arquivo existe
if [ ! -f "$BANNER_FILE" ]; then
    echo -e "${YELLOW}[banner.sh] ERRO: banner não encontrado em $BANNER_FILE${RESET}"
    exit 1
fi

clear
echo -e "${GREEN}Iniciando Enzo Linux...\n${RESET}"

# Exibe o banner linha por linha
while IFS= read -r line; do
    echo -e "${CYAN}$line${RESET}"
    sleep 0.03
done < "$BANNER_FILE"

echo ""

# Simula logs do kernel durante boot
LOGS=(
    "Carregando kernel GPT..."
    "Inicializando módulos essenciais..."
    "Montando /system/core..."
    "Detectando hardware virtual..."
    "Inicializando drivers de entrada e toque..."
    "Preparando interface gráfica (em breve)..."
    "Sistema unificado usuário+sistema detectado"
    "Todos os módulos carregados com sucesso"
)

for log in "${LOGS[@]}"; do
    echo -e "${GREEN}[Kernel GPT]: $log${RESET}"
    sleep 0.4
done

echo ""
echo -e "${YELLOW}>>> Enzo Linux iniciado com sucesso!${RESET}"
echo -e "${YELLOW}>>> Digite 'help' para listar comandos do sistema.${RESET}"
echo ""

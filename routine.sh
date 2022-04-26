#!/bin/bash
#-------------------------------------------------
# execute com um dos seguintes comandos:
# 		bash ./routine.sh
# 		bash ./routine.sh all
# 		bash ./routine.sh debug
# 		bash ./routine.sh release
#-------------------------------------------------
# limpa o terminal
clear
# cria a pasta para arquivos *.o de "debug" e "release"
mkdir -p objects/debug
mkdir -p objects/release
# compila o programa com o makefile
# se $1 não for informado, define o valor padrão como "all"
make ${1:-all}
# executa o programa
echo
./mids

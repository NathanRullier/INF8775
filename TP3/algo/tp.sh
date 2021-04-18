#!/bin/bash

# INF8775 - Analyse et conception d'algorithmes
#   TP2 - Problème du voyageur de commerce
#
#   AUTEUR :
#     HAOUAS, Mohammed Najib - 06 mars 2021
#
#   RÉSUMÉ DES CHANGEMENTS :
#     03/08/2021 - Disponibilité initiale.
#
#   DOC :
#     Arguments non positionnels :
#       -a glouton -> ALG=0
#       -a progdyn -> ALG=1
#       -a approx  -> ALG=2
#       -e CHEMIN_EXEMPLAIRE -> INST="CHEMIN_EXEMPLAIRE"
#       -p -> PRINT=1, sinon, si non indiqué, PRINT=0
#       -t -> TIME=1, sinon, si non indiqué, PRINT=0
#
#     Rappel : les paramètres de ligne de commande sont passés comme des strings.

PRINT=0
TIME=0
DIG=0
ALG=0
INST=""

while getopts "e:a:ptd" o; do
    case $o in
        e)
            INST=$OPTARG
            ;;
        a)
            ALG=$OPTARG
            ;;
        p)
            PRINT=1
            ;;
        t)
            TIME=1
            ;;
        d)
            DIG=1
            ;;
    esac
done

./exec $INST $ALG $TIME $PRINT $DIG
#python3 main.py $INST $ALG $TIME $PRINT
#java main.java $INST $ALG $TIME $PRINT
#...
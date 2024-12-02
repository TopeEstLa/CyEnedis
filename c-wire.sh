#!/bin/bash

EXEC_NAME="CyEnedis"

function send_help() {
    echo "Usage: ./c-wire.sh [ARG] [OPTION]"
    echo "Arguments:"
    echo "  ARG[0] input csv file"
    echo "  ARG[1] Station type (HVB, HVA, LV)"
    echo "  ARG[2] Consumer type (COMP, INDIV, ALL)"
    echo "  ARG[3] Number of stations *optional*"
    echo "Options:"
    echo "  -h  Show this help"
    echo "  -c Force compilation"
    exit 0
}

function prepare_and_clean_folder() {
  rm -rf tmp/
  mkdir -p input tmp graphs
}

function compile_exec() {
    make clean
    make
    if [ $? -ne 0 ]; then
        echo "Error while compiling the project"
        exit 1
    fi
}

for arg in "$@"; do
    case "$arg" in
        -h)
            send_help
            ;;
        -c)
            compile_exec
            exit 0
            ;;
    esac
done

if [ $# -lt 3 ]; then
    echo "Invalid number of arguments"
    send_help
fi

CSV_FILE=$1
STATION_TYPE=$2
CONSUMER_TYPE=$3
POWER_PLANT_ID=$4
OUTPUT_FILE_NAME=""

if [ $STATION_TYPE != "hvb" ] && [ $STATION_TYPE != "hva" ] && [ $STATION_TYPE != "lv" ]; then
    echo "Station type must be (hvb, hva, lv)"
    exit 1
fi

if [ $CONSUMER_TYPE != "comp" ] && [ $CONSUMER_TYPE != "indiv" ] && [ $CONSUMER_TYPE != "all" ]; then
    echo "Consumer type must be (comp, indiv, all)"
    exit 1
fi

if [ ${STATION_TYPE,,} == "hvb" ] && { [[ ${CONSUMER_TYPE,,} == "indiv" ]] || [[ ${CONSUMER_TYPE,,} == "all" ]] }; then
    echo "You can't have HVB and INDIV or ALL"
    exit 1
fi

if [ ${STATION_TYPE,,} == "hva" ] && { [[ ${CONSUMER_TYPE,,} == "indiv" ]] || [[ ${CONSUMER_TYPE,,} == "all" ]] }; then
    echo "You can't have HVB and INDIV or ALL"
    exit 1
fi

if [ ! -f $CSV_FILE ]; then
    echo "File not found"
    exit 1
fi

if [ -z $POWER_PLANT_ID ]; then
    POWER_PLANT_ID=-1
fi


if [ ! -f $EXEC_NAME ]; then
    echo "Executable not found, compiling..."
    compile_exec
fi


prepare_and_clean_folder



START_TIME=$(date +%s)

if [ $POWER_PLANT_ID == -1 ]; then
    echo "./$EXEC_NAME $CSV_FILE $STATION_TYPE $CONSUMER_TYPE"
    ./$EXEC_NAME $CSV_FILE $STATION_TYPE $CONSUMER_TYPE
    OUTPUT_FILE_NAME="${STATION_TYPE}_${CONSUMER_TYPE}"
else
    echo "./$EXEC_NAME $CSV_FILE $STATION_TYPE $CONSUMER_TYPE $POWER_PLANT_ID"
    ./$EXEC_NAME $CSV_FILE $STATION_TYPE $CONSUMER_TYPE $POWER_PLANT_ID
    OUTPUT_FILE_NAME="${STATION_TYPE}_${CONSUMER_TYPE}_${POWER_PLANT_ID}"
fi

END_TIME=$(date +%s)
ELAPSED_TIME=$((END_TIME - START_TIME))

STATUS_CODE=$?

if [ $STATUS_CODE == 0 ]; then
    echo "Le processus a réussi en $ELAPSED_TIME secondes (statut : $STATUS_CODE)"
else
    echo "Le processus a échoué en $ELAPSED_TIME secondes (statut : $STATUS_CODE)"
fi

echo "Output file: $OUTPUT_FILE_NAME"

if [ ${STATION_TYPE,,} != "lv" ] || [ ${CONSUMER_TYPE,,} != "all" ]; then
  exit 1
fi

echo "Generating graphs..."
if [ $STATUS_CODE != 0 ]; then
    echo "Generation script failed, skipping..."
    exit 1
fi


gnuplot -persist << EOF
  set terminal png size 1200,600
  set output 'graphs/total_consumption.png'
  set title 'Consumption of 10 LV lowest and higest consumers'
  set style data histogram
  set style fill solid
  set xtics rotate by -45
  set ylabel 'Consumption (kWh)'
  set xlabel 'Consumer ID'
  set datafile separator ","
  plot '${OUTPUT_FILE_NAME}_minmax.csv' using 2:xtic(1) with boxes title 'Consumption'
EOF


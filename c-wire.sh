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
    echo "  -benchmark Set benchmark mode"
    echo "  -test Set test mode"
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
        -benchmark)
            export RUNNING_BENCHMARK=1
            exit 0
            ;;
        -test)
            export RUNNING_TESTS=1
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

if [ ${STATION_TYPE,,} == "hvb" ]; then
  if  [ ${CONSUMER_TYPE,,} == "indiv" ] || [ ${CONSUMER_TYPE,,} == "all" ]; then
    echo "You can't have HVB and INDIV or ALL"
    exit 1
  fi
fi

if [ ${STATION_TYPE,,} == "hva" ]; then
  if [ ${CONSUMER_TYPE,,} == "indiv" ] || [ ${CONSUMER_TYPE,,} == "all" ]; then
    echo "You can't have HVA and INDIV or ALL"
    exit 1
  fi
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

echo "  _____         ______                   _  _"
echo " / ____|       |  ____|                 | |(_)"
echo "| |      _   _ | |__    _ __    ___   __| | _  ___"
echo "| |     | | | ||  __|  | '_ \  / _ \ / _` || |/ __|"
echo "| |____ | |_| || |____ | | | ||  __/| (_| || |\__ \"
echo " \_____| \__, ||______||_| |_| \___| \__,_||_||___/"
echo "          __/ |"
echo "         |___/"

if [ $POWER_PLANT_ID == -1 ]; then
    ./$EXEC_NAME $CSV_FILE $STATION_TYPE $CONSUMER_TYPE
    STATUS_CODE=$?
    OUTPUT_FILE_NAME="${STATION_TYPE}_${CONSUMER_TYPE}"
else
    ./$EXEC_NAME $CSV_FILE $STATION_TYPE $CONSUMER_TYPE $POWER_PLANT_ID
    STATUS_CODE=$?
    OUTPUT_FILE_NAME="${STATION_TYPE}_${CONSUMER_TYPE}_${POWER_PLANT_ID}"
fi

END_TIME=$(date +%s)
ELAPSED_TIME=$((END_TIME - START_TIME))

if [ $STATUS_CODE == 0 ]; then
      echo "The process was successful in $ELAPSED_TIME seconds (status : $STATUS_CODE)"
else
      echo "The process failed in $ELAPSED_TIME seconds (status : $STATUS_CODE)"
fi

case "$STATUS_CODE" in
  0)
    echo "Output file: ${OUTPUT_FILE_NAME}.csv"
    ;;
  2)
    echo "Error while reading the given parameters"
    ;;
  3)
    echo "Param is not valid (csv-file does not exist ?, station-type is not valid ?, consumer-type is not valid ?)"
    ;;
  4)
    echo "Error while reading the file or building the AVL tree"
    ;;
  5)
    echo "Error while collecting data from AVL and ordering it"
    ;;
  6)
    echo "Error while writing output csv file"
    ;;
  7)
    echo "Error while writing output 'minmax' csv file"
    ;;
  *)
    echo "Unknown error"
    ;;
esac

if [ $STATUS_CODE != 0 ]; then
      exit $STATUS_CODE
fi

if [ ${STATION_TYPE,,} != "lv" ] || [ ${CONSUMER_TYPE,,} != "all" ]; then
  exit 0
fi

echo "Generating graphs..."
if [ $STATUS_CODE != 0 ]; then
    echo "Generation script failed, skipping..."
    exit 1
fi


gnuplot -persist << EOF
  set terminal png size 1200,600
  set output 'graphs/${OUTPUT_FILE_NAME}_load_graph.png'
  set title 'Load graph of the 10 busiest and least loaded LV stations'
  set style data histogram
  set style fill solid
  set xtics rotate by -45
  set ylabel 'Load (kWh)'
  set xlabel 'Station ID'
  set datafile separator ","
  plot '${OUTPUT_FILE_NAME}_minmax.csv' using 3:xtic(1) with boxes title 'Load'
EOF

echo "Graphs generated in graphs/${OUTPUT_FILE_NAME}_load_graph.png"
#!/bin/bash

PROG_FOLDER="codeC"
EXEC_NAME="${PROG_FOLDER}/CyEnedis"

printf '\033[0;36m'

function send_help() {
    echo "Usage: ./c-wire.sh [ARG] [OPTION]"
    echo "Arguments:"
    echo "  ARG[0] input csv file"
    echo "  ARG[1] Station type (HVB, HVA, LV)"
    echo "  ARG[2] Consumer type (COMP, INDIV, ALL)"
    echo "  ARG[3] Number of power plant *optional*"
    echo "Options:"
    echo "  -h  Show this help"
    echo "  -c Force compilation"
    echo "  -benchmark Set benchmark mode"
    echo "  -test Set test mode"
    exit 0
}

function prepare_and_clean_folder() {
  rm -rf tmp/
  mkdir -p input output tmp graphs
  if [ $? -ne 0 ]; then
    echo "Error while creating the folders"
    exit 20
  fi
}

function compile_exec() {
  cd ${PROG_FOLDER}
  make clean
  make
  if [ $? -ne 0 ]; then
    echo "Error while compiling the project"
    exit 21
  fi
  cd ..
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
            ./$EXEC_NAME -test
            chmod +x test.sh
            ./test.sh
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
    exit 22
fi

if [ $CONSUMER_TYPE != "comp" ] && [ $CONSUMER_TYPE != "indiv" ] && [ $CONSUMER_TYPE != "all" ]; then
    echo "Consumer type must be (comp, indiv, all)"
    exit 22
fi

if [ ${STATION_TYPE,,} == "hvb" ]; then
  if  [ ${CONSUMER_TYPE,,} == "indiv" ] || [ ${CONSUMER_TYPE,,} == "all" ]; then
    echo "You can't have HVB and INDIV or ALL"
    exit 22
  fi
fi

if [ ${STATION_TYPE,,} == "hva" ]; then
  if [ ${CONSUMER_TYPE,,} == "indiv" ] || [ ${CONSUMER_TYPE,,} == "all" ]; then
    echo "You can't have HVA and INDIV or ALL"
    exit 22
  fi
fi

if [ ! -f $CSV_FILE ]; then
    echo "File not found"
    exit 22
fi

if [ -z $POWER_PLANT_ID ]; then
    POWER_PLANT_ID=-1
fi

if ! [[ $POWER_PLANT_ID =~ ^[0-9]+$  ]] && [[ $POWER_PLANT_ID != -1 ]]; then
  echo "Power plant id must be a positive number"
  exit 22
fi

echo "  _____         ______                   _  _"
echo " / ____|       |  ____|                 | |(_)"
echo "| |      _   _ | |__    _ __    ___   __| | _  ___"
echo "| |     | | | ||  __|  | '_ \  / _ \ / _  || |/ __|"
echo "| |____ | |_| || |____ | | | ||  __/| (_| || |\__  "
echo " \_____| \__, ||______||_| |_| \___| \__,_||_||___/"
echo "          __/ |"
echo "         |___/"

if [ ! -f $EXEC_NAME ]; then
    echo "Executable not found, compiling..."
    compile_exec
fi


prepare_and_clean_folder


START_TIME=$(date +%s)


if [ $POWER_PLANT_ID == -1 ]; then
    ./$EXEC_NAME $CSV_FILE $STATION_TYPE $CONSUMER_TYPE
    STATUS_CODE=$?
    OUTPUT_FILE_NAME="${STATION_TYPE}_${CONSUMER_TYPE}"
else
    ./$EXEC_NAME $CSV_FILE $STATION_TYPE $CONSUMER_TYPE $POWER_PLANT_ID
    STATUS_CODE=$?
    OUTPUT_FILE_NAME="${STATION_TYPE}_${CONSUMER_TYPE}_${POWER_PLANT_ID}"
fi


if [ $STATUS_CODE == 0 ]; then
      echo "The process was successful (status : $STATUS_CODE)"
else
      END_TIME=$(date +%s)
      ELAPSED_TIME=$((END_TIME - START_TIME))
      echo "The process failed on $ELAPSED_TIME seconds (status : $STATUS_CODE)"
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
    echo "Error while reading the file or building the AVL tree, or you ask a power plant that did not exist "
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
  127)
    echo "Program was compiled successfully but i could not find it ???"
    ;;
  *)
    echo "Unknown error"
    ;;
esac

if [ $STATUS_CODE != 0 ]; then
    exit $STATUS_CODE
fi

if [ $STATION_TYPE != "lv" ] || [ $CONSUMER_TYPE != "all" ]; then
    END_TIME=$(date +%s)
    ELAPSED_TIME=$((END_TIME - START_TIME))
    echo "Process finish on $ELAPSED_TIME seconds"
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
  set title 'Load and Capacity graph of the 10 busiest and 10 least loaded LV stations'
  set style data histogram
  set style histogram clustered gap 1
  set style fill solid
  set autoscale
  set xtics rotate by -45
  set ylabel 'kWh'
  set xlabel 'Station ID'
  set datafile separator ":"
  set key outside

  plot 'output/${OUTPUT_FILE_NAME}_minmax.csv' using 2:xtic(1) title 'Capacity' lc rgb 'green', '' using 3 title 'Load' lc rgb 'red'
EOF

echo "Graphs generated in graphs/${OUTPUT_FILE_NAME}_load_graph.png"

END_TIME=$(date +%s)
ELAPSED_TIME=$((END_TIME - START_TIME))

echo "Process finish on $ELAPSED_TIME seconds"
echo "Done"
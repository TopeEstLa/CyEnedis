#!/bin/bash

PROG_FOLDER="codeC"
EXEC_NAME="${PROG_FOLDER}/CyEnedis"
TEST_FILE="input/test-data.csv"

./$EXEC_NAME $TEST_FILE hvb comp
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "$EXEC_NAME $TEST_FILE hvb comp"
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME $TEST_FILE hva comp
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "$EXEC_NAME $TEST_FILE hva comp"
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME $TEST_FILE lv comp
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "$EXEC_NAME $TEST_FILE lv comp"
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME $TEST_FILE lv indiv
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "$EXEC_NAME $TEST_FILE lv indiv"
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME $TEST_FILE lv all
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "$EXEC_NAME $TEST_FILE lv all"
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME $TEST_FILE lv all 1
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "$EXEC_NAME $TEST_FILE lv all 1"
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME $TEST_FILE hvb comp 2
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "$EXEC_NAME $TEST_FILE hvb comp 2"
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME $TEST_FILE hva comp 1
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "$EXEC_NAME $TEST_FILE hva comp 1"
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

printf "[2J[H"
echo "All test passed"
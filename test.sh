#!/bin/bash

EXEC_NAME="CyEnedis"

./$EXEC_NAME test-data.csv hvb comp
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME test-data.csv hva comp
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME test-data.csv lv comp
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME test-data.csv lv indiv
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME test-data.csv lv all
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME test-data.csv lv all 1
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME test-data.csv hvb comp 2
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi

./$EXEC_NAME test-data.csv hva comp 3
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed exit code $STATUS_CODE"
    exit 1
fi
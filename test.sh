#!/bin/bash

EXEC_NAME="CyEnedis"

./$EXEC_NAME test-data hvb comp
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed"
    exit 1
fi

./$EXEC_NAME test-data hva comp
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed"
    exit 1
fi

./$EXEC_NAME test-data lv comp
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed"
    exit 1
fi

./$EXEC_NAME test-data lv indiv
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed"
    exit 1
fi

./$EXEC_NAME test-data lv all
STATUS_CODE=$?
if [ $STATUS_CODE != 0 ]; then
    echo "Test failed"
    exit 1
fi


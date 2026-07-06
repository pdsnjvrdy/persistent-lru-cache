#!/bin/bash

CYCLES=1000
WAL_FILE="crash_test.wal"
CHECKPOINT_FILE="crash_checkpoint.txt"

rm -f "$WAL_FILE" "$CHECKPOINT_FILE"

echo "Starting crash fuzz test ($CYCLES cycles)..."

for (( i=1; i<=CYCLES; i++ )); do
    ./crash_test_writer &
    PID=$!

    # sleep random fraction of a second (0.1 to 0.9)
    sleep 0.$(( RANDOM % 9 + 1 ))

    kill -9 $PID 2>/dev/null
    wait $PID 2>/dev/null

    ./crash_test_writer
    STATUS=$?

    if [ $STATUS -ne 0 ]; then
        echo "FAIL: data loss detected on cycle $i"
        exit 1
    fi

    if [ $(wc -l < "$CHECKPOINT_FILE") -ge 1000 ]; then
        echo "Writer completed full run at cycle $i."
        break
    fi

    echo "Cycle $i OK"
done

echo "All crash tests passed. No data loss."
exit 0
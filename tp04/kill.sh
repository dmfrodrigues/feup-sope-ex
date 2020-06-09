#!/bin/bash

sleep $1
psresult=$(ps u | grep "$3" | grep -v "kill.sh")
proc=$(echo "$psresult" | head -n 1 | awk '{print $2}')
name=$(echo "$psresult" | head -n 1 | awk '{for (i=11; i<=NF; i++) print $i}')
echo Killing $proc \(\"$name\"\) with $2
kill $2 $proc

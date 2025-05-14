#!/bin/sh

while true
do
    echo "-----------------------------"
    echo "📅 Timestamp: $(date '+%Y-%m-%d %H:%M:%S')"
    echo "🌡️  Reading Sensor Data:"
    /usr/bin/aht-20
    echo "-----------------------------"
    sleep 5
done

#!/bin/bash
notify-send "볼륨: $(pactl get-sink-volume @DEFAULT_SINK@ | awk '/Volume/{ print $5 }')" -h string:synchronous:volume -t 2000

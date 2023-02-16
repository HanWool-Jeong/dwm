#!/bin/bash
notify-send "볼륨 $(pactl get-sink-mute @DEFAULT_SINK@)" -h string:synchronous:volume -t 2000

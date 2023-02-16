#!/bin/bash

MUTE=$(pactl get-sink-mute @DEFAULT_SINK@)

if [ "$MUTE" == "Mute: yes" ]; then
	echo Mute
else
	pactl get-sink-volume @DEFAULT_SINK@ | awk '/Volume/{ print $5 }'
fi

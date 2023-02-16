#!/bin/bash
out=$(
    echo -n "VOL: $(~/.dwm/print_vol.sh) | "
	echo -n "MEM: $(free -h | awk '{ print $3; }' | awk 'NR==2 { print; }')/$(free -h | awk '{ print $3; }' | awk 'NR==3 { print; }') | "
	echo -n "CPU: $(printf "%2.0f" $(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1}') )% | "
	#echo -n "CPU: $(printf "%2.0f" $(mpstat | grep -A 5 "%idle" | tail -n 1 | awk -F " " '{print 100 -  $14}'a))% | "
    #echo -n "$( date +"%F %T" )"
    echo -n "$( date +"%F %H:%M" )"
)
xsetroot -name "$out"

#!/bin/sh

setxkbmap -option korean:ralt_hangul -option korean:rctrl_hanja &
fcitx5 -d &
picom --config ~/dwm/picom/picom.conf &
nm-applet &
blueman-applet &
pasystray &
dunst -config ~/dwm/dunst/dunstrc &
nitrogen --restore &
greenclip daemon > /dev/null &

xss-lock --transfer-sleep-lock -- xsecurelock &
xidlehook --not-when-fullscreen --not-when-audio --timer 3600 'systemctl suspend' '' &

conky -q --config ~/dwm/conky/conky.conf | dwm-setstatus > /dev/null &

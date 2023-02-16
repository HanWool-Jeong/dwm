#!/bin/sh

mv ~/dwm/log/error.log ~/dwm/log/error.log.old
#mv ~/dwm/log/autostart_error.log ~/dwm/log/autostart_error.log.old

#sh -x ~/dwm/scripts/autostart.sh > ~/dwm/log/autostart_error.log
dwm 2> ~/dwm/log/error.log


#sh -x ~/dwm/scripts/autostart.sh
#dwm

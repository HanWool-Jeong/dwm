theme_rasi="~/dwm/rofi/powermenu.rasi"

lock="lock" 
suspend="suspend"
logout="logout"
reboot="reboot"
shutdown="shutdown"
options="$lock\n$logout\n$suspend\n$reboot\n$shutdown"

uptime=$(uptime -p | sed -e 's/up //g')

chosen="$(echo -e "$options" | rofi -no-config -p "Uptime: $uptime" -dmenu -theme $theme_rasi -selected-row 0)"
case $chosen in
	$lock)
		sleep 0.1 && xset dpms force off
		;;
	$suspend)
		systemctl suspend
		;;
	$logout)
		killall dwm
		;;
	$reboot)
		systemctl reboot
		;;
	$shutdown)
		systemctl poweroff
		;;
esac

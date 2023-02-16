dwm-setstatus : dwm-setstatus.c
	gcc dwm-setstatus.c -o dwm-setstatus -lX11

all: dwm-setstatus

clean:
	rm dwm-setstatus

install: all
	cp dwm-setstatus /usr/local/bin

uninstall:
	rm /usr/local/bin/dwm-setstatus

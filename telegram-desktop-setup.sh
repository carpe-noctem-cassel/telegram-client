#!/bin/bash

(
	cd /tmp; 
	wget -O telegram-desktop.tar.xz https://telegram.org/dl/desktop/linux; 
	sudo tar -Jxf telegram-desktop.tar.xz -C /opt/;
	sudo ln -s /opt/Telegram/Telegram /usr/local/bin/telegram;
	echo "[Desktop Entry]\nEncoding=UTF-8\n"\
	     "Version=1.0\nName=Telegram Desktop\nComment=Official desktop version of Telegram messaging app\n"\
	     "Exec=telegram %u\nIcon=telegram\nTerminal=false\nStartupWMClass=Telegram\nType=Application\n"\
	     "Categories=Network;\nMimeType=application/x-xdg-protocol-tg;x-scheme-handler/tg;\nX-Desktop-File-Install-Version=0.22"\
       	> /usr/share/applications/telegramdesktop.desktop
)

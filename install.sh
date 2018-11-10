#!/bin/bash

echo "Welcome to teamwork-\"Chatbot\" setup assistant."

echo "Cloning repositorys"
if [ -d "$telegramm-client" ]; then
	echo "Skipping repository \"telegram-client\""
else
	git clone https://github.com/carpe-noctem-cassel/telegram-client.git
fi
if [ -d "$tgbot-cpp" ]; then
	echo "Skipping repository \"tgbot-cpp\""
else
	git clone https://github.com/reo7sp/tgbot-cpp.git
fi

depends="g++ make binutils cmake libssl-dev libboost-system-dev"

echo "Installing neccesary dependencies"
sudo apt install $depends

echo "Building Telegram api"
(cd ~/teamwork-ws/tgbot-cpp ; cmake . ; make ; sudo make install)

#!/bin/bash

echo "Welcome to teamwork-\"Chatbot\" setup assistant."

depends="git g++ make binutils cmake libssl-dev libboost-system-dev curl capnproto"

echo "Installing neccesary dependencies"
sudo apt install $depends

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

echo "Building Telegram api"
dir=$(pwd)
(cd $dir/tgbot-cpp ; cmake . ; make ; sudo make install)

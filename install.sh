#!/bin/bash

echo "Welcome to teamwork-\"Chatbot\" setup assistant."

depends="git g++ make binutils cmake libssl-dev libboost-system-dev curl capnproto libcapnp-dev libzmq3-dev ros-melodic-desktop-full python-catkin-tools"

echo "Adding ros repository to sources"
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
sudo apt update

echo "adding setup.sh to ~/.bashrc"
if ! grep -Fxq "/opt/ros/" ~/.bashrc
then
    echo "#fancy prompt that also shows the current branch" >> ~/.bashrc
    echo "export PS1='\[\033[01;32m\]\u@\h\[\033[01;34m\] \w \[\033[01;31m\]$(__git_ps1 \"[%s]\")\[\033[01;34m\]\$\[\033[00m\] '" >> ~/bashrc
    echo "# ROS specific" >> ~/.bashrc
    echo "source /opt/ros/melodic/setup.sh" >> ~/.bashrc
    echo "export DOMAIN_FOLDER=$(pwd)" >> ~/.bashrc
fi

echo "Adding zeromq key"
wget https://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/xUbuntu_18.04/Release.key -O- | sudo apt-key add

echo "Installing neccesary dependencies"
sudo apt install -y $depends

while true; do
    read -p "Did you setup an ssh key for your github account?(y/n)" yn
    case $yn in 
        [Yy]* ) overSSSH=true;;
        [Nn]* ) overSSH=false;;
        * ) Please answer with yes or no;;
    esac
done


echo "Cloning repositorys"
(
    cd src
    if [ -d "$telegramm-client" ]; then
        echo "Skipping repository \"telegram-client\""
    else
        if "$overSSH"; then
            git clone git@github.com:dasys-lab/telegram-client.git
        else
            git clone https://github.com/carpe-noctem-cassel/telegram-client.git
    fi
    if [ -d "$tgbot-cpp" ]; then
        echo "Skipping repository \"tgbot-cpp\""
    else
        if "$overSSH"; then
            git clone git@github.com:dasys-lab/tgbot-cpp.git
        else
            git clone https://github.com/dasys-lab/tgbot-cpp.git
    fi
    if [-d "$capnzero"]; then
        echo "Skipping repository \"capnzero\""
    else
        if "$overSSH"; then
            git clone git@github.com:dasys-lab/capnzero.git
        else
            git clone https://github.com/dasys-lab/capnzero.git
    fi
)

echo "Building Telegram api"
dir=$(pwd)
(cd $dir/src/tgbot-cpp ; cmake . ; make ; sudo make install)

echo "Building catkin packages"
(catkin build)

# telegram-client
## Description
This project is supposed to build a telegram bot to allow natural language communication between humans an distributed robots from distributet systems group of the univerity of Kassel.  

## Dependencies and links
The repository depends on the Telegram bot api from reo7sp:  
https://github.com/reo7sp/tgbot-cpp.git  
The documentation of zeromq:  
http://zguide.zeromq.org/page:all  
The capnproto documentation:  
https://capnproto.org/   
One possible library for the configuration manager:  
https://github.com/open-source-parsers/jsoncpp  

## Installation
1. Create directory for your workspace
    ```bash
    mkdir <workspace>
    ```
2. Enter the workspace directory using  
    ```bash 
    cd  <workspace>
    ```
3. Add the package source for zeromq with the folllowing three commands:  
   ```bash
   sudo -i
   echo "deb http://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/xUbuntu_18.04/ ./" >> /etc/apt/sources.list
   exit
   ```
4. If you want to use the install script from our repository:
  * Use the following command to download the script:  
  ```bash
    wget -O install.sh https://github.com/carpe-noctem-cassel/telegram-client/raw/master/install.sh
  ```
  * set the execuatble flag with:
  ```bash
    chmod +x install.sh
  ```
  * Run the script using  
  ```bash
    ./install.sh
  ```
5. If you can not setup the project using a script or if the script does not work proceed with the next step.
   If the script did not crash you are done.
6. Install the dependencies for the telegram api:  
```bash
    sudo apt install g++ make binutils cmake libssl-dev libboost-system-dev capnproto libcapnp-dev
```
7. clone the telegram bot api using following command:
```bash
    git clone https://github.com/reo7sp/tgbot-cpp.git
```
8. Enter the repository:
```bash
    cd tgbot-cpp
```
9. run Cmake with:  
```bash
    cmake .
```
10. build the api using:  
```bash
    make
```
11. Install the api using:  
```bash
    sudo make install
```
12. leave the directory:  
```bash
    cd ..
```
13. clone our repository:  
```bash
    git clone https://github.com/carpe-noctem-cassel/telegram-client.git
```
14. Download and install the gpg key for the package-source of zeromq:  
```bash
    wget https://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/xUbuntu_18.04/Release.key -O- | sudo apt-key add
```
15. Install zeromq:
```bash
    sudo apt install libzmq3-dev
```
16. Installing the official Telegram client:  
    * Make shure that you are in your workspace and change to the directory of the telegram-client repository.  
```bash
    cd telegram-client  
```
    * Run the install script with:  
```bash
    sudo ./telegram-desktop-setup.sh  
```
17. Change the ownership of the executable of the telegram client.
```bash
    sudo chown <username> /usr/local/bin/telegram
```
18. more steps to come...

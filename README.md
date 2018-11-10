# telegram-client
## Installation
1. Create directory for your workspace
2. Enter the workspace directory using
    cd  \<workspace\>
3. If you want to use the install script from our repository:
  * Use the following command to download the script:  
    wget -O install.sh https://github.com/carpe-noctem-cassel/telegram-client/raw/master/install.sh
  * Run the script using ./install.sh
4. If you can not setup the project using a script or if the script does not work proceed with the next step.
   If the script did not crash you are done.
5. Install the dependencies for the telegram api:
    sudo apt install g++ make binutils cmake libssl-dev libboost-system-dev
6. clone the telegram bot api using following command:
    git clone https://github.com/reo7sp/tgbot-cpp.git
7. Enter the repository:
    cd tgbot-cpp
8. run Cmake with:
    cmake .
9. build the api using:
    make
10. Install the api using:
    sudo make install
11. leave the directory:
    cd ..
12. clone our repolitory:
    git clone https://github.com/carpe-noctem-cassel/telegram-client.git
13. more steps to come...

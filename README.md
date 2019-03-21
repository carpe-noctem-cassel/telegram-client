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
    mkdir <workspace>/src
    ```
2. Enter the workspace directory using  
    ```bash 
    cd  <workspace>/src
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
    cd ..
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
sudo apt install g++ make binutils cmake libssl-dev libboost-system-dev capnproto libcapnp-dev ros-melodic-desktop-full python-catkin-tools
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
14. clone the capnzero repository:
```bash
git clone https://github.com/dasys-lab/capnzero.git
```
15. Download and install the gpg key for the package-source of zeromq:  
```bash
wget https://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/xUbuntu_18.04/Release.key -O- | sudo apt-key add
```
16. Install zeromq:libzmq3-dev ros-melodic-full python-catkin-tools
```bash
sudo apt install libzmq3-dev
```
17. Installing the official Telegram client:  
    * Make shure that you are in your workspace and change to the directory of the telegram-client repository.  
    ```bash
    cd telegram-client  libzmq3-dev ros-melodic-full python-catkin-tools
    ```
    * Run the install script with:  
    ```bash
    sudo ./telegram-desktop-setup.sh  
    ```
18. Change the ownership of the executable of the telegram client.
```bash
sudo chown <username> /usr/local/bin/telegram
```
19. Open your .bashrc file:
```bash
nano ~/.bashrc
```
20. Scroll to the end of the file and append the following line:
```bash
#fancy prompt that also shows the current branch
export PS1='\[\033[01;32m\]\u@\h\[\033[01;34m\] \w \[\033[01;31m\]$(__git_ps1 "[%s]")\[\033[01;34m\]\$\[\033[00m\] '
# ROS specific
source /opt/ros/melodic/setup.sh
export DOMAIN_FOLDER=/home/stefan/teamwork-ws/
```
21. Close your shell:
```bash
exit
```
22. Open a new shell
23. navigate back to your workspace:
```bash
cd <wokspace>/
```
24. Build the catkin projects with:
```bash
catkin build
```
25. Set an environment Variable to the root of your workspace inside your .bashrc:
```bash
export KEY_PATH=<Path/to/your/telegram.key>
```
25. To run the bot you have to ge an api key first. The key is not inside the repository for obvieous reasons.
    Add a file called telegram.key and paste the api key into the file. If you dont have a key,you could optain it by texting the botfather bot. [Here is the Botfather](https://telegram.me/botfather)

25. more steps to come...

## Parts of the project  
| Name      | Description | Tasks |
| --------- | ----------- | ----- |
| tg_bridge | The connection between Telegram and the robots system. This part is supposed to forward messaged recived from telegram to tha robot and forward messages from the robot to Telegram. |  |

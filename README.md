# telegram-client
## Description
This project is supposed to build a telegram bot to allow natural language communication between humans an distributed robots from distributet systems group of the univerity of Kassel.  

## Dependencies and links
The repository depends on the Telegram bot api from reo7sp:  
https://github.com/dasys-lab/tgbot-cpp  
The documentation of zeromq:  
http://zguide.zeromq.org/page:all  
The capnproto documentation:  
https://capnproto.org/    

## Installation
1. Create directory for your workspace
    ```bash
    mkdir <workspace>/src
    ```
2. Enter the workspace directory using  
    ```bash 
    cd  <workspace>
    ```
3. Add the package source for zeromq draft verion with the folllowing three commands:  
   ```bash
   sudo -i
   echo "deb http://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/xUbuntu_18.04/ ./" >> /etc/apt/sources.list
   exit
   ```
4. If you want to use the install script from our repository:
  * Use the following command to download the script:  
    ```bash
    cd ..
    wget -O install.sh https://github.com/dasys-lab/telegram-client/raw/master/install.sh
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
7. navigate into src directory:
```bash
cd src
```
8. clone the telegram bot api using following command. If you have set up an ssh key for your computer on github, we would advise to use the commands for ssh, since we find it easier to work with from day to day:
```bash
git clone https://github.com/dasys-lab/tgbot-cpp.git # over https or 
git clone git@github.com:dasys-lab/tgbot-cpp.git # over ssh
```
9. Enter the repository:
```bash
cd tgbot-cpp
```
10. run Cmake with:  
```bash
cmake .
```
11. build the api using:  
```bash
make
```
12. Install the api using:  
```bash
sudo make install
```
13. leave the directory:  
```bash
cd ..
```
14. clone our repository. If you have set up an ssh key for your computer on github, we would advise to use the commands for ssh, since we find it easier to work with from day to day:  
```bash
git clone https://github.com/carpe-noctem-cassel/telegram-client.git # over https or 
git clone git@github.com:dasys-lab/telegram-client.git # over ssh
```
15. clone the capnzero repository. If you have set up an ssh key for your computer on github, we would advise to use the commands for ssh, since we find it easier to work with from day to day:
```bash
git clone https://github.com/dasys-lab/capnzero.git # over https or
git clone git@github.com:dasys-lab/capnzero.git # over ssh
```
16. Download and install the gpg key for the package-source of zeromq:  
```bash
wget https://download.opensuse.org/repositories/network:/messaging:/zeromq:/git-draft/xUbuntu_18.04/Release.key -O- | sudo apt-key add
```
17. Install zeromq:libzmq3-dev ros-melodic-full python-catkin-tools
```bash
sudo apt install libzmq3-dev
```
18. Installing the official Telegram client:  
    * Make shure that you are in your workspace and change to the directory of the telegram-client repository.  
    ```bash
    cd telegram-client
    ```
    * Run the install script with:  
    ```bash
    sudo ./telegram-desktop-setup.sh  
    ```
19. Change the ownership of the executable of the telegram client.
```bash
sudo chown <username> /usr/local/bin/telegram
```
20. Open your .bashrc file:
```bash
nano ~/.bashrc
```
21. Scroll to the end of the file and append the following line:
```bash
#fancy prompt that also shows the current branch
export PS1='\[\033[01;32m\]\u@\h\[\033[01;34m\] \w \[\033[01;31m\]$(__git_ps1 "[%s]")\[\033[01;34m\]\$\[\033[00m\] '
# ROS specific
source /opt/ros/melodic/setup.sh
export DOMAIN_FOLDER=Path/to/the/workspace
```
22. Close your shell, or reload it:
```bash
exit # If you want to open a new
source ~/.bashrc # If you want to reload the shell
```
23. Open a new shell if yout closed the old one
24. navigate back to your workspace:
```bash
cd <wokspace>/
```
25. Build the catkin projects with:
```bash
catkin build
```

26. To run the bot you have to ge an api key first. The key is not inside the repository for obvieous reasons.
    Add a file called telegram.key and paste the api key into the file. If you dont have a key,you could optain it by texting the botfather bot. [Here is the Botfather](https://telegram.me/botfather) Creating a new api key needs no further explanation, since it is a guided process.
    
27. Put your api-key into a text file and place it somewhere you will find it. We suggest naming it telegram.key

28. Set an environment Variable to the root of your workspace inside your .bashrc:
```bash
export KEY_PATH=Path/to/your/telegram.key
```

## Parts of the project  
These are the components, that we anticipated to be usefull. They are not fixed, so they can change during further developement.
<table>
    <tr>
        <th>Name</th>
        <th>Description</th>
        <th>Tasks</th>
    </tr>
    <tr>
        <td>tg_bridge</td>
        <td>The connection between Telegram and the robots system. This part is supposed to forward messaged recived from telegram to tha robot and forward messages from the robot to Telegram.</td>
        <td>
            <ul>
                <li>[x] Communicate with Telegram. </li>
                <li>[x] Send Messages form Telegram To Robot. </li>
                <li>[x] Create Message data structure and wrap capnproto message with it. </li>
                <li>[x] Create Listener to echo messages for debugging. </li>
                <li>[x] Create dispatcher to send messages to Telegram.</li>
                <li>[x] Send Messsages from Robot to Telegram </li>
                <li>[x] Combine sending and reciving with threads.</li>
                <li>[ ] Create dummy bridge for debugging work.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <td>msg_proc</td>
        <td>Parses the messages and fills implicit info, so the further processing does not have to find these informations.</td>
        <td>
            <ul>
                <li>[ ] Find library that is suitable for our needs.</li>
                <li>[ ] Build working example with the libraries to test which works best.</li>
                <li>[ ] Create a program that parses Messages from the bridge.</li>
                <li>[ ] Get add filling implicit information from common knowledge or user information.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <td>usr_manager</td>
        <td>A Program that stores and manages user information.</td>
        <td>
            <ul>
                <li>[ ] Create a program that listens to incoming messages and stores the userinfo from messages, if the userid is not stored yet.</li>
                <li>[ ] add the ability to add additional user info via a message or prompt.</li>
                <li>[ ] implement a way to search for information about a specific user.</li>
            </ul>
        </td>
    </tr>
    <tr>
        <td>conf_manager</td>
        <td>A program that manages configurations between all parts of the system. This part is optional and will likely not be implemented.</td>
        <td>
            <ul>
                <li>[ ] create a program that can read and store key/value pairs to a file.</li>
                <li>[ ] Create a program to querry/write for configurations over socket and add socket support to the program.</li>
                <li>[ ] add notifications on changed values.</li>
            </ul>
        </td>
    </tr>
</table>

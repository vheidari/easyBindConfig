![logo](https://cloud.githubusercontent.com/assets/919149/23335720/60b8972c-fbd0-11e6-85e4-ce7f8d7f28a4.png)

# SERVER ADMIN NOTE
 - `Easy Bind Config` is now a stable version. You can use EBC on your server to quickly configure Bind.

# About Easy Bind Config
 - This helps you easily install and configure Bind on your server. If you aren't familiar with `Bind` and you want to read more information, please check this link.  : [About Bind Dns Software](https://www.isc.org/downloads/bind/)

## linux server support 
 - You can make and install `Easy Bind Config` on the following distributions: Ubuntu, Mint, Kali, Fedora and Debian

## How can you install and use it?
 * -- Step 01: Download Easy Bind Config from the Git URL and unzip it.
 * -- Step 02: Compile the `main.cpp` file in the Easy Bind Config folder.
 * -- Step 03: Run the binary with `root` privileges and enjoy!

## Note : 
 - To compile `Easy Bind Config,` please use the `C++11` flag as shown in the following snippet :
 	
 ```
 -- g++ -std=c++0x  -o easyBindConfig main.cpp
 ```

## command and help
 * -- `config`   = For start config bind on your server. use this command.
 * -- `install`  = For start install bind dns server software on your server.  
 * -- `remove`   = For remove bind from your server you can use this command. 
 * -- `restore`  = For restore bind from your server you can use this command. 
 * -- `enable`   = For enable bind service and make a symbolic link use this command.
 * -- `start`    = For start bind service use this command.
 * -- `stop`     = For stop bind service use this command.
 * -- `disable`  = For disable bind service use this command.
 * -- `reset`    = For reset bind service use this command.
 * -- `exit`     = For exit from easyBindConfig use this command.
 * -- `back`     = For back to main page use this command.
 * -- `help`     = If you need help you can this command.



## easyBindConfig video tutorial 
- Comming soon

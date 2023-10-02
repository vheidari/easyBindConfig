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
 * -- `config`   = To start configuring Bind on your server, use this command.
 * -- `install`  = To start installing Bind DNS server software on your server, use this command.
 * -- `remove`   = To remove Bind from your server, you can use this command.
 * -- `restore`  = To restore Bind on your server, you can use this command.
 * -- `enable`   = To enable the Bind service and create a symbolic link, use this command.
 * -- `start`    = To start the Bind service, use this command.
 * -- `stop`     = To stop the Bind service, use this command.
 * -- `disable`  = To disable the Bind service, use this command.
 * -- `reset`    = To reset the Bind service, use this command.
 * -- `exit`     = To exit from easyBindConfig, use this command.
 * -- `back`     = To go back to the main page menu, use this command.
 * -- `help`     = If you need help, you can use this command.

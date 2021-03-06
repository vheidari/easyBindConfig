#include <sys/types.h>
#include <dirent.h>

using namespace std;
class SysCommand {

public:

	// return bind install status
	string bindInstallStatus(bool bindInstall)
	{
		if(bindInstall)
		 { 
		 	return 	 " \033[7;32m install - ready to makeing config+zoon file :-)\033[0m\n";
		 } 
		 else 
		 { 
			 return  " \033[7;31m not install :-(\033[0m\n";
		 }
	}

	//install bind server on linux distro by check linux type
	void bindServiceInstall(string linuxType)
	{
		if(linuxType == "Ubuntu")
		{
			system("sudo apt-get install --reinstall bind9");
		}
		else if(linuxType == "Centos")
		{
			system("sudo yum install bind bind-utils");
		}		
		else if(linuxType == "Fedora")
		{
			system("sudo yum install bind*");
		}		
		else if(linuxType == "Debian")
		{
			system("sudo apt-get install --reinstall bind9");
		}
	}

	//unistall bind dns server on distro by  check linux type
	void bindServiceUnistall(string linuxType)
	{
		if(linuxType == "Ubuntu")
		{
			system("sudo apt-get purge --auto-remove bind9");
		}
		else if(linuxType == "Centos")
		{
			system("sudo yum remove bind*");
		}		
		else if(linuxType == "Fedora")
		{
			system("sudo yum remove bind*");
		}		
		else if(linuxType == "Debian")
		{
			system("sudo apt-get purge --auto-remove bind9");
		}

	}

	//start bind server by linux type
	void bindServiceStart(string linuxType)
	{	
		if(linuxType == "Ubuntu")
		{
			system("sudo /etc/init.d/bind9 start");
			usleep(3000000);
		}
		else if(linuxType == "Centos")
		{
			system("systemctl start named");
		}		
		else if(linuxType == "Fedora")
		{
			system("systemctl start named");
		}		
		else if(linuxType == "Debian")
		{
			system("sudo /etc/init.d/bind9 start");
		}

	}

	//restart bind server by linux type
	void bindServiceRestart(string linuxType)
	{
		if(linuxType == "Ubuntu")
		{
			system("sudo /etc/init.d/bind9 restart");
		}
		else if(linuxType == "Centos")
		{
			system("systemctl restart named");
		}		
		else if(linuxType == "Fedora")
		{
			system("systemctl restart named");
		}		
		else if(linuxType == "Debian")
		{
			system("sudo /etc/init.d/bind9 restart");
		}
	}	


	//stop bind server by linux type
	void bindServiceStop(string linuxType)
	{
		if(linuxType == "Ubuntu")
		{
			system("sudo /etc/init.d/bind9 stop");
		}
		else if(linuxType == "Centos")
		{
			system("systemctl stop named");
		}		
		else if(linuxType == "Fedora")
		{
			system("systemctl stop named");
		}		
		else if(linuxType == "Debian")
		{
			system("sudo /etc/init.d/bind9 stop");
		}
	}

	//enable bind server by linux type
	void bindServiceEnable(string linuxType)
	{
		if(linuxType == "Ubuntu")
		{
			system("sudo /etc/init.d/bind9 enable");
		}
		else if(linuxType == "Centos")
		{
			system("systemctl enable named");
		}		
		else if(linuxType == "Fedora")
		{
			system("systemctl enable named");
		}		
		else if(linuxType == "Debian")
		{
			system("sudo /etc/init.d/bind9 enable");
		}
	}
	

	//disable bind server by linux type
	void bindServiceDisable(string linuxType)
	{
		if(linuxType == "Ubuntu")
		{
			system("sudo /etc/init.d/bind9 disable");
		}
		else if(linuxType == "Centos")
		{
			system("systemctl disable named");
		}		
		else if(linuxType == "Fedora")
		{
			system("systemctl disable named");
		}		
		else if(linuxType == "Debian")
		{
			system("sudo /etc/init.d/bind9 disable");
		}

	}

	//status bind server by linux type
	void bindServiceStatus(string linuxType)
	{
		if(linuxType == "Ubuntu")
		{
			system("sudo /etc/init.d/bind9 status");
		}
		else if(linuxType == "Centos")
		{
			system("systemctl status named");
		}		
		else if(linuxType == "Fedora")
		{
			system("systemctl status named");
		}		
		else if(linuxType == "Debian")
		{
			system("sudo /etc/init.d/bind9 status");
		}
	}

	// copy all import file of bind
	void copyAndMakeBackup(string linuxType)
	{
		if(linuxType == "Ubuntu")
		{
			system("mkdir /etc/bind/BindBackup");
			system("cp /etc/bind/named.conf.local /etc/bind/BindBackup");
			system("cp /etc/default/bind9 /etc/bind/BindBackup");
		}
		else if(linuxType == "Centos")
		{
			system("mkdir /etc/named/BindBackup");
			system("cp /etc/named.conf  /etc/named/BindBackup");
			system("cp /etc/resolv.conf /etc/named/BindBackup");
			system("cp /etc/hosts /etc/named/BindBackup");
		}
		else if(linuxType == "Fedora")
		{
			system("mkdir /etc/named/BindBackup");
			system("cp /etc/named.conf  /etc/named/BindBackup");
			system("cp /etc/resolv.conf /etc/named/BindBackup");
			system("cp /etc/hosts /etc/named/BindBackup");
		}		
		else if(linuxType == "Debian")
		{
			system("mkdir /etc/bind/BindBackup");
			system("cp /etc/bind/named.conf.local /etc/bind/BindBackup");
			system("cp /etc/default/bind9 /etc/bind/BindBackup");
		}

	}
	// restore Orginal file in /etc/bind/ and /etc/default/
	void restoreOrginalfile(string linuxType)
	{
		if(linuxType == "Ubuntu")
		{
			system("cp /etc/bind/BindBackup/named.conf.local /etc/bind");
			system("cp /etc/bind/BindBackup/bind9 /etc/default ");
		}
		else if(linuxType == "Centos")
		{
			system("cp /etc/named/BindBackup/named.conf /etc");
			system("cp /etc/named/BindBackup/resolv.conf /etc");
			system("cp /etc/named/BindBackup/hosts /etc");
		}
		else if(linuxType == "Fedora")
		{
			system("cp /etc/named/BindBackup/named.conf /etc");
			system("cp /etc/named/BindBackup/resolv.conf /etc");
			system("cp /etc/named/BindBackup/hosts /etc");
		}		
		else if(linuxType == "Debian")
		{
			system("cp /etc/bind/BindBackup/named.conf.local /etc/bind");
			system("cp /etc/bind/BindBackup/bind9 /etc/default ");
		}

	}

	void exitFromEbc()
	{
		system("reset");
		cout << "good bye ADMIN have good time \n";
		exit(0);
	}	


	// show help page
	void help()
		{
			system("reset");
			
			string pointer;

			while(true)
			{
				cout << " \033[7;32m easy Bind Config help - version 0.1 \033[0m\n" << endl;
				cout << "-----------------------------------------------------------------------" << endl;
				cout << "DESCRIPTION : " << endl<< endl;
				cout << " +Command: \033[7;32m config \033[0m\n" << endl;
				cout << " 	- For start config bind on your server. use this command." << endl;
				cout << endl;
				cout << " +Command: \033[7;32m install \033[0m\n" << endl;
				cout << " 	- For start install bind dns server software on your server. " << endl;
				cout << "	  you can use this command. this is auto install bind on your server" << endl;
				cout << "	  work on default easyBindConfig distro support." << endl;
				cout << endl;
				cout << " +Command: \033[7;32m remove \033[0m\n" << endl;
				cout << " 	- For remove bind from your server you can use this command. " << endl;
				cout << endl;			
				cout << " +Command: \033[7;32m restore \033[0m\n" << endl;
				cout << " 	- after install bind on your server by easyBindConfig. EBC backup " << endl;
				cout << " 	  bind default config. if problems in config  use this command" << endl;
				cout << " 	  EBC restore backup file and rewrite config file." << endl;
				cout << endl;			
				cout << " +Command: \033[7;32m enable \033[0m\n" << endl;
				cout << " 	- for enable bind service and make a symbolic link use this command." << endl;
				cout << endl;			
				cout << " +Command: \033[7;32m start \033[0m\n" << endl;
				cout << " 	- for start bind service use this command." << endl;
				cout << endl;			
				cout << " +Command: \033[7;32m stop \033[0m\n" << endl;
				cout << " 	- for stop bind service use this command." << endl;
				cout << endl;			
				cout << " +Command: \033[7;32m disable \033[0m\n" << endl;
				cout << " 	- for disable bind service use this command." << endl;
				cout << endl;			
				cout << " +Command: \033[7;32m reset \033[0m\n" << endl;
				cout << " 	- for reset bind service use this command." << endl;
				cout << endl;			
				cout << " +Command: \033[7;32m exit \033[0m\n" << endl;
				cout << " 	- for exit from easyBindConfig use this command." << endl;
				cout << endl;			
				cout << " +Command: \033[7;32m back \033[0m\n" << endl;
				cout << " 	- for back to main page use this command." << endl;
				cout << endl;			
				cout << " +Command: \033[7;32m help \033[0m\n" << endl;
				cout << " 	- if you need help you can this command." << endl;
				cout << endl;
				cout << "-----------------------------------------------------------------------" << endl;
				cout << "	+for back to main page type 'back' " << endl;
				cout << "EBC > ";
				cin  >> pointer;

				if(pointer == "back")
				{
					break;
				}
				else if(pointer == "exit")
				{
					SysCommand::exitFromEbc();
				}
				else
				{
					system("reset");
				}
			}

		}


};


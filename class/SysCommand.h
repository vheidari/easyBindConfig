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
			system("sudo apt-get install bind*");
		}
		else if(linuxType == "Centos")
		{
			system("sudo yum install bind*");
		}		
		else if(linuxType == "Fedora")
		{
			system("sudo yum install bind*");
		}		
		else if(linuxType == "Debian")
		{
			system("sudo apt-get install bind*");
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
			system("sudo apt-get remove bind*");
		}

	}

	//start bind server by linux type
	void bindServiceStart(string linuxType)
	{	
		if(linuxType == "Ubuntu")
		{
			system("sudo /etc/init.d/bind9 start");
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


};


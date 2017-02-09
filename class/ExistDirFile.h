#include <sys/types.h>
#include <dirent.h>

using namespace std;

class ExistDirFile {
	
	public:
	
	// checking bind install in Ubuntu - Centos - Fedora - Debian
    bool bindIsInstall( string linuxType)
	{	
		if(linuxType == "Ubuntu")
		{
			
			DIR* checkbindDir = opendir("/usr/share/bind9");
			if(checkbindDir)
			 {
			 	return true;
			 }
			 else
			 {
			 	return false;
			 }
		}
		else if(linuxType == "Centos")
		{
			DIR* checkbindDir = opendir("/etc/named");
			if(checkbindDir)
			 {
			 	return true;
			 }
			 else
			 {
			 	return false;
			 }
			
		}	
		else if(linuxType == "Fedora")
		{
			DIR* checkbindDir = opendir("/etc/bind");
			if(checkbindDir)
			 {
			 	return true;
			 }
			 else
			 {
			 	return false;
			 }

		}
		else if(linuxType == "Debian")
		{
			DIR* checkbindDir = opendir("/etc/bind");
			if(checkbindDir)
			 {
			 	return true;
			 }
			 else
			 {
			 	return false;
			 }

		}
		else
		{
			return false;
		}

	}

	// cheking backup filder make and bind backup is exist
	bool chekingBindBackup(string linuxType)
	{
		if(linuxType == "Ubuntu")
		{
			DIR* checkbackupDir = opendir("/etc/bind/BindBackup");
			if (checkbackupDir)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}


};
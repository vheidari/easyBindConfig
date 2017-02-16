#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "class/SysCommand.h"
#include "class/MakeFile.h"
#include "class/ExistDirFile.h"
#include "class/Validate.h"


//make standard library name space
using namespace std;


// start main of DSCv project 
int main()
{
	//make input string variable
	string pointer,
		   dominName, 
		   ipAddress,
		   optionv4,
		   zoneDirectory,
		   allowQuery,
		   typeZone,
		   allowUpdate,
		   linuxType,
		   linuxName,
		   bindInstallStatus,
		   line;

    //make input boolian variable
    //defualt bind dns options 
	bool recurasion = false;
	bool dnssec_enable =  true;
	bool dnssec_validation = true;
	bool bindInstall = false;
	bool bindBackupExist = false;
	bool ipVer4Status = false;
	bool dominNameStatus = false;

	char getKeyPress;



	//check linux distro
	ifstream getLinuxType;
	getLinuxType.open("/etc/os-release");
		if(getLinuxType.is_open())
		{
			while(!getLinuxType.eof())
			{
				getline(getLinuxType, line);
				if(line.find("ID=ubuntu", 0) != string::npos)
				{	
					linuxType = "Ubuntu";
					linuxName = "Ubuntu";
				}
				else if(line.find("ID=linuxmint", 0) != string::npos)
				{
					linuxType = "Ubuntu";
					linuxName = "Mint";
				}				
				else if(line.find("ID=kali", 0) != string::npos)
				{
					linuxType = "Ubuntu";
					linuxName = "Kali";
				}				
				else if(line.find("ID=\"centos\"", 0) != string::npos)
				{
					linuxType = "Centos";
					linuxName = "Centos";
				}
				else if(line.find("ID=fedora", 0) != string::npos)
				{
					linuxType = "Fedora";
					linuxName = "Fedora";

				}				
				else if(line.find("ID=debian", 0) != string::npos)
				{
					linuxType = "Debian";
					linuxName = "Debian";
				}
			}	
		}
	
	while(true)
	{

		//check bind is install
		ExistDirFile ExistDirObject;
		bindInstall = ExistDirObject.bindIsInstall(linuxType);



		//return bind install status
		SysCommand BindStatus;
		bindInstallStatus = BindStatus.bindInstallStatus(bindInstall);

		//run command 
		SysCommand syscommand;

		if(linuxName == "")
		{
			linuxType = "Unknown os";
			linuxName = "Unknown os";
		}

		 system("reset");
		 cout << "Easy Bind Config version 0.1 \n";
		 cout << "-------------------------------------------------------\n";
		 cout << "	+ EBC help to you make easy CONFIG and ZOON file for Bind Dns Server \n";
		 cout << "	+ Author 	: VAHID HEIDARI \n";
		 cout << "	+ Author EMAIL  : vahid-heidari@hotmail.com \n";
		 cout << "	+ License  	: MIT License \n";
		 cout << "-------------------------------------------------------\n";
		 cout << "Your linux is :  " << linuxName << " distro " << endl;
		 cout << "\n";
		 cout << "Bind dns server is : " << bindInstallStatus << endl;
		 cout << "-------------------------------------------------------\n";

		 if(linuxType == "Unknown os")
		 {
		 	cout << "EBC Unkhowe Os and not work on linux distro !\n";
		 	cout << "easyBindConfig only work on Ubuntu,Mint,Centos,Fedora,Debian \n";
		 	cout << "-------------------------------------------------------\n";
		 	usleep(3000000);
		 	syscommand.exitFromEbc();
		 }

		//check BindBackup is exist in /etc/bind
		bindBackupExist = ExistDirObject.chekingBindBackup(linuxType);
			


		 if(bindInstall)
		 {

		 	//get command by pointer 
		 	cout << "For initial bind server please type 'config' \n";
		 	cout << "	+If you need help type 'help' \n";
		 	cout << "EBC > ";
		 	cin  >> pointer;

		 	if(pointer == "config")
		 	{

			 	if(linuxType == "Ubuntu")
				{
			 	
				 	if(!bindBackupExist)
				 	{
				 		//make backup from bind file 
				 		SysCommand bindBackUpFile;
				 		bindBackUpFile.copyAndMakeBackup(linuxType);
				 	}

				 	cout << "EBC find Bind Dns Server software \n";
				 	cout << "	+Please insert ip server ex = 48.10.15.30\n";
				 	cout << "EBC > ";
				 	cin  >> pointer;
				 	
				 	if(pointer == "exit")
				 	{
						syscommand.exitFromEbc();
				 	}
				 	else if(pointer == "back")
				 	{
				 		continue;
				 	}
				 	else if(pointer == "help")
				 	{
				 		//todo
				 	}
				 	else
				 	{
				 		ipAddress = pointer;

				 		//chack ipAddress version 4
				 		Validate validInput;
				 		ipVer4Status = validInput.validateIpV4Address(ipAddress);
	
					 	if(!ipVer4Status)
					 	{
					 		cout << "Your input ip is not valid ! Please Wait easyBindConfig restart...\n";
					 		usleep(3000000);
					 		continue;
					 	}
	
				 	   cout << "	+Please insert domin name ex = mydomin.com\n";
   				 	   cout << "EBC > ";
   				 	   cin  >>	pointer;

   				 		if(pointer == "exit")
					 	{
							syscommand.exitFromEbc();
					 	}
					 	else if(pointer == "back")
					 	{
					 		continue;
					 	}
					 	else if(pointer == "help")
				 		{
				 			//todo
				 		}
   					  	else
   					  	{
   					  	    dominName = pointer;
   				 	   
		   				    //check dominName input by user
		   			   	    dominNameStatus = validInput.validateDomineName(dominName);
		   				    if(!dominNameStatus)
		   				    {
		   				 	   	cout << "Your input domine name is not valid ! Please Wait easyBindConfig restart...\n";
		   				 	   	usleep(3000000);
		   				 	   	continue;
		   				    }
		   				 	   
		   				 	// making bind9 file in /etc/default/bind9
		   				 	MakeFile makeBind9;
		   				 	makeBind9.ubuntuMakeBind9File();
		   
		   				 	// make and backup zone file in /etc/bind/zones
		   				 	// update zone and master file
		   				 	MakeFile MakeZoneFile;
		   				 	MakeZoneFile.updateZoneInNamedFile(linuxType, dominName);
		   				 	MakeZoneFile.updateReversInNamedFile(linuxType, ipAddress);
		   
						    // make zone file and master file
							MakeZoneFile.ubuntuMakeZoneFile(dominName, ipAddress);
						 	MakeZoneFile.ubuntuMakeMasterFile(dominName, ipAddress);	

						 	system("reset");

						 	cout << "Please wite ... \n";
						 	cout << "------------------------------------------------ \n";
						 	cout << "BIND IS NOW CONFIG BY easyBindConfig ;-)\n";
						 	cout << "------------------------------------------------ \n";
						 	cout << "Your  ip address : " << ipAddress << endl;
		   				 	cout << "Your domin name  : " << dominName << endl;
		   				 	cout << "Your nameserver  : " << "dns1." << dominName << endl;
		   				 	cout << "Your nameserver  : " << "dns2." << dominName << endl;
						 	cout << "------------------------------------------------ \n";
						 	
						 	//restart bind dns server
						 	syscommand.bindServiceRestart(linuxType);

		   				 	usleep(10000000);
   					  	}

				 	}
				 	
				}
				else if(linuxType == "Centos")
				{
					
				 	if(!bindBackupExist)
				 	{
				 		//make backup from bind file 
				 		SysCommand bindBackUpFile;
				 		bindBackUpFile.copyAndMakeBackup(linuxType);
				 	}

				 	cout << "EBC find Bind Dns Server software \n";
				 	cout << "	+Please insert ip server ex = 48.10.15.30\n";
				 	cout << "EBC > ";
				 	cin  >> pointer;
				 	
				 	if(pointer == "exit")
				 	{
						syscommand.exitFromEbc();
				 	}
				 	else if(pointer == "back")
				 	{
				 		continue;
				 	}
				 	else if(pointer == "help")
				 	{
				 		//todo
				 	}
				 	else
				 	{
				 		ipAddress = pointer;

				 		//chack ipAddress version 4
				 		Validate validInput;
				 		ipVer4Status = validInput.validateIpV4Address(ipAddress);
	
					 	if(!ipVer4Status)
					 	{
					 		cout << "Your input ip is not valid ! Please Wait easyBindConfig restart...\n";
					 		usleep(3000000);
					 		continue;
					 	}
	
				 	   cout << "	+Please insert domin name ex = mydomin.com\n";
   				 	   cout << "EBC > ";
   				 	   cin  >>	pointer;

   				 		if(pointer == "exit")
					 	{
							syscommand.exitFromEbc();
					 	}
					 	else if(pointer == "back")
					 	{
					 		continue;
					 	}
					 	else if(pointer == "help")
				 		{
				 			//todo
				 		}
   					  	else
   					  	{
   					  	    dominName = pointer;
   				 	   
		   				    //check dominName input by user
		   			   	    dominNameStatus = validInput.validateDomineName(dominName);
		   				    if(!dominNameStatus)
		   				    {
		   				 	   	cout << "Your input domine name is not valid ! Please Wait easyBindConfig restart...\n";
		   				 	   	usleep(3000000);
		   				 	   	continue;
		   				    }
		   				 	   
		   				    //todo centos
		   					
		   				 	// make and backup zone file in /etc/bind/zones
		   				 	// update zone and master file
		   				 	MakeFile MakeZoneFile;
		   				 	MakeZoneFile.updateZoneInNamedFile(linuxType, dominName);
		   				 	MakeZoneFile.updateReversInNamedFile(linuxType, ipAddress);
		   					
		   					/*
						    // make zone file and master file
							MakeZoneFile.ubuntuMakeZoneFile(dominName, ipAddress);
						 	MakeZoneFile.ubuntuMakeMasterFile(dominName, ipAddress);	

						 	system("reset");

						 	cout << "Please wite ... \n";
						 	cout << "------------------------------------------------ \n";
						 	cout << "BIND IS NOW CONFIG BY easyBindConfig ;-)\n";
						 	cout << "------------------------------------------------ \n";
						 	cout << "Your  ip address : " << ipAddress << endl;
		   				 	cout << "Your domin name  : " << dominName << endl;
		   				 	cout << "Your nameserver  : " << "dns1." << dominName << endl;
		   				 	cout << "Your nameserver  : " << "dns2." << dominName << endl;
						 	cout << "------------------------------------------------ \n";
						 	
						 	//restart bind dns server
						 	syscommand.bindServiceRestart(linuxType);

		   				 	usleep(30000000);
		   				 	*/
   					  	}

				 	}
				}
				else if(linuxType == "Fedora")
				{	
					//todo
				}
				else if(linuxType == "Debian")
				{
					//todo	
				}
		 	}
		 	else if(pointer == "help")
		 	{
	
		 	}
		 	else if(pointer == "remove")
		 	{
		 		syscommand.bindServiceUnistall(linuxType);
		 	}
		 	else if(pointer == "restor")
		 	{
		 		syscommand.restoreOrginalfile(linuxType);
		 	}
		 	else if(pointer == "start")
		 	{
		 		syscommand.bindServiceStart(linuxType);
		 	}
		 	else if(pointer == "stop")
		 	{
		 		syscommand.bindServiceStop(linuxType);
		 	}
		 	else if(pointer == "enable")
		 	{
		 		syscommand.bindServiceEnable(linuxType);
		 	}
		 	else if(pointer == "disable")
		 	{
		 		syscommand.bindServiceDisable(linuxType);

		 	}
		 	else if(pointer == "reset")
		 	{
		 		syscommand.bindServiceRestart(linuxType);
		 	}
		 	else if(pointer == "exit")
		 	{
		 		syscommand.exitFromEbc();
		 	}


		 }
		 else
		 {
		 	cout << "EBC NOTfind Bind Dns Server software \n";
			cout << "	+For install Bind Dns Server Soft type 'install' \n";
			cout << "EBC > ";
			cin  >>	pointer;
			if(pointer == "install")
			{
				//install bind service on linux by linuxType
				SysCommand BindServiceInstall;
				BindServiceInstall.bindServiceInstall(linuxType);
				BindServiceInstall.bindServiceStart(linuxType);
				BindServiceInstall.bindServiceEnable(linuxType);
			}
			else if(pointer == "help")
		 	{
				//todo
		 	}
		 	else if(pointer == "exit")
		 	{
		 		syscommand.exitFromEbc();
		 	}

			system("clear");
			bindInstall = true;
			continue;
		 }



	} //end of while


}
#include <sys/types.h>
#include <dirent.h>
#include <sstream>

using namespace std;
class MakeFile {

public:


	// making bind9 file in /etc/default/bind9
	void ubuntuMakeBind9File()
	{
		ofstream configFile;
		configFile.open("/etc/default/bind9");
		configFile  << "# run resolvconf?\n";
		configFile  << "RESOLVCONF=no\n";
		configFile  << "\n";
		configFile  << "# startup options for the server\n";
		configFile  << "OPTIONS=\"-4 -u bind\"\n";
		configFile.close();
	}

	//update zone file and make zones directory
	void updateZoneInNamedFile(string linuxType, string dominName)
	{
		if(linuxType == "Ubuntu")
		{
			system("mkdir /etc/bind/zones");
			system("cp /etc/bind/named.conf.local /etc/bind/named.conf.local.backup");

			ofstream makeZone;
			makeZone.open("/etc/bind/named.conf.local", std::ios::app);
			makeZone << "\n";
			makeZone << "####################  zone+master make by easy bind config #####################";
			makeZone << "\n" << endl;
			makeZone << "zone \"" << dominName << "\" {" << endl;
			makeZone << "type master;" <<  endl;
			makeZone << "file \"/etc/bind/zones/" << dominName << ".db\";" << endl;
			makeZone << "};" << endl;
			makeZone << "\n";
			makeZone.close();
		}
		else if(linuxType == "Centos")
		{
			system("mkdir /var/named/zones");
			system("cp /etc/named.conf /var/named/named.conf.backup");

			ofstream makeZone;
			makeZone.open("/etc/named.conf", std::ios::app);
			makeZone << "\n";
			makeZone << "####################  zone+master make by easy bind config #####################";
			makeZone << "\n" << endl;
			makeZone << "zone \"" << dominName << "\" {" << endl;
			makeZone << "type master;" <<  endl;
			makeZone << "file \"/var/named/zones/" << dominName << ".db\";" << endl;
			makeZone << "};" << endl;
			makeZone << "\n";
			makeZone.close();
		}
	}

	// update named.conf.local file and add master recorde
	// help link :
	// --http://stackoverflow.com/questions/10366631/c-how-to-convert-ip-address-to-bytes
	void updateReversInNamedFile(string linuxType, string ipAddress)
	{
		if(linuxType == "Ubuntu")
		{
			stringstream s(ipAddress);
			int a,b,c,d;
			char ch;
			s >> a >> ch >> b >> ch >> c >> ch >> d;
			ofstream makeZoneMaster;
			makeZoneMaster.open("/etc/bind/named.conf.local", std::ios::app);
			makeZoneMaster << "\n" << endl;
			makeZoneMaster << "zone \"" << c << "." << b << "." << a << ".in-addr.arpa\" {" << endl;
			makeZoneMaster << "type master;" << endl;
			makeZoneMaster << "file \"/etc/bind/zones/rev." << c << "." << b << "." << a << ".in-addr.arpa\";" << endl;
			makeZoneMaster << "allow-update { none; };" << endl;
			makeZoneMaster << "};" << endl;
			makeZoneMaster << "\n";
			makeZoneMaster << "#################### zone+master make by easy bind config #####################";
			makeZoneMaster << "\n";
			makeZoneMaster.close();
		}
		else if(linuxType == "Centos")
		{


			ifstream readNamed;
			string readLine;
			readNamed.open("/etc/named.conf");

			ofstream writeNamed;
			writeNamed.open("/var/named/named.conf");

			if(readNamed.is_open())
			{
				while(!readNamed.eof())
				{
					getline(readNamed, readLine);
					if(readLine == "	listen-on port 53 { 127.0.0.1; };")
					{
						writeNamed << "	listen-on port 53 { 127.0.0.1; " + ipAddress + "; };" << endl;
						continue;
					}
					writeNamed << readLine << endl;
				}
			}

			readNamed.close();
			writeNamed.close();

			// check /var/named/named.conf is exist and rewrite on /etc/named.conf
			ifstream checkNamed;
			checkNamed.open("/var/named/named.conf");
			if(checkNamed.is_open())
			{
				checkNamed.close();
				system("cp /var/named/named.conf /etc/named.conf");
				system("rm -rf /var/named/named.conf");
			}
			else
			{
				checkNamed.close();
			}



			stringstream s(ipAddress);
			int a,b,c,d;
			char ch;
			s >> a >> ch >> b >> ch >> c >> ch >> d;
			ofstream makeZoneMaster;
			makeZoneMaster.open("/etc/named.conf", std::ios::app);
			makeZoneMaster << "\n" << endl;
			makeZoneMaster << "zone \"" << c << "." << b << "." << a << ".in-addr.arpa\" {" << endl;
			makeZoneMaster << "type master;" << endl;
			makeZoneMaster << "file \"/var/named/zones/rev." << c << "." << b << "." << a << ".in-addr.arpa\";" << endl;
			makeZoneMaster << "allow-update { none; };" << endl;
			makeZoneMaster << "};" << endl;
			makeZoneMaster << "\n";
			makeZoneMaster << "#################### zone+master make by easy bind config #####################";
			makeZoneMaster << "\n";
			makeZoneMaster.close();

		}

	}

	//make zone file for domain
	void ubuntuMakeZoneFile(string dominName, string ipAddress)
	{
		string path = "/etc/bind/zones/" + dominName + ".db";

		ofstream makeZoneFile;
		makeZoneFile.open(path.c_str());
		makeZoneFile << "; BIND data file for " << dominName << endl;
		makeZoneFile << ";" << endl;
		makeZoneFile << "$TTL 14400" << endl;
		makeZoneFile << "@ IN SOA ns1." << dominName << ". host." << dominName << ". (" << endl;
		makeZoneFile << "201006601 ; Serial" << endl;
		makeZoneFile << "7200 ; Refresh" << endl;
		makeZoneFile << "120 ; Retry" << endl;
		makeZoneFile << "2419200 ; Expire" << endl;
		makeZoneFile << "604800) ; Default TTL" << endl;
		makeZoneFile << dominName << ". IN NS ns1." << dominName << "." << endl;
		makeZoneFile << dominName << ". IN NS ns2." << dominName << "." << endl;
		makeZoneFile << dominName << ". IN MX 10 mail." << dominName << "." << endl;
		makeZoneFile << dominName << ". IN A " << ipAddress << endl;
		makeZoneFile << "ns1 IN A " << ipAddress << endl;
		makeZoneFile << "ns2 IN A " << ipAddress << endl;
		makeZoneFile << "www IN CNAME " << dominName << "." << endl;
		makeZoneFile << "mail IN A " << ipAddress << endl;
		makeZoneFile << "ftp IN CNAME " << dominName << "." << endl;
		makeZoneFile << dominName << ". IN TXT \"v=spf1 ip4:" << ipAddress << " a mx ~all\"" << endl;
		makeZoneFile << "mail IN TXT \"v=spf1 a -all\"" << endl;
		makeZoneFile.close();

	}

	//make a master file for ip address
	void ubuntuMakeMasterFile( string dominName, string ipAddress)
	{
		stringstream s(ipAddress);
		int a,b,c,d;
		char ch;
		s >> a >> ch >> b >> ch >> c >> ch >> d;

		string path = "/etc/bind/zones/rev." + to_string(c) + "." + to_string(b) + "." + to_string(a) + ".in-addr.arpa";


		ofstream makeMasterFile;
		makeMasterFile.open(path.c_str());
		makeMasterFile << "$ORIGIN " 		   			 << to_string(c) + "." + to_string(b) + "." + to_string(a) + ".in-addr.arpa.\n";
		makeMasterFile << "$TTL 86400"  	  			 << endl;
		makeMasterFile << "@ IN SOA " 		   			 << dominName << ". " << "host." << dominName <<". (" << endl;
		makeMasterFile << "2010081401; serial" 			 << endl;
		makeMasterFile << "28800; refresh after 6 hours" << endl;
		makeMasterFile << "604800; retry after 1 hour"   << endl;
		makeMasterFile << "604800; expire after 1 week"  << endl;
		makeMasterFile << "86400 ); minimum TTL of 1 day"<< endl;
		makeMasterFile << ";" 		   					 << endl;
		makeMasterFile << "@	IN	NS	ns1." 		     << dominName << "." << endl;
		makeMasterFile << ";"  							 << endl;
		makeMasterFile << "1	IN	PTR	ns1."  	         << dominName << "." << endl;
		makeMasterFile << "2	IN	PTR	ns2."  	     	 << dominName << "." << endl;
		makeMasterFile << ";"  							 << endl;
		makeMasterFile << "5	IN	PTR	server1."  	     << dominName << "." << endl;
		makeMasterFile << "6	IN	PTR	server2."  	     << dominName << "." << endl;
		makeMasterFile << ";"  							 << endl;
		makeMasterFile << "3	IN	PTR	ftp."  	     	 << dominName << "." << endl;
		makeMasterFile << "4	IN	PTR	ftp."  	         << dominName << "." << endl;
		makeMasterFile << "\n";
		makeMasterFile.close();


	}




};

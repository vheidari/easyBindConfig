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
	void ubuntuUpdateZoneInNamedFile(string dominName)
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

	// update named.conf.local file and add master recorde 
	// help link : 
	// --http://stackoverflow.com/questions/10366631/c-how-to-convert-ip-address-to-bytes
	void ubuntuUpdateMasterInNamedFile(string ipAddress)
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
		makeZoneMaster << "};" << endl;
		makeZoneMaster << "\n";
		makeZoneMaster << "#################### zone+master make by easy bind config #####################";
		makeZoneMaster << "\n";
		makeZoneMaster.close();

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
		makeMasterFile << "@ IN SOA " 	<< dominName << "." << "host." << dominName <<". (" << endl;
		makeMasterFile << "2010081401;" << endl;
		makeMasterFile << "28800;"   	<< endl;
		makeMasterFile << "604800;"     << endl;
		makeMasterFile << "604800;"  	<< endl;
		makeMasterFile << "86400 );" 	<< endl;
		makeMasterFile << "IN NS ns1." 	<< dominName << "." << endl;
		makeMasterFile << "4 IN PTR "  	<< dominName << "." << endl;
		makeMasterFile << "\n";
		makeMasterFile.close();


	}
		



};
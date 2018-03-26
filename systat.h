#include <iostream>
#include <string>

using namespace std;

/*
	Class to get system statistics.
*/
class Systat
{
	public:
		void GetSystemInformation();
		void PrintFile(string filename);
		void PrintCpuInfo ();
		void PrintCpuSpecifics(string line);
		void testprint();	
};


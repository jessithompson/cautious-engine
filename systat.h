#include <iostream>
#include <string>

using namespace std;

class Systat
{
	public:
		void GetSystemInformation();
		void PrintFile(string filename);
		void PrintCpuInfo ();
		void PrintCpuSpecifics(string line);
		void testprint();	
};


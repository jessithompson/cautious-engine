#include "systat.h"
#include <iostream> 
#include <fstream>
#include <string>

using namespace std;	

/* 
Function: GetSystemInformation

Calls functions to gather system information and 
prints to screen. 
Input: none
Output: none
*/
void Systat::GetSystemInformation()
{
	try 
	{
		cout << "version: " << endl;
		PrintFile("version");

		cout << "uptime: " << endl;
		PrintFile("uptime");

		cout << "meminfo:" << endl;
		PrintFile("meminfo");

		cout << "cpuinfo:" << endl;
		PrintFile("cpuinfo");
	}
	catch (...) {}
}


/* 
Function: PrintFile

Only opens files in /proc/ directory. If cpuinfo then function to print
specific information is called. 

Note: used from https://www.mcs.sdsmt.edu/ckarlsso/csc456/spring18/src/ALP/clock-speed.c

Input: string filename - file in /proc/ directory to open
Output: none
*/
void Systat::PrintFile(string filename)
{
	string filePath = "/proc/" + filename;
	ifstream systemFile(filePath);
	while (true)
	{
		if (!systemFile.good())
			break;
		string currentLine;
		getline(systemFile, currentLine);

		string cpuInfoName = "cpuinfo";
		if (cpuInfoName ==filename)
		{
			PrintCpuSpecifics(currentLine);
			if (currentLine.find("cache size") != string::npos)
			{
				break;
			}
		}
		else
		{
			cout << currentLine << endl;
		}

	}
}

/* 
Function: PrintCpuSpecifics

Checks to see if input parameter line matches any of the required fields
to print. 

Input: string line - string to check 
Output: none
*/
void Systat::PrintCpuSpecifics(string line)
{
	if (line.find("vendor_id") != string::npos || line.find("cpu family") != string::npos 
		|| line.find("model") != string::npos || line.find("stepping") != string::npos
		|| line.find("cpu MHz") != string::npos || line.find("cache size") != string::npos)
	{
		cout << line << endl;
	}
	else
		return;
}
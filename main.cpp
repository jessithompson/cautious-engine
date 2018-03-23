#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "systat.h"
#include "pid.h"
#include "cmdnm.h"
#include "execute.h"

using namespace std;
void PrintUsageInfo();
vector<string> SplitUserCommand(string entireCommand);

/* 
Function: main

Handle command line argument and requests by user for information. 

Input: int argc - number of command line arguments given by user
	   char * argv[] - each command line argument provided   
Output: int returnValue - state of program as it exits 
					(non-zero indicates problems)
*/
int main(int argc, char *argv[])
{
	// parse command line arguments
	if (argc > 2)
	{
		cout << "Correct usage of this program is './dash' or './dash -h' for help" << endl;
		return 1;
	}
	else if (argc == 2)
	{
		string helpString = "-h";
		string inputString = argv[1];
		if (inputString == helpString)
		{
			PrintUsageInfo();	
			return 0;
		}
		else
		{
			cout << "Invalid usage. Exiting..." << endl;
			return 1;
		}
	}

	string invalidCommand = "Invalid command!";
	string command = "";
	cout<<"dash>";
	while (getline(cin, command) && command != "exit" && command != "e")
	{	
		// split command string on spaces and handle any problems with that
		vector<string> splitCommand = SplitUserCommand(command);
		if (splitCommand.size() == 2 && splitCommand[0] == "cmdnm")
		{
			Cmdnm _cmdnm(splitCommand[1]);
			if (_cmdnm.ContainsNumericOnly(splitCommand[1]))
			{
				_cmdnm.GetCommandName();
			}
			else
			{
				cout << invalidCommand << "   - Please enter a valid pid\ndash>";
				continue;
			}
		}
		else if (splitCommand.size() == 1 && splitCommand[0] == "cmdnm")	
		{
			cout << invalidCommand << "   - Please enter a valid pid\ndash>";
			continue;
		}
		else if (splitCommand.size() == 2 && splitCommand[0] == "pid")
		{
			ProcessIdentifier procid("");
			procid.ProcessDirectory("/proc", splitCommand[1]);
			if (procid.processName == "")
			{
				cout << "No process found with name of " << splitCommand[1] << endl; 
			}
			else
				cout << procid.processName << endl;
			cout<<"dash>";
			continue;
		}
		else if (splitCommand.size() == 1 && splitCommand[0] == "pid")
		{
			cout << invalidCommand << "   - Please enter a valid pid\ndash>";
			continue;
		}
		else if (splitCommand.size() == 1 && splitCommand[0] == "systat")
		{
			Systat systemInfo;
			systemInfo.GetSystemInformation();
			cout<<"dash>";
			continue;
		}
		else if (splitCommand[0] == "cd")
		{

		}
		else
		{
			ExecuteCommand runCommand(command);
			runCommand.Execute();
			cout<<"dash>";
			continue;
		}
		
		cout<<"dash>";
	}

	return 0;	
}


/* 
Function: PrintUsageInfo

Prints helpful usage info to screen. 

Input: none 
Output: none
*/
void PrintUsageInfo()
{
   cout << "-------- DASH --------" << endl; 
   cout << "\nOnce program starts, use these commands:" << endl;
   cout << "* cmdnm <pid>     - Returns command string that started the given process id." << endl;
   cout << "* pid <command>   - Returns list of processes started by this command" << endl;
   cout << "* systat          - Prints CPU info, uptime, and memory stats" << endl;
   cout << "* exit            - Quits program\n" << endl;
   cout << "To run program enter './dash '\n" << endl;
}

/* 
Function: SplitUserCommand

Tokenize user input on spaces and return as a vector of strings.

Note: Code in this function modified from :
   http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html

Input: string entireCommand - string to tokenize  
Output: vector<string> - each string between spaces
*/
vector<string> SplitUserCommand(string entireCommand)
{
   vector<string> tokenized;
   string buffer;
   stringstream ss(entireCommand);

   while (ss >> buffer)
   {
      tokenized.push_back(buffer);
   }

   return tokenized;
}
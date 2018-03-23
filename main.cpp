#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <limits.h>
#include <unistd.h> 
#include "systat.h"
#include "pid.h"
#include "cmdnm.h"
#include "execute.h"
#include "dash.h"

using namespace std;


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

	char buf[256];
	string currentDirectory = "";
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
	  currentDirectory = "error";
	}
	else
	{
	  currentDirectory = string(buf);
	}
	Dash dashProg(currentDirectory);

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
			dashProg.PrintUsageInfo();	
			return 0;
		}
		else
		{
			cout << "Invalid usage. Exiting..." << endl;
			return 1;
		}
	}

	dashProg.runDash();	
	return 0;	
}


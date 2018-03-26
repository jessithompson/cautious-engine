#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <limits.h>
#include <unistd.h> 
#include <csignal>
#include "systat.h"
#include "pid.h"
#include "pipe.h"
#include "cmdnm.h"
#include "execute.h"
#include "dash.h"

using namespace std;

void signal_handler(int signal);

/* 
Function: main

Handle command line argument and requests by user for information. 
Sets up signal handlers.
Starts Dash.

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

	Dash dashProg;

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

	// set up signal handlers
	signal(SIGABRT, signal_handler);
	signal(SIGFPE, signal_handler);
	signal(SIGILL, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGTERM, signal_handler);

	dashProg.runDash();	
	return 0;	
}

/* 
Function: signal_handler

Prints each signal received by Dash. 

Input: int signal - signal recieved by program
Output: none
*/
void signal_handler(int signal)
{
	cout << "Signal " << to_string(signal) << " recieved" << endl;
}
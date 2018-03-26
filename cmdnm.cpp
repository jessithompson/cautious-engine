#include "cmdnm.h"
#include "utilities.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/* 
	Cmdnm constructor
*/
Cmdnm::Cmdnm() : pid("") {}

/* 
Cmdnm constructor

Input: string processID - process to evaluate
Output: none
*/
Cmdnm::Cmdnm(string processID): pid(processID) {}

string Cmdnm::getProcessId()
{
	return pid;
}

/* 
Function: GetCommandName

Ensures process id provided is valid, and 
then calls function to open cmdline file for
that process id. 

Input: none
Output: none
*/
void Cmdnm::GetCommandName()
{
	try 
	{
		if (!IsValidPid(pid))
		{
			cout << "Please enter a valid PID" << endl;
			return;
		} 
		else
		{
			DoFileWork(pid);
		}
	}
	catch (...)
	{}
}


/* 
Function: GetStartingProcess

Walks through supplied string from the last character 
toward the first until it encounters a '/' character,
building a string by copying each character as it goes. 

Returns result process by building string backwards
to the one just built. 

Input: string cmd - command string path to parse
Output: string resultProcess - name of starting process
*/
string Cmdnm::GetStartingProcess(string cmd)
{
	string startingCommand = "";

	// walk through string from behind until first slash
	for (int i = cmd.length() - 1; i > -1; i--)
	{
		if (cmd.at(i) == '/')
		{
			break;
		}
		else
		{
			startingCommand += cmd.at(i);
		}
	}	

	string resultProcess;
	for (int i = startingCommand.length()-1; i > -1; i--)
	{
		resultProcess.push_back(startingCommand.at(i));
	}
	return resultProcess;

}

/* 
Function: IsValidPid

Determines if supplied process id is valid by
attempting to open cmdline file of the pid in
proc directory.

Input: string pid - process id to check
Output: bool opened - success or fail on file open
*/
bool Cmdnm::IsValidPid(string pid)
{
	bool opened;
	string filename = "/proc/" + pid + "/cmdline";
	ifstream cmdnmFile(filename);\
	opened = cmdnmFile.is_open();
	if (opened)
	{
		cmdnmFile.close();
	}

	return opened;
}

/* 
Function: DoFileWork

Opens cmdline file for supplied process id and 
parses it to get the starting process, which it prints.
If the file is empty then it wasn't started by the 
command line

Input: string pid - process id to investigate
Output: none
*/
void Cmdnm::DoFileWork(string pid)
{
	Utilities utility;
	// open file
	string filename = "/proc/" + pid + "/cmdline";
	ifstream cmdnmFile(filename);
	if (cmdnmFile.is_open())
	{
		string currentLine;
		bool emptyFile = true;
		while (getline(cmdnmFile, currentLine))
		{
			// if the file wasn't empty, parse it and print process
			emptyFile = false;
			string withSpaces = utility.ReplaceNullTermToFirst(currentLine);
			cout << GetStartingProcess(withSpaces) << endl;
		}
		if (emptyFile)
		{
			cout << "This process was not started by the command line" << endl;
		}
	}
	
}

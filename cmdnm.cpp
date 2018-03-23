#include "cmdnm.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Cmdnm::Cmdnm() : pid("") {}

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
Function: ReplaceNullTermToFirst

Walks through supplied string, copying each character
into a different string until a null terminator is found, 
and then returns.

Input: string line - string to parse and copy
Output: string result - string from first character 
						of line to the first null terminator
*/
string Cmdnm::ReplaceNullTermToFirst(string line)
{
	// walk through string looking for spaces
	string result = "";
	int length = line.length();
	for (int i = 0; i < length; i++)
	{
		if (line.at(i) == '\0')
		{
			break;
		}
		else
		{
			// build result string one character at a time
			result += line.at(i);
		}
	}

	return result;
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
			string withSpaces = ReplaceNullTermToFirst(currentLine);
			cout << GetStartingProcess(withSpaces) << endl;
		}
		if (emptyFile)
		{
			cout << "This process was not started by the command line" << endl;
		}
	}
	
}

/* 
Function: ContainsNumericOnly

Function to determine if a string contains only numbers.

Input: string testString - string to check
Output: true if only contains numbers, false otherwise
*/	
bool Cmdnm::ContainsNumericOnly(string testString)
{
	return !(testString.find_first_not_of("0123456789") != string::npos);
}
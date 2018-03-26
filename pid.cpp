#include <ftw.h>
#include <iostream> 
#include <fstream>
#include <string>
#include <dirent.h>

#include "pid.h"
#include "string.h"
#include "cmdnm.h"
#include "utilities.h"

using namespace std;	

/* 
Process Identifier constructor

Input: string name - process name to investigate
Output: none
*/
ProcessIdentifier::ProcessIdentifier(string name) : processName(name) {}

/* 
Function: ProcessDirectory

Function to parse a directory by processing its individual objects

Note: modified from Bodislav Nicolae at 
https://stackoverflow.com/questions/9138866/c-list-all-directories-and-subdirectories-within-in-linux

Input: string directory - directory to parse
	   string process - process to look for
Output: none
*/
void ProcessIdentifier::ProcessDirectory(string directory, string process)
{
    DIR* dir = opendir(directory.c_str());

    //set the new path for the content of the directory
    string path = directory + "/";

    // couldn't open directory for some reason
    if(NULL == dir)
    {
        return;
    }

    dirent* object = readdir(dir);

    while(object != NULL)
    {
        ProcessObject(path, process, object);
        object = readdir(dir);
    }

    //we finished with the directory so remove it from the path
    path.resize(path.length() - 1 - directory.length());
    closedir(dir);
}

/* 
Function: ProcessObject

If a directory, call ProcessDirectory and if it's a file 
	named cmdline then send it to be printed.

Note: modified from Bodislav Nicolae at 
https://stackoverflow.com/questions/9138866/c-list-all-directories-and-subdirectories-within-in-linux

Input: string path - directory being parsed
	   string process - process to look for
	   struct dirent* object - object currently being parsed
Output: none
*/
void ProcessIdentifier::ProcessObject(string path, string process, struct dirent* object)
{
    // if it's a directory
    if(object->d_type == DT_DIR)
    {	
		char firstCharacter = (object->d_name[0]);
		string firstCharacterString(1, firstCharacter);
		string numbers = "0123456789";

		// only process directories that are process ids, 
		// so the file must be totally numeric
		Utilities utility;
		if (utility.ContainsNumericOnly(string(object->d_name)))
		{
			// open up this directory too
			ProcessDirectory(path + string(object->d_name), process);
		}

        return;
    }

    // if a file, open it and process if it's cmdline file
    if(object->d_type == DT_REG)
    {
    	string cmdlineFile = "cmdline";
    	string entityName(object->d_name);
    	if (cmdlineFile == entityName)
    	{
    		ExtractCmdline(path + entityName, process);
    	}
        return;
    }
}


/* 
Function: ExtractCmdline

Opens cmdline file for provided process, reads it and 
calls functions to print relevant information.

Input: string file - full path of file to open
	   string process - process to look for
Output: none
*/
void ProcessIdentifier::ExtractCmdline(string file, string process)
{
	ifstream cmdnmFile(file);
	if (cmdnmFile.is_open())
	{
		string currentLine;
		while (getline(cmdnmFile, currentLine))
		{
			Utilities utility;
			Cmdnm helper;
			string withSpaces = utility.ReplaceNullTermToFirst(currentLine);
			string startingProcess = helper.GetStartingProcess(withSpaces);
			if (startingProcess == process)
				FindProcess(file);
		}
	}
}

/* 
Function: Print Process

	Given a path from the proc directory, extract 
	the process name and print it to the screen.

Input: string path - full path of file
Output: none
*/
void ProcessIdentifier::FindProcess(string path)
{
	path.erase(0, 6); // get rid of /proc/

	// figure out where process name ends and build result from there
	size_t position = path.find_first_of("/"); 
	string result; 
	for (uint i = 0; i < position; i++)
	{
		result.push_back(path.at(i));
	}

	processName = result;
}
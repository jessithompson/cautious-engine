#include "utilities.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h> 

string Utilities::GetExePath()
{
	char buf[256];
   string cwd = "";
   if (getcwd(buf, sizeof(buf)) == NULL)
   {
      cwd = "error";
   }
   else
   {
      cwd = string(buf);
   }
   return cwd;
}

/* This method clearly taken from example code*/
void Utilities::Print_cpu_time(int pidToUse)
{
   struct rusage usage;
   getrusage (RUSAGE_SELF, &usage);
   cout << "\n~~~Process stats of PID " << pidToUse << "~~~" << endl;
   cout << "CPU Time: " << usage.ru_utime.tv_sec << "." << usage.ru_utime.tv_usec << 
            " sec user, " << usage.ru_stime.tv_sec << "." << usage.ru_stime.tv_usec << " system" << endl;
   cout << "Page faults: " << usage.ru_majflt << ", swaps: " << usage.ru_nswap << endl;
}

// this function shamelessly used from Pushkoff 
// @ https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
string Utilities::Trim(string trimString)
{
    string::const_iterator it = trimString.begin();
    while (it != trimString.end() && isspace(*it))
        it++;

    string::const_reverse_iterator rit = trimString.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}

// inspired by Vincenzo Pii @
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
vector<string> Utilities::ParseCommand_AndSplit(string command, string delimiter)
{
	size_t pos = 0;
	vector<string> tokens;
	while ((pos = command.find(delimiter)) != string::npos) {
	    tokens.push_back(Trim(command.substr(0, pos)));
	    command.erase(0, pos + delimiter.length());
	}
	tokens.push_back(Trim(command));
	return tokens;
}

/* 
Function: ContainsNumericOnly

Function to determine if a string contains only numbers.

Input: string testString - string to check
Output: true if only contains numbers, false otherwise
*/	
bool Utilities::ContainsNumericOnly(string testString)
{
	return !(testString.find_first_not_of("0123456789") != string::npos);
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
string Utilities::ReplaceNullTermToFirst(string line)
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
#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <vector>

using namespace std;

/*
	Helper class that contains some frequently used methods across
	the program.
 */
class Utilities 
{
	public:
		string GetExePath();
		void Print_cpu_time(int pidToUse);
		string Trim(string trimString);
		vector<string> ParseCommand_AndSplit(string command, string delimiter);
		bool ContainsNumericOnly(string testPid);
		string ReplaceNullTermToFirst(string line);

};

#endif
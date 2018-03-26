#ifndef DASH_H
#define DASH_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* 
	Class to run main part of Dash program.
*/
class Dash
{
	public:
		void runDash();
		void PrintUsageInfo();
		vector<string> SplitUserCommand(string entireCommand);
};

#endif
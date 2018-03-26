#ifndef DASH_H
#define DASH_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
This function used from example @ https://www.mcs.sdsmt.edu/ckarlsso/csc456/spring18/src/basic_shell.c 
*/
class Dash
{
	public:
		void runDash();
		void PrintUsageInfo();
		vector<string> SplitUserCommand(string entireCommand);
};

#endif
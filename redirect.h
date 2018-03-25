#ifndef REDIRECT_H
#define REDIRECT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
This function used from example @ https://www.mcs.sdsmt.edu/ckarlsso/csc456/spring18/src/basic_shell.c 
*/
class Redirect
{
	private:
		string command;
		string direction;
		string filename;
		string partial_command;
		vector<string> parsedCommand;
		bool AssignDirection();
		void RunCommand();
		vector<string> ParseCommand_Output();
		vector<string> ParseCommand_Input();
		void RunCommand_Output();
		void RunCommand_Input();
		void Print_cpu_time(int pidToUse);

	public:
		Redirect(string command);
		void DoRedirect();
};

#endif
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
		void RunCommand_Output();
		void RunCommand_Input();

	public:
		Redirect(string command);
		void DoRedirect();
};

#endif
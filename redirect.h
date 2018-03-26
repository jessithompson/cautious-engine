#ifndef REDIRECT_H
#define REDIRECT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* 
	Class to run redirect (< or >) commands.
*/
class Redirect
{
	private:
		string command;
		string direction;
		string filename;
		string partial_command;
		vector<string> parsedCommand;
		bool debug;
		bool AssignDirection();
		void RunCommand();
		void RunCommand_Output();
		void RunCommand_Input();

	public:
		Redirect(string command);
		void DoRedirect();
};

#endif
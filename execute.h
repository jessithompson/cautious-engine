#ifndef EXECUTE_H
#define EXECUTE_H 

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
	A class to run various commands. 
*/
class ExecuteCommand
{
	private:
		string command;
		char* args[];
	public:
		ExecuteCommand(string command);
		int Execute();
		void ChangeDirectory(string directory);
		void Signal(string procId, string signalToSend);
};

#endif
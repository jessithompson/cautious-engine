#ifndef EXECUTE_H
#define EXECUTE_H 

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
This function used from example @ https://www.mcs.sdsmt.edu/ckarlsso/csc456/spring18/src/basic_shell.c 
*/
class ExecuteCommand
{
	private:
		string command;
		char* args[];
		void Print_cpu_time(int pidToUse);
		string GetExePath();
	public:
		ExecuteCommand(string command);
		int Execute();
		bool ContainsNumericOnly(string testPid);
		void ChangeDirectoryAndRunNewProc(string directory);
		void Signal(string procId, string signalToSend);

};

#endif
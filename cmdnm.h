#include <iostream>
#include <string>

using namespace std;

/* 
	Function to return command name of a process.
*/
class Cmdnm
{
	private:
		string pid;
	public:
		Cmdnm();
		Cmdnm(string processID);
		string getProcessId();
		void GetCommandName();
		bool IsValidPid(string pid);
		string ReplaceNullTermToFirst(string line);
		string GetStartingProcess(string cmd);
		void DoFileWork(string pid);	
};
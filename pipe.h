#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
This function used from example @ https://www.mcs.sdsmt.edu/ckarlsso/csc456/spring18/src/basic_shell.c 
*/
class Pipe
{
	private:
		string command;
		vector<string> tokenizedCommand;
		void RunCommands();
		
	public:
		Pipe(string command);
		void DoPipe();

};

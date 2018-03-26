#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
	Class to handle piping commands
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

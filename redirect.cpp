#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h> 
#include <vector>
#include "dash.h"
#include "redirect.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

Redirect::Redirect(string _command) : command(_command) {}

void Redirect::DoRedirect()
{
	if (AssignDirection())
	{
		if (direction == ">")
		{
			cout << "Output chosen " << endl;
			parsedCommand = ParseCommand_Output();
			filename = parsedCommand[1];
			partial_command = parsedCommand[0];
			cout << "Filename: " << filename << "  Command: " << partial_command << endl;
			RunCommand_Output();
		}
		else
		{
			parsedCommand = ParseCommand_Input();
			filename = parsedCommand[0];
			partial_command = parsedCommand[1];
		}
	}
	else
	{
		cout << "There was a problem doing the redirect" << endl;
		return;
	}

}

/* 
tcs @ http://www.cplusplus.com/forum/general/94879/

*/
void Redirect::RunCommand_Output()
{
	cout << "Running output command" << endl;
	int normalOutput = dup(1);
	int fd = open(filename.c_str(),  O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	dup2(fd, 1);
	close(fd);

	int childpid, status, waitpid;
	childpid = fork(); 
	if (childpid == 0) 
	{ 
		execl("/bin/sh", "/bin/sh", "-c", partial_command.c_str(), NULL);
		exit(5); 
	} 

	// undo output redirect
	fflush(stdout);
	dup2(normalOutput, 1);
	close(normalOutput);

	waitpid = wait(&status); 
	cout << "* Process Id of child process: " << childpid << endl;
	printf("Shell process %d exited with status %d\n", waitpid, (status >> 8)); 
	Print_cpu_time(waitpid);
	return;
}
/* This method clearly taken from example code*/
void Redirect::Print_cpu_time(int pidToUse)
{
   struct rusage usage;
   getrusage (RUSAGE_SELF, &usage);
   cout << "\n~~~Process stats of PID " << pidToUse << "~~~" << endl;
   cout << "CPU Time: " << usage.ru_utime.tv_sec << "." << usage.ru_utime.tv_usec << 
            " sec user, " << usage.ru_stime.tv_sec << "." << usage.ru_stime.tv_usec << " system" << endl;
   cout << "Page faults: " << usage.ru_majflt << ", swaps: " << usage.ru_nswap << endl;

}
bool Redirect::AssignDirection()
{
	if (command.find(">") != string::npos)
	{
		direction = ">";
		return true;
	}
	else if (command.find("<") != string::npos)
	{
		direction = "<";
		return true;
	}
	else
		return false;
}

// inspired by Vincenzo Pii @
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
vector<string> Redirect::ParseCommand_Output()
{
	size_t pos = 0;
	vector<string> tokens;
	string split = ">";
	while ((pos = command.find(split)) != string::npos) {
	    tokens.push_back(command.substr(0, pos));
	    command.erase(0, pos + split.length());
	}
	tokens.push_back(command);
	return tokens;
	
}

// inspired by Vincenzo Pii @
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
vector<string> Redirect::ParseCommand_Input()
{
	size_t pos = 0;
	vector<string> tokens;
	string split = "<";
	while ((pos = command.find(split)) != string::npos) {
	    tokens.push_back(command.substr(0, pos));
	    command.erase(0, pos + split.length());
	}
	tokens.push_back(command);
	return tokens;
	
}
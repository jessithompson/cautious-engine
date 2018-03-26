#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h> 
#include <vector>
#include "dash.h"
#include "redirect.h"
#include "utilities.h"
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
		Utilities utility;
		if (direction == ">")
		{
			parsedCommand = utility.ParseCommand_AndSplit(command, ">");
			filename = parsedCommand[1];
			partial_command = parsedCommand[0];
			RunCommand_Output();
		}
		else if (direction == "<")
		{
			parsedCommand = utility.ParseCommand_AndSplit(command, "<");
			filename = parsedCommand[1];
			partial_command = parsedCommand[0];
			RunCommand_Input();
		}
		else
		{
			cout << "There was a problem doing the redirect" << endl;
			return;
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
	int normalOutput = dup(1);
	int fileDescriptor = open(filename.c_str(),  O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (fileDescriptor < 0)
	{
		cout << "There was a problem opening " << filename << " for output" << endl;
		return;
	}
	dup2(fileDescriptor, 1);
	close(fileDescriptor);

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
	Utilities utility;
	utility.Print_cpu_time(waitpid);
	return;
}

/* 
tcs @ http://www.cplusplus.com/forum/general/94879/

*/
void Redirect::RunCommand_Input()
{
	filename = "myoutput"; 
	int normalInput = dup(0);
	int input = open(filename.c_str(),  O_RDONLY);
	dup2(input, 0);
	close(input);
	Utilities utility;

	int childpid, status, waitpid;
	childpid = fork(); 
	if (childpid == 0) 
	{ 
		cout << "* Process Id of child process: " << getpid() << endl;
    	cout << "\nOutput: " << endl;
		execl("/bin/sh", "/bin/sh", "-c", partial_command.c_str(), NULL);
		exit(5); 
	} 

	// undo output redirect
	fflush(stdout);
	dup2(normalInput, 0);
	close(normalInput);

	waitpid = wait(&status); 
	printf("Shell process %d exited with status %d\n", waitpid, (status >> 8)); 
	utility.Print_cpu_time(waitpid);
	return;
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
/*vector<string> Redirect::ParseCommand_Output()
{
	size_t pos = 0;
	vector<string> tokens;
	string split = ">";
	while ((pos = command.find(split)) != string::npos) {
	    tokens.push_back(Trim(command.substr(0, pos)));
	    command.erase(0, pos + split.length());
	}
	tokens.push_back(Trim(command));
	return tokens;
	
}*/

// inspired by Vincenzo Pii @
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
/*vector<string> Redirect::ParseCommand_Input()
{
	size_t pos = 0;
	vector<string> tokens;
	string split = "<";
	while ((pos = command.find(split)) != string::npos) {
	    tokens.push_back(Trim(command.substr(0, pos)));
	    command.erase(0, pos + split.length());
	}
	tokens.push_back(Trim(command));

	return tokens;
}*/
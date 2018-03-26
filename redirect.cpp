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

/* 
Function: Redirect constructor

Sets class member command as part of instructor. 

Input: string _command - redirect command as input by user
Output: none
*/
Redirect::Redirect(string _command) : command(_command) { debug = false;}

/* 
Function: DoRedirect

Completes preprocessessing for redirection command 
and begins execution of the command. 

Input: none
Output: none
*/
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
Function: RunCommand_Output

Completes output redirect command. 

Please note that some of this code was helped by 
tcs @ http://www.cplusplus.com/forum/general/94879/ in 
addition to class example code at 
https://www.mcs.sdsmt.edu/ckarlsso/csc456/spring18/src/redir.c

Input: none
Output: none
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

	if (debug)
	{
		waitpid = wait(&status); 
		cout << "* Process Id of child process: " << childpid << endl;
		printf("Shell process %d exited with status %d\n", waitpid, (status >> 8)); 
		Utilities utility;
		utility.Print_cpu_time(waitpid);
	}
	else
		wait(&status); 

	return;
}

/* 
Function: RunCommand_Input

Completes input redirect command. 

Please note that some of this code was helped by 
tcs @ http://www.cplusplus.com/forum/general/94879/ in 
addition to class example code at 
https://www.mcs.sdsmt.edu/ckarlsso/csc456/spring18/src/redir.c

Input: none
Output: none
*/
void Redirect::RunCommand_Input()
{
	int normalInput = dup(0);
	int input = open(filename.c_str(),  O_RDONLY);
	dup2(input, 0);
	close(input);

	int childpid, status, waitpid;
	childpid = fork(); 
	if (childpid == 0) 
	{ 
		if (debug)
		{
			cout << "* Process Id of child process: " << getpid() << endl;
    		cout << "\nOutput: " << endl;
		}

		execl("/bin/sh", "/bin/sh", "-c", partial_command.c_str(), NULL);
		exit(5); 
	} 

	// undo output redirect
	fflush(stdout);
	dup2(normalInput, 0);
	close(normalInput);

	if (debug)
	{
		waitpid = wait(&status); 
		printf("Shell process %d exited with status %d\n", waitpid, (status >> 8)); 
		Utilities utility;
		utility.Print_cpu_time(waitpid);
	}
	else
		wait(&status); 

	return;
}

/* 
Function: AssignDirection

Designates whether the redirect is done by input
or output.

Input: none
Output: none
*/
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
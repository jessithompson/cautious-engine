#include <iostream>
#include <vector>
#include <unistd.h> 
#include <sys/wait.h>
#include "pipe.h"
#include "execute.h"
#include "utilities.h"

using namespace std;

Pipe::Pipe(string _command) : command(_command) {}

void Pipe::DoPipe()
{
	Utilities utility;
	tokenizedCommand = utility.ParseCommand_AndSplit(command, "|");
	if (tokenizedCommand.size() < 3 && tokenizedCommand[0] != "" && tokenizedCommand[1] != "")
	{
		RunCommands();
	}
	else if (tokenizedCommand.size() >= 3)
	{
		cout << "Only implemented single pipe command. The rest of this code is executed via built-in shell." << endl;
		ExecuteCommand runCommand(command);
		runCommand.Execute();
	}
}

// inspired by https://www.mcs.sdsmt.edu/ckarlsso/csc456/spring18/src/pipe.c
void Pipe::RunCommands()
{
	int pid1, pid2, waitpid1, waitpid2,  status;
	int pipefd[2];
	pid1 = fork();
	string message1, message2;
	string cputime1, cputime2;
	Utilities utility;

	if (pid1 == 0)
	{
		pipe(pipefd);
		pid2 = fork();
		if (pid2 == 0)
		{
			close(1);
			dup(pipefd[1]);
			close(pipefd[0]); 
			close(pipefd[1]);

			// use ExecuteCommand code to run 
			cout << "* Process Id of grandchild process: " << getpid() << endl;
			cout << "\nOutput: " << endl;
			execl("/bin/sh", "/bin/sh", "-c", tokenizedCommand[0].c_str(), NULL);
			perror("Exec failed: "); 
			exit(1); 
		}
		waitpid1 = wait(&status);
		message1 = "Grandchild process " + to_string(waitpid1) + " exited with status " + to_string(status>>8); 
		utility.Print_cpu_time(waitpid1);

		close(0);              // close standard input
		dup(pipefd[0]);       // redirect the input
		close(pipefd[0]);     // close unnecessary file descriptor
		close(pipefd[1]);     // close unnecessary file descriptor

		cout << message1 << endl;
		utility.Print_cpu_time(waitpid1);

		// use ExecuteCommand code to run 
		cout << "* Process Id of child process: " << getpid() << endl;
		cout << "\nOutput: " << endl;
		execl("/bin/sh", "/bin/sh", "-c", tokenizedCommand[1].c_str(), NULL);
		perror("Exec failed: "); 
		exit(5);
	}	
	else
	{
		waitpid2 = wait(&status);
		cout << "Child process " << to_string(waitpid2) << " exited with status " << to_string(status >> 8) << endl;
		utility.Print_cpu_time(waitpid2);
	}
}
#include "execute.h"
#include <vector>
#include <sstream>
#include <string.h> 
#include <unistd.h> 
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include "dash.h"
#include "utilities.h"

using namespace std;

/* 
Function: ExecuteCommand constructor

Input: string _command - command as input by user
Output: none
*/
ExecuteCommand::ExecuteCommand(string _command) : command(_command) {}

/* 
Function: Execute

Method to run shell commands by sending a command string to
the directory of symbolic links for shell executables.

This function used from example @
https://www.mcs.sdsmt.edu/ckarlsso/csc456/spring18/src/basic_shell.c 

Input: none
Output: none
*/
int ExecuteCommand::Execute()
{
   if (command=="")
   {
      return -1; // not a valid command
   }

   int childpid, status, waitpid;
   Utilities utility;
   childpid = fork(); 
   if (childpid == 0) 
   { 
      cout << "* Process Id of child process: " << getpid() << endl;
      cout << "\nOutput: " << endl;
      execl("/bin/sh", "/bin/sh", "-c", command.c_str(), NULL);

      perror("Exec failed: "); 
      exit(5); 
   } 
   waitpid = wait(&status); 
   printf("Shell process %d exited with status %d\n", waitpid, (status >> 8)); 
   utility.Print_cpu_time(waitpid);

   return 0;
}

/* 
Function: ChangeDirectory

Changes current working directory to specified directory
from user. 

Please note this method used to be different, and can be found
at the bottom of this fi.

Input: string directory - directory to change to.
Output: none
*/
void ExecuteCommand::ChangeDirectory(string directory)
{
   chdir(directory.c_str());
}

/* 
Function: Signal

Sends a signal to a given proces.

Input: string signalToSend - signal to send via kill command 
      string procId - process to send signal to
Output: none
*/
void ExecuteCommand::Signal(string signalToSend, string procId)
{
   int childpid, status, waitpid;
   Utilities utility;
   childpid = fork(); 
   if (childpid == 0) 
   { 
      cout << "Sending signal " << signalToSend << " to process " << procId << endl;
      cout << "* Process Id of child process: " << getpid() << endl;
      if (kill(stoi(procId), stoi(signalToSend)) != 0)
      {
         cout << "There was a problem sending this signal" << endl;
      }
      exit(5); 
   } 
   waitpid = wait(&status); 
   printf("Shell process %d exited with status %d\n", waitpid, (status >> 8)); 
   utility.Print_cpu_time(waitpid);
}

// Note this method as other change directory function
//void ExecuteCommand::ChangeDirectory(string directory)
//{
      //Utilities utility;
      //int childpid, status, waitpid;
      //childpid = fork(); 
      //if (childpid == 0) 
     // { 
       //  cout << "* Process Id of child process: " << getpid() << endl;
         //chdir(directory.c_str());      
         //Dash newDash(directory);
         //newDash.runDash();

        // exit(5); 
      //} 
      //waitpid = wait(&status); 
      //printf("Shell process %d exited with status %d\n", waitpid, (status >> 8)); 
     //utility.Print_cpu_time(waitpid);
//}
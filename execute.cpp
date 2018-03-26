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

ExecuteCommand::ExecuteCommand(string _command) : command(_command) {}
/*
This function used from example @ https://www.mcs.sdsmt.edu/ckarlsso/csc456/spring18/src/basic_shell.c 
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
      // this code snipped here from Andy Ross @ Stackoverflow
      // Link: https://stackoverflow.com/questions/1511797/convert-string-to-argv-in-c
      // use shell symbolic link to execute c-string version of this command
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

void ExecuteCommand::ChangeDirectory(string directory)
{
   chdir(directory.c_str());
}

void ExecuteCommand::Signal(string signalToSend, string procId)
{
   int childpid, status, waitpid;
   Utilities utility;
   childpid = fork(); 
   if (childpid == 0) 
   { 
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

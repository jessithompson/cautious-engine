#include "execute.h"
#include <vector>
#include <sstream>
#include <string.h> 
#include <unistd.h> 
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

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
   childpid = fork(); 
   if (childpid == 0) 
   { 
      // this code snipped here from Andy Ross @ Stackoverflow
      // Link: https://stackoverflow.com/questions/1511797/convert-string-to-argv-in-c
      // use shell symbolic link to execute c-string version of this command
      execl("/bin/sh", "/bin/sh", "-c", command.c_str(), NULL);

      //execvp(args[0], args); 
      perror("Exec failed: "); 
      exit(5); 
   } 
   waitpid = wait(&status); 
   printf("Shell process %d exited with status %d\n", waitpid, (status >> 8)); 
   Print_cpu_time();
   return 0;
}


/* 
Function: SplitUserCommand

Tokenize user input on spaces and return as a vector of strings.

Note: Code in this function modified from :
   http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html

Input: string entireCommand - string to tokenize  
Output: vector<string> - each string between spaces
*/
vector<string> ExecuteCommand::SplitUserCommand(string entireCommand)
{
   vector<string> tokenized;
   string buffer;
   stringstream ss(entireCommand);

   while (ss >> buffer)
   {
      tokenized.push_back(buffer);
   }

   return tokenized;
}

/* This method clearly taken from example code*/
void ExecuteCommand::Print_cpu_time()
{
   struct rusage usage;
   getrusage (RUSAGE_SELF, &usage);
   cout << "CPU Time: " << usage.ru_utime.tv_sec << "." << usage.ru_utime.tv_usec << 
            " sec user, " << usage.ru_stime.tv_sec << "." << usage.ru_stime.tv_usec << " system" << endl;

}
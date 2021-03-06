#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <limits.h>
#include <unistd.h> 
#include "systat.h"
#include "pid.h"
#include "pipe.h"
#include "cmdnm.h"
#include "execute.h"
#include "dash.h"
#include "redirect.h"
#include "utilities.h"

/* 
Function: runDash

Runs main part of program to receive commands.

Input: none
Output: none
*/
void Dash::runDash()
{
   cout<<"dash>";
   string invalidCommand = "Invalid command!";
   string command = "";
   Utilities utility;
   while (getline(cin, command) && command != "exit" && command != "e")
   {  
      if (command == "")
      {
         cout << "dash>";
         continue;
      }
      // split command string on spaces and handle any problems with that
      vector<string> splitCommand = SplitUserCommand(command);
      if (splitCommand.size() == 2 && splitCommand[0] == "cmdnm")
      {
         Cmdnm _cmdnm(splitCommand[1]);
         if (utility.ContainsNumericOnly(splitCommand[1]))
         {
            _cmdnm.GetCommandName();
         }
         else
         {
            cout << invalidCommand << "   - Please enter a valid pid\ndash>";
            continue;
         }
      }
      else if (splitCommand.size() == 1 && splitCommand[0] == "cmdnm")  
      {
         cout << invalidCommand << "   - Please enter a valid pid\ndash>";
         continue;
      }
      else if (splitCommand.size() == 2 && splitCommand[0] == "pid")
      {
         ProcessIdentifier procid("");
         procid.ProcessDirectory("/proc", splitCommand[1]);
         if (procid.processName == "")
         {
            cout << "No process found with name of " << splitCommand[1] << endl; 
         }
         else
            cout << procid.processName << endl;
         cout<<"dash>";
         continue;
      }
      else if (splitCommand.size() == 1 && splitCommand[0] == "pid")
      {
         cout << invalidCommand << "   - Please enter a valid pid\ndash>";
         continue;
      }
      else if (splitCommand.size() == 1 && splitCommand[0] == "systat")
      {
         Systat systemInfo;
         systemInfo.GetSystemInformation();
         cout<<"dash>";
         continue;
      }
      else if (splitCommand[0] == "cd")
      {
         ExecuteCommand runCommand(command);
         runCommand.ChangeDirectory(splitCommand[1]);
         cout<<"dash>";
         continue;

         // Old code (see documentation for explanation):
         /* runCommand.ChangeDirectoryAndRunNewProc(splitCommand[1]);
            return; // by the time line 74 returns it will have exited Dash*/
      }
      else if (splitCommand[0] == "signal" && splitCommand.size() == 3)
      {
         ExecuteCommand runCommand(command);
         runCommand.Signal(splitCommand[1], splitCommand[2]);
      }      
      else if (splitCommand[0] == "signal" && splitCommand.size() != 3)
      {
         cout << invalidCommand << "   - Please enter a valid signal number and pid\ndash>";
         continue;
      }
      else if (command.find("|") != string::npos)
      {
         Pipe runPipe(command);
         runPipe.DoPipe();
         cout<<"dash>";
         continue;
      }
      else if (command.find(">") != string::npos || command.find("<") != string::npos)
      {
         Redirect runRedirect(command);
         runRedirect.DoRedirect();
         cout<<"dash>";
         continue;
      }
      else
      {
         ExecuteCommand runCommand(command);
         runCommand.Execute();
         cout<<"dash>";
         continue;
      }
      
      cout<<"dash>";
   }
}

/* 
Function: PrintUsageInfo

Prints helpful usage info to screen. 

Input: none 
Output: none
*/
void Dash::PrintUsageInfo()
{
   cout << "-------- DASH --------" << endl; 
   cout << "\nOnce program starts, use these commands:" << endl;
   cout << "* cmdnm <pid>     - Returns command string that started the given process id." << endl;
   cout << "* pid <command>   - Returns list of processes started by this command" << endl;
   cout << "* systat          - Prints CPU info, uptime, and memory stats" << endl;
   cout << "* exit            - Quits program\n" << endl;
   cout << "To run program enter './dash '\n" << endl;
}

/* 
Function: SplitUserCommand

Tokenize user input on spaces and return as a vector of strings.

Note: Code in this function modified from :
   http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html

Input: string entireCommand - string to tokenize  
Output: vector<string> - each string between spaces
*/
vector<string> Dash::SplitUserCommand(string entireCommand)
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


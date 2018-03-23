#include <iostream>
#include <string>

using namespace std;

class ProcessIdentifier 
{
	public: 
		string processName;
		ProcessIdentifier(string name);
		void ProcessDirectory(string directory, string process);
		void ProcessObject(string path, string process, struct dirent* entity);
		void ExtractCmdline(string file, string process);
		void FindProcess(string path);
};
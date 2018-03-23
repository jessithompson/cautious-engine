#include <iostream>
#include <string>

using namespace std;

class ProcessIdentifier 
{
	public: 
		void ProcessDirectory(string directory, string process);
		void ProcessObject(string path, string process, struct dirent* entity);
		void ExtractCmdline(string file, string process);
		void PrintProcess(string path);
};
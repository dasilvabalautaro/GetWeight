#ifndef File_h
#define File_h

#include <iostream>
#include <fstream> 
#include <direct.h>
#include <sstream> 
#include <time.h>

using namespace std;

class File
{
public:
	File();
	~File();
	void SetNameDirectory(string name);
	void SetNameFile(string name);
	void WriteFile(string content);
	void WriteFile(string content, string path);
	bool DeleteFile();
	bool DeleteFile(string filePath);
	void CreateDirectory();
	void WriteToFileLog(string Message);
	string GetNameDirectory();
	string ReadFileText();
	string ReadFileText(string path);
	bool is_file_exist()
	{
		string pathFile = nameDirectory + "/" + nameFile;
		std::ifstream infile(pathFile);
		return infile.good();
	}

private:
	string nameDirectory;
	string nameFile;

};


#endif // !File_h


#include "File.h"

File::File()
{
}

File::~File()
{
}

void File::SetNameDirectory(string name) {
	nameDirectory = name;
}

void File::SetNameFile(string name) {
	nameFile = name;
}

void File::WriteFile(string content) {
	CreateDirectory();
	string path = nameDirectory + "/" + nameFile;
	ofstream file_obj;
	file_obj.open(path, ios::app);
	file_obj.write(content.c_str(), sizeof(char) * content.size());
	file_obj.close();

}

void File::WriteFile(string content, string path) {
	ofstream file_obj;
	file_obj.open(path, ios::app);
	file_obj.write(content.c_str(), sizeof(char) * content.size());
	file_obj.close();
}

void File::WriteToFileLog(string Message) {
	time_t _tm = time(NULL);

	struct tm* curtime = localtime(&_tm);
	string year = to_string(1900 + curtime->tm_year);
	string month = to_string(1 + curtime->tm_mon);
	string day = to_string(curtime->tm_mday);
	string date = day + "_" + month + "_" + year;
	string hour = to_string(1 + curtime->tm_hour);

	//string strTime = asctime(curtime);	

	string directoryLog = "Logs";
	string path = directoryLog + "/ClientLog_" + date + ".txt";
	int result = _mkdir((char*)&directoryLog);
	string out = hour + ": " + Message + "\n";
	std::ofstream log(path, std::ios_base::app | std::ios_base::out);
	log << out;
	log.close();

}

bool File::DeleteFile() {
	string path = nameDirectory + "/" + nameFile;
	if (remove(path.c_str()) != 0) {
		return false;
	}
	else {
		return true;
	}

}

bool File::DeleteFile(string filePath) {

	if (remove(filePath.c_str()) != 0) {
		return false;
	}
	else {
		return true;
	}

}

void File::CreateDirectory() {
	int result = _mkdir((char*)&nameDirectory);
}

string File::GetNameDirectory() {
	return nameDirectory;
}

string File::ReadFileText() {
	string result = "";
	string path = nameDirectory + "/" + nameFile;
	ifstream streamFile;
	streamFile.open(path);
	if (streamFile.good()) {
		stringstream streamContent;
		streamContent << streamFile.rdbuf();
		result = streamContent.str();
		streamFile.close();
	}
	return result;

}

string File::ReadFileText(string path) {
	string result = "";	
	ifstream streamFile;
	streamFile.open(path);
	if (streamFile.good()) {
		stringstream streamContent;
		streamContent << streamFile.rdbuf();
		result = streamContent.str();
		streamFile.close();
	}
	return result;

}
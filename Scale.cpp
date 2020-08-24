#include "Scale.h"

Scale::Scale()
{
	SetNameDirectory(DIRECTORYWEIGHT);
	SetNameFileData(NAMEFILEWEIGHT);
	jsonConfig->SetNameDirectory(DIRECTORYCONFIGURATION);
	jsonConfig->SetNameFileConfiguration(NAMEFILECONFIG);
}

Scale::~Scale()
{
}

void Scale::ParseJSONToObject() {
	string errors;
	jsonStructure->jsonBody.clear();
	jsonStructure->stringJSON = jsonStructure->manageFile->ReadFileText();
	//cout << "cadena :" << jsonStructure->stringJSON << endl;
	if (!jsonStructure->stringJSON.empty())
	{
		bool parsingSuccessful = jsonStructure->reader->parse(jsonStructure->stringJSON.c_str(),
			jsonStructure->stringJSON.c_str() + jsonStructure->stringJSON.size(),
			&jsonStructure->jsonBody, &errors);
		if (parsingSuccessful)
		{
			SetValueJSONToConfiguration();
		}
		
	}
	else
	{
		string message = "Not found file " + NAMEFILEWEIGHT;
		jsonStructure->manageFile->WriteToFileLog(message);
	}
	
}

void Scale::SetValueJSONToConfiguration() {
	const Json::Value params = jsonStructure->jsonBody[PARAMS];
	for (Json::Value::const_iterator it = params.begin();
		it != params.end(); ++it) {

		if (it.key().asString() == SCALEONE) {
			scaleOne = it->asInt();
		}
		else if (it.key().asString() == SCALETWO) {
			scaleTwo = it->asInt();
		}
		else if (it.key().asString() == SCALETHREE) {
			scaleThree = it->asInt();
		}
		else if (it.key().asString() == SCALEFOUR) {
			scaleFour = it->asInt();
		}
		else if (it.key().asString() == SCALETOTAL) {
			total = it->asInt();
		}
	}

}

void Scale::WriteFileOnlyTotal() {
	string result = to_string(total);
	file->WriteFile(result, fileWeights);
}

void Scale::WriteFileWeight(Vehicles vehicle) {
	string result = "";

	if ((float)((float)scaleOne/1000.0f) <= (float)vehicle.GetScaleOne())
	{
		result += to_string(scaleOne) + "|1|";
	}
	else
	{
		result += to_string(scaleOne) + "|0|";
	}

	if ((float)((float)scaleTwo/1000.0f) <= (float)vehicle.GetScaleTwo())
	{
		result += to_string(scaleTwo) + "|1|";
	}
	else
	{
		result += to_string(scaleTwo) + "|0|";
	}
	if ((float)((float)scaleThree/1000.0f) <= (float)vehicle.GetScaleThree())
	{
		result += to_string(scaleThree) + "|1|";
	}
	else
	{
		result += to_string(scaleThree) + "|0|";
	}
	if ((float)((float)scaleFour/1000.0f) <= (float)vehicle.GetScaleFour())
	{
		result += to_string(scaleFour) + "|1|";
	}
	else
	{
		result += to_string(scaleFour) + "|0|";
	}

	//cout << "scalefour " << (scaleFour / 1000) << " table " << vehicle.GetScaleFour() << endl;

	result += to_string(total);

	file->WriteFile(result, fileWeights);
}

void Scale::DeleteFileWeight() {
	file->DeleteFile(fileWeights);
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

string Scale::GetCodeVehicle() {
	string content = file->ReadFileText(fileSAP);

	std::vector<std::string> values = split(content, ';');
	/*for (int i = 0; i < values.size(); i++)
	{
		cout << values[i] << endl;
	}*/
	if (values.size() > 9)
	{
		return values[9];
	}

	string message = "Not found code vehicle.";
	file->WriteToFileLog(message);
	return "";
}

void Scale::ParseMapConfigToJSON() {
	jsonConfig->jsonBody.clear();
	jsonConfig->jsonParams.clear();
	std::map<std::string, std::string> params;

	params.insert(std::pair<std::string, std::string>(NAMEFILESAP, fileSAP));
	params.insert(std::pair<std::string, std::string>(NAMEFILEWEIGHTS, fileWeights));
		
	std::map<std::string, std::string>::const_iterator it = params.begin(),
		end = params.end();

	for (; it != end; ++it) {
		jsonConfig->jsonParams[it->first] = it->second;

	}

	jsonConfig->jsonBody[CONFIGURATION] = CLIENT_CONFIGURATION;
	jsonConfig->jsonBody[PARAMS] = jsonConfig->jsonParams;

	jsonConfig->SaveConfiguration();

}

void Scale::ParseJSONToObjectClient() {
	string errors;
	jsonConfig->jsonBody.clear();
	jsonConfig->stringJSON = jsonConfig->manageFile->ReadFileText();
	//cout << "cadena :" << jsonStructure->stringJSON << endl;
	if (!jsonConfig->stringJSON.empty())
	{
		bool parsingSuccessful = jsonConfig->reader->parse(jsonConfig->stringJSON.c_str(),
			jsonConfig->stringJSON.c_str() + jsonConfig->stringJSON.size(),
			&jsonConfig->jsonBody, &errors);
		if (parsingSuccessful)
		{
			SetValueJSONToConfigClient();
		}

	}
	else
	{
		string message = "Not found file " + NAMEFILECONFIG;
		jsonConfig->manageFile->WriteToFileLog(message);
	}
}

void Scale::SetValueJSONToConfigClient() {
	const Json::Value params = jsonConfig->jsonBody[PARAMS];
	for (Json::Value::const_iterator it = params.begin();
		it != params.end(); ++it) {

		if (it.key().asString() == NAMEFILESAP) {
			fileSAP = it->asString();
		}
		else if (it.key().asString() == NAMEFILEWEIGHTS) {
			fileWeights = it->asString();
		}		
	}
}

void Scale::LoadConfiguration() {
	jsonConfig->manageFile->CreateDirectory();
	if (!jsonConfig->manageFile->is_file_exist()) {
		ParseMapConfigToJSON();
	}	

	ParseJSONToObjectClient();
}
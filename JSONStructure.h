#ifndef JSONStructure_h
#define JSONStructure_h

#include <json/json.h>
#include "File.h"
#include "Vehicles.h"

class JSONStructure
{
public:
	JSONStructure();
	~JSONStructure();
	void SetStringJSON(string json) {
		stringJSON = json;
	}

	string GetStringJSON() {
		return stringJSON;
	}

	void SetNameFileConfiguration(string name) {
		manageFile->SetNameFile(name);
	}
	void SetNameDirectory(string name) {
		manageFile->SetNameDirectory(name);
	}

	string GetNameDirectory() {
		return manageFile->GetNameDirectory();
	}

	Json::Value jsonParams;
	Json::Value jsonBody;
	Json::Value jsonArray;
	//Json::Reader reader;

	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();

	File* manageFile = new File();

	string stringJSON;

	std::vector <Vehicles> listConfig;

	void WriteJSONToString();
	void SaveConfiguration();

	void ConfigVehicles();
	void ParseJSONToListVehicle();
	int SearchIndexCode(std::string valueCode);

private:
	const string CONFIGURATION = "configuration";
	const string TRUCK_CONFIGURATION = "truck_configuration";
	const string LIST = "list";
	const string DIRECTORYVEHICLES = "vehicles";
	const string VEHICLESFILE = "vehicles_config.txt";
	File* manageFileVehicles = new File();
	void SaveConfigurationVehicles();
	void SetValueJSONToList();
};


#endif // !JSONStructure_h


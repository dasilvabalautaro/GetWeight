#ifndef Scale_h
#define Scale_h
#include "JSONStructure.h"

class Scale
{
public:
	Scale();
	~Scale();
	void ParseJSONToObject();
	void LoadConfiguration();
	void SetNameFileData(string name) {
		jsonStructure->SetNameFileConfiguration(name);
	}
	void SetNameDirectory(string name) {
		jsonStructure->SetNameDirectory(name);
	}

	int GetScaleOne() {
		return scaleOne;
	}

	int GetScaleTwo() {
		return scaleTwo;
	}

	int GetScaleThree() {
		return scaleThree;
	}

	int GetScaleFour() {
		return scaleFour;
	}

	int GetScaleTotal() {
		return total;
	}

	void WriteFileWeight(Vehicles vehicle);
	void WriteFileOnlyTotal();
	void DeleteFileWeight();
	string GetCodeVehicle();

private:
	int scaleOne = 0;
	int scaleTwo = 0;
	int scaleThree = 0;
	int scaleFour = 0;
	int total = 0;
	string fileSAP = "DAT_VEHICULO.txt";
	string fileWeights = "pesoproduccion.txt";
	JSONStructure* jsonStructure = new JSONStructure();
	JSONStructure* jsonConfig = new JSONStructure();
	File* file = new File();
	const string PARAMS = "Params";
	const string SCALEONE = "scale_one";
	const string SCALETWO = "scale_two";
	const string SCALETHREE = "scale_three";
	const string SCALEFOUR = "scale_four";
	const string SCALETOTAL = "total";
	const string DIRECTORYWEIGHT = "weight";
	const string NAMEFILEWEIGHT = "weight.txt";

	const string DIRECTORYCONFIGURATION = "configuration";
	const string NAMEFILECONFIG = "config_client.txt";
	const string NAMEFILESAP = "file_sap";
	const string NAMEFILEWEIGHTS = "file_weights";
	const string CONFIGURATION = "configuration";
	const string CLIENT_CONFIGURATION = "config_client";
	void SetValueJSONToConfiguration();
	void ParseMapConfigToJSON();
	void ParseJSONToObjectClient();
	void SetValueJSONToConfigClient();
};


#endif // !Scale_h


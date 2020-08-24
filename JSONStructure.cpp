#include "JSONStructure.h"

JSONStructure::JSONStructure()
{
    manageFileVehicles->SetNameDirectory(DIRECTORYVEHICLES);
    manageFileVehicles->SetNameFile(VEHICLESFILE);
    manageFileVehicles->CreateDirectory();
}

JSONStructure::~JSONStructure()
{
}

void JSONStructure::WriteJSONToString() {
	Json::StreamWriterBuilder builder;
	builder.settings_["indentation"] = "    ";
	stringJSON = Json::writeString(builder, jsonBody);
}

void JSONStructure::SaveConfiguration() {
	if (manageFile->DeleteFile()) {};
	WriteJSONToString();
	manageFile->WriteFile(stringJSON);
}

void JSONStructure::SaveConfigurationVehicles() {
    if (manageFileVehicles->DeleteFile()) {};
    WriteJSONToString();
    manageFileVehicles->WriteFile(stringJSON);
}

void JSONStructure::ConfigVehicles() {   

    if (!manageFileVehicles->is_file_exist())
    {
        jsonBody.clear();
        jsonArray.clear();
        jsonArray[0]["code"] = "C2";
        jsonArray[0]["scaleOne"] = 7;
        jsonArray[0]["scaleTwo"] = 11;
        jsonArray[0]["scaleThree"] = 0;
        jsonArray[0]["scaleFour"] = 0;
        jsonArray[0]["total"] = 18;

        jsonArray[1]["code"] = "C3";
        jsonArray[1]["scaleOne"] = 7;
        jsonArray[1]["scaleTwo"] = 18;
        jsonArray[1]["scaleThree"] = 0;
        jsonArray[1]["scaleFour"] = 0;
        jsonArray[1]["total"] = 25;

        jsonArray[2]["code"] = "T3S2";
        jsonArray[2]["scaleOne"] = 7;
        jsonArray[2]["scaleTwo"] = 18;
        jsonArray[2]["scaleThree"] = 18;
        jsonArray[2]["scaleFour"] = 0;
        jsonArray[2]["total"] = 43;

        jsonArray[3]["code"] = "T3S3";
        jsonArray[3]["scaleOne"] = 7;
        jsonArray[3]["scaleTwo"] = 18;
        jsonArray[3]["scaleThree"] = 25;
        jsonArray[3]["scaleFour"] = 0;
        jsonArray[3]["total"] = 48;


        // create the main object

        jsonBody[CONFIGURATION] = TRUCK_CONFIGURATION;
        jsonBody[LIST] = jsonArray;

        SaveConfigurationVehicles();
    }
    
}

void JSONStructure::ParseJSONToListVehicle() {
    string errors;
    jsonBody.clear();
    stringJSON = manageFileVehicles->ReadFileText();
    //cout << "cadena :" << stringJSON << endl;
    if (!stringJSON.empty())
    {
        bool parsingSuccessful = reader->parse(stringJSON.c_str(),
            stringJSON.c_str() + stringJSON.size(),
            &jsonBody, &errors);
        if (parsingSuccessful)
        {
            SetValueJSONToList();
        }

    }
    else
    {
        string message = "Not found file " + VEHICLESFILE;
        manageFileVehicles->WriteToFileLog(message);

    }
}

void JSONStructure::SetValueJSONToList() {
    const Json::Value& list = jsonBody[LIST];

    for (int i = 0; i < (int)list.size(); i++) {
        Vehicles vehicle;
        vehicle.SetCode(list[i]["code"].asString());
        vehicle.SetScaleOne(list[i]["scaleOne"].asUInt());
        vehicle.SetScaleTwo(list[i]["scaleTwo"].asUInt());
        vehicle.SetScaleThree(list[i]["scaleThree"].asUInt());
        vehicle.SetScaleFour(list[i]["scaleFour"].asUInt());
        vehicle.SetScaleTotal(list[i]["total"].asUInt());
        listConfig.push_back(vehicle);
    }
    
}

int JSONStructure::SearchIndexCode(std::string valueCode) {
    for (int i = 0; i < listConfig.size(); i++)
    {
        if (listConfig[i].GetCode() == valueCode)
        {
            return i;
        }
    }

    return -1;
}
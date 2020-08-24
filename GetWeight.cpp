#include <iostream>
#include "Scale.h"


int main()
{
    Scale* scale = new Scale();
    JSONStructure* jsonStructure = new JSONStructure();
    jsonStructure->manageFile->WriteToFileLog("Init capture");
    jsonStructure->ConfigVehicles();
    jsonStructure->ParseJSONToListVehicle();
    scale->LoadConfiguration();
    scale->DeleteFileWeight();
    string code = scale->GetCodeVehicle();
    
    if (!code.empty())
    {
        int index = jsonStructure->SearchIndexCode(code);
        if (index != -1)
        {
            jsonStructure->manageFile->WriteToFileLog("Code vehicle correct: " + code);
            Vehicles vehicle = jsonStructure->listConfig[index];
            scale->ParseJSONToObject();
            scale->WriteFileWeight(vehicle);

        }
        else
        {
            jsonStructure->manageFile->WriteToFileLog("Code vehicle incorrect: " + code);
        }
    }
    else {
        jsonStructure->manageFile->WriteToFileLog("There is no DAT_VEHICULO.txt file and only the total is printed.");
        scale->ParseJSONToObject();
        scale->WriteFileOnlyTotal();
    }    

    jsonStructure->manageFile->WriteToFileLog("End capture.");
}


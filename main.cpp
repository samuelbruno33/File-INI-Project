#include <iostream>
#include <string>

#include "CIniFile.h"

int main() {
    CIniFile iniFile("/home/samuel/Documenti/Università/Lab di Programmazione/FileINIProject/ini_test.ini");
    iniFile.ReadFile();

    cout << "Hello" << endl;
    cout << "NKeys = " << iniFile.NumSections() << endl;
    cout << "Num Values for 386enh = " << iniFile.NumValues("386enh") << endl;
    cout << "Num Values for popopopoaiaiaiaia = " << iniFile.NumValues("popopopoaiaiaiaia") << endl;
    cout << "Num Values for crapXXX = " << iniFile.NumValues("crapXXX") << endl;
    //cout << "crapXXX:fred = " << iniFile.GetValue( "crapXXX", "fred", 3.14159) << endl;
    cout << "ScreenTime:previousProjectorProcessID = ";
    //cout << iniFile.GetValue<int>("ScreenTime", "previousProjectorProcessID") << endl;
    //iniFile.DeleteValue( "drivers", "timer");
    cout << "Num drivers = " << iniFile.NumValues( "drivers") << endl;
    //cout << "drivers:timer = " << iniFile.GetValue<string>( "drivers", "timer") << endl;
    //cout << "drivers:wave = " << iniFile.GetValue<string>( "drivers", "wave") << endl;

    iniFile.setPath("/home/samuel/Documenti/Università/Lab di Programmazione/FileINIProject/ini_test.sav");

    iniFile.AddSection("popopopoaiaiaiaia");
    iniFile.AddKeyComment("popopopoaiaiaiaia","ciao lulz");
    iniFile.NewHeaderComment("MA IO TENGO IL DIESEL");
    iniFile.SetValue("popopopoaiaiaiaia","MAMMA MIA",50);

    iniFile.WriteFile();

    for (int keyID = 0; keyID < iniFile.NumSections(); keyID++) {
        cout<<"Section = " << iniFile.GetSection(keyID) << endl;
        //for (int valueID = 0; valueID < iniFile.NumValues(keyID); valueID++)
            //cout<<"ValueName = "<<iniFile.GetValueName(keyID,valueID)<<"Value = "<<iniFile.GetValue<string>(keyID,valueID)<<endl;
    }
    return 0;
}
#include <iostream>
#include <string>

#include "CIniFile.h"

//Path lavoro: C:\Users\sbruno\Documents\Samuel\Varie\Uni\Lab Programmazione\FileINIProject 1.2\Files\ini_test.ini
//Path casa: /home/samuel/Documenti/Università/Lab di Programmazione/FileINIProject 1.2/Files/ini_test.ini

int main() {
    ///Utilizzo la raw string per inserire correttamente la path e non usare le doppie barre laterali
    CIniFile iniFile(R"(C:\Users\sbruno\Documents\Samuel\Varie\Uni\Lab Programmazione\FileINIProject 1.2\Files\ini_test.ini)");
    iniFile.ReadFile();

    //TEST LETTURA DATI DA FILE
    cout << "Num Sections = " << iniFile.NumSections() << endl;
    cout << "Num Values for Prova = " << iniFile.NumValuesInSection("Prova") << endl;
    cout << "Num Values for Ripperoni = " << iniFile.NumValuesInSection("Ripperoni") << endl;
    cout << "Ripperoni:Osvaldo = " << iniFile.GetValue<string>("Ripperoni", "Osvaldo", "Pippo") << endl;
    cout << "Num of Section 3 Test = " << iniFile.NumValuesInSection("Section 3 Test") << endl;
    cout << "Section 3 Test:Type_Integer1 = " << iniFile.GetValue<int>("Section 3 Test", "Type_Integer1") << endl;
    cout << "Prova:type_Bool = " << iniFile.GetValue<bool>("Prova", "type_Bool") << endl;
    cout << "Prova:type2_Bool = " << iniFile.GetValue<bool>("Prova", "type2_Bool") << endl;

    //TEST COMMENTI
    cout<<iniFile.GetHeaderComment(0)<<endl;
    cout<<iniFile.GetHeaderComment(1)<<endl;
    cout<<iniFile.GetHeaderComment(5)<<endl;
    cout<<iniFile.NumKeyCommentsInSection(1)<<endl;
    cout<<iniFile.NumKeyCommentsInSection("Test Scrittura")<<endl;
    cout<<iniFile.GetKeyComment("Prova",0)<<endl;
    cout<<iniFile.NumHeaderComments()<<endl;

    //TEST PARAMETRO IN SEZIONE
    cout<<iniFile.GetValueName("Section 1",0)<<endl;

    //TEST SCRITTURA SU FILE
    iniFile.AddSection("Test Scrittura");
    iniFile.AddKeyCommentInSection("Test Scrittura","Commento per la sezione Test Scrittura");
    iniFile.NewHeaderComment("Questo invece è un commento di scrittura per l'header");
    iniFile.SetValue("Test Scrittura","test_Write",50);
    iniFile.SetValue(3,0,55); //Sovrascrive il dato 50 sopra in 55

    //TEST CANCELLAZIONE DATI SU FILE
    //iniFile.DeleteValue("drivers", "timer");

    iniFile.WriteFile();

    ///Se si vuole salvare un file con un altra estensione del tipo .sav
    //iniFile.setPath(R"(C:\Users\sbruno\Documents\Samuel\Varie\Uni\Lab Programmazione\FileINIProject 1.2\Files\ini_test.sav)");

    ///Output dell'intero file INI
    for(int keyID = 0; keyID < iniFile.NumSections(); keyID++) {
        cout<<"\nSection = " << iniFile.GetSection(keyID) << endl;
        for (int valueID = 0; valueID < iniFile.NumValuesInSection(keyID); valueID++)
            cout<<"ValueName = "<<iniFile.GetValueName(keyID,valueID)<<"Value = "<<iniFile.GetValue<string>(keyID,valueID)<<endl;
    }
    return 0;
}

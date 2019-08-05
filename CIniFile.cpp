//
// Created by samuel on 05/07/19.
//

#include <fstream>
#include <exception>
#include "CIniFile.h"

bool CIniFile::ReadFile()
{
    fstream f;
    string line;
    string keyName, valueName, value;
    string::size_type pLeft, pRight;

    //Apro il file
    f.open(getPath().c_str(), ios::in);
    if(f.fail()){
        return false;
    }

    while(getline(f, line)) {
        if (line.length()) {
            //Check della stringa se esiste oppure no
            if ((pLeft = line.find_first_of(";#[=")) != string::npos)
            {
                switch (line[pLeft]) {
                    case '[':
                        if ((pRight = line.find_last_of(']')) != string::npos && pRight > pLeft) {
                            keyName = line.substr(pLeft + 1, pRight - pLeft - 1);
                            AddSection(keyName);
                        }
                        break;

                    case '=':
                        valueName = line.substr(0, pLeft);
                        value = line.substr(pLeft + 1);
                        SetValue(keyName, valueName, value);
                        break;

                    //Ci possono essere due tipologie di commenti che iniziano con # o ;
                    case ';':
                    case '#':
                        if (section.empty())
                            NewHeaderComment(line.substr(pLeft + 1));
                        else
                            AddKeyCommentInSection(keyName, line.substr(pLeft + 1));
                        break;
                }
            }
        }
    }
    f.close();

    return !section.empty();
}

bool CIniFile::WriteFile()
{
    int commentID, keyID, valueID;
    fstream f;

    f.open(getPath().c_str(), ios::out);
    if (f.fail())
        return false;

    // Scrive l'intestazione di commenti
    for (commentID = 0; commentID < comments.size(); commentID++)
        f << ';' << comments[commentID] << endl;
    if (!comments.empty())
        f << endl;

    //Scrive su file le sezioni contenenti le varie chiavi di valori
    for (keyID = 0; keyID < keys.size(); keyID++) {
        f << '[' << section[keyID] << ']' << endl;
        // Commenti
        for (commentID = 0; commentID < keys[keyID].comment.size(); commentID++)
            f << ';' << keys[keyID].comment[commentID] << endl;
        // Valori
        for (valueID = 0; valueID < keys[keyID].names.size(); valueID++)
            f << keys[keyID].names[valueID] << '=' << keys[keyID].value[valueID] << endl;
        f << endl;
    }
    f.close();

    return true;
}

void CIniFile::ChangeFileName()
{
    string putKeys, putString, newFileName;

    cout << "Inserisci il nome del file su cui lavorare (senza estensione): ";
    getline(cin, putString);
    cout << "Inserisci l'estensione del file: ";
    getline(cin, putKeys);
    newFileName = putString + "." + putKeys;
    setFileName(newFileName);
    cout << "Nome del file: " << getFileName() << endl;
}

string CIniFile::ChangePath()
{
    int ins = 0;
    string putPath,jumpString;

    cout<<"\nNome del file corrente: "<<getFileName()<<"\n"<<endl;
    cout<<"Vuoi cambiare file di lavoro ?"<<endl;
    cout<<"Inserisci scelta <0-no 1-si>: ";
    cin>>ins;
    getline(cin, jumpString);
    if(cin.fail() || ins >= 2){
        cout<<"Hai inserito un input sbagliato!"<<endl;
        cin.clear();
        getline(cin, jumpString);
        return "";
    }
    else if(ins == 1)
        ChangeFileName();

    cout<<"Inserisci la path dove è presente il file. Non bisogna inserire nella path anche il nome del file ma solo la sua locazione."<<endl;
    cout<<"Path: ";
    getline(cin,putPath);
    setPath(putPath + "/" + getFileName());
    cout<<getPath()<<endl;
    cout<<"\nPath cambiata correttamente!"<<endl;
    return putPath;
}

void CIniFile::RenameFileName(const string& putString, const string& putKeys)
{
    string newFileName = putString + "." + putKeys;

    size_t count = getPath().find_last_of('/');
    string initPath = getPath().substr(0,count);

    string newPath = initPath + "/" + newFileName;
    string oldPath = initPath + "/" + getFileName();
    rename(oldPath.c_str(),newPath.c_str());
    setFileName(newFileName);
    setPath(newPath);
    cout << "Nome del file: " << getFileName() << endl;
}

int CIniFile::FindSection(string const &keyName) const
{
    for(int keyID = 0; keyID < section.size(); keyID++)
        if (section[keyID] == keyName)
            return keyID;

    return noID;
}

int CIniFile::AddSection(string const &keyName)
{
    section.resize(section.size() + 1, keyName);
    keys.resize(keys.size() + 1);
    return section.size() - 1; //Ritorna l'ultima posizione della chiave inserita
}

string CIniFile::GetSection(int const &keyID) const
{
    if(keyID < section.size())
        return section[keyID];
    else
        return "";
}

void CIniFile::GetValuesInSection(int const &keyID)
{
    if(keyID == noID)
        cout<<"ID non trovato!"<<endl;

    cout<<"\nSezione = " << GetSection(keyID) << endl;
    for (int valueID = 0; valueID < NumKeyValuesInSection(keyID); valueID++)
        cout<<"Nome Valore = "<<GetValueName(keyID,valueID)<<", Valore = "<<GetValue<string>(keyID,valueID)<<endl;
}

int CIniFile::NumKeyValuesInSection(int const &keyID)
{
    if(keyID < keys.size())
        return keys[keyID].names.size();
    return 0;
}

int CIniFile::NumKeyValuesInSection(string const &keyName)
{
    int keyID = FindSection(keyName);
    if(keyID == noID)
        return 0;
    return keys[keyID].names.size();
}

bool CIniFile::DeleteSection(string const& keyName)
{
    int keyID = FindSection(keyName);
    if(keyID == noID)
        return false;

    auto sectionPos = section.begin() + keyID;
    auto keyPos = keys.begin() + keyID;
    section.erase(sectionPos, sectionPos + 1);
    keys.erase(keyPos, keyPos + 1);

    return true;
}

int CIniFile::FindValue(int const &keyID, string const &valueName) const
{
    if(keys.empty() || keyID >= keys.size())
        return noID;

    for(int valueID = 0; valueID < keys[keyID].names.size(); valueID++)
        if(keys[keyID].names[valueID] == valueName)
            return valueID;

    return noID;
}

string CIniFile::GetValueName(int const &keyID, int const &valueID) const
{
    if(keyID < keys.size() && valueID < keys[keyID].names.size())
        return keys[keyID].names[valueID];
    return "";
}

string CIniFile::GetValueName(string const &keyName, int const &valueID) const
{
    int keyID = FindSection(keyName);
    if(keyID == noID)
        return "ID non trovato!";
    return GetValueName(keyID, valueID);
}

int CIniFile::NumKeyCommentsInSection(int const &keyID) const
{
    if(keyID < keys.size())
        return keys[keyID].comment.size();
    return 0;
}

int CIniFile::NumKeyCommentsInSection(string const &keyName) const
{
    int keyID = FindSection(keyName);
    if(keyID == noID)
        return 0;
    return keys[keyID].comment.size();
}

bool CIniFile::AddKeyCommentInSection(int const &keyID, string const &comment)
{
    if(keyID < keys.size()) {
        keys[keyID].comment.resize(keys[keyID].comment.size() + 1, comment);
        return true;
    }
    return false;
}

bool CIniFile::AddKeyCommentInSection(string const &keyName, string const &comment)
{
    int keyID = FindSection(keyName);
    if (keyID == noID)
        return false;
    return AddKeyCommentInSection(keyID, comment);
}

string CIniFile::GetKeyComment(int const &keyID, int const &commentID) const
{
    if(keyID < keys.size() && commentID < keys[keyID].comment.size())
        return keys[keyID].comment[commentID];
    return "";
}

string CIniFile::GetKeyComment(string const &keyName, int const &commentID) const
{
    int keyID = FindSection(keyName);
    if (keyID == noID)
        return "ID non trovato!";
    return GetKeyComment(keyID, commentID);
}

bool CIniFile::DeleteValueInSection(string const &keyName, string const &valueName)
{
    int keyID = FindSection(keyName);
    if(keyID == noID)
        return false;

    int valueID = FindValue(keyID, valueName);
    if(valueID == noID)
        return false;

    auto namePos = keys[keyID].names.begin() + valueID;
    auto valuePos = keys[keyID].value.begin() + valueID;
    keys[keyID].names.erase(namePos, namePos + 1);
    keys[keyID].value.erase(valuePos, valuePos + 1);
    return true;
}

bool CIniFile::DeleteCommentInSection(int const &keyID, int const &commentID)
{
    if(keyID < keys.size() && commentID < keys[keyID].comment.size()) {
        auto commentPos = keys[keyID].comment.begin() + commentID;
        keys[keyID].comment.erase(commentPos, commentPos + 1);
        return true;
    }
    return false;
}

bool CIniFile::DeleteCommentInSection(string const &keyName, int const &commentID)
{
    int keyID = FindSection(keyName);
    if(keyID == noID)
        return false;
    return DeleteCommentInSection(keyID, commentID);
}

bool CIniFile::DeleteAllCommentsInSection(string const &keyName)
{
    int keyID = FindSection(keyName);
    if(keyID == noID)
        return false;
    return DeleteAllCommentsInSection(keyID);
}

bool CIniFile::DeleteAllCommentsInSection(int const &keyID)
{
    if(keyID < keys.size()) {
        keys[keyID].comment.clear();
        return true;
    }
    return false;
}

void CIniFile::NewHeaderComment(string const &comment)
{
    comments.resize(comments.size() + 1, comment);
}

string CIniFile::GetHeaderComment(int const &commentID) const
{
    if(commentID < comments.size())
        return comments[commentID];
    return "";
}

void CIniFile::GetAllHeaderComments()
{
    for(int commentID = 0; commentID < NumHeaderComments(); commentID++)
        cout<<";"<<GetHeaderComment(commentID)<<endl;
}

bool CIniFile::DeleteHeaderComment(int commentID)
{
    if (commentID < comments.size()) {
        auto commentPos = comments.begin() + commentID;
        comments.erase(commentPos, commentPos + 1);
        return true;
    }
    return false;
}

void CIniFile::Type_Choice_SetValue(int type_choice, string const &putKeys, string const &putString, string insValue)
{
    try
    {
        if(type_choice == 1)
            SetValue(putKeys,putString,insValue);
        else if(type_choice == 2)
            SetValue(putKeys,putString,insValue);
        else if(type_choice == 3)
            SetValue(putKeys,putString,insValue);
        else if(type_choice == 4){
            insValue = getBoolValue(insValue);
            if(insValue != "2")
                SetValue(putKeys,putString,insValue);
        }
        else
            cout<<"Hai inserito un codice di tipo della variabile sbagliato!"<<endl;
    }
    catch(exception& e) {
        cout << "Conversione fallita! Proabile errore di scelta di tipo del valore." << endl;
        cout <<"Eccezione lanciata: "<<e.what()<<endl;
    }
}

void CIniFile::Type_Choice_GetValue(int type_choice, string const &putKeys, string const &putString, string insValue)
{
    try
    {
        if(type_choice == 1)
            cout<<"Valore: "<<GetValue(putKeys,putString,insValue)<<endl;
        else if(type_choice == 2)
            cout<<"Valore: "<<GetValue(putKeys,putString,stoi(insValue))<<endl;
        else if(type_choice == 3)
            cout<<"Valore: "<<GetValue(putKeys,putString,stof(insValue))<<endl;
        else if(type_choice == 4)
        {
            insValue = getBoolValue(insValue);
            int insBool = stoi(insValue);
            if(insBool != 2)
                cout<<"Valore: "<<GetValue(putKeys,putString,boost::lexical_cast<bool>(insBool))<<endl;
        }
        else
            cout<<"Hai inserito un codice di tipo della variabile sbagliato!"<<endl;
    }
    catch(exception& e) {
        cout << "Conversione fallita! Proabile errore di scelta di tipo del valore." << endl;
        cout <<"Eccezione lanciata: "<<e.what()<<endl;
    }
}

bool CIniFile::SetValue(string const &keyName, string const &valueName, const string& value, bool const &create){
    int keyID = FindSection(keyName);
    if(keyID == noID) {
        if(create)
            keyID = AddSection(keyName);
        else
            return false;
    }
    int valueID = FindValue(keyID, valueName);
    if(valueID == noID){
        if(!create)
            return false;
        keys[keyID].names.resize(keys[keyID].names.size() + 1, valueName);
        keys[keyID].value.resize(keys[keyID].value.size() + 1, value);
    }
    else
        keys[keyID].value[valueID] = value;

    return true;
}

string CIniFile::getBoolValue(string ret){
    //Valori accettati per ritornare TRUE '1', 'yes', 'true' e 'on',
    //invece '0', 'no', 'false' e 'off' ritornano quindi FALSE.
    if(ret == "1" || ret == "yes" || ret == "true" || ret == "on")
        ret = "1";
    else if(ret == "0"  || ret == "no"  || ret == "false"  || ret == "off")
        ret = "0";
    else{
        cout<<"Errore nell'inserimento del valore booleano."<<endl;
        ret = "2";
    }
    return ret;
}

void CIniFile::toString()
{
    GetAllHeaderComments();

    for(int keyID = 0; keyID < NumSections(); keyID++) {
        cout<<"\nSezione = " << GetSection(keyID) << endl;
        for (int valueID = 0; valueID < NumKeyValuesInSection(keyID); valueID++)
            cout<<"Nome Valore = "<<GetValueName(keyID,valueID)<<", Valore = "<<GetValue<string>(keyID,valueID)<<endl;
    }
}
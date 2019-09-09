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
    string sectionName, valueName, value;
    string::size_type pLeft, pRight;
    int sectionID = 0;
    int valueID = 0;
    int count = 1;

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
                            sectionName = line.substr(pLeft + 1, pRight - pLeft - 1);
                            AddSection(sectionName);
                            sectionID = FindSection(sectionName);
                        }
                        break;

                    case '=':
                        valueName = line.substr(0, pLeft);
                        value = line.substr(pLeft + 1);
                        valueID = FindValue(sectionID,valueName);
                        //Se una chiave ha un valueID diverso da -1 al momento della lettura iniziale del file allora
                        //vuol dire che esiste già una chiave con lo stesso nome e quindi riscrivo il nome della
                        //chiave stessa in modo che non possa sovrascrivere l'altro valore già presente nel file.
                        if(valueID != -1){
                            count++;
                            valueName.append(std::to_string(count));
                        }
                        SetValue(sectionName, valueName, value);
                        break;

                    //Ci possono essere due tipologie di commenti che iniziano con # o ;
                    case ';':
                    case '#':
                        if (section.empty())
                            NewHeaderComment(line.substr(pLeft + 1));
                        else
                            AddKeyCommentInSection(sectionName, line.substr(pLeft + 1));
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
    int commentID, sectionID, valueID;
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
    for (sectionID = 0; sectionID < keys.size(); sectionID++) {
        f << '[' << section[sectionID] << ']' << endl;
        // Commenti
        for (commentID = 0; commentID < keys[sectionID].comment.size(); commentID++)
            f << ';' << keys[sectionID].comment[commentID] << endl;
        // Valori
        for (valueID = 0; valueID < keys[sectionID].names.size(); valueID++)
            f << keys[sectionID].names[valueID] << '=' << keys[sectionID].value[valueID] << endl;
        f << endl;
    }
    f.close();

    return true;
}

void CIniFile::ChangeFileName(const string& putString, const string& putKeys)
{
    string newFileName = putString + "." + putKeys;
    setFileName(newFileName);
    cout << "Nome del file: " << getFileName() << endl;
}

string CIniFile::ChangePath(const string& putPath)
{
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

int CIniFile::FindSection(string const &sectionName) const
{
    for(int sectionID = 0; sectionID < section.size(); sectionID++)
        if (section[sectionID] == sectionName)
            return sectionID;

    return noID;
}

int CIniFile::AddSection(string const &sectionName)
{
    section.push_back(sectionName);
    keys.resize(keys.size() + 1);
    return section.size() - 1; //Ritorna l'ultima posizione della chiave inserita
}

string CIniFile::GetSection(int const &sectionID) const
{
    if(sectionID < section.size())
        return section[sectionID];
    else
        return "";
}

void CIniFile::GetValuesInSection(int const &sectionID)
{
    if(sectionID == noID)
        cout<<"ID non trovato!"<<endl;

    cout<<"\nSezione = " << GetSection(sectionID) << endl;
    for (int valueID = 0; valueID < NumKeyValuesInSection(sectionID); valueID++)
        cout<<"Nome Valore = "<<GetValueName(sectionID,valueID)<<", Valore = "<<GetValue<string>(sectionID,valueID)<<endl;
}

int CIniFile::NumKeyValuesInSection(int const &sectionID)
{
    if(sectionID < keys.size())
        return keys[sectionID].names.size();
    return 0;
}

int CIniFile::NumKeyValuesInSection(string const &sectionName)
{
    int sectionID = FindSection(sectionName);
    if(sectionID == noID)
        return 0;
    return keys[sectionID].names.size();
}

bool CIniFile::DeleteSection(string const& sectionName)
{
    int sectionID = FindSection(sectionName);
    if(sectionID == noID)
        return false;

    auto sectionPos = section.begin() + sectionID;
    auto keyPos = keys.begin() + sectionID;
    section.erase(sectionPos, sectionPos + 1);
    keys.erase(keyPos, keyPos + 1);

    return true;
}

int CIniFile::FindValue(int const &sectionID, string const &valueName) const
{
    if(keys.empty() || sectionID >= keys.size())
        return noID;

    for(int valueID = 0; valueID < keys[sectionID].names.size(); valueID++)
        if(keys[sectionID].names[valueID] == valueName)
            return valueID;

    return noID;
}

string CIniFile::GetValueName(int const &sectionID, int const &valueID) const
{
    if(sectionID < keys.size() && valueID < keys[sectionID].names.size())
        return keys[sectionID].names[valueID];
    return "";
}

string CIniFile::GetValueName(string const &sectionName, int const &valueID) const
{
    int sectionID = FindSection(sectionName);
    if(sectionID == noID)
        return "ID non trovato!";
    return GetValueName(sectionID, valueID);
}

int CIniFile::NumKeyCommentsInSection(int const &sectionID) const
{
    if(sectionID < keys.size())
        return keys[sectionID].comment.size();
    return 0;
}

int CIniFile::NumKeyCommentsInSection(string const &sectionName) const
{
    int sectionID = FindSection(sectionName);
    if(sectionID == noID)
        return 0;
    return keys[sectionID].comment.size();
}

bool CIniFile::AddKeyCommentInSection(int const &sectionID, string const &comment)
{
    if(sectionID < keys.size()) {
        keys[sectionID].comment.push_back(comment);
        return true;
    }
    return false;
}

bool CIniFile::AddKeyCommentInSection(string const &sectionName, string const &comment)
{
    int sectionID = FindSection(sectionName);
    if (sectionID == noID)
        return false;
    return AddKeyCommentInSection(sectionID, comment);
}

string CIniFile::GetKeyComment(int const &sectionID, int const &commentID) const
{
    if(sectionID < keys.size() && commentID < keys[sectionID].comment.size())
        return keys[sectionID].comment[commentID];
    return "";
}

string CIniFile::GetKeyComment(string const &sectionName, int const &commentID) const
{
    int sectionID = FindSection(sectionName);
    if (sectionID == noID)
        return "ID non trovato!";
    return GetKeyComment(sectionID, commentID);
}

bool CIniFile::DeleteValueInSection(string const &sectionName, string const &valueName)
{
    int sectionID = FindSection(sectionName);
    if(sectionID == noID)
        return false;

    int valueID = FindValue(sectionID, valueName);
    if(valueID == noID)
        return false;

    auto namePos = keys[sectionID].names.begin() + valueID;
    auto valuePos = keys[sectionID].value.begin() + valueID;
    keys[sectionID].names.erase(namePos, namePos + 1);
    keys[sectionID].value.erase(valuePos, valuePos + 1);
    return true;
}

bool CIniFile::DeleteCommentInSection(int const &sectionID, int const &commentID)
{
    if(sectionID < keys.size() && commentID < keys[sectionID].comment.size()) {
        auto commentPos = keys[sectionID].comment.begin() + commentID;
        keys[sectionID].comment.erase(commentPos, commentPos + 1);
        return true;
    }
    return false;
}

bool CIniFile::DeleteCommentInSection(string const &sectionName, int const &commentID)
{
    int sectionID = FindSection(sectionName);
    if(sectionID == noID)
        return false;
    return DeleteCommentInSection(sectionID, commentID);
}

bool CIniFile::DeleteAllCommentsInSection(string const &sectionName)
{
    int sectionID = FindSection(sectionName);
    if(sectionID == noID)
        return false;
    return DeleteAllCommentsInSection(sectionID);
}

bool CIniFile::DeleteAllCommentsInSection(int const &sectionID)
{
    if(sectionID < keys.size()) {
        keys[sectionID].comment.clear();
        return true;
    }
    return false;
}

void CIniFile::NewHeaderComment(string const &comment)
{
    comments.push_back(comment);
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
    if(type_choice == 1){
        insValue = getBoolValue(insValue);
        if(insValue != "2")
            SetValue(putKeys,putString,insValue);
    }
    else if (type_choice > 1)
        cout<<"Hai inserito un codice di tipo della variabile sbagliato!"<<endl;
    else
        SetValue(putKeys,putString,insValue);
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

bool CIniFile::SetValue(string const &sectionName, string const &valueName, const string& value, bool const &create)
{
    int sectionID = FindSection(sectionName);
    if(sectionID == noID) {
        if(create){
            sectionID = AddSection(sectionName);
            cout<<"Nuova sezione creata!"<<endl;
        }
        else
            return false;
    }

    int valueID = FindValue(sectionID, valueName);
    if(valueID == noID){
        if(!create)
            return false;
        keys[sectionID].names.push_back(valueName);
        keys[sectionID].value.push_back(value);
    }
    else{
        keys[sectionID].value[valueID] = value;
        cout<<"Valore modificato correttamente!"<<endl;
    }

    return true;
}

string CIniFile::getBoolValue(string ret)
{
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

    for(int sectionID = 0; sectionID < NumSections(); sectionID++) {
        cout<<"\nSezione = " << GetSection(sectionID) << endl;
        for (int valueID = 0; valueID < NumKeyValuesInSection(sectionID); valueID++)
            cout<<"Nome Valore = "<<GetValueName(sectionID,valueID)<<", Valore = "<<GetValue<string>(sectionID,valueID)<<endl;
    }
}
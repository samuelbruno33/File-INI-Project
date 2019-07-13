//
// Created by samuel on 24/06/19.
//

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

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

int CIniFile::FindSection(string const &keyName) const
{
    for(int keyID = 0; keyID < section.size(); keyID++)
        if (section[keyID] == keyName)
            return keyID;

    return noID;
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

int CIniFile::NumValuesInSection(int const &keyID)
{
    if(keyID < keys.size())
        return keys[keyID].names.size();
    return 0;
}

int CIniFile::NumValuesInSection(string const &keyName)
{
    int keyID = FindSection(keyName);
    if(keyID == noID)
        return 0;
    return keys[keyID].names.size();
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
        return "";
    return GetValueName(keyID, valueID);
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
        return "";
    return GetKeyComment(keyID, commentID);
}

//
// Created by samuel on 05/07/19.
//

#include <string>
#include <vector>

#include "Key.h"

#ifndef FILEINIPROJECT_CINIFILE_H
#define FILEINIPROJECT_CINIFILE_H

using namespace std;

class CIniFile
{
public:
    enum error{noID = -1};

    explicit CIniFile(string const initialPath = "") : defaultPath(initialPath) {}
    virtual ~CIniFile(){};

    bool ReadFile();
    bool WriteFile();

    void setPath(string newPath)
    {
        defaultPath = newPath;
    }

    string getPath() const
    {
        return defaultPath;
    }

    //Funzione che cerca l'ID della chiave all'interno della sezione e ritorna un chiave di errore se non esiste
    int FindKey(string const &keyName) const;

    //Funzione che cerca l'ID della valore all'interno della chiave e ritorna un chiave di errore se non esiste
    int FindValue(int const &keyID, string const &valueName) const;

    //Ritorna il numero corrente di chiavi all'interno dell'intero file ini
    int NumSections() const
    {
        return section.size();
    }

    //Aggiunge una nuova sezione
    int AddSection(string const &keyName);

    //Ritorna una stringa contente il nome della sezione cercata
    string GetSection(int const &keyID) const;

    //Ritorna il numero di valori delle chiavi per una specifica chiave
    int NumValues(int const &keyID);
    int NumValues(string const &keyName);

    // Ritorna il nome di una chiave passando il parametro per keyName o per keyID.
    string GetValueName(int const &keyID, int const &valueID) const;
    string GetValueName(string const &keyName, int const &valueID) const;

    // Numero di commenti nell'intestazione
    int NumHeaderComments()
    {
        return comments.size();
    }

    // Aggiungi un intestazione di commenti
    void NewHeaderComment(string const &comment);

    // Ritorna un intestazione di commenti
    string GetHeaderComment(int const &commentID) const;

    // Ritorna il numero dei commenti per una determinata chiave
    int NumKeyComments(int const &keyID) const;
    int NumKeyComments(string const &keyName) const;

    // Aggiungi un commento interno della chiave
    bool AddKeyComment(int const &keyID, string const &comment);
    bool AddKeyComment(string const &keyName, string const &comment);

    // Ritorna un commento interno della chiave
    string GetKeyComment(int const &keyID, int const &commentID) const;
    string GetKeyComment(string const &keyName, int const &commentID) const;

    //Setta i valori delle chiavi all'interno del file
    template<typename T>
    bool AddValue(int const &keyID, int const &valueID, T value){
        if(keyID < keys.size() && valueID < keys[keyID].names.size())
            keys[keyID].value[valueID] = value;

        return false;
    }

    template<typename T>
    bool SetValue(string const &keyName, string const &valueName, T value, bool const &create = true){
        int keyID = FindKey(keyName);
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

    //Fa ritornare i valori delle chiavi presenti all'interno del file
    template<typename T>
    T GetValue(int const &keyID, int const &valueID, T defValue = 0) {
        if(keyID < keys.size() && valueID < keys[keyID].names.size())
            return keys[keyID].value[valueID];
        return defValue;
    }

    template<typename T>
    T GetValue(string const &keyName, string const &valueName, T defValue = 0) {
        int keyID = FindKey(keyName);
        if (keyID == noID)
            return defValue;

        int valueID = FindValue(keyID, valueName);
        if (valueID == noID)
            return defValue;

        return keys[keyID].value[valueID];
    }

private:
    string defaultPath;
    vector<string> section;
    vector<string> comments;
    vector<Key> keys;
};

#endif //FILEINIPROJECT_CINIFILE_H

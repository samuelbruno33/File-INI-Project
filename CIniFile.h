//
// Created by samuel on 24/06/19.
//

#include <string>
#include <vector>
#include <typeinfo>
#include <boost/lexical_cast.hpp>

#include "Key.h"

#ifndef FILEINIPROJECT_CINIFILE_H
#define FILEINIPROJECT_CINIFILE_H

using namespace std;

class CIniFile
{
public:
    enum error{noID = -1};

    explicit CIniFile(string const initialPath = "") : defaultPath(initialPath) {}
    virtual ~CIniFile() = default;;

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

    //Funzione che cerca l'ID della sezione attraverso il suo nome e ritorna un chiave di errore se non esiste
    int FindSection(string const &keyName) const;

    //Funzione che cerca l'ID del valore all'interno della sezione e ritorna un chiave di errore se non esiste
    int FindValue(int const &keyID, string const &valueName) const;

    //Ritorna il numero corrente delle sezioni all'interno dell'intero file ini
    int NumSections() const
    {
        return section.size();
    }

    //Aggiunge una nuova sezione
    int AddSection(string const &keyName);

    //Ritorna una stringa contente il nome della sezione cercata
    string GetSection(int const &keyID) const;

    //Ritorna il numero di valori delle chiavi per una specifica sezione
    int NumValuesInSection(int const &keyID);
    int NumValuesInSection(string const &keyName);

    // Ritorna il nome di una chiave per una specifica sezione
    string GetValueName(int const &keyID, int const &valueID) const;
    string GetValueName(string const &keyName, int const &valueID) const;

    // Numero di commenti nell'intestazione
    int NumHeaderComments()
    {
        return comments.size();
    }

    // Aggiungi una riga di commento nell'intestazione
    void NewHeaderComment(string const &comment);

    // Ritorna un commento specifico presente nell'intestazione
    string GetHeaderComment(int const &commentID) const;

    // Ritorna il numero dei commenti per una determinata sezione
    int NumKeyCommentsInSection(int const &keyID) const;
    int NumKeyCommentsInSection(string const &keyName) const;

    // Aggiungi un commento interno alla sezione
    bool AddKeyCommentInSection(int const &keyID, string const &comment);
    bool AddKeyCommentInSection(string const &keyName, string const &comment);

    // Ritorna un commento interno alla sezione
    string GetKeyComment(int const &keyID, int const &commentID) const;
    string GetKeyComment(string const &keyName, int const &commentID) const;

    //Setta i valori delle chiavi all'interno del file
    template<typename T>
    bool SetValue(int const &keyID, int const &valueID, T val){
        string value = boost::lexical_cast<string>(val);
        if(keyID < keys.size() && valueID < keys[keyID].names.size())
            keys[keyID].value[valueID] = value;
        return false;
    }

    template<typename T>
    bool SetValue(string const &keyName, string const &valueName, T val, bool const &create = true){
        string value = boost::lexical_cast<string>(val);
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

    //Fa ritornare i valori delle chiavi presenti all'interno del file
    template<typename T>
    T GetValue(int const &keyID, int const &valueID, T const defValue = T()) {
        if(keyID < keys.size() && valueID < keys[keyID].names.size()){
            string ret = keys[keyID].value[valueID];
            if(typeid(defValue) == typeid(bool)) {
                ret = getBoolValue(ret);
            }
            return boost::lexical_cast<T>(ret);
        }
        else
            return defValue;
    }

    template<typename T>
    T GetValue(string const &keyName, string const &valueName, T const defValue = T()) {
        int keyID = FindSection(keyName);
        if (keyID == noID){
            return defValue;
        }
        int valueID = FindValue(keyID, valueName);
        if (valueID == noID){
            return defValue;
        }
        string ret = keys[keyID].value[valueID];
        if(typeid(defValue) == typeid(bool)) {
            ret = getBoolValue(ret);
        }
        return boost::lexical_cast<T>(ret);
    }

    //Controllo del tipo Booleano nel ritorno del valore nella macro-funzione getValue.
    //Questo controllo è fondamentale perchè all'interno file INI ci sono diverse modalità di dichiarazione
    //di un valore booleano.
    static string getBoolValue(string ret){
        //Valori accettati per ritornare TRUE '1', 'yes', 'true' e 'on',
        //invece '0', 'no', 'false' e 'off' ritornano quindi FALSE.
        if(ret == "1" || ret == "yes" || ret == "true" || ret == "on")
            ret = "1";
        else
            ret = "0";
        return ret;
    }

private:
    string defaultPath;
    vector<string> section;
    vector<string> comments;
    vector<Key> keys;
};

#endif //FILEINIPROJECT_CINIFILE_H

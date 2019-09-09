//
// Created by samuel on 05/07/19.
//

#include <iostream>
#include <string>
#include <utility>
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
    explicit CIniFile(const string& initialPath = "./Files", string fn = "ini_file.ini") : fileName(std::move(fn)){
        defaultPath = initialPath + "/" + fileName;
    }
    virtual ~CIniFile() = default;

    /// Funzioni di lettura e scrittura

    bool ReadFile();
    bool WriteFile();

    /// Funzioni che riguardano le path e il nome del file

    void setPath(string newPath)
    {
        defaultPath = std::move(newPath);
    }

    string getPath() const
    {
        return defaultPath;
    }

    const string &getFileName() const {
        return fileName;
    }

    void setFileName(const string &fn) {
        CIniFile::fileName = fn;
    }

    //Funzione che viene utilizzata per cambiare il nome del file insieme alla path
    void ChangeFileName(const string& putString, const string& putKeys);

    //Funzione che viene utilizzata per cambiare la path del file
    string ChangePath(const string& putPath);

    //Funzione che viene utilizzata per rinominare il file
    void RenameFileName(const string& putString, const string& putKeys);

    ///Funzioni che riguardano le sezioni

    //Funzione che cerca l'ID della sezione attraverso il suo nome e ritorna un chiave di errore se non esiste
    int FindSection(string const &sectionName) const;

    //Ritorna il numero corrente delle sezioni all'interno dell'intero file ini
    int NumSections() const
    {
        return section.size();
    }

    //Aggiunge una nuova sezione
    int AddSection(string const &sectionName);

    //Ritorna una stringa contente il nome della sezione cercata
    string GetSection(int const &sectionID) const;

    //Stampa il nome della sezione con i suoi relativi parametri e valori
    void GetValuesInSection(int const &sectionID);

    //Ritorna il numero dei parametri presenti in una sezione
    int NumKeyValuesInSection(int const &sectionID);
    int NumKeyValuesInSection(string const &sectionName);

    // Elimina un intera sezione e i suoi relativi parametri
    bool DeleteSection(const string& sectionName);

    ///Funzioni che riguardano le chiavi all'interno delle sezioni

    //Funzione che cerca l'ID del valore all'interno della sezione e ritorna un chiave di errore se non esiste
    int FindValue(int const &sectionID, string const &valueName) const;

    // Ritorna il nome del parametro cercato per una specifica sezione
    string GetValueName(int const &sectionID, int const &valueID) const;
    string GetValueName(string const &sectionName, int const &valueID) const;

    // Ritorna il numero dei commenti per una determinata sezione
    int NumKeyCommentsInSection(int const &sectionID) const;
    int NumKeyCommentsInSection(string const &sectionName) const;

    // Aggiunge un commento interno alla sezione
    bool AddKeyCommentInSection(int const &sectionID, string const &comment);
    bool AddKeyCommentInSection(string const &sectionName, string const &comment);

    // Ritorna un commento interno alla sezione
    string GetKeyComment(int const &sectionID, int const &commentID) const;
    string GetKeyComment(string const &sectionName, int const &commentID) const;

    // Elimina un parametro e il corrispondente valore presente in una determinata sezione
    bool DeleteValueInSection(string const &sectionName, const string &valueName);

    // Elimina un commento presente nella sezione
    bool DeleteCommentInSection(int const &sectionID, int const &commentID);
    bool DeleteCommentInSection(string const &sectionName, int const &commentID);

    // Elimina tutti i commenti presenti nella sezione
    bool DeleteAllCommentsInSection(int const &sectionID);
    bool DeleteAllCommentsInSection(string const &sectionName);

    ///Funzioni che riguardano i commenti d'intestazione

    // Ritorna il numero di commenti presenti nell'intestazione
    int NumHeaderComments()
    {
        return comments.size();
    }

    // Aggiunge una riga di commento nell'intestazione
    void NewHeaderComment(string const &comment);

    // Ritorna un commento specifico presente nell'intestazione
    string GetHeaderComment(int const &commentID) const;

    // Ritorna tutti i commenti d'intestazione
    void GetAllHeaderComments();

    // Elimina un singolo commento d'intestazione
    bool DeleteHeaderComment(int commentID);

    // Elimina tutti i commenti d'intestazione
    void DeleteAllHeaderComments()
    {
        comments.clear();
    }

    ///Funzioni che servono per aggiungere un valore o visualizzarlo all'interno della sezione

    //Funzione che serve per determinare il tipo di dato da inserire nel file INI
    void Type_Choice_SetValue(int type_choice, string const &putKeys, string const &putString, string insValue);
    void Type_Choice_GetValue(int type_choice, string const &putKeys, string const &putString, string insValue);

    //Setta i valori delle chiavi all'interno del file
    bool SetValue(string const &sectionName, string const &valueName, const string& value, bool const &create = true);

    //Fa ritornare i valori delle chiavi presenti all'interno del file
    template<typename T>
    T GetValue(int const &sectionID, int const &valueID, T const defValue = T()) {
        if (sectionID < keys.size() && valueID < keys[sectionID].names.size()) {
            string ret = keys[sectionID].value[valueID];
            if(typeid(T) == typeid(bool)) {
                ret = getBoolValue(ret);
                int val = stoi(ret);
                if(val == 2)
                    goto boolean_label;
                else
                    return boost::lexical_cast<T>(val);
            }
            else if(typeid(T) == typeid(int))
                return boost::lexical_cast<T>(stoi(ret));
            else if(typeid(T) == typeid(float))
                return boost::lexical_cast<T>(stof(ret));
            else if(typeid(T) == typeid(string))
                return boost::lexical_cast<T>(ret);
            else{
                boolean_label:
                cout<<"Ritorna il valore di default: ";
                return boost::lexical_cast<T>(defValue);
            }
        }
    }

    template<typename T>
    T GetValue(string const &sectionName, string const &valueName, T const defValue = T()) {
        int sectionID = FindSection(sectionName);
        if(sectionID == noID)
            return defValue;

        int valueID = FindValue(sectionID, valueName);
        if(valueID == noID)
            return defValue;

        string ret = keys[sectionID].value[valueID];
        if(typeid(T) == typeid(bool)) {
            ret = getBoolValue(ret);
            int val = stoi(ret);
            if (val != 2)
                return boost::lexical_cast<T>(val);
            else
                goto boolean_label;
        }
        else if(typeid(T) == typeid(int))
            return boost::lexical_cast<T>(stoi(ret));
        else if(typeid(T) == typeid(float))
            return boost::lexical_cast<T>(stof(ret));
        else if(typeid(T) == typeid(string))
            return boost::lexical_cast<T>(ret);
        else{
          boolean_label:
            cout<<"Ritorna il valore di default: ";
            return boost::lexical_cast<T>(defValue);
        }
    }

    //Controllo del tipo Booleano nel ritorno del valore nella macro-funzione getValue.
    //Questo controllo è fondamentale perchè all'interno file INI ci sono diverse modalità di dichiarazione
    //di un valore booleano.
    static string getBoolValue(string ret);

    ///Funzione che stampa l'intero file INI
    void toString();

private:
    string defaultPath;
    string fileName;
    vector<string> section;
    vector<string> comments;
    vector<Key> keys;
};

#endif //FILEINIPROJECT_CINIFILE_H
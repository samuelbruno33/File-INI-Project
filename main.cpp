//
// Created by sbruno on 09/07/2019.
//

#include <iostream>
#include <string>
#include "CIniFile.h"

using namespace std;

int main()
{
    int ans=0,choice,type_choice,putComment,defVal;
    string putString,putKeys,insValue,jumpString,fileName = "ini_test.ini";

    CIniFile iniFile(R"(/home/samuel/Documenti/Università/Lab di Programmazione/FileINIProject/Files/ini_test.ini)");
    iniFile.ReadFile();

    while(ans==0)
    {
        cout<<"\n---------MENU'---------\n";
        cout<<"0)Esci dal programma\n";
        cout<<"1)Aggiungi commento d'intestazione\n";
        cout<<"2)Aggiungi sezione\n";
        cout<<"3)Aggiungi valore all'interno di una sezione\n";
        cout<<"4)Aggiungi commento all'interno di una sezione\n";
        cout<<"5)Visualizza tutta la sezione\n";
        cout<<"6)Visualizza un valore specifico presente in una sezione\n";
        cout<<"7)Visualizza un commento specifico presente in una sezione\n";
        cout<<"8)Visualizza tutti i commenti d'intestazione\n";
        cout<<"9)Visualizza uno specifico commento d'intestazione\n";
        cout<<"10)Elimina sezione\n";
        cout<<"11)Elimina un valore specifico in una sezione\n";
        cout<<"12)Elimina un commento specifico in una sezione\n";
        cout<<"13)Elimina tutti i commenti in una sezione\n";
        cout<<"14)Elimina tutti i commenti d'intestazione\n";
        cout<<"15)Elimina uno specifico commento d'intestazione\n";
        cout<<"16)Visualizza contenuto del file INI\n";
        cout<<"17)Salva file con un altro nome\n";
        cout<<"18)Cambia la path del file\n";
        cout<<"\n";

        cout<<"Inserisci la tua scelta:";
        cin>>choice;

        //Salta la riga per problemi di inserimento del carattere con il cin, poichè una volta preso l'input (di un solo carattere
        //alla volta), il cin a fine riga di input mette uno /n che sballa la visualizzazione e l'input successivi presenti nei case.
        getline(cin, jumpString);

        switch(choice)
        {
            default:cout<<"Attenzione! Stai per uscire dal programma...Attendi!"<<endl;
                cout<<"\n";
                ans=1;
                break;

            case 1:
                cout<<"Inserisci il commento da porre nell'intestazione: ";
                getline(cin,putString);
                iniFile.NewHeaderComment(putString);
                iniFile.WriteFile();
                cout<<"Inserimento avvenuto con successo!"<<endl;
                break;

            case 2:
                cout<<"Inserisci il nome che vuoi dare alla nuova sezione: ";
                getline(cin,putString);
                iniFile.AddSection(putString);
                iniFile.WriteFile();
                cout<<"Inserimento avvenuto con successo!"<<endl;
                break;

            case 3:
                cout<<"Inserisci il nome della sezione che vuoi visualizzare. Se si inserisce una nome della sezione non esistente ne verrà creata una nuova."<<endl;
                cout<<"Inserisci: ";
                getline(cin,putKeys);
                cout<<"Inserisci il valore da porre all'interno di "<<putKeys<<": ";
                getline(cin,putString);
                cout<<"Vuoi inserire una stringa, un intero, un float o un booleano? <1-String,2-Int,3-Float,4-Bool>: ";
                cin>>type_choice;
                if(cin.fail()){
                    cout<<"Hai inserito un input sbagliato!";
                    cin.clear();
                    ans=1;
                    break;
                }
                getline(cin, jumpString);
                cout<<"Inserisci un valore da inserire all'interno di "<<putString<<": ";
                getline(cin,insValue);
                iniFile.Type_Choice_SetValue(type_choice,putKeys,putString,insValue);
                iniFile.WriteFile();
                break;

            case 4:
                cout<<"Inserisci la sezione dove verrà scritto il commento: ";
                getline(cin,putKeys);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                {
                    cout<<"Nome sezione non esistente!"<<endl;
                    break;
                }
                cout<<"Inserisci il commento da porre all'interno di "<<putKeys<<": ";
                getline(cin,putString);
                iniFile.AddKeyCommentInSection(putKeys,putString);
                iniFile.WriteFile();
                cout<<"Inserimento avvenuto con successo!"<<endl;
                break;

            case 5:
                cout<<"Inserisci la sezione che vuoi visualizzare: ";
                getline(cin,putKeys);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                {
                    cout<<"Nome sezione non esistente!"<<endl;
                    break;
                }
                iniFile.GetValuesInSection(iniFile.FindSection(putKeys));
                break;

            case 6:
                cout<<"Inserisci la sezione di cui vuoi visualizzare i dati: ";
                getline(cin,putKeys);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                {
                    cout<<"Nome sezione non esistente!"<<endl;
                    break;
                }
                cout<<"Inserisci il nome del parametro da cercare all'interno di "<<putKeys<<": ";
                getline(cin,putString);
                if(iniFile.FindValue(iniFile.FindSection(putKeys),putString) == iniFile.noID)
                {
                    cout<<"Nome parametro non esistente!"<<endl;
                    break;
                }
                cout<<"Stai cercando una stringa, un intero, un float o un booleano? <1-String,2-Int,3-Float,4-Bool>: ";
                cin>>type_choice;
                if(cin.fail()){
                    cout<<"Hai inserito un input sbagliato!";
                    cin.clear();
                    ans=1;
                    break;
                }
                cout<<"Vuoi inserire un valore di default nel caso non esistessero il parametro o la sezione da cercare? <0-no,1-si>: ";
                cin>>defVal;
                if(cin.fail()){
                    cout<<"Hai inserito un input sbagliato!";
                    cin.clear();
                    ans=1;
                    break;
                }
                getline(cin, jumpString);

                if(defVal == 1){
                    cout<<"Inserisci il valore di default: ";
                    getline(cin,insValue);
                    iniFile.Type_Choice_GetValue_DefValue(type_choice,putKeys,putString,insValue);
                }
                else if(defVal == 0)
                    iniFile.Type_Choice_GetValue(type_choice,putKeys,putString);
                else
                    cout<<"Hai inserito un codice di inserimento del valore di default sbagliato!"<<endl;
                break;

            case 7:
                cout<<"Inserisci la sezione da cui vuoi visualizzare il commento: ";
                getline(cin,putKeys);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                {
                    cout<<"Nome sezione non esistente!"<<endl;
                    break;
                }
                cout<<"Inserisci il numero del relativo commento che vuoi visualizzare: ";
                cin>>putComment;
                if(cin.fail()){
                    cout<<"Hai inserito un input sbagliato!";
                    cin.clear();
                    ans=1;
                    break;
                }
                else if(putComment > iniFile.NumKeyCommentsInSection(putKeys))
                    cout<<"Hai inserito un numero di commento che non esiste!"<<endl;
                else
                    cout<<";"<<iniFile.GetKeyComment(putKeys,putComment)<<endl;
                break;

            case 8:
                iniFile.GetAllHeaderComments();
                break;

            case 9:
                cout<<"Inserisci il numero del relativo commento d'intestazione che vuoi visualizzare. Il numero del commento da inserire inizia da 0."<<endl;
                cout<<"Inserisci: ";
                cin>>putComment;
                if(cin.fail()){
                    cout<<"Hai inserito un input sbagliato!";
                    cin.clear();
                    ans=1;
                    break;
                }
                else if(putComment > iniFile.NumHeaderComments())
                    cout<<"Hai inserito un numero di commento che non esiste!"<<endl;
                else
                    cout<<";"<<iniFile.GetHeaderComment(putComment)<<endl;
                break;

            case 10:
                cout<<"Inserisci il nome della sezione da eliminare: ";
                getline(cin,putString);
                iniFile.DeleteSection(putString);
                iniFile.WriteFile();
                break;

            case 11:
                cout<<"Inserisci il nome della sezione da eliminare: ";
                getline(cin,putKeys);
                cout<<"Inserisci il parametro di una sezione da eliminare: ";
                getline(cin,putString);
                iniFile.DeleteValueInSection(putKeys,putString);
                iniFile.WriteFile();
                break;

            case 12:
                cout<<"Inserisci il nome della sezione da eliminare: ";
                getline(cin,putKeys);
                cout<<"Inserisci il numero del commento da eliminare: ";
                cin>>putComment;
                if(cin.fail()){
                    cout<<"Hai inserito un input sbagliato!";
                    cin.clear();
                    ans=1;
                    break;
                }
                else if(putComment > iniFile.NumHeaderComments())
                    cout<<"Hai inserito un numero di commento che non esiste!"<<endl;
                else{
                    iniFile.DeleteCommentInSection(putKeys,putComment);
                    iniFile.WriteFile();
                }
                break;

            case 13:
                cout<<"Inserisci il nome della sezione da cui verranno eliminati i commenti: ";
                getline(cin,putKeys);
                iniFile.DeleteAllCommentsInSection(putKeys);
                iniFile.WriteFile();
                break;

            case 14:
                iniFile.DeleteHeaderComments();
                iniFile.WriteFile();
                break;

            case 15:
                cout<<"Inserisci il numero del commento dell'intestazione da eliminare: ";
                cin>>putComment;
                if(cin.fail()){
                    cout<<"Hai inserito un input sbagliato!";
                    cin.clear();
                    ans=1;
                    break;
                }
                else if(putComment > iniFile.NumHeaderComments())
                    cout<<"Hai inserito un numero di commento che non esiste!"<<endl;
                else
                {
                    iniFile.DeleteHeaderComment(putComment);
                    iniFile.WriteFile();
                }
                break;

            case 16:
                iniFile.toString();
                break;

            case 17:
                cout<<"Scegli il nome che vuoi dare al tuo nuovo file: ";
                getline(cin,putString);
                cout<<"Scegli l'estensione da dare al tuo nuovo file: ";
                getline(cin,putKeys);
                fileName = putString + "." + putKeys;
                cout<<"\nNome del file: "<<fileName<<endl;
                iniFile.setPath("/home/samuel/Documenti/Università/Lab di Programmazione/FileINIProject/Files/"+fileName);
                iniFile.WriteFile();
                cout<<"\nFile salvato correttamente!"<<endl;
                break;

            case 18:
                //Path Lavoro: C:\Users\sbruno\Documents\Samuel\Varie\Uni\Lab Programmazione\FileINIProject\Files\ini_test.ini
                cout<<"Inserisci la path dove è presente il file. Non bisogna inserire nella path anche il nome del file ma solo la sua locazione.";
                cout<<"Inserisci: ";
                getline(cin,putString);
                iniFile.setPath(putString + "/" + fileName);
                iniFile.WriteFile();
                cout<<"\nPath cambiata correttamente!"<<endl;
                break;
        }
    }
   return 0;
}

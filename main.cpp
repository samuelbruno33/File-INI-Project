//
// Created by sbruno on 09/07/2019.
//

#include "CIniFile.h"

using namespace std;

int main()
{
    int ans=0,choice,type_choice,putComment,defVal;
    string putString,putKeys,insValue,jumpString,defPath;

    cout<<"\n"
          "\n"
          "----------------------------------------------------------------------------------------------------\n"
          "___________.__.__           .___ _______  .___  __________                   __               __   \n"
          "\\_   _____/|__|  |   ____   |   |\\      \\ |   | \\______   \\_______  ____    |__| ____   _____/  |_ \n"
          " |    __)  |  |  | _/ __ \\  |   |/   |   \\|   |  |     ___/\\_  __ \\/  _ \\   |  |/ __ \\_/ ___\\   __\\\n"
          " |     \\   |  |  |_\\  ___/  |   /    |    \\   |  |    |     |  | \\(  <_> )  |  \\  ___/\\  \\___|  |  \n"
          " \\___  /   |__|____/\\___  > |___\\____|__  /___|  |____|     |__|   \\____/\\__|  |\\___  >\\___  >__|  \n"
          "     \\/                 \\/              \\/                              \\______|    \\/     \\/      \n"
          "----------------------------------------------------------------------------------------------------\n"
          ""<<endl;

    CIniFile iniFile;
    iniFile.ReadFile();

redo_label:
    cout<<"Default path: "<<iniFile.getPath()<<endl;
    cout<<"\nVuoi inserire una nuova path di locazione del tuo file INI? <0-no 1-si>: ";
    cin>>defVal;
    getline(cin, jumpString);
    if(cin.fail() || defVal >= 2){
        cout<<"Hai inserito un input sbagliato!"<<endl;
        cin.clear();
        getline(cin, jumpString);
        goto redo_label;
    }
    if(defVal == 1)
        goto case_label;

    while(ans==0)
    {
        cout<<"\n---------MENU'---------\n";
        cout<<"0)Esci dal programma\n";
        cout<<"1)Aggiungi commento d'intestazione\n";
        cout<<"2)Aggiungi sezione\n";
        cout<<"3)Aggiungi o modifica valore all'interno di una sezione\n";
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
        cout<<"17)Cambia la path del file\n";
        cout<<"18)Rinomina il file\n";
        cout<<"\n";

        cout<<"Inserisci la tua scelta:";
        cin>>choice;

        //Salta la riga per problemi di inserimento del carattere con il cin, poichè una volta preso l'input (di un solo carattere
        //alla volta), il cin a fine riga di input mette uno /n che sballa la visualizzazione e gli input successivi presenti nei case.
        getline(cin, jumpString);

        switch(choice)
        {
            default:cout<<"Attenzione! Stai per uscire dal programma...Attendi!"<<endl;
                cout<<"\n";
                sleep(1);
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
                cout<<"Inserisci il nome della sezione da modificare. Se si inserisce una nome della sezione non esistente ne verrà creata una nuova."<<endl;
                cout<<"Inserisci: ";
                getline(cin,putKeys);
                cout<<"Inserisci il nome del parametro da porre all'interno di "<<putKeys<<": ";
                getline(cin,putString);
                cout<<"Vuoi inserire una stringa, un intero, un float o un booleano? <1-String,2-Int,3-Float,4-Bool>: ";
                cin>>type_choice;
                getline(cin, jumpString);
                if(cin.fail()){
                    cout<<"\nHai inserito un input sbagliato!"<<endl;
                    cin.clear();
                    getline(cin, jumpString);
                }
                else
                {
                    cout<<"Inserisci il valore da immettere all'interno di "<<putString<<": ";
                    getline(cin,insValue);
                    iniFile.Type_Choice_SetValue(type_choice,putKeys,putString,insValue);
                    iniFile.WriteFile();
                }
                break;

            case 4:
                cout<<"Inserisci la sezione dove verrà scritto il commento: ";
                getline(cin,putKeys);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                    cout<<"\nNome sezione non esistente!"<<endl;
                else
                {
                    cout<<"Inserisci il commento da porre all'interno di "<<putKeys<<": ";
                    getline(cin,putString);
                    iniFile.AddKeyCommentInSection(putKeys,putString);
                    iniFile.WriteFile();
                    cout<<"Inserimento avvenuto con successo!"<<endl;
                }
                break;

            case 5:
                cout<<"Inserisci la sezione che vuoi visualizzare: ";
                getline(cin,putKeys);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                    cout<<"\nNome sezione non esistente!"<<endl;
                else
                    iniFile.GetValuesInSection(iniFile.FindSection(putKeys));
                break;

            case 6:
                cout<<"Inserisci la sezione di cui vuoi visualizzare i dati: ";
                getline(cin,putKeys);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                    cout<<"\nNome sezione non esistente!"<<endl;
                else
                {
                    cout<<"Inserisci il nome del parametro da cercare all'interno di "<<putKeys<<": ";
                    getline(cin,putString);
                    if(iniFile.FindValue(iniFile.FindSection(putKeys),putString) == iniFile.noID)
                        cout<<"\nNome parametro non esistente!"<<endl;
                    else
                    {
                        cout<<"Stai cercando una stringa, un intero, un float o un booleano? <1-String,2-Int,3-Float,4-Bool>: ";
                        cin>>type_choice;
                        getline(cin, jumpString);
                        if(cin.fail()){
                            cout<<"\nHai inserito un input sbagliato!"<<endl;
                            cin.clear();
                            getline(cin, jumpString);
                        }
                        else
                        {
                            cout<<"Inserisci il valore di default nel caso non esistesse il parametro e la sezione da cercare: ";
                            getline(cin,insValue);
                            iniFile.Type_Choice_GetValue(type_choice,putKeys,putString,insValue);
                        }
                    }
                }
                break;

            case 7:
                cout<<"Inserisci la sezione da cui vuoi visualizzare il commento: ";
                getline(cin,putKeys);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                    cout<<"\nNome sezione non esistente!"<<endl;
                else
                {
                    cout<<"Inserisci il numero del relativo commento che vuoi visualizzare: ";
                    cin>>putComment;
                    if(cin.fail()){
                        cout<<"\nHai inserito un input sbagliato!"<<endl;
                        cin.clear();
                        getline(cin, jumpString);
                    }
                    else if(putComment >= iniFile.NumKeyCommentsInSection(putKeys))
                        cout<<"\nHai inserito un numero di commento che non esiste!"<<endl;
                    else
                        cout<<";"<<iniFile.GetKeyComment(putKeys,putComment)<<endl;
                }
                break;

            case 8:
                iniFile.GetAllHeaderComments();
                break;

            case 9:
                cout<<"Inserisci il numero del relativo commento d'intestazione che vuoi visualizzare. Il numero del commento da inserire inizia da 0."<<endl;
                cout<<"Inserisci: ";
                cin>>putComment;
                if(cin.fail()){
                    cout<<"\nHai inserito un input sbagliato!"<<endl;
                    cin.clear();
                    getline(cin, jumpString);
                }
                else if(putComment >= iniFile.NumHeaderComments())
                    cout<<"\nHai inserito un numero di commento che non esiste!"<<endl;
                else
                    cout<<";"<<iniFile.GetHeaderComment(putComment)<<endl;
                break;

            case 10:
                cout<<"Inserisci il nome della sezione da eliminare: ";
                getline(cin,putString);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                    cout<<"\nNome sezione non esistente!"<<endl;
                else
                {
                    iniFile.DeleteSection(putString);
                    iniFile.WriteFile();
                }
                break;

            case 11:
                cout<<"Inserisci il nome della sezione: ";
                getline(cin,putKeys);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                    cout<<"\nNome sezione non esistente!"<<endl;
                else
                {
                    cout<<"Inserisci il parametro di "<<putKeys<<" da eliminare: ";
                    getline(cin,putString);
                    if(iniFile.FindValue(iniFile.FindSection(putKeys),putString) == iniFile.noID)
                        cout<<"\nNome parametro non esistente!"<<endl;
                    else
                    {
                        iniFile.DeleteValueInSection(putKeys,putString);
                        iniFile.WriteFile();
                    }
                }
                break;

            case 12:
                cout<<"Inserisci il nome della sezione: ";
                getline(cin,putKeys);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                    cout<<"\nNome sezione non esistente!"<<endl;
                else
                {
                    cout<<"Inserisci il numero del commento da eliminare: ";
                    cin>>putComment;
                    if(cin.fail()){
                        cout<<"\nHai inserito un input sbagliato!"<<endl;
                        cin.clear();
                        getline(cin, jumpString);
                    }
                    else if(putComment >= iniFile.NumKeyCommentsInSection(putKeys))
                        cout<<"\nHai inserito un numero di commento che non esiste!"<<endl;
                    else
                    {
                        iniFile.DeleteCommentInSection(putKeys,putComment);
                        iniFile.WriteFile();
                    }
                }
                break;

            case 13:
                cout<<"Inserisci il nome della sezione da cui verranno eliminati i commenti: ";
                getline(cin,putKeys);
                if(iniFile.FindSection(putKeys) == iniFile.noID)
                    cout<<"\nNome sezione non esistente!"<<endl;
                else
                {
                    iniFile.DeleteAllCommentsInSection(putKeys);
                    iniFile.WriteFile();
                }
                break;

            case 14:
                iniFile.DeleteAllHeaderComments();
                iniFile.WriteFile();
                break;

            case 15:
                cout<<"Inserisci il numero del commento dell'intestazione da eliminare: ";
                cin>>putComment;
                if(cin.fail()){
                    cout<<"\nHai inserito un input sbagliato!"<<endl;
                    cin.clear();
                    getline(cin, jumpString);
                }
                else if(putComment >= iniFile.NumHeaderComments())
                    cout<<"\nHai inserito un numero di commento che non esiste!"<<endl;
                else
                {
                    iniFile.DeleteHeaderComment(putComment);
                    iniFile.WriteFile();
                }
                break;

            case 16:
                iniFile.toString();
                break;

        case_label:
            case 17:
                defPath = iniFile.ChangePath();
                iniFile = CIniFile(defPath,iniFile.getFileName());
                iniFile.ReadFile();
                break;

            case 18:
                cout << "Scegli il nome che vuoi dare al file (senza estensione): ";
                getline(cin, putString);
                cout << "Scegli l'estensione da dare al file: ";
                getline(cin, putKeys);
                iniFile.RenameFileName(putString,putKeys);
                break;
        }
    }
   return 0;
}
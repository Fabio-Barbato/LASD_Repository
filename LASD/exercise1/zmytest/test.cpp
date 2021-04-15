
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include "test.hpp"



/* ************************************************************************** */


void myTest(){
    uint sceltaStrutturaDati;
    ulong dimensioneStruttura;
    std::cout<<"Test della libreria in esecuzione..."<<std::endl;
    std::cout<<"Scegliere una struttura dati:\n1)Vettore;\n2)Lista;\n\nScegli: ";
    std::cin>>sceltaStrutturaDati;
    std::cout<<"Inserire dimensione della struttura: ";
    std::cin>>dimensioneStruttura;
    if(sceltaStrutturaDati==1)
        CreazioneVector(dimensioneStruttura);
    else if(sceltaStrutturaDati==2){
        CreazioneList(dimensioneStruttura);
    }


}

void CreazioneList(ulong dimensioneStruttura){
    int sceltaDati;
    std::cout<<"Scegliere su quali dati lavorare:\n1)Interi;\n2)Decimali;\n3)Stringhe\n\nScegli: ";
    std::cin>>sceltaDati;

    if(sceltaDati==1){
        lasd::List<int> list;   //costruzione lista di interi
        srand(time(NULL));
        for(int i=1;i<=dimensioneStruttura;i++){
            list.InsertAtBack(rand()%50);
        }
        MenuList(list);
    }
    else if(sceltaDati==2){
        lasd::List<float> list;   //costruzione list di float
        srand(time(NULL));
        for(int i=1;i<=dimensioneStruttura;i++)
            list.InsertAtBack(float(rand())/float(RAND_MAX));
        MenuList(list);
    }
    else if(sceltaDati==3){
        lasd::List<std::string> list;  //costruzione list di stringhe
        for(int i=1;i<=dimensioneStruttura;i++)
            list.InsertAtBack(GenerateString());
        MenuList(list);
    }

}

void CreazioneVector(ulong dimensioneStruttura){
    int sceltaDati;
    std::cout<<"Scegliere su quali dati lavorare:\n1)Interi;\n2)Decimali;\n3)Stringhe\n\nScegli: ";
    std::cin>>sceltaDati;

    if(sceltaDati==1){
        lasd::Vector<int> vector(dimensioneStruttura);   //costruzione vector di interi
        srand(time(NULL));
        for(int i=0;i<vector.Size();i++)
            vector[i]=rand()%50;
        MenuVector(vector);
    }
    else if(sceltaDati==2){
        lasd::Vector<float> vector(dimensioneStruttura);   //costruzione vector di float
        srand(time(NULL));
        for(int i=0;i<vector.Size();i++)
            vector[i]=float(rand())/float(RAND_MAX);
        MenuVector(vector);
    }
    else if(sceltaDati==3){
        lasd::Vector<std::string> vector(dimensioneStruttura);  //costruzione vector di stringhe
        for(int i=0;i<vector.Size();i++)
            vector[i]=GenerateString();
        MenuVector(vector);
    }

}

template <typename Data>
void MenuList(lasd::List<Data> list){
    int sceltaOp;

    do {
        std::cout<< "Quali operazioni vuoi effettuare?:\n1)Visualizza elemento iniziale;\n2)Visualizza elemento finale;\n3)Visualizza un elemento di uno specifico indice"<< std::endl;
        std::cout<< "4)Visualizza tutti gli elementi della struttura;\n5)Controlla l'esistenza di un valore;\n6)Operazioni speciali;\n7)Rimuovi un elemento in testa;\n8)Rimuovi un elemento in testa (con lettura);\nScegli: ";
        std::cin >> sceltaOp;
        if (sceltaOp >= 1 && sceltaOp <= 5)
            OperazioniGenericheList(sceltaOp, list);
        else if(sceltaOp==6) {
            OperazioniSpecialiList(&list);
        } else if (sceltaOp==7){
            list.RemoveFromFront();
            std::cout<<"Elemento rimosso!"<<std::endl;
        }else if(sceltaOp==8){
            std::cout<<"Elemento rimosso: "<<list.FrontNRemove()<<std::endl;
        }
    }while (sceltaOp>=1 && sceltaOp<=10);
}

template <typename Data>
void MenuVector(lasd::Vector<Data> vector){
    int sceltaOp;

    do {
        std::cout<< "Quali operazioni vuoi effettuare?:\n1)Visualizza elemento iniziale;\n2)Visualizza elemento finale;\n3)Visualizza un elemento di uno specifico indice"<< std::endl;
        std::cout<< "4)Visualizza tutti gli elementi della struttura;\n5)Controlla l'esistenza di un valore;\n6)Operazioni speciali;\n7)Resize;\nScegli: ";
        std::cin >> sceltaOp;
        if (sceltaOp >= 1 && sceltaOp <= 5)
            OperazioniGenericheVector(sceltaOp, vector);
        else if(sceltaOp==6) {
            OperazioniSpecialiVector(&vector);
        } else if (sceltaOp==7){
            unsigned long n;
            std::cout<<"Inserisci la nuova dimensione del vettore: ";
            std::cin>>n;
            vector.Resize(n);
        }
    }while (sceltaOp>=1 && sceltaOp<=7);
}

template <typename Data>
void OperazioniGenericheList(int scelta, lasd::List<Data> list){

    if(scelta==1){
        std::cout<<"Elemento iniziale: "<<list.Front()<<std::endl;
    } else if (scelta==2){
        std::cout<<"Elemento finale: "<<list.Back()<<std::endl;
    } else if (scelta==3){
        int index;
        std::cout<<"Seleziona l'indice dell'elemento da visualizzare (da 1 a "<<list.Size()<<"): ";
        std::cin>>index;
        std::cout<<"Elemento di indice "<<index<<": "<<list[index]<<std::endl;
    } else if (scelta==4){
        list.MapPreOrder(&MapPrint<Data>, nullptr);
    }else if(scelta==5){
        Data valore;
        std::cout<<"Inserisci un valore per scoprire se si trova nel tuo vettore: ";
        std::cin>>valore;
        if(list.Exists(valore))
            std::cout<<valore<<" si trova nella tua lista"<<std::endl;
        else
            std::cout<<valore<<" non si trova nella tua lista"<<std::endl;
    }


}

template <typename Data>
void OperazioniGenericheVector(int scelta, lasd::Vector<Data> vector){

    if(scelta==1){
        std::cout<<"Elemento iniziale: "<<vector.Front()<<std::endl;
    } else if (scelta==2){
        std::cout<<"Elemento finale: "<<vector.Back()<<std::endl;
    } else if (scelta==3){
        int index;
        std::cout<<"Seleziona l'indice dell'elemento da visualizzare (da 0 a "<<vector.Size()-1<<"): ";
        std::cin>>index;
        std::cout<<"Elemento di indice "<<index<<": "<<vector[index]<<std::endl;
    } else if (scelta==4){
        vector.MapPreOrder(&MapPrint<Data>, nullptr);
    }else if(scelta==5){
        Data valore;
        std::cout<<"Inserisci un valore per scoprire se si trova nel tuo vettore: ";
        std::cin>>valore;
        if(vector.Exists(valore))
            std::cout<<valore<<" si trova nel tuo vettore"<<std::endl;
        else
            std::cout<<valore<<" non si trova nel tuo vettore"<<std::endl;
    }


}

void OperazioniSpecialiList(lasd::List<int>* list){
    int sceltaOp;
    std::cout<< "Quali operazioni vuoi effettuare?:\n1)Raddoppia tutti gli elementi;\n2)Restituisci la somma di tutti i numeri minori di un numero da te inserito;\n3)Inserisci un valore in testa;\n4)Inserisci un valore in coda;\nScegli: ";
    std::cin>>sceltaOp;
    if(sceltaOp==1){
        list->MapPreOrder(&MapRedouble, nullptr);
    }else if(sceltaOp==2){
        int somma=0;
        int n;
        std::cout<< "Inserisci un numero: ";
        std::cin>>n;
        list->FoldPreOrder(&FoldSomma, &n, &somma);
        std::cout<<"La somma dei numeri minori di "<<n<<" : "<<somma<<std::endl;
    }else if(sceltaOp==3){
        int n;
        std::cout<<"Inserisci un valore da inserire alla testa: ";
        std::cin>>n;
        list->InsertAtFront(n);
    } else if (sceltaOp==4){
        int n;
        std::cout<<"Inserisci un valore da inserire alla coda: ";
        std::cin>>n;
        list->InsertAtBack(n);
    }

}

void OperazioniSpecialiList(lasd::List<float>* list){
    int sceltaOp;
    std::cout<< "Quali operazioni vuoi effettuare?:\n1)1)Eleva tutti gli elementi al quadrato;\n2)Restituisci il prodotto di tutti i numeri maggiori di un numero da te inserito;\n3)Inserisci un valore in testa;\n4)Inserisci un valore in coda;\nScegli: ";
    std::cin>>sceltaOp;
    if(sceltaOp==1){
        list->MapPreOrder(&MapPotenza, nullptr);
    }else if(sceltaOp==2){
        float prodotto=0;
        int n;
        std::cout<< "Inserisci un numero: ";
        std::cin>>n;
        list->FoldPreOrder(&FoldProdotto, &n, &prodotto);
        std::cout<<"Il prodotto dei numeri maggiori di "<<n<<" : "<<prodotto<<std::endl;
    } else if(sceltaOp==3){
        float n;
        std::cout<<"Inserisci un valore da inserire alla testa: ";
        std::cin>>n;
        list->InsertAtFront(n);
    } else if (sceltaOp==4){
        float n;
        std::cout<<"Inserisci un valore da inserire alla coda: ";
        std::cin>>n;
        list->InsertAtBack(n);
    }
}

void OperazioniSpecialiList(lasd::List<std::string>* list){
    int sceltaOp;
    std::cout<< "Quali operazioni vuoi effettuare?:\n1)Effettua uppercase su ogni stringa;\n2)Concatena tutte le stringhe di lunghezza minore o uguale di un numero da te inserito;\nScegli: ";
    std::cin>>sceltaOp;

    if(sceltaOp==1){
        list->MapPreOrder(&MapUppercase, nullptr);
    } else if(sceltaOp==2){
        std::string stringaConcat;
        int n;
        std::cout<< "Inserisci un numero: ";
        std::cin>>n;
        list->FoldPreOrder(&FoldConcat, &n, &stringaConcat);
        std::cout<<"Stringa concatenata "<<n<<" : "<<stringaConcat<<std::endl;
    } else if(sceltaOp==3){
        std::string n;
        std::cout<<"Inserisci un valore da inserire alla testa: ";
        std::cin>>n;
        list->InsertAtFront(n);
    } else if (sceltaOp==4){
        std::string n;
        std::cout<<"Inserisci un valore da inserire alla coda: ";
        std::cin>>n;
        list->InsertAtBack(n);
    }

}


void OperazioniSpecialiVector(lasd::Vector<int>* vector){
    int sceltaOp;
    std::cout<< "Quali operazioni vuoi effettuare?:\n1)Raddoppia tutti gli elementi;\n2)Restituisci la somma di tutti i numeri minori di un numero da te inserito;\nScegli: ";
    std::cin>>sceltaOp;
    if(sceltaOp==1){
        vector->MapPreOrder(&MapRedouble, nullptr);
    }else if(sceltaOp==2){
        int somma=0;
        int n;
        std::cout<< "Inserisci un numero: ";
        std::cin>>n;
        vector->FoldPreOrder(&FoldSomma, &n, &somma);
        std::cout<<"La somma dei numeri minori di "<<n<<" : "<<somma<<std::endl;
    }

}

void OperazioniSpecialiVector(lasd::Vector<float>* vector){
    int sceltaOp;
    std::cout<< "Quali operazioni vuoi effettuare?:\n1)Eleva tutti gli elementi al quadrato;\n2)Restituisci il prodotto di tutti i numeri maggiori di un numero da te inserito;\nScegli: ";
    std::cin>>sceltaOp;
    if(sceltaOp==1){
        vector->MapPreOrder(&MapPotenza, nullptr);
    }else if(sceltaOp==2){
        float prodotto=0;
        int n;
        std::cout<< "Inserisci un numero: ";
        std::cin>>n;
        vector->FoldPreOrder(&FoldProdotto, &n, &prodotto);
        std::cout<<"Il prodotto dei numeri maggiori di "<<n<<" : "<<prodotto<<std::endl;
    }
}

void OperazioniSpecialiVector(lasd::Vector<std::string>* vector){
    int sceltaOp;
    std::cout<< "Quali operazioni vuoi effettuare?:\n1)Effettua uppercase su ogni stringa;\n2)Concatena tutte le stringhe di lunghezza minore o uguale di un numero da te inserito;\nScegli: ";
    std::cin>>sceltaOp;

    if(sceltaOp==1){
        vector->MapPreOrder(&MapUppercase, nullptr);
    } else if(sceltaOp==2){
        std::string stringaConcat;
        int n;
        std::cout<< "Inserisci un numero: ";
        std::cin>>n;
        vector->FoldPreOrder(&FoldConcat, &n, &stringaConcat);
        std::cout<<"Stringa concatenata "<<n<<" : "<<stringaConcat<<std::endl;
    }

}

void FoldSomma(const int& dat, const void* n, void* somma)  noexcept {
    if(dat<*(int*)n)
        *(int*)somma= *(int*)somma+dat;
}

void FoldProdotto(const float& dat, const void* n, void* prodotto)  noexcept {
    if(dat<*(int*)n)
        *(float*)prodotto= *(float*)prodotto+dat;
}

void FoldConcat(const std::string& dat, const void* n, void* stringaConcat)  noexcept{
    if(dat.length()<*(int*)n)
        *(std::string*)stringaConcat= *(std::string*)stringaConcat+dat;
}

template <typename Data>
void MapPrint(Data& valueToPrint, void* null){
    std::cout<<valueToPrint<<std::endl;
}


void MapRedouble(int& value, void* par){
    value = value * 2;
}

void MapPotenza(float& value, void* par){
    value = value * value;
}

void MapUppercase(std::string& value, void* par){
    std::for_each(value.begin(), value.end(), [](char & c) {
        c = ::toupper(c);
    });
}

std::string GenerateString(){
    std::string string;

    for(int i=0;i<10;i++){
        char charOfString(rand()%25+97);
        string.push_back(charOfString);
    }

    return string;
}

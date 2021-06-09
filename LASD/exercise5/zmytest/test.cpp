#include <iostream>
#include "test.hpp"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace lasd;

void myTest(){
  int sceltaDati;
  int scelta_menu;
  int righe;
  int col;
  int scelta_struttura;
  std::cout<<"Scegliere su quali dati lavorare:\n1)Interi;\n2)Decimali;\n3)Stringhe\n\nScegli: ";
  std::cin>>sceltaDati;
  std::cout<<"Scegliere numero righe: ";
  std::cin>>righe;
  std::cout<<"Scegliere numero colonne: ";
  std::cin>>col;

  if(sceltaDati==1){
    std::cout << "Scegli struttura:\n1)Vettoriale;\n2)CSR;\nScegli:  ";
    std::cin >> scelta_struttura;
    if (scelta_struttura==1) {
      MatrixVec<int> matvec(righe,col);
      PopolazioneRandom(matvec);
      do {
        std::cout << "Vuoi effettuare operazioni generiche o Map/Fold?\n\nScegli: ";
        std::cin >> scelta_menu;
        if (scelta_menu==1) {
          Menu(matvec);
        }
        else if(scelta_menu==2){
          OpSpeciali(matvec);
        }
      } while(scelta_menu==1 || scelta_menu==2);
    } else if (scelta_struttura==2) {
      MatrixCSR<int> matcsr(righe,col);
      PopolazioneRandom(matcsr);
      do {
        std::cout << "Vuoi effettuare operazioni generiche o Map/Fold?\n\nScegli: ";
        std::cin >> scelta_menu;
        if (scelta_menu=1)
          Menu(matcsr);
        else if(scelta_menu==2){
          OpSpeciali(matcsr);
        }
      } while(scelta_menu==1 || scelta_menu==2);
    }

  }
  else if(sceltaDati==2){
    std::cout << "Scegli struttura:\n1)Vettoriale;\n2)CSR;\nScegli:  ";
    std::cin >> scelta_struttura;
    if (scelta_struttura==1) {
      MatrixVec<float> matvec(righe,col);
      PopolazioneRandom(matvec);
      do {
        std::cout << "Vuoi effettuare operazioni generiche o Map/Fold?\n\nScegli: ";
        std::cin >> scelta_menu;
        if (scelta_menu==1) {
          Menu(matvec);
        }
        else if(scelta_menu==2){
          OpSpeciali(matvec);
        }
      } while(scelta_menu==1 || scelta_menu==2);
    } else if (scelta_struttura==2) {
      MatrixCSR<float> matcsr(righe,col);
      PopolazioneRandom(matcsr);
      do {
        std::cout << "Vuoi effettuare operazioni generiche o Map/Fold?\n\nScegli: ";
        std::cin >> scelta_menu;
        if (scelta_menu==1) {
          Menu(matcsr);
        }
        else if(scelta_menu==2){
          OpSpeciali(matcsr);
        }
      } while(scelta_menu==1 || scelta_menu==2);
    }
  }
  else if(sceltaDati==3){
    std::cout << "Scegli struttura:\n1)Vettoriale;\n2)CSR;\nScegli:  ";
    std::cin >> scelta_struttura;
    if (scelta_struttura==1) {
      MatrixVec<std::string> matvec(righe,col);
      PopolazioneRandom(matvec);
      do {
        std::cout << "Vuoi effettuare operazioni generiche o Map/Fold?\n\nScegli: ";
        std::cin >> scelta_menu;
        if (scelta_menu==1) {
          Menu(matvec);
        }
        else if(scelta_menu==2){
          OpSpeciali(matvec);
        }
      } while(scelta_menu==1 || scelta_menu==2);
    } else if (scelta_struttura==2) {
      MatrixCSR<std::string> matcsr(righe,col);
      PopolazioneRandom(matcsr);
      do {
        std::cout << "Vuoi effettuare \n1)Operazioni generiche\n2)Map/Fold?\n\nScegli: ";
        std::cin >> scelta_menu;
        if (scelta_menu==1) {
          Menu(matcsr);
        }
        else if(scelta_menu==2){
          OpSpeciali(matcsr);
        }
      } while(scelta_menu==1 || scelta_menu==2);
    }
  }
}


void PopolazioneRandom(Matrix<int>& mat){
  int scelta;
  ulong num_elem;
  std::cout << "Vuoi riempire la tua matrice con inserimenti random?\n1)Si;\n2)No" << '\n';
  std::cout << "Scegli: ";
  std::cin >> scelta;
  ulong inserimenti=0;
  ulong r;
  ulong c;
  if (scelta==1) {
    std::cout << "Quanti elementi vuoi inserire?: ";
    std::cin >> num_elem;
    while (inserimenti<num_elem) {
      try{
        r=(rand()%mat.RowNumber());
        c=(rand()%mat.ColumnNumber());
        mat(r,c) = rand()%100;
        inserimenti++;
        std::cout << "Inserito elemento "<< ReadData(mat,r,c)<<" nella cella ("<<r<<","<<c<<")." << '\n';
      }catch(std::out_of_range e){
        std::cout << "Non esiste la cella ("<<r<<","<<c<<")!" << '\n';
      }
    }
  }
}


void PopolazioneRandom(Matrix<float>& mat){
  int scelta;
  ulong num_elem;
  std::cout << "Vuoi riempire la tua matrice con inserimenti random?\n1)Si;\n2)No" << '\n';
  std::cout << "Scegli: ";
  std::cin >> scelta;
  ulong inserimenti=0;
  ulong r;
  ulong c;
  if (scelta==1) {
    std::cout << "Quanti elementi vuoi inserire?: ";
    std::cin >> num_elem;
    while (inserimenti<num_elem) {
      try{
        r=(rand()%mat.RowNumber());
        c=(rand()%mat.ColumnNumber());
        mat(r,c) = rand()%100;
        inserimenti++;
        std::cout << "Inserito elemento "<< ReadData(mat,r,c)<<" nella cella ("<<r<<","<<c<<")." << '\n';
      }catch(std::out_of_range e){
        std::cout << "Non esiste la cella ("<<r<<","<<c<<")!" << '\n';
      }
    }
  }
}


void PopolazioneRandom(Matrix<std::string>& mat){
  int scelta;
  ulong num_elem;
  std::cout << "Vuoi riempire la tua matrice con inserimenti random?\n1)Si;\n2)No" << '\n';
  std::cout << "Scegli: ";
  std::cin >> scelta;
  ulong inserimenti=0;
  ulong r;
  ulong c;
  if (scelta==1) {
    std::cout << "Quanti elementi vuoi inserire?: ";
    std::cin >> num_elem;
    while (inserimenti<num_elem) {
      try{
        r=(rand()%mat.RowNumber());
        c=(rand()%mat.ColumnNumber());
        mat(r,c) = GenerateString();
        inserimenti++;
        std::cout << "Inserito elemento "<< ReadData(mat,r,c)<<" nella cella ("<<r<<","<<c<<")." << '\n';
      }catch(std::out_of_range e){
        std::cout << "Non esiste la cella ("<<r<<","<<c<<")!" << '\n';
      }
    }
  }
}

template <typename Data>
void Menu(Matrix<Data>& mat){
  int scelta;
  ulong riga;
  ulong col;
  ulong num;
  Data elem;
   do{
     std::cout << "Scegliere l'operazione da effettuare:\n1)Visita PreOrder;\n2)Visita PostOrder;\n3)Esistenza di una cella;\n4)Visualizza elemento in una cella;\n5)Ridimensiona righe;\n6)Ridimensiona colonne;\n7)Empty;\n8)Size;\n9)Clear;\n10)Inserimento;\n11)Esistenza di un valore;\n12)Numero righe;\n13)Numero colonne;\n\nScegli: ";
     std::cin>>scelta;
    if (scelta==1) {
      mat.MapPreOrder(&MapPrint<Data>, nullptr);
    } else if (scelta==2) {
      mat.MapPostOrder(&MapPrint<Data>, nullptr);
    }else if (scelta==3) {
      std::cout << "Inserisci riga: ";
      std::cin >> riga;
      std::cout << "Inserisci colonna: ";
      std::cin >> col;
      std::cout << "La cella ";
      if (mat.ExistsCell(riga,col)) {
        std::cout << "esiste!"<<'\n';
      }else
        std::cout << "non esiste!"<<'\n';
    }else if (scelta==4) {
      std::cout << "Inserisci riga: ";
      std::cin >> riga;
      std::cout << "Inserisci colonna: ";
      std::cin >> col;
      try{
        std::cout << "Elemento: "<<ReadData(mat, riga, col) << '\n';
      }catch(std::out_of_range e){
        std::cout << "Fuori dal range!" << '\n';
      }catch(std::length_error e){
        std::cout << "Elemento non presente!" << '\n';
      }

    }else if (scelta==5) {
      std::cout << "Inserisci nuova riga: ";
      std::cin >> num;
      mat.RowResize(num);
    }else if (scelta==6) {
      std::cout << "Inserisci nuova colonna: ";
      std::cin >> num;
      mat.ColumnResize(num);
    }else if (scelta==7) {
      std::cout << "La matrice ";
      if (mat.Empty()) {
        std::cout << "è vuota!"<<'\n';
      }else
        std::cout << "non è vuota!"<<'\n';
    }else if (scelta==8) {
      std::cout << "Size: "<<mat.Size() << '\n';
    }else if (scelta==9) {
      mat.Clear();
      std::cout << "Matrice pulita!"<< '\n';
    }else if (scelta==10) {
      try{
        std::cout << "Scegli elemento da inserire: ";
        std::cin >> elem;
        std::cout << "In quale riga?: ";
        std::cin >> riga;
        std::cout << "In quale colonna?: ";
        std::cin >> col;
        mat(riga,col) = elem;
        std::cout << "Elemento inserito!" << '\n';
      }catch(std::out_of_range e){
        std::cout << "La cella selezionata non esiste!" << '\n';
      }
    }else if(scelta==11){
      std::cout << "Elemento da cercare: ";
      std::cin >> elem;
      std::cout << "L'elemento inserito ";
      if (mat.Exists(elem)) {
        std::cout << "esiste!"<<'\n';
      }else
        std::cout << "non esiste!"<<'\n';
    }else if(scelta==12){
      std::cout << "Numero righe: "<<mat.RowNumber() << '\n';
    }else if(scelta==13){
      std::cout << "Numero colonne: "<<mat.ColumnNumber() << '\n';
    }
  }while (scelta>0 && scelta<14);

}


void OpSpeciali(Matrix<int>& mat){
  int scelta;
  std::cout << "1)Prodotto per numeri minori di n;\n2)Moltiplica gli elementi per 2\n\nScegli: ";
  std::cin>>scelta;

  if (scelta == 1) {
    int n;
    int prod = 1;
    std::cout << "Inserisci numero: ";
    std::cin >> n;
    mat.FoldPreOrder(&FoldProdotto, &n, &prod);
    std::cout << "Prodotto: "<<prod << '\n';
  } else if (scelta == 2) {
    mat.MapPostOrder(&MapRedouble, nullptr);
    std::cout << "Matrice modificata: ";
    mat.MapPreOrder(&MapPrint<int>, nullptr);
  }

}

void OpSpeciali(Matrix<float>& mat){
  int scelta;
  std::cout << "1)Somma per numeri maggiori di n;\n2)Eleva gli elementi al cubo\n\nScegli: ";
  std::cin>>scelta;

  if (scelta == 1) {
    int n;
    float sum = 0;
    std::cout << "Inserisci numero: ";
    std::cin >> n;
    mat.FoldPreOrder(&FoldSomma, &n, &sum);
    std::cout << "Somma: "<<sum << '\n';
  } else if (scelta == 2) {
    mat.MapPostOrder(&MapPotenza, nullptr);
    std::cout << "Matrice modificata: ";
    mat.MapPreOrder(&MapPrint<float>, nullptr);
  }
}


  void OpSpeciali(Matrix<std::string>& mat){
    int scelta;
    std::string string_concat;
    std::cout << "1)Concatenazione per le stringhe con lunghezza minore o uguale a n;\n2)Concatenazione in testa di una specifica stringa\n\nScegli: ";
    std::cin>>scelta;

    if (scelta == 1) {
      int n;
      std::cout << "Inserisci numero: ";
      std::cin >> n;
      mat.FoldPreOrder(&FoldConcat, &n, &string_concat);
      std::cout << "Stringa concatenata: "<<string_concat << '\n';
    } else if (scelta == 2) {
      std::cout << "Inserisci stringa: ";
      std::cin >> string_concat;
      mat.MapPreOrder(&MapConcat, &string_concat);
      std::cout << "Matrice modificata: ";
      mat.MapPreOrder(&MapPrint<std::string>, nullptr);
      std::cout << '\n';
    }
  }


    template <typename Data>
    void MapPrint(const Data& dat, void* _) {
      std::cout << dat << " ";
    }

    void MapRedouble(int& value, void* par){
        value = value * 2;
    }

    void MapPotenza(float& value, void* par){
        value = (-value) * (-value) * (-value);
    }

    void MapConcat(std::string& value, void* stringaConcat){
      value= *(std::string*)stringaConcat+value;
    }


    void FoldSomma(const float& dat, const void* n, void* somma)  noexcept {
        if(dat>*(int*)n)
            *(float*)somma= *(float*)somma+dat;
    }

    void FoldProdotto(const int& dat, const void* n, void* prodotto)  noexcept {
        if(dat<*(int*)n)
            *(int*)prodotto= *(int*)prodotto*dat;
    }

    void FoldConcat(const std::string& dat, const void* n, void* stringaConcat)  noexcept{
        if(dat.length()<=*(int*)n)
            *(std::string*)stringaConcat= *(std::string*)stringaConcat+dat;
    }

    std::string GenerateString(){
        std::string string;

        for(int i=0;i<10;i++){
            char charOfString(rand()%25+97);
            string.push_back(charOfString);
        }

        return string;
    }

    template <typename Data>
    const Data& ReadData(const Matrix<Data>& mat, ulong i, ulong j){
        return mat(i, j);
    }

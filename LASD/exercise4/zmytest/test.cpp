#include <iostream>
#include "test.hpp"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace lasd;

void myTest(){
  int sceltaDati;
  int scelta_menu;
  int dimensioneStruttura;
  std::cout<<"Scegliere su quali dati lavorare:\n1)Interi;\n2)Decimali;\n3)Stringhe\n\nScegli: ";
  std::cin>>sceltaDati;
  std::cout<<"Scegliere dimensione albero: ";
  std::cin>>dimensioneStruttura;

  if(sceltaDati==1){
      Vector<int> vec(dimensioneStruttura);   //costruzione vec di interi
      srand(time(NULL));
      for(int i=0;i<dimensioneStruttura;i++){
          vec[i]=(rand()%100);
      }
      std::cout << "Vettore: ";
      for (ulong i = 0; i < dimensioneStruttura; i++) {
        std::cout<< vec[i]<<" ";
      }
      std::cout <<'\n';
      BST<int> bt(vec);

      do{
        std::cout << "1)Operazioni generiche;\n2)Operazioni map/fold\nScegli: ";
        std::cin >> scelta_menu;
        if (scelta_menu==1) {
          Menu(bt);
        } else if (scelta_menu==2) {
          OpSpecialiBinaryTree(bt);
        }
      }while(scelta_menu<3 && scelta_menu>0);

  }
  else if(sceltaDati==2){
      Vector<float> vec(dimensioneStruttura);   //costruzione vec di float
      srand(time(NULL));
      for(int i=0;i<dimensioneStruttura;i++){
          vec[i] = (float(rand())/float(RAND_MAX));
        }
        std::cout << "Vettore: ";
        for (ulong i = 0; i < dimensioneStruttura; i++) {
          std::cout<< vec[i]<<" ";
        }
        std::cout <<'\n';
      BST<float> bt(vec);
      do{
        std::cout << "1)Operazioni generiche;\n2)Operazioni map/fold\nScegli: ";
        std::cin >> scelta_menu;
        if (scelta_menu==1) {
          Menu(bt);
        } else if (scelta_menu==2) {
          OpSpecialiBinaryTree(bt);
        }
      }while(scelta_menu<3 && scelta_menu>0);
  }
  else if(sceltaDati==3){
      Vector<std::string> vec(dimensioneStruttura);  //costruzione vec di stringhe
      for(int i=0;i<dimensioneStruttura;i++)
          vec[i] = (GenerateString());

          std::cout << "Vettore: ";
          for (ulong i = 0; i < dimensioneStruttura; i++) {
            std::cout<< vec[i]<<" ";
          }
          std::cout <<'\n';
      BST<std::string> bt(vec);
      do{
        std::cout << "1)Operazioni generiche;\n2)Operazioni map/fold\nScegli: ";
        std::cin >> scelta_menu;
        if (scelta_menu==1) {
          Menu(bt);
        } else if (scelta_menu==2) {
          OpSpecialiBinaryTree(bt);
        }
      }while(scelta_menu<3 && scelta_menu>0);
  }
}

template <typename Data>
void Menu(BST<Data>& binarytree){
  int scelta;
  Data elem;
   do{
     std::cout << "Scegliere l'operazione da effettuare:\n1)Visita;\n2)Esistenza di un valore;\n3)Inserisci un elemento;\n4)Rimuovi un elemento;\n5)Rimuovi massimo;\n6)Rimuovi minimo;\n7)Leggi massimo;\n8)Leggi minimo;\n9)Leggi e rimuovi massimo;\n10)Leggi e rimuovi minimo;\n11)Rimuovi predecessore;\n12)Rimuovi successore;\n13)Leggi predecessore;\n14)Leggi successore;\n15)Leggi e rimuovi predecessore;\n16)Leggi e rimuovi successore;\n\nScegli: ";
     std::cin>>scelta;
    if (scelta==1) {
      VisitaBinaryTree(binarytree);
    } else if (scelta==2) {
      ExistBinaryTree(binarytree);
    }else if (scelta==3) {
      std::cout << "Inserisci elemento: ";
      std::cin >> elem;
      binarytree.Insert(elem);
    }else if (scelta==4) {
      std::cout << "Rimuovi elemento: ";
      std::cin >> elem;
      binarytree.Remove(elem);
      std::cout << "Rimosso!" << '\n';
    }else if (scelta==5) {
      binarytree.RemoveMax();
      std::cout << "Rimosso!" << '\n';
    }else if (scelta==6) {
      binarytree.RemoveMin();
      std::cout << "Rimosso!" << '\n';
    }else if (scelta==7) {
      std::cout << "Massimo: "<<binarytree.Max() << '\n';
    }else if (scelta==8) {
      std::cout << "Minimo: "<<binarytree.Min() << '\n';
    }else if (scelta==9) {
      std::cout << "Massimo: "<<binarytree.MaxNRemove() << '\n';
    }else if (scelta==10) {
      std::cout << "Minimo: "<<binarytree.MinNRemove() << '\n';
    }else if (scelta==11) {
      std::cout << "Predecessore di: ";
      std::cin >> elem;
      binarytree.RemovePredecessor(elem);
      std::cout << "Rimosso!" << '\n';
    }else if (scelta==12) {
      std::cout << "Successore di: ";
      std::cin >> elem;
      binarytree.RemoveSuccessor(elem);
      std::cout << "Rimosso!" << '\n';
    }else if (scelta==13) {
      std::cout << "Predecessore di: ";
      std::cin >> elem;
      std::cout << "Predecessore: "<<binarytree.Predecessor(elem) << '\n';
    }else if (scelta==14) {
      std::cout << "Successore di: ";
      std::cin >> elem;
      std::cout << "Successore: "<<binarytree.Successor(elem) << '\n';
    }else if (scelta==15) {
      std::cout << "Predecessore di: ";
      std::cin >> elem;
      std::cout << "Predecessore: "<<binarytree.PredecessorNRemove(elem) << '\n';
    }else if (scelta==16) {
      std::cout << "Successore di: ";
      std::cin >> elem;
      std::cout << "Successore: "<<binarytree.SuccessorNRemove(elem) << '\n';
    }
  }while (scelta>0 && scelta<17);

}

template <typename Data>
void VisitaBinaryTree(BST<Data>& binarytree){
  int scelta;
  std::cout<<"Scegliere come visualizzare gli elementi:\n1)PreOrder;\n2)PostOrder;\n3)InOrder;\n4)BreadthOrder\n\nScegli: ";
  std::cin>>scelta;

  if (scelta == 1) {
    binarytree.MapPreOrder(&MapPrint<Data>, nullptr);
    std::cout << '\n';
  } else if (scelta == 2) {
    binarytree.MapPostOrder(&MapPrint<Data>, nullptr);
    std::cout << '\n';
  }
  else if (scelta == 3) {
    binarytree.MapInOrder(&MapPrint<Data>, nullptr);
    std::cout << '\n';
  }
  else if (scelta == 4) {
    binarytree.MapBreadth(&MapPrint<Data>, nullptr);
    std::cout << '\n';
  }
}


template <typename Data>
void ExistBinaryTree(BST<Data>& binarytree){
  Data scelta;
  std::cout << "Inserisci: ";
  std::cin>>scelta;
  if(binarytree.Exists(scelta))
    std::cout << "L'elemento "<<scelta<<" esiste!" << '\n';
  else
    std::cout << "L'elemento "<<scelta<< " non esiste!" << '\n';

    std::cout << "Albero: ";
    binarytree.MapBreadth(&MapPrint<Data>, nullptr);
}

void OpSpecialiBinaryTree(BST<int>& binarytree){
    int n;
    int prod = 1;
    std::cout << "Inserisci numero: ";
    std::cin >> n;
    binarytree.FoldPreOrder(&FoldProdotto, &n, &prod);
    std::cout << "Prodotto: "<<prod << '\n';


}

void OpSpecialiBinaryTree(BST<float>& binarytree){
    int n;
    float sum = 0;
    std::cout << "Inserisci numero: ";
    std::cin >> n;
    binarytree.FoldPreOrder(&FoldSomma, &n, &sum);
    std::cout << "Somma: "<<sum << '\n';

}

void OpSpecialiBinaryTree(BST<std::string>& binarytree){

    std::string string_concat;
    int n;
    std::cout << "Inserisci numero: ";
    std::cin >> n;
    binarytree.FoldPreOrder(&FoldConcat, &n, &string_concat);
    std::cout << "Stringa concatenata: "<<string_concat << '\n';

}


    template <typename Data>
    void MapPrint(const Data& dat, void* _) {
      std::cout << dat << " ";
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

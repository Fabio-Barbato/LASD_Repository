#include <iostream>
#include "test.hpp"
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace lasd;
std::string GenerateString(){
    std::string string;

    for(int i=0;i<10;i++){
        char charOfString(rand()%25+97);
        string.push_back(charOfString);
    }

    return string;
}

void myTest(){
    uint sceltaStrutturaDati;
    ulong dimensioneStruttura;
    std::cout<<"Test della libreria in esecuzione..."<<std::endl;
    std::cout<<"Scegliere una struttura dati:\n1)BinaryTreeVec;\n2)BinaryTreeLnk;\n\nScegli: ";
    std::cin>>sceltaStrutturaDati;
    std::cout<<"Inserire dimensione iniziale della struttura: ";
    std::cin>>dimensioneStruttura;
    if(sceltaStrutturaDati==1)
        CreazioneBinaryTreeVec(dimensioneStruttura);
    else if(sceltaStrutturaDati==2){
      //  CreazioneBinaryTreeLnk(dimensioneStruttura);
    }


    std::cout << "Test terminato!" << '\n';
  }


  void CreazioneBinaryTreeVec(ulong dimensioneStruttura){
      int sceltaDati;
      int scelta_menu;
      std::cout<<"Scegliere su quali dati lavorare:\n1)Interi;\n2)Decimali;\n3)Stringhe\n\nScegli: ";
      std::cin>>sceltaDati;

      if(sceltaDati==1){
          Vector<int> vec(dimensioneStruttura);   //costruzione vec di interi
          srand(time(NULL));
          for(int i=0;i<dimensioneStruttura;i++){
              vec[i]=(rand()%50);
          }
          BinaryTreeVec<int> bt(vec);

          do{
            std::cout << "1)Operazioni generiche;\n2)Operazioni map/fold\nScegli: ";
            std::cin >> scelta_menu;
            if (scelta_menu==1) {
              MenuBinaryTree(bt);
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
          BinaryTreeVec<float> bt(vec);
          do{
            std::cout << "1)Operazioni generiche;\n2)Operazioni map/fold\nScegli: ";
            std::cin >> scelta_menu;
            if (scelta_menu==1) {
              MenuBinaryTree(bt);
            } else if (scelta_menu==2) {
              OpSpecialiBinaryTree(bt);
            }
          }while(scelta_menu<3 && scelta_menu>0);
      }
      else if(sceltaDati==3){
          Vector<std::string> vec(dimensioneStruttura);  //costruzione vec di stringhe
          for(int i=0;i<dimensioneStruttura;i++)
              vec[i] = (GenerateString());

          BinaryTreeVec<std::string> bt(vec);
          do{
            std::cout << "1)Operazioni generiche;\n2)Operazioni map/fold\nScegli: ";
            std::cin >> scelta_menu;
            if (scelta_menu==1) {
              MenuBinaryTree(bt);
            } else if (scelta_menu==2) {
              OpSpecialiBinaryTree(bt);
            }
          }while(scelta_menu<3 && scelta_menu>0);
      }
    }

    template <typename Data>
    void MenuBinaryTree(BinaryTreeVec<Data> binarytree){
      int scelta;
       do{
         std::cout << "Scegliere l'operazione da effettuare:\n1)Visita;\n2)Esistenza di un valore;\n3)Naviga con gli iteratori\n4)Naviga tra i nodi\n\nScegli: ";
         std::cin>>scelta;
        if (scelta==1) {
          VisitaBinaryTree(binarytree);
        } else if (scelta==2) {
          ExistBinaryTree(binarytree);
        } else if(scelta==3){
          VisitaIterBT(binarytree);
        }else if(scelta==4){
          NavigaConNodi(binarytree);
        }
      }while (scelta>0 && scelta<5);

    }


    template <typename Data>
    void NavigaConNodi(BinaryTreeVec<Data> binarytree) {
      int scelta;
      struct lasd::BinaryTreeVec<Data>::NodeVec::NodeVec* node = &binarytree.Root();
      do {
        std::cout << "1)Vuoi visualizzare il nodo corrente;\n2)Vuoi andare a destra;\n3)Vuoi andare a sinistra;\nScegli: " << '\n';
        std::cin >> scelta;

        if (scelta==1) {
          std::cout <<"Elemento: "<<node->Element() << '\n';
        }
        else if(scelta==2 && node->HasLeftChild()){
          node = &node->LeftChild();
        }else if(scelta==3 && node->HasRightChild()){
          node = &node->RightChild();
        }
      } while(!node->IsLeaf());
      std::cout << "Albero terminato!" << '\n';
    }

    template <typename Data>
    void VisitaIterBT(BinaryTreeVec<Data> binarytree){
      int scelta;
      do {
        std::cout << "Scegliere come visualizzare gli elementi:\n1)PreOrder;\n2)PostOrder;\n3)InOrder;\n4)BreadthOrder\n\nScegli: ";
        std::cin >> scelta;

        if (scelta==1) {
          BTPreOrderIterator<Data> it(binarytree);
          ViaggiaConIter(binarytree, it);
        } else if (scelta==2) {
          BTPostOrderIterator<Data> it(binarytree);
          ViaggiaConIter(binarytree, it);
        } else if(scelta==3) {
          BTInOrderIterator<Data> it(binarytree);
          ViaggiaConIter(binarytree, it);
        } else if(scelta==4){
          BTBreadthIterator<Data> it(binarytree);
          ViaggiaConIter(binarytree, it);
        }
      } while(scelta>0 && scelta<5);
    }

      template <typename Data>
      void ViaggiaConIter(BinaryTreeVec<Data> binarytree, BTPreOrderIterator<Data> itr) {
        int scelta;
        do {
          std::cout << "1)Vuoi visualizzare l'elemento puntato;\n2)Vuoi andare al nodo successivo;\nScegli: " << '\n';
          std::cin >> scelta;

          if (scelta==1) {
            std::cout << *itr << '\n';
          }
          else{
            ++itr;
          }
        } while(!itr.Terminated());
        std::cout << "Albero terminato!" << '\n';
      }

      template <typename Data>
      void ViaggiaConIter(BinaryTreeVec<Data> binarytree, BTPostOrderIterator<Data> itr) {
        int scelta;
        do {
          std::cout << "1)Vuoi visualizzare l'elemento puntato;\n2)Vuoi andare al nodo successivo;\nScegli: " << '\n';
          std::cin >> scelta;

          if (scelta==1) {
            std::cout << *itr << '\n';
          }
          else{
            ++itr;
          }
        } while(!itr.Terminated());
        std::cout << "Albero terminato!" << '\n';
      }

      template <typename Data>
      void ViaggiaConIter(BinaryTreeVec<Data> binarytree, BTInOrderIterator<Data> itr) {
        int scelta;
        do {
          std::cout << "1)Vuoi visualizzare l'elemento puntato;\n2)Vuoi andare al nodo successivo;\nScegli: " << '\n';
          std::cin >> scelta;

          if (scelta==1) {
            std::cout << *itr << '\n';
          }
          else{
            ++itr;
          }
        } while(!itr.Terminated());
        std::cout << "Albero terminato!" << '\n';
      }

      template <typename Data>
      void ViaggiaConIter(BinaryTreeVec<Data> binarytree, BTBreadthIterator<Data> itr) {
        int scelta;
        do {
          std::cout << "1)Vuoi visualizzare l'elemento puntato;\n2)Vuoi andare al nodo successivo;\nScegli: " << '\n';
          std::cin >> scelta;

          if (scelta==1) {
            std::cout << *itr << '\n';
          }
          else{
            ++itr;
          }
        } while(!itr.Terminated());
        std::cout << "Albero terminato!" << '\n';
      }


    template <typename Data>
    void ExistBinaryTree(BinaryTreeVec<Data> binarytree){
      Data scelta;
      std::cout << "Inserisci: ";
      std::cin>>scelta;
      if(binarytree.Exists(scelta))
        std::cout << "L'elemento "<<scelta<<" esiste!" << '\n';
      else
        std::cout << "L'elemento "<<scelta<< " non esiste!" << '\n';

        std::cout << "Albero: " << '\n';
        binarytree.MapBreadth(&MapPrint<Data>, nullptr);
    }


    template <typename Data>
    void VisitaBinaryTree(BinaryTreeVec<Data> binarytree){
      int scelta;
      std::cout<<"Scegliere come visualizzare gli elementi:\n1)PreOrder;\n2)PostOrder;\n3)InOrder;\n4)BreadthOrder\n\nScegli: ";
      std::cin>>scelta;

      if (scelta == 1) {
        binarytree.MapPreOrder(&MapPrint<Data>, nullptr);
      } else if (scelta == 2) {
        binarytree.MapPostOrder(&MapPrint<Data>, nullptr);
      }
      else if (scelta == 3) {
        binarytree.MapInOrder(&MapPrint<Data>, nullptr);
      }
      else if (scelta == 4) {
        binarytree.MapBreadth(&MapPrint<Data>, nullptr);
      }
    }


    void OpSpecialiBinaryTree(BinaryTreeVec<int> binarytree){
      int scelta;
      std::cout << "1)Prodotto per numeri minori di n;\n2)Moltiplica gli elementi per 3\n\nScegli: " << '\n';
      std::cin>>scelta;

      if (scelta == 1) {
        int n;
        int prod = 1;
        std::cout << "Inserisci numero: " << '\n';
        std::cin >> n;
        binarytree.FoldPreOrder(&FoldProdotto, &n, &prod);
        std::cout << "Prodotto: "<<prod << '\n';
      } else if (scelta == 2) {
        binarytree.MapPostOrder(&MapRedouble, nullptr);
        std::cout << "Albero modificato: " << '\n';
        binarytree.MapBreadth(&MapPrint<int>, nullptr);
      }

    }

    void OpSpecialiBinaryTree(BinaryTreeVec<float> binarytree){
      int scelta;
      std::cout << "1)Somma per numeri maggiori di n;\n2)Eleva gli elementi al cubo\n\nScegli: " << '\n';
      std::cin>>scelta;

      if (scelta == 1) {
        int n;
        float sum = 0;
        std::cout << "Inserisci numero: " << '\n';
        std::cin >> n;
        binarytree.FoldPreOrder(&FoldSomma, &n, &sum);
        std::cout << "Somma: "<<sum << '\n';
      } else if (scelta == 2) {
        binarytree.MapPostOrder(&MapPotenza, nullptr);
        std::cout << "Albero modificato: " << '\n';
        binarytree.MapBreadth(&MapPrint<float>, nullptr);
      }
    }

    void OpSpecialiBinaryTree(BinaryTreeVec<std::string> binarytree){
      int scelta;
      std::cout << "1)Concatenazione per le stringhe con lunghezza minore o uguale a n;\n2)Concatenazione in testa di una specifica stringa\n\nScegli: " << '\n';
      std::cin>>scelta;

      if (scelta == 1) {
        int n;
        std::string string_concat = 0;
        std::cout << "Inserisci numero: " << '\n';
        std::cin >> n;
        binarytree.FoldPreOrder(&FoldConcat, &n, &string_concat);
        std::cout << "Stringa concatenata: "<<string_concat << '\n';
      } else if (scelta == 2) {
        binarytree.MapPostOrder(&MapConcat, nullptr);
        std::cout << "Albero modificato: " << '\n';
        binarytree.MapBreadth(&MapPrint<std::string>, nullptr);
      }
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


    void MapRedouble(int& value, void* par){
        value = value * 3;
    }

    void MapPotenza(float& value, void* par){
        value = value * value * value;
    }

    void MapConcat(std::string& value, void* stringaConcat){
    *(std::string*)stringaConcat= *(std::string*)stringaConcat+value;
    }

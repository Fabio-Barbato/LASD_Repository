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
      std::cout<<"Scegliere su quali dati lavorare:\n1)Interi;\n2)Decimali;\n3)Stringhe\n\nScegli: ";
      std::cin>>sceltaDati;

      if(sceltaDati==1){
          Vector<int> vec(dimensioneStruttura);   //costruzione vec di interi
          srand(time(NULL));
          for(int i=0;i<dimensioneStruttura;i++){
              vec[i]=(rand()%50);
          }
          BinaryTreeVec<int> bt(vec);
          MenuBinaryTree(bt);
      }
      else if(sceltaDati==2){
          Vector<float> vec(dimensioneStruttura);   //costruzione vec di float
          srand(time(NULL));
          for(int i=0;i<dimensioneStruttura;i++){
              vec[i] = (float(rand())/float(RAND_MAX));
            }
          BinaryTreeVec<float> bt(vec);
          MenuBinaryTree(bt);
      }
      else if(sceltaDati==3){
          Vector<std::string> vec(dimensioneStruttura);  //costruzione vec di stringhe
          for(int i=0;i<dimensioneStruttura;i++)
              vec[i] = (GenerateString());

          BinaryTreeVec<std::string> bt(vec);
          MenuBinaryTree(bt);
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

    template <typename Data>
    void OpSpecialiBinaryTreeVecInt(BinaryTreeVec<int> binarytree){
      int scelta;
      std::cout << "1)Prodotto per numeri minori di n;\n2)Potenza di 3\n\nScegli: " << '\n';
      std::cin>>scelta;

      if (scelta == 1) {
        int n;
        int sum = 0;
        std::cout << "Inserisci numero: " << '\n';
        binarytree.FoldPreOrder(&FoldProdotto, &n, &sum);
        std::cout << "Somma: "<<sum << '\n';
      } else if (scelta == 2) {
        binarytree.MapPostOrder(&MapRedouble, nullptr);
        std::cout << "Albero modificato: " << '\n';
        binarytree.MapBreadth(&MapPrint<Data>, nullptr);
      }

    }


    template <typename Data>
    void MapPrint(const Data& dat, void* _) {
      std::cout << dat << " ";
    }

    void FoldSomma(const int& dat, const void* n, void* somma)  noexcept {
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

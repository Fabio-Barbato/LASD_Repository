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
    std::cout<<"Scegliere una struttura dati:\n1)StackVec;\n2)QueueVec;\n3)QueueLst;\n4)StackLst;\n\nScegli: ";
    std::cin>>sceltaStrutturaDati;
    std::cout<<"Inserire dimensione iniziale della struttura: ";
    std::cin>>dimensioneStruttura;
    if(sceltaStrutturaDati==1)
        CreazioneStackVec(dimensioneStruttura);
    else if(sceltaStrutturaDati==2){
        CreazioneQueueVec(dimensioneStruttura);
    }
    else if(sceltaStrutturaDati==3){
        CreazioneQueueLst(dimensioneStruttura);
    }
    else if(sceltaStrutturaDati==4){
        CreazioneStackLst(dimensioneStruttura);
    }
    std::cout << "Test terminato!" << '\n';
  }


  void CreazioneStackVec(ulong dimensioneStruttura){
      int sceltaDati;
      std::cout<<"Scegliere su quali dati lavorare:\n1)Interi;\n2)Decimali;\n3)Stringhe\n\nScegli: ";
      std::cin>>sceltaDati;

      if(sceltaDati==1){
          lasd::StackVec<int> stack;   //costruzione stack di interi
          srand(time(NULL));
          for(int i=1;i<=dimensioneStruttura;i++){
              stack.Push(rand()%50);
          }
          MenuStackVec(stack);
      }
      else if(sceltaDati==2){
          lasd::StackVec<float> stack;   //costruzione stack di float
          srand(time(NULL));
          for(int i=1;i<=dimensioneStruttura;i++)
              stack.Push(float(rand())/float(RAND_MAX));
          MenuStackVec(stack);
      }
      else if(sceltaDati==3){
          lasd::StackVec<std::string> stack;  //costruzione stack di stringhe
          for(int i=1;i<=dimensioneStruttura;i++)
              stack.Push(GenerateString());
          MenuStackVec(stack);
      }

  }

  template <typename Data>
  void MenuStackVec(lasd::StackVec<Data> stack){
    uint scelta;
    do{
    std::cout << "Quali operazioni vuoi effettuare?\n1)Inserisci un elemento\n2)Rimuovi un elemento\n3)Rimuovi un elemento e leggilo\n4)Scopri se è vuoto\n5)Scopri dimensione\n6)Svuota\n7)Leggi la testa\n\nScegli: " << '\n';
    std::cin>>scelta;
    if(scelta==1){
      std::cout << "Inserisci: " << '\n';
      Data elem;
      std::cin >> elem;
      stack.Push(elem);
    }
    else if(scelta==2){
      try{
        stack.Pop();
        std::cout << "Elemento rimosso!" << std::endl;
      }catch(std::length_error e){
        std::cout << "Stack vuoto!" << '\n';
      }

    }
    else if(scelta==3){
      try{
        std::cout << "Testa: "<< stack.TopNPop() << std::endl;
      }catch(std::length_error e){
        std::cout << "Stack vuoto" << '\n';
      }

    }
    else if(scelta==4){
      try{
        if(!stack.Empty())
        std::cout << "Stack non vuoto"<< std::endl;
      }catch(std::length_error e){
        std::cout << "Stack vuoto" << '\n';
      }

    }
    else if(scelta==5){
      std::cout << "Size: "<<stack.Size() << std::endl;
    }
    else if(scelta==6){
      stack.Clear();
      std::cout << "Stack pulito!" << '\n';
    }
    else if(scelta==7){
      try{
        std::cout << "Testa: "<< stack.Top() << std::endl;
      }catch(std::length_error e){
        std::cout << "Stack vuoto" << '\n';
      }
    }
  }while (scelta<=7 && scelta>=1) ;
}

void CreazioneStackLst(ulong dimensioneStruttura){
    int sceltaDati;
    std::cout<<"Scegliere su quali dati lavorare:\n1)Interi;\n2)Decimali;\n3)Stringhe\n\nScegli: ";
    std::cin>>sceltaDati;

    if(sceltaDati==1){
        lasd::StackLst<int> stack;   //costruzione stack di interi
        srand(time(NULL));
        for(int i=1;i<=dimensioneStruttura;i++){
            stack.Push(rand()%50);
        }
        MenuStackLst(stack);
    }
    else if(sceltaDati==2){
        lasd::StackLst<float> stack;   //costruzione stack di float
        srand(time(NULL));
        for(int i=1;i<=dimensioneStruttura;i++)
            stack.Push(float(rand())/float(RAND_MAX));
        MenuStackLst(stack);
    }
    else if(sceltaDati==3){
        lasd::StackLst<std::string> stack;  //costruzione stack di stringhe
        for(int i=1;i<=dimensioneStruttura;i++)
            stack.Push(GenerateString());
        MenuStackLst(stack);
    }

}

template <typename Data>
void MenuStackLst(lasd::StackLst<Data> stack){
  uint scelta;
  do{
  std::cout << "Quali operazioni vuoi effettuare?\n1)Inserisci un elemento\n2)Rimuovi un elemento\n3)Rimuovi un elemento e leggilo\n5)Scopri dimensione\n6)Svuota\n7)Leggi la testa\n\nScegli: " << '\n';
  std::cin>>scelta;
  if(scelta==1){
    std::cout << "Inserisci: " << '\n';
    Data elem;
    std::cin >> elem;
    stack.Push(elem);
  }
  else if(scelta==2){
    try{
      stack.Pop();
      std::cout << "Elemento rimosso!" << std::endl;
    }catch(std::length_error e){
      std::cout << "Stack vuoto!" << '\n';
    }

  }
  else if(scelta==3){
    try{
      std::cout << "Testa: "<< stack.TopNPop() << std::endl;
    }catch(std::length_error e){
      std::cout << "Stack vuoto" << '\n';
    }

  }
  else if(scelta==5){
    std::cout << "Size: "<<stack.Size() << std::endl;
  }
  else if(scelta==6){
    stack.Clear();
    std::cout << "Stack pulito!" << '\n';
  }
  else if(scelta==7){
    try{
      std::cout << "Testa: "<< stack.Top() << std::endl;
    }catch(std::length_error e){
      std::cout << "Stack vuoto" << '\n';
    }
  }
}while (scelta<=7 && scelta>=1 && scelta!=4) ;
}

void CreazioneQueueVec(ulong dimensioneStruttura){
    int sceltaDati;
    std::cout<<"Scegliere su quali dati lavorare:\n1)Interi;\n2)Decimali;\n3)Stringhe\n\nScegli: ";
    std::cin>>sceltaDati;

    if(sceltaDati==1){
        lasd::QueueVec<int> queue;   //costruzione stack di interi
        srand(time(NULL));
        for(int i=1;i<=dimensioneStruttura;i++){
            queue.Enqueue(rand()%50);
        }
        MenuQueueVec(queue);
    }
    else if(sceltaDati==2){
        lasd::QueueVec<float> queue;   //costruzione stack di float
        srand(time(NULL));
        for(int i=1;i<=dimensioneStruttura;i++)
            queue.Enqueue(float(rand())/float(RAND_MAX));
        MenuQueueVec(queue);
    }
    else if(sceltaDati==3){
        lasd::QueueVec<std::string> queue;  //costruzione stack di stringhe
        for(int i=1;i<=dimensioneStruttura;i++)
            queue.Enqueue(GenerateString());
        MenuQueueVec(queue);
    }

}

template <typename Data>
void MenuQueueVec(lasd::QueueVec<Data> queue){
  uint scelta;
  do{
  std::cout << "Quali operazioni vuoi effettuare?\n1)Inserisci un elemento\n2)Rimuovi un elemento\n3)Rimuovi un elemento e leggilo\n4)Scopri se è vuoto\n5)Scopri dimensione\n6)Svuota\n7)Leggi la testa\n\nScegli: " << '\n';
  std::cin>>scelta;
  if(scelta==1){
    std::cout << "Inserisci: " << '\n';
    Data elem;
    std::cin >> elem;
    queue.Enqueue(elem);
  }
  else if(scelta==2){
    try{
      queue.Dequeue();
      std::cout << "Elemento rimosso!" << std::endl;
    }catch(std::length_error e){
      std::cout << "Queue vuoto!" << '\n';
    }

  }
  else if(scelta==3){
    try{
      std::cout << "Testa: "<< queue.HeadNDequeue() << std::endl;
    }catch(std::length_error e){
      std::cout << "Queue vuoto" << '\n';
    }

  }
  else if(scelta==4){
    try{
      if(!queue.Empty()){
      std::cout << "Queue non vuoto"<< std::endl;}
    }catch(std::length_error e){
      std::cout << "Queue vuoto" << '\n';
    }

  }
  else if(scelta==5){
    std::cout << "Size: "<<queue.Size() << std::endl;
  }
  else if(scelta==6){
    queue.Clear();
    std::cout << "Queue pulito!" << '\n';
  }
  else if(scelta==7){
    try{
      std::cout << "Testa: "<< queue.Head() << std::endl;
    }catch(std::length_error e){
      std::cout << "Queue vuoto" << '\n';
    }
  }
}while (scelta<=7 && scelta>=1) ;
}


void CreazioneQueueLst(ulong dimensioneStruttura){
    int sceltaDati;
    std::cout<<"Scegliere su quali dati lavorare:\n1)Interi;\n2)Decimali;\n3)Stringhe\n\nScegli: ";
    std::cin>>sceltaDati;

    if(sceltaDati==1){
        lasd::QueueLst<int> queue;   //costruzione stack di interi
        srand(time(NULL));
        for(int i=1;i<=dimensioneStruttura;i++){
            queue.Enqueue(rand()%50);
        }
        MenuQueueLst(queue);
    }
    else if(sceltaDati==2){
        lasd::QueueLst<float> queue;   //costruzione stack di float
        srand(time(NULL));
        for(int i=1;i<=dimensioneStruttura;i++)
            queue.Enqueue(float(rand())/float(RAND_MAX));
        MenuQueueLst(queue);
    }
    else if(sceltaDati==3){
        lasd::QueueLst<std::string> queue;  //costruzione stack di stringhe
        for(int i=1;i<=dimensioneStruttura;i++)
            queue.Enqueue(GenerateString());
        MenuQueueLst(queue);
    }

}

template <typename Data>
void MenuQueueLst(lasd::QueueLst<Data> queue){
  uint scelta;
  do{
  std::cout << "Quali operazioni vuoi effettuare?\n1)Inserisci un elemento\n2)Rimuovi un elemento\n3)Rimuovi un elemento e leggilo\n5)Scopri dimensione\n6)Svuota\n7)Leggi la testa\n\nScegli: " << '\n';
  std::cin>>scelta;
  if(scelta==1){
    std::cout << "Inserisci: " << '\n';
    Data elem;
    std::cin >> elem;
    queue.Enqueue(elem);
  }
  else if(scelta==2){
    try{
      queue.Dequeue();
      std::cout << "Elemento rimosso!" << std::endl;
    }catch(std::length_error e){
      std::cout << "Queue vuoto!" << '\n';
    }

  }
  else if(scelta==3){
    try{
      std::cout << "Testa: "<< queue.HeadNDequeue() << std::endl;
    }catch(std::length_error e){
      std::cout << "Queue vuoto" << '\n';
    }

  }
  else if(scelta==5){
    std::cout << "Size: "<<queue.Size() << std::endl;
  }
  else if(scelta==6){
    queue.Clear();
    std::cout << "Queue pulito!" << '\n';
  }
  else if(scelta==7){
    try{
      std::cout << "Testa: "<< queue.Head() << std::endl;
    }catch(std::length_error e){
      std::cout << "Queue vuoto" << '\n';
    }
  }
}while (scelta<=7 && scelta>=1 && scelta!=4) ;
}

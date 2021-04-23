
namespace lasd {

/* ************************************************************************** */

//Enqueue (copy)
template <typename Data>
void QueueVec<Data>::Enqueue(const Data& value){
  if(size==0){ //Queue vuota
    Elements = new Data[10];
    size = 10;
    Elements[0] = value;
    head = &Elements[0];
    tail = &Elements[1];
  }
  else{ //Queue non piena
    Elements[tail] = value;
    if (tail+1 > &Elements[size-1]){ //tail arrivata alla fine del Vector
      if(head == &Elements[0]){ //Vector pieno
        Expand();
      }
      else{
        tail = Elements[0];
      }
    }
    else{//tail non alla fine del Vector
      if(head == tail+1){//Vector pieno
        Expand();
      }
      else{
        tail++;
      }
    }
  }
 }

/* ************************************************************************** */

}

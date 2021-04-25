
namespace lasd {

/* ************************************************************************** */

//Enqueue (copy)
template <typename Data>
void QueueVec<Data>::Enqueue(const Data& value){
  if(size==0){ //Queue vuota
    Elements = new Data[2] {};
    size = 2;
    Elements[0] = value;
    head = 0;
    tail = 1;
  }
  else{ //Queue non piena
    Elements[tail] = value;
    tail++;
    if (tail == size){ //tail arrivata alla fine del Vector
      if(head == 0){ //Vector pieno
        Expand();
      }
      else{
        tail = 0;
      }
    }
    else{//tail non alla fine del Vector
      if(head == tail+1){//Vector pieno
        Expand();
      }
    }
  }
 }

 //Enqueue (move)
 template <typename Data>
 void QueueVec<Data>::Enqueue(Data&& value) noexcept{
   if(size==0){ //Queue vuota
     Elements = new Data[2]{};
     size = 2;
     std::swap(Elements[0] , value);
     head=0;
     tail = 1;
   }
   else{ //Queue non piena
     std::swap(Elements[tail] , value);
     tail++;
     if (tail == size){ //tail arrivata alla fine del Vector
       if(head == 0){ //Vector pieno
         Expand();
       }
       else{
         tail = 0;
       }
     }
     else{//tail non alla fine del Vector
       if(head == tail+1){//Vector pieno
         Expand();
       }
     }
   }
  }

  //Head
  template <typename Data>
  Data& QueueVec<Data>::Head() const{
    if(!(Empty())){
      return Elements[head];
    }
    else{
      throw std::length_error("Empty");
    }
  }

  //Size
  template <typename Data>
  ulong QueueVec<Data>::Size() const noexcept{
    if(head>tail){
      return size - (head - tail);
    }
    else{
      return tail-head;
    }
  }

  //Empty
  template <typename Data>
  bool QueueVec<Data>::Empty() const noexcept{
    return Size() == 0;
  }

  //Dequeue
  template <typename Data>
  void QueueVec<Data>::Dequeue() {
    if(Empty()){
      throw std::length_error("Empty");
    }
    else{
      head++;
      if(head == size){ //Se la head è arrivata alla fine del Vector
        head = 0;
      }


      if(Size() == size/4){
        Reduce();
      }
    }
  }

  //HeadNDequeue
  template <typename Data>
  Data QueueVec<Data>::HeadNDequeue(){
    Data dat = Head();
    Dequeue();
    return dat;
  }

  //Clear
  template <typename Data>
  void QueueVec<Data>::Clear(){
    Vector<Data>::Clear();
    tail = 0;
    head = 0;
  }

  //SwapVectors
  template <typename Data>
  void QueueVec<Data>::SwapVectors(const ulong x){
    Data* TmpElements = new Data[x]{};
     ulong i=0;
       if(tail<head){
             for(ulong index = head; index < size; index++){
                 std::swap(Elements[index], TmpElements[i]);
                 i++;
             }
             for(ulong index = 0; index < tail; index++){
                 std::swap(Elements[index], TmpElements[i]);
                 i++;
             }
         }else{
           for(ulong index = head; index < tail; index++){
               std::swap(Elements[index], TmpElements[i]);
               i++;
         }}
     std::swap(Elements, TmpElements);
     size = x;
     tail=tail-head;
     head=0;
     delete[] TmpElements;
  }

  //Expand
  template <typename Data>
  void QueueVec<Data>::Expand(){
      SwapVectors(size*2);
  }

  //Reduce
  template <typename Data>
  void QueueVec<Data>::Reduce(){
      SwapVectors(size/2);
  }

  //Comparison operators
  template <typename Data>
  bool QueueVec<Data>::operator==(const QueueVec<Data>& queue) const noexcept{
    if(Size()==queue.Size() && head == queue.head && tail == queue.tail){
      ulong index = head;
      if(head<tail){
        while (index<tail) {
          if (Elements[index] != queue.Elements[index]) {
            return false;
          }
          index++;
        }
        return true;
      }else{
        while (index<size) {
          if (Elements[index] != queue.Elements[index]) {
            return false;
          }
          index++;
        }
        index=0;
        while (index<tail) {
          if (Elements[index] != queue.Elements[index]) {
            return false;
          }
          index++;
        }
        return true;
      }
  }else{
    return false;
  }
}

  template <typename Data>
  bool QueueVec<Data>::operator!=(const QueueVec<Data>& queue) const noexcept{
    return !(*this == queue);
  }

  //Specific constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const LinearContainer<Data>& con){
    size = con.Size();
    Elements = new Data[size] {};
    for (ulong i = 0; i < con.Size(); i++) {
      Elements[i] = con[i];
      tail++;
    }
  }

  //Copy constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const QueueVec<Data>& queue){
    size = queue.size;
    Elements = new Data [size] {};
    head = queue.head;
    tail = head;
    ulong index = queue.head;
    while (index<size && index!= queue.tail) {
      Enqueue(queue.Elements[index]);
      index++;
    }
    if(index==size){
      index = 0;
      while (index!= queue.tail) {
        Enqueue(queue.Elements[index]);
        index++;
      }
    }
  }

  //Move constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(QueueVec<Data>&& queue) noexcept{
    std::swap(size, queue.size);
    std::swap(Elements, queue.Elements);
    std::swap(head, queue.head);
    std::swap(tail, queue.tail);
  }

  //Destructor
  template <typename Data>
  QueueVec<Data>::~QueueVec(){
    Clear();
  }

  //Copy assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& queue){
    QueueVec<Data>* tmp = new QueueVec<Data>(queue);
    std::swap(*tmp, *this);
    delete tmp;
    return *this;
  }

  //Move assignment
  template<typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& queue) noexcept{
    std::swap(size, queue.size);
    std::swap(Elements, queue.Elements);
    std::swap(head, queue.head);
    std::swap(tail, queue.tail);

    return *this;
  }


/* ************************************************************************** */

}

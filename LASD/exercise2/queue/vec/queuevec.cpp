
namespace lasd {

/* ************************************************************************** */

//Enqueue (copy)
template <typename Data>
void QueueVec<Data>::Enqueue(const Data& value){
  if(size==0){ //Queue vuota
    Elements = new Data[10] {};
    size = 10;
    Elements[0] = value;
    head = &Elements[0];
    tail = &Elements[1];
  }
  else{ //Queue non piena
    Elements[(tail - &Elements[0])] = value;
    if (tail+1 > &Elements[size-1]){ //tail arrivata alla fine del Vector
      if(head == &Elements[0]){ //Vector pieno
        Expand();
      }
      else{
        tail = &Elements[0];
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

 //Enqueue (move)
 template <typename Data>
 void QueueVec<Data>::Enqueue(Data&& value) noexcept{
   if(size==0){ //Queue vuota
     Elements = new Data[3]{};
     size = 3;
     std::swap(Elements[0] , value);
     head = &Elements[0];
     tail = &Elements[0];
   }
   else{ //Queue non piena
     std::swap(Elements[(tail - &Elements[0])] , value);
     if (tail+1 > &Elements[size-1]){ //tail arrivata alla fine del Vector
       if(head == &Elements[0]){ //Vector pieno
         Expand();
       }
       else{
         tail = &Elements[0];
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

  //Head
  template <typename Data>
  Data& QueueVec<Data>::Head() const{
    if(!(Empty())){
      return *head;
    }
    else{
      throw std::length_error("Empty");
    }
  }

  //Size
  template <typename Data>
  ulong QueueVec<Data>::Size() const noexcept{
    if(head>tail){
      ulong head_long = head - &Elements[0];
      ulong tail_long = tail - &Elements[0];
      return size - head_long - tail_long;
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
      if(head+1 > &Elements[size-1]){ //Se la head è arrivata alla fine del Vector
        head = &Elements[0];
      }
      else{
        head++;
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
    tail = nullptr;
    head = nullptr;
  }

  //SwapVectors
  template <typename Data>
  void QueueVec<Data>::SwapVectors(const ulong new_size){
    Data* tmp = new Data[new_size] {};
    ulong index_tmp = 0;
    ulong index = head - &Elements[size];
    while(index<size && index!=tail - &Elements[0]){
      tmp[index_tmp] = Elements[index];
      index++;
      index_tmp++;
    }
    if(index==size){
      index = 0;
      while (index != tail - &Elements[0]) {
        tmp[index_tmp] = Elements[index];
        index++;
        index_tmp++;
      }
    }
    std::swap(Elements, tmp);
    head = &Elements[0];
    tail = &Elements[index_tmp];
    delete[] tmp;
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
    if(size == queue.size && Size()==queue.Size() && head - &Elements[0] == queue.head - &queue.Elements[0] && tail - &Elements[0] == queue.tail - &queue.Elements[0]){
      ulong index = head - &Elements[0];
      while (index<size && index != tail - &Elements[0]) {
        if(Elements[index]!= queue.Elements[index]){
          return false;
        }
        index++;
      }
      if(index== tail - &Elements[0]){
        return true;
      }
      else{
        index = 0;
        while(index != tail - &Elements[0]){
          if(Elements[index]!= queue.Elements[index]){
            return false;
          }
          index++;
        }
        return true;
      }
    }
    else{
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
    head = &Elements[0];
    tail = head;
    for (ulong i = 0; i < size; i++) {
      Enqueue(con[i]);
    }
  }

  //Copy constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const QueueVec<Data>& queue){
    size = queue.size;
    Elements = new Data [size] {};
    head = &Elements[queue.head - &Elements[0]];
    tail = head;
    ulong index = queue.head - &Elements[0];
    while (index<size && index!= queue.tail - &Elements[0]) {
      Enqueue(queue.Elements[index]);
    }
    if(index==size){
      index = 0;
      while (index!= queue.tail - &Elements[0]) {
        Enqueue(queue.Elements[index]);
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

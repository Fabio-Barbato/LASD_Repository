
namespace lasd {

/* ************************************************************************** */

//Enqueue(copy)
template <typename Data>
void QueueLst<Data>::Enqueue(const Data& value){
  List<Data>::InsertAtBack(value);
}

//Enqueue(move)
template <typename Data>
void QueueLst<Data>::Enqueue(Data&& value) noexcept{
  List<Data>::InsertAtBack(std::move(value));
}

//Head
template <typename Data>
Data& QueueLst<Data>::Head() const{
  return List<Data>::Front();
}

//Dequeue
template <typename Data>
void QueueLst<Data>::Dequeue(){
  List<Data>::RemoveFromFront();
}

//HeadNDequeue
template <typename Data>
Data QueueLst<Data>::HeadNDequeue(){
  return List<Data>::FrontNRemove();
}

//Clear
template <typename Data>
void QueueLst<Data>::Clear(){
  List<Data>::Clear();
}

//Destructor
template <typename Data>
QueueLst<Data>::~QueueLst(){
  Clear();
}

//Comparison operators
template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& queue) const noexcept{
  return List<Data>::operator==(queue);
}

template <typename Data>
bool QueueLst<Data>::operator!=(const QueueLst<Data>& queue) const noexcept{
  return !(*this==queue);
}

//Copy constructor
template <typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data>& queue){
  struct List<Data>::Node* tmp = queue.head;
  for (ulong i = 0; i < queue.size; i++) {
    Enqueue(tmp->info);
    tmp = tmp->next;
  }
}


//Copy assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& queue){
  QueueLst<Data>* tmp_que = new QueueLst<Data>(queue);
  std::swap(*this, *tmp_que);
  delete tmp_que;
  return *this;
}

//Move constructor
template <typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data>&& queue) noexcept{
  std::swap(head, queue.head);
  std::swap(tail, queue.tail);
  std::swap(size, queue.size);
}

//Move assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& queue) noexcept{
  std::swap(head, queue.head);
  std::swap(tail, queue.tail);
  std::swap(size, queue.size);

  return *this;
}

//Specific constructor
template <typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& con){
  size = 0;
  for (ulong i = 0; i < con.Size(); i++) {
    Enqueue(con[i]);
  }
}
/* ************************************************************************** */

}

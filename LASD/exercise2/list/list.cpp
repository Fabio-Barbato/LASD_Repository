#include <iostream>
namespace lasd {

/* ************************************************************************** */
//Node methods

//Node specific constructor
template <typename Data>
List<Data>::Node::Node(const Data value){
  info = value;
  next = nullptr;
}

//Node copy constructor
template <typename Data>
List<Data>::Node::Node(const Node& node_copied){
  info = node_copied->info;
  next = node_copied->next;
}

//Node move constructor
template <typename Data>
List<Data>::Node::Node(Node&& node_swapped) noexcept{
  std::swap(info, node_swapped->info);
  std::swap(next, node_swapped->next);
}


//Comparison operators
template <typename Data>
bool List<Data>::Node::operator==(const Node& node) const noexcept{
  if(info == node->info)
     return true;
  else
     return false;
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node& node) const noexcept{
  return !(*this==node);
}


//List methods

//InsertAtFront(copy)
template <typename Data>
void List<Data>::InsertAtFront(const Data& value){
  Node* tmp = new Node(value);
  if(head==nullptr){
    tmp->next = head;
    head = tmp;
    tail = head;
  }
  else{
    tmp->next = head;
    head = tmp;
  }
  size++;
}

//InsertAtFront(move)
template <typename Data>
void List<Data>::InsertAtFront(Data&& value) noexcept{
  Node* tmp = new Node(value);
  std::swap(tmp->info, value);
  if(head==nullptr){
    tmp->next = head;
    head = tmp;
    tail = head;
  }
  else{
    tmp->next = head;
    head = tmp;
  }
  size++;
}

//InsertAtBack(copy)
template <typename Data>
void List<Data>::InsertAtBack(const Data& value) {
  Node* tmp = new Node(value);
  if(size==0){
    tmp->next = head;
    head = tmp;
    tail = head;
  }
  else{
    tail->next = tmp;
    tail = tmp;
    tmp->next = nullptr;
  }
  size++;

}

//InsertAtBack(move)
template <typename Data>
void List<Data>::InsertAtBack(Data&& value) noexcept{
  Node* tmp = new Node(std::move(value));
  if(size==0){
    tmp->next = head;
    head = tmp;
    tail = head;
  }
  else{
    tail->next = tmp;
    tail = tmp;
    tmp->next = nullptr;
  }
  size++;

}

//RemoveFromFront
template <typename Data>
void List<Data>::RemoveFromFront(){
  if(size>0){
    Node* tmp = head;
    head = tmp->next;
    size--;
    delete tmp;
  }else{
    throw std::length_error("Empty List!");
  }
}

//FrontNRemove
template <typename Data>
Data List<Data>::FrontNRemove(){
  if(size>0){
    Data dat;
    Node* tmp = head;
    head = tmp->next;
    size--;
    dat = tmp->info;
    delete tmp;
    return dat;
  }else{
    throw std::length_error("Empty List!");
  }
}


//Clear
template <typename Data>
void List<Data>::Clear(){
  ulong tmpsize = size;
  for (ulong i = 0; i < tmpsize; i++) {
    RemoveFromFront();
  }
}

//Specific constructor
template <typename Data>
List<Data>::List(const LinearContainer<Data>& con){
  size = 0;
  for (ulong i = 0; i < con.Size(); i++) {
    InsertAtBack(con[i]);
  }
}

//Operator []
template <typename Data>
Data& List<Data>::operator[](const ulong index) const {
  if(index>size){
    throw std::out_of_range("Out of range! List size: "+ std::to_string(size));
  }
  else{
    Node* tmp = head;
    ulong i=0;
    for (ulong i = 0; i < index; i++) {
      tmp = tmp->next;
    }
    return tmp->info;
  }

}

//Copy constructor
template <typename Data>
List<Data>::List(const List<Data>& lst){
  for (ulong i = 0; i < lst.size; i++) {
    InsertAtBack(lst[i]);
  }
  size = lst.size;
}

//Move constructor
template <typename Data>
List<Data>::List(List<Data>&& lst) noexcept{
  std::swap(head, lst.head);
  std::swap(tail, lst.tail);
  std::swap(size, lst.size);
}

//Destructor
template <typename Data>
List<Data>::~List(){
  Clear();
}

//Copy assignment
template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& lst){
  List<Data>* tmplst = new List<Data>(lst);
  std::swap(*this, *tmplst);
  delete tmplst;
  return *this;
}

//Move assignment
template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& lst) noexcept{
  std::swap(head, lst.head);
  std::swap(tail, lst.tail);
  std::swap(size, lst.size);
  return *this;
}

//Comparison operators
template <typename Data>
bool List<Data>::operator==(const List<Data>& lst) const noexcept{
  if(size == lst.size){
    ulong index = 0;
    while (index<size) {
      if((*this)[index]!=lst[index]){
        return false;
      }
      index++;
    }
    return true;
  }
  else{
    return false;
  }

}

template <typename Data>
bool List<Data>::operator!=(const List<Data>& lst) const noexcept{
  return !((*this)==lst);
}

//Front
template <typename Data>
Data& List<Data>::Front() const{
  if(head==nullptr){
    throw std::length_error("Empty List!");
  }
  else{
    return head->info;
  }

}

//Back
template <typename Data>
Data& List<Data>::Back() const{
  if(head==nullptr){
    throw std::length_error("Empty List!");
  }
  else{
    return tail->info;
  }
}

//MapPreOrder
template <typename Data>
void List<Data>::MapPreOrder(const MapFunctor fun, void* par){
  for(ulong index = 0; index < size; index++){
    fun((*this)[index], par);
  }
}

//MapPostOrder
template <typename Data>
void List<Data>::MapPostOrder(const MapFunctor fun, void* par){
  ulong index = size;
  while(index>0) {
    fun((*this)[--index], par);
  }
}

//FoldPreOrder
template <typename Data>
void List<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc) const{
  for(ulong index = 0; index<size; index++) {
    fun((*this)[index], par, acc);
  }
}

//FoldPostOrder
template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc) const{
  ulong index = size;
  while(index>0) {
    fun((*this)[--index], par, acc);
  }
}
/* ************************************************************************** */

}

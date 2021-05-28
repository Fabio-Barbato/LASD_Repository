
namespace lasd {


/* ************************************************************************** */
//Push(copy)
template <typename Data>
void StackLst<Data>::Push(const Data& value){
  List<Data>::InsertAtFront(value);
}

//Push(move)
template <typename Data>
void StackLst<Data>::Push(Data&& value) noexcept{
  List<Data>::InsertAtFront(std::move(value));
}

//Top
template <typename Data>
Data& StackLst<Data>::Top() const{
  return List<Data>::Front();
}

//Pop
template <typename Data>
void StackLst<Data>::Pop(){
  List<Data>::RemoveFromFront();
  }


//TopNPop
template <typename Data>
Data StackLst<Data>::TopNPop(){
  return List<Data>::FrontNRemove();
}

//Clear
template <typename Data>
void StackLst<Data>::Clear(){
  List<Data>::Clear();
}

//Destructor
template <typename Data>
StackLst<Data>::~StackLst(){
  Clear();
}

//Comparison operators
template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& stck) const noexcept{
  return List<Data>::operator==(stck);
}

template <typename Data>
bool StackLst<Data>::operator!=(const StackLst<Data>& stck) const noexcept{
  return !(*this==stck);
}

//Move constructor
template <typename Data>
StackLst<Data>::StackLst(StackLst<Data>&& stk) noexcept{
  std::swap(head, stk.head);
  std::swap(size, stk.size);
}

//Move assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stk) noexcept{
  std::swap(head, stk.head);
  std::swap(size, stk.size);

  return *this;
}

//Copy constructor
template <typename Data>
StackLst<Data>::StackLst(const StackLst<Data>& stk) {
  struct List<Data>::Node* tmp = stk.head;
  StackLst<Data> tmp_stack;
  for (ulong i = 0; i < stk.size; i++) {
    tmp_stack.Push(tmp->info);
    tmp = tmp->next;
  }

  tmp = tmp_stack.head;
  for (ulong i = 0; i < stk.size; i++) {
    Push(tmp->info);
    tmp = tmp->next;
  }

}

//Copy assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stk){
  StackLst<Data>* tmpstk = new StackLst<Data>(stk);
  std::swap(*this, *tmpstk);
  delete tmpstk;
  return *this;
}


//Specific constructor
template <typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data>& con){
  size = 0;
  for (long i = con.Size()-1; i >= 0; i--){
    Push(con[i]);
  }
}
/* ************************************************************************** */

}

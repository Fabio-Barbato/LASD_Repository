
namespace lasd {


/* ************************************************************************** */
//Push(copy)
template <typename Data>
void StackLst<Data>::Push(const Data& value){
  List<Data>::Node::Node* tmp = new Node(value);
  if(head==nullptr){
    tmp->next = head;
    head = tmp;
  }
  else{
    tmp->next = head;
    head = tmp;
  }
  size++;
}

//Push(move)
template <typename Data>
void StackLst<Data>::Push(Data&& value) noexcept{
  Node* tmp = new Node(value);
  std::swap(tmp->info, value);
  if(head==nullptr){
    tmp->next = head;
    head = tmp;
  }
  else{
    tmp->next = head;
    head = tmp;
  }
  size++;
}

//Top
template <typename Data>
Data& StackLst<Data>::Top() const{
  if(head==nullptr){
    throw std::length_error("Empty Stack!");
  }
  else{
    return head->info;
  }
}

//Pop
template <typename Data>
void StackLst<Data>::Pop(){
  if(size>0){
    Node* tmp = head;
    head = tmp->next;
    size--;
    delete tmp;
  }else{
    throw std::length_error("Empty Stack!");
  }
}

//TopNPop
template <typename Data>
Data StackLst<Data>::TopNPop(){
  if(size>0){
    Data dat;
    Node* tmp = head;
    head = tmp->next;
    size--;
    dat = tmp->info;
    delete tmp;
    return dat;
  }else{
    throw std::length_error("Empty Stack!");
  }
}

//Clear
template <typename Data>
void StackLst<Data>::Clear(){
  ulong tmpsize = size;
  for (ulong i = 0; i < tmpsize; i++) {
    Pop();
  }
}

//Destructor
template <typename Data>
StackLst<Data>::~StackLst(){
  Clear();
}

//Comparison operators
template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& stck) const noexcept{
  if(size == stck.size){
    Node* tmp1 = head;
    Node* tmp2 = stck.head;
    while(tmp1!=nullptr && tmp1 == tmp2){
      tmp1 = tmp1->next;
      tmp2 = tmp2->next;
    }
    if(tmp1==nullptr){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
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
  StackLst<Data> tmp_stk;
  Node* tmp_node = stk.head;
  for (ulong i = 0; i < stk.size; i++) {
    tmp_stk.Push(tmp_node->info);
    tmp_node = tmp_node->next;
  }

  tmp_node = tmp_stk.head;
  for (ulong i = 0; i < tmp_stk.size; i++) {
    Push(tmp_node->info);
    tmp_node = tmp_node->next;
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
  for (ulong i = con.Size(); i >= 0; i--){
    Push(con[i]);
  }
}
/* ************************************************************************** */

}

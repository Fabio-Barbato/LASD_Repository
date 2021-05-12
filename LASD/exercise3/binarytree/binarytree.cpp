
#include "../queue/lst/queuelst.hpp"

#include "../stack/lst/stacklst.hpp"

namespace lasd {

/* ************************************************************************** */


//Node

//Comparison operator (Node)
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept{
    if(Element() != node.Element()){  //se gli elementi dei nodi sono diversi
      return false;
    }
    else{ //se gli elementi dei nodi sono uguali
      if(HasLeftChild() == node.HasLeftChild()){ //hanno o non hanno entrambi figlio sinistro
        if(HasLeftChild()){ //hanno figlio sinistro?
          return LeftChild() == node.LeftChild(); //vero se i sottoalber sx sono uguali, false altrimenti
        }
      }
      else{
        return false;
      }
      if(HasRightChild() == node.HasRightChild()){
        if(HasRightChild()){
          return RightChild() == node.RightChild();
        }
      }
      else{
        return false;
      }
      return true;
    }
}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept{
  return !(*this == node);
}


/*  ************************************************************** */

//BinaryTree


//Comparison operator
template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt) const noexcept{
  return (size == bt.size && Root() == bt.Root());
}

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& bt) const noexcept{
  return !(*this == bt);
}

//MapPreOrder
template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  if(size>0){
    MapPreOrderAux(fun, Root(), par);
  }
}

//MapPostOrder
template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  if(size>0){
    MapPostOrderAux(fun, Root(), par);
  }
}

//MapInOrder
template <typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par) {
  if(size>0){
    MapInOrderAux(fun, Root(), par);
  }
}

//FoldPreOrder
template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const{
  if(size>0){
    FoldPreOrderAux(fun, Root(), par, acc);
  }
}

//FoldInOrder
template <typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc) const{
  if(size>0){
    FoldInOrderAux(fun, Root(), par, acc);
  }
}

//FoldPostOrder
template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
  if(size>0){
    FoldPostOrderAux(fun, Root(), par, acc);
  }
}

//MapBreadth
template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par){
  if(size>0){
    Node* tmp = &Root();
    QueueLst<Node*>* queue = new QueueLst<Node*>();
    do {
      fun(tmp->Element(), par);
      if(tmp->HasLeftChild()){
        queue->Enqueue(&tmp->LeftChild());
      }
      if(tmp->HasRightChild()){
        queue->Enqueue(&tmp->RightChild());
      }
      tmp = queue->HeadNDequeue();
    } while (!queue->Empty());
    fun(tmp->Element(), par);
  }
}

//FoldBreadth
template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const{
  if(size>0){
    Node* tmp = &Root();
    QueueLst<Node*>* queue = new QueueLst<Node*>();
    do {
      fun(tmp->Element(), par, acc);
      if(tmp->HasLeftChild()){
        queue->Enqueue(&tmp->LeftChild());
      }
      if(tmp->HasRightChild()){
        queue->Enqueue(&tmp->RightChild());
      }
      tmp = queue->HeadNDequeue();
    } while (!queue->Empty());
    fun(tmp->Element(), par, acc);
    delete queue;
  }
}

//MapPreOrderAux
template <typename Data>
void BinaryTree<Data>::MapPreOrderAux(const MapFunctor fun, Node& node, void* par) {
  fun(node.Element(), &par);
  if(node.HasLeftChild()){
    MapPreOrderAux(fun, node.LeftChild(), par);
  }
  if(node.HasRightChild()){
    MapPreOrderAux(fun, node.RightChild(), par);
  }
}

//MapPostOrderAux
template <typename Data>
void BinaryTree<Data>::MapPostOrderAux(const MapFunctor fun, Node& node, void* par) {
  if(node.HasLeftChild()){
    MapPostOrderAux(fun, node.LeftChild(), par);
  }
  if(node.HasRightChild()){
    MapPostOrderAux(fun, node.RightChild(), par);
  }
  fun(node.Element(), par);
}

//MapInOrderAux
template <typename Data>
void BinaryTree<Data>::MapInOrderAux(const MapFunctor fun, Node& node, void* par) {
  if(node.HasLeftChild()){
    MapInOrderAux(fun, node.LeftChild(), par);
  }
  fun(node.Element(), par);
  if(node.HasRightChild()){
    MapInOrderAux(fun, node.RightChild(), par);
  }
}

//FoldPreOrderAux
template <typename Data>
void BinaryTree<Data>::FoldPreOrderAux(const FoldFunctor fun, Node& node, const void* par, void* acc) const{
  fun(node.Element(), par, acc);
  if(node.HasLeftChild()){
    FoldPreOrderAux(fun, node.LeftChild(), par, acc);
  }
  if(node.HasRightChild()){
    FoldPreOrderAux(fun, node.RightChild(), par, acc);
  }
}

//FoldPostOrderAux
template <typename Data>
void BinaryTree<Data>::FoldPostOrderAux(const FoldFunctor fun, Node& node, const void* par, void* acc) const{
  if(node.HasLeftChild()){
    FoldPostOrderAux(fun, node.LeftChild(), par, acc);
  }
  if(node.HasRightChild()){
    FoldPostOrderAux(fun, node.RightChild(), par, acc);
  }
  fun(node.Element(), par, acc);
}

//FoldInOrderAux
template <typename Data>
void BinaryTree<Data>::FoldInOrderAux(const FoldFunctor fun, Node& node, const void* par, void* acc) const{
  if(node.HasLeftChild()){
    FoldInOrderAux(fun, node.LeftChild(), par, acc);
  }
  fun(node.Element(), par, acc);
  if(node.HasRightChild()){
    FoldInOrderAux(fun, node.RightChild(), par, acc);
  }
}
/* ************************************************************************** */

//BTPreOrderIterator

//Specific constructor
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt){
    node = &bt.Root();
    stack = new StackLst<struct BinaryTree<Data>::Node*>();
  }

//Copy constructor
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& it){
    node = it.node;
    stack = it.stack;
  }

  //Move constructor
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& it) noexcept{
    std::swap(node, it.node);
    std::swap(stack, it.stack);
  }

  //Destructor
  template <typename Data>
  BTPreOrderIterator<Data>::~BTPreOrderIterator(){
    delete stack;
  }

  //Copy assignment
  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& it){
    BTPreOrderIterator<Data>* it_tmp = new BTPreOrderIterator<Data>(it);
    std::swap(*this, *it_tmp);
    delete it_tmp;

    return *this;
  }

  //Move assignment
  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& it) noexcept {
    std::swap(node, it.node);
    std::swap(stack, it.stack);

    return *this;
  }

  //Comparison operators
  template <typename Data>
  bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& it) const noexcept{
    return node == it.node && stack == it.stack;
  }

  template <typename Data>
  bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& it) const noexcept{
    return !(*this==it);
  }

  //Operator *
  template <typename Data>
  Data& BTPreOrderIterator<Data>::operator*() const{
    if(node == nullptr){
      throw std::out_of_range("Out of range!");
    }
    else{
      return node->Element();
    }
  }

  //Terminated
  template <typename Data>
  bool BTPreOrderIterator<Data>::Terminated() const noexcept{
    return (node == nullptr && stack->Empty());
  }

  //Operator ++
  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    if(!Terminated()){
      if(node->HasLeftChild()){
        if(node->HasRightChild()){
          stack->Push(&node->RightChild());
        }
        node = &node->LeftChild();
      }
      else if (node->HasRightChild()){
        node = &node->RightChild();
      }
      else{
        if(!stack->Empty()){
          node = stack->TopNPop();
        }
        else{
          node = nullptr;
        }
      }
    }

    return *this;
  }

  /*  ******************************************************************** */

  //BTPostOrderIterator

  //LeftMostLeaf
  template <typename Data>
  void BTPostOrderIterator<Data>::LeftMostLeaf(struct BinaryTree<Data>::Node& new_node){

    if(new_node.HasLeftChild() || new_node.HasRightChild()){
      if(new_node.HasLeftChild()){
        stack->Push(&new_node);
        LeftMostLeaf(new_node.LeftChild());
      }
      else{
        stack->Push(&new_node);
        LeftMostLeaf(new_node.RightChild());
      }
    }
    else{
      node = &new_node;
    }

  }

  //Specific constructor
    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt){
      stack = new StackLst<struct BinaryTree<Data>::Node*>();
      LeftMostLeaf(bt.Root());
    }

  //Copy constructor
    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& it){
      node = it.node;
      stack = it.stack;
    }

    //Move constructor
    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& it) noexcept{
      std::swap(node, it.node);
      std::swap(stack, it.stack);
    }

    //Destructor
    template <typename Data>
    BTPostOrderIterator<Data>::~BTPostOrderIterator(){
      delete stack;
    }

    //Copy assignment
    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& it){
      BTPostOrderIterator<Data>* it_tmp = new BTPostOrderIterator<Data>(it);
      std::swap(*this, *it_tmp);
      delete it_tmp;

      return *this;
    }

    //Move assignment
    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& it) noexcept {
      std::swap(node, it.node);
      std::swap(stack, it.stack);

      return *this;
    }

    //Comparison operators
    template <typename Data>
    bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& it) const noexcept{
      return node == it.node && stack == it.stack;
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& it) const noexcept{
      return !(*this==it);
    }

    //Operator *
    template <typename Data>
    Data& BTPostOrderIterator<Data>::operator*() const{
      if(node == nullptr){
        throw std::out_of_range("Out of range!");
      }
      else{
        return node->Element();
      }
    }

    //Terminated
    template <typename Data>
    bool BTPostOrderIterator<Data>::Terminated() const noexcept{
      return (node == nullptr && stack->Empty());
    }

    //Operator ++
    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++(){
      if(!Terminated()){
        if(!stack->Empty()){
          struct BinaryTree<Data>::Node* tmp = stack->Top();
          if(tmp->HasLeftChild()){
            if(node == &tmp->LeftChild() && tmp->HasRightChild()){
              LeftMostLeaf(tmp->RightChild());
            }
            else{
              if(stack->Empty()){
                node = nullptr;
              }
              else{
                node = stack->TopNPop();
              }
            }
          }
          else{
            node = stack->TopNPop();
          }
        }
        else{
          node = nullptr;
        }
      }
      return *this;
    }


  /*  ************************************************************************* */

  //BTInOrderIterator


  //LeftMostChild
  template <typename Data>
  void BTInOrderIterator<Data>::LeftMostChild(struct BinaryTree<Data>::Node& new_node) {
    if(new_node.HasLeftChild()){
      stack->Push(&new_node);
      LeftMostChild(new_node.LeftChild());
    }
    else
      node = &new_node;
  }

  //Specific constructor
    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt){
      stack = new StackLst<struct BinaryTree<Data>::Node*>();
      LeftMostChild(bt.Root());
    }

  //Copy constructor
    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& it){
      node = it.node;
      stack = it.stack;
    }

    //Move constructor
    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& it) noexcept{
      std::swap(node, it.node);
      std::swap(stack, it.stack);
    }

    //Destructor
    template <typename Data>
    BTInOrderIterator<Data>::~BTInOrderIterator(){
      delete stack;
    }

    //Copy assignment
    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& it){
      BTInOrderIterator<Data>* it_tmp = new BTInOrderIterator<Data>(it);
      std::swap(*this, *it_tmp);
      delete it_tmp;

      return *this;
    }

    //Move assignment
    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& it) noexcept {
      std::swap(node, it.node);
      std::swap(stack, it.stack);

      return *this;
    }

    //Comparison operators
    template <typename Data>
    bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& it) const noexcept{
      return node == it.node && stack == it.stack;
    }

    template <typename Data>
    bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& it) const noexcept{
      return !(*this==it);
    }

    //Operator *
    template <typename Data>
    Data& BTInOrderIterator<Data>::operator*() const{
      if(node == nullptr){
        throw std::out_of_range("Out of range!");
      }
      else{
        return node->Element();
      }
    }

    //Terminated
    template <typename Data>
    bool BTInOrderIterator<Data>::Terminated() const noexcept{
      return (node == nullptr && stack->Empty());
    }

    //Operator ++
    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
      if(!Terminated()){
        if(node->HasRightChild()){
          LeftMostChild(node->RightChild());
        }
        else{
          if(!stack->Empty()){
            node = stack->TopNPop();
          }
          else{
            node = nullptr;
          }
        }
      }

      return *this;
    }


/*    ************************************************************************* */

//BTBreadthIterator

//Specific constructor
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt){
    queue = new QueueLst<struct BinaryTree<Data>::Node*>();
    node = &bt.Root();
  }

//Copy constructor
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& it){
    node = it.node;
    queue = it.queue;
  }

  //Move constructor
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& it) noexcept{
    std::swap(node, it.node);
    std::swap(queue, it.queue);
  }

  //Destructor
  template <typename Data>
  BTBreadthIterator<Data>::~BTBreadthIterator(){
    delete queue;
  }

  //Copy assignment
  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& it){
    BTBreadthIterator<Data>* it_tmp = new BTBreadthIterator<Data>(it);
    std::swap(*this, *it_tmp);
    delete it_tmp;

    return *this;
  }

  //Move assignment
  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& it) noexcept {
    std::swap(node, it.node);
    std::swap(queue, it.queue);

    return *this;
  }

  //Comparison operators
  template <typename Data>
  bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& it) const noexcept{
    return node == it.node && queue == it.queue;
  }

  template <typename Data>
  bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& it) const noexcept{
    return !(*this==it);
  }

  //Operator *
  template <typename Data>
  Data& BTBreadthIterator<Data>::operator*() const{
    if(node == nullptr){
      throw std::out_of_range("Out of range!");
    }
    else{
      return node->Element();
    }
  }

  //Terminated
  template <typename Data>
  bool BTBreadthIterator<Data>::Terminated() const noexcept{
    return (node == nullptr && queue->Empty());
  }

  //Operator ++
  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    if(!Terminated()){
      if(node->HasLeftChild()){
        queue->Enqueue(&node->LeftChild());
      }
      if(node->HasRightChild()){
        queue->Enqueue(&node->RightChild());
      }
      if(!queue->Empty())
        node = queue->HeadNDequeue();
      else
        node = nullptr;
    }

    return *this;
  }
}

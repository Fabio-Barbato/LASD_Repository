
#include "../queue/vec/queuevec.hpp"

#include "../stack/vec/stackvec.hpp"

namespace lasd {

/* ************************************************************************** */


//Node

//Comparison operator (Node)
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept{
    if(Element() != node.Element()){
      return false;
    }
    else{
      if(HasLeftChild() == node.HasLeftChild()){
        if(HasLeftChild){
          LeftChild() == node.LeftChild();
        }
      }
      else{
        return false;
      }
      if(HasRightChild() == node.HasRightChild()){
        if(HasRightChild){
          RightChild() == node.RightChild();
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
  return Root() == bt.Root();
}

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& bt) const noexcept{
  return !(*this == bt);
}

//MapPreOrder
template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  if(size!=0){
    Node* tmp = Root();
    MapPreOrderAux(&fun, &tmp, &par);
  }
}

//MapPostOrder
template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  if(size!=0){
    Node* tmp = Root();
    MapPostOrderAux(&fun, &tmp, &par);
  }
}

//MapInOrder
template <typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par) {
  if(size!=0){
    Node* tmp = Root();
    MapInOrderAux(&fun, &tmp, &par);
  }
}

//FoldPreOrder
template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const{
  if(size!=0){
    Node* tmp = Root();
    FoldPreOrderAux(&fun, &tmp, &par, &acc);
  }
}

//FoldPostOrder
template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
  if(size!=0){
    Node* tmp = Root();
    FoldPostOrderAux(&fun, &tmp, &par, &acc);
  }
}

//MapBreadth
template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par){
  if(size!=0){
    Node* tmp = Root();
    QueueVec<Node*> queue = new QueueVec<Node*>();
    do {
      fun(&tmp, par);
      if(tmp.HasLeftChild()){
        queue.Enqueue();
      }
      if(tmp.HasRightChild()){
        queue.Enqueue();
      }
      tmp = queue.HeadNDequeue();
    } while (!queue.Empty());
    fun(&tmp, par);
  }
}

//FoldBreadth
template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const{
  if(size!=0){
    Node* tmp = Root();
    QueueVec<Node*> queue = new QueueVec<Node*>();
    do {
      fun(&tmp, par, acc);
      if(tmp.HasLeftChild()){
        queue.Enqueue();
      }
      if(tmp.HasRightChild()){
        queue.Enqueue();
      }
      tmp = queue.HeadNDequeue();
    } while (!queue.Empty());
    fun(&tmp, par, acc);
  }
}

//MapPreOrderAux
template <typename Data>
void BinaryTree<Data>::MapPreOrderAux(const MapFunctor fun, Node* node, void* par) {
  fun(&node, par);
  if(node.HasLeftChild()){
    MapPreOrderAux(&fun, node.LeftChild(), &par);
  }
  if(node.HasRightChild()){
    MapPreOrderAux(&fun, node.RightChild(), &par);
  }
}

//MapPostOrderAux
template <typename Data>
void BinaryTree<Data>::MapPostOrderAux(const MapFunctor fun, Node* node, void* par) {
  if(node.HasLeftChild()){
    MapPostOrderAux(&fun, node.LeftChild(), &par);
  }
  if(node.HasRightChild()){
    MapPostOrderAux(&fun, node.RightChild(), &par);
  }
  fun(&node, par);
}

//MapInOrderAux
template <typename Data>
void BinaryTree<Data>::MapInOrderAux(const MapFunctor fun, Node* node, void* par) {
  if(node.HasLeftChild()){
    MapInOrderAux(&fun, node.LeftChild(), &par);
  }
  fun(&node, par);
  if(node.HasRightChild()){
    MapInOrderAux(&fun, node.RightChild(), &par);
  }
}

//FoldPreOrderAux
template <typename Data>
void BinaryTree<Data>::FoldPreOrderAux(const FoldFunctor fun, Node* node, const void* par, void* acc) const{
  fun(&node, par);
  if(node.HasLeftChild()){
    FoldPreOrderAux(&fun, node.LeftChild(), &par, &acc);
  }
  if(node.HasRightChild()){
    FoldPreOrderAux(&fun, node.RightChild(), &par, &acc);
  }
}

//FoldPostOrderAux
template <typename Data>
void BinaryTree<Data>::FoldPostOrderAux(const FoldFunctor fun, Node* node, const void* par, void* acc) const{
  if(node.HasLeftChild()){
    FoldPostOrderAux(&fun, node.LeftChild(), &par, &acc);
  }
  if(node.HasRightChild()){
    FoldPostOrderAux(&fun, node.RightChild(), &par, &acc);
  }
  fun(&node, par);
}

//FoldInOrderAux
template <typename Data>
void BinaryTree<Data>::FoldInOrderAux(const FoldFunctor fun, Node* node, const void* par, void* acc) const{
  if(node.HasLeftChild()){
    FoldInOrderAux(&fun, node.LeftChild(), &par, &acc);
  }
  fun(&node, par);
  if(node.HasRightChild()){
    FoldInOrderAux(&fun, node.RightChild(), &par, &acc);
  }
}
/* ************************************************************************** */

//BTPreOrderIterator

//Specific constructor
  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt){
    node = bt.Root();
    stack = new StackVec<Data>();
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
    delete node;
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
  struct BinaryTree<Data>::Node& BTPreOrderIterator<Data>::operator*() const{
    if(node == nullptr){
      std::out_of_range("Out of range!");
    }
    else{
      return *node;
    }
  }

  //Terminated
  template <typename Data>
  bool BTPreOrderIterator<Data>::Terminated() const noexcept{
    return (node == nullptr);
  }

  //Operator ++
  template <typename Data>
  struct BinaryTree<Data>::Node& BTPreOrderIterator<Data>::operator++() {
    if(node != nullptr){
      if(node.HasLeftChild()){
        if(node.HasRightChild()){
          stack.Push(node.RightChild());
        }
        node = node.LeftChild();
      }
      else if (node.HasRightChild()){
        node = node.RightChild();
      }
      else{
        if(!stack.Empty()){
          node = stack.TopNPop();
        }
        else{
          std::out_of_range("Out of range!");
        }
      }
    }
    else{
      std::out_of_range("Out of range!");
    }
  }

  /*  ******************************************************************** */

  //BTPostOrderIterator

  //LeftMostLeaf
  template <typename Data>
  struct BinaryTree<Data>::Node& BTPostOrderIterator<Data>::LeftMostLeaf(struct BinaryTree<Data>::Node& node) const noexcept{
    if(node.HasLeftChild()){
      stack.Push(node);
      LeftMostLeaf(node.LeftChild());
    }
    if(node.HasRightChild()){
      stack.Push(node);
      LeftMostLeaf(node.RightChild());
    }

    return node;
  }

  //Specific constructor
    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt){
      stack = new StackVec<Data>();
      node = LeftMostLeaf(bt.Root());
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
      delete node;
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
    struct BinaryTree<Data>::Node& BTInOrderIterator<Data>::operator*() const{
      if(node == nullptr){
        std::out_of_range("Out of range!");
      }
      else{
        return *node;
      }
    }

    //Terminated
    template <typename Data>
    bool BTInOrderIterator<Data>::Terminated() const noexcept{
      return (node == nullptr);
    }

    //Operator ++
    template <typename Data>
    struct BinaryTree<Data>::Node& BTInOrderIterator<Data>::operator++(){
      if(node!=nullptr){
        if(stack.Empty()){
          std::out_of_range("Out of range!");
        }
        else{
          Node* tmp = stack.Top();
          if(tmp.HasLeftChild()){
            if(node == tmp.LeftChild()){
              node = LeftMostLeaf(tmp.RightChild());
            }
            else{
              if(stack.Empty()){
                std::out_of_range("Out of range!");
              }
              else{
                node = stack.TopNPop();
              }
            }
          }
          else{
            node = stack.TopNPop();
          }

        }
      }
    }


  /*  ************************************************************************* */

  //BTInOrderIterator


  //LeftMostChild
  template <typename Data>
  struct BinaryTree<Data>::Node& BTInOrderIterator<Data>::LeftMostChild(struct BinaryTree<Data>::Node& node) const noexcept{
    if(node.HasLeftChild()){
      stack.Push(node);
      LeftMostChild(node.LeftChild());
    }

    return node;
  }
  //Specific constructor
    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt){
      stack = new StackVec<Data>();
      node = LeftMostChild(bt.Root());
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
      delete node;
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
    struct BinaryTree<Data>::Node& BTInOrderIterator<Data>::operator*() const{
      if(node == nullptr){
        std::out_of_range("Out of range!");
      }
      else{
        return *node;
      }
    }

    //Terminated
    template <typename Data>
    bool BTInOrderIterator<Data>::Terminated() const noexcept{
      return (node == nullptr);
    }

    //Operator ++
    template <typename Data>
    struct BinaryTree<Data>::Node& BTInOrderIterator<Data>::operator++() {
      if(node!=nullptr){
        if(node.HasRightChild()){
          node = node.LeftMostChild(node.RightChild());
        }
        else{
          if(!stack.Empty()){
            node = stack.TopNPop();
          }
          else{
            std::out_of_range("Out of range!");
          }

        }
      }
      else{
        std::out_of_range("Out of range!");
      }
    }
}

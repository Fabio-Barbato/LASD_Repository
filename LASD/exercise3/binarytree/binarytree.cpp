
#include "../queue/vec/queuevec.hpp"

#include "../stack/lst/stacklst.hpp"

namespace lasd {

/* ************************************************************************** */

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

}

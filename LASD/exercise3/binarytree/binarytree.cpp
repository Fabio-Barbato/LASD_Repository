
#include "../queue/lst/queuelst.hpp"

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

/* ************************************************************************** */

}

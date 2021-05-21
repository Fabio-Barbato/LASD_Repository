
namespace lasd {

/* ************************************************************************** */


 //Specific constructor
 template <typename Data>
 BST<Data>::BST(const LinearContainer<Data>& con){
   for (ulong i = 0; i < con.Size(); i++) {
     Insert(con[i]);
   }
 }

  //Copy constructor
  template <typename Data>
  BST<Data>::BST(const BST<Data>& bt){
    BinaryTreeLnk<Data>::BinaryTreeLnk(bt);
  }

  //Move constructor
  template <typename Data>
  BST<Data>::BST(BST<Data>&& bt) noexcept{
    BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(bt));
  }

  //Copy assignment
  template <typename Data>
  BST<Data>& BST<Data>::operator=(const BST<Data>& bt){
    return BinaryTreeLnk<Data>::operator=(bt);
  }

  //Move assignment
  template <typename Data>
  BST<Data>& BST<Data>::operator=(BST<Data>&& bt) noexcept{
    return BinaryTreeLnk<Data>::operator=(std::move(bt));
  }

  //Comparison operators
  template <typename Data>
  bool BST<Data>::operator==(const BST<Data>& bt) const noexcept{
    if(*this.size == bt.size){
      BTInOrderIterator<Data> it1(*this);
      BTInOrderIterator<Data> it2(bt);
      while (*it1==*it2 && !it1.Terminated()) {
        ++it1;
        ++it2;
      }
      if(it1.Terminated())
        return true;
      else
        return false;
    }
    else
      return false;
  }

  template <typename Data>
  bool BST<Data>::operator!=(const BST<Data>& bt) const noexcept{
    return !(*this==bt);
  }



//Insert(Copy)
 template <typename Data>
 void BST<Data>::Insert(const Data& dat){
   NodeLnk*& pt = FindPointerTo(root, dat);
   if(pt == nullptr){
     pt = new NodeLnk(dat);
     size++;
   }
 }

 //Insert(move)
 template <typename Data>
 void BST<Data>::Insert(Data&& dat) noexcept{
   NodeLnk*& pt = FindPointerTo(root, dat);
   if(pt == nullptr){
     pt = new NodeLnk(std::move(dat));
     size++;
   }
 }

 //Remove
 template <typename Data>
 void BST<Data>::Remove(const Data& dat) noexcept{
   delete Detach(FindPointerTo(root, dat));
   size--;
 }

 //Min
 template <typename Data>
 const Data& BST<Data>::Min() const{
   if(root==nullptr){
     throw std::length_error("Empty!");
   }else{
     return FindPointerToMin(root)->info;
   }
 }

 /*
 Data MinNRemove(); // (concrete function must throw std::length_error when empty)
 void RemoveMin(); // (concrete function must throw std::length_error when empty)*/

 //Max
 template <typename Data>
 const Data& BST<Data>::Max() const{
   if(root==nullptr){
     throw std::length_error("Empty!");
   }else{
     return FindPointerToMax(root)->info;
   }
 }

 /*
 Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
 void RemoveMax(); // (concrete function must throw std::length_error when empty)

 Data& Predecessor(const Data&); // (concrete function must throw std::length_error when not found)
 Data PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
 void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when not found)

 Data& Successor(const Data&); // (concrete function must throw std::length_error when not found)
 Data SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
 void RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when not found)*/

//Detach
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& pt) noexcept{
  if (pt!=nullptr){
    if(pt->HasLeftChild() && pt->HasRightChild()){
      NodeLnk* tmp = DetachMin(pt->right);
      std::swap(tmp->info, pt->info);
      return tmp;
    }
    else if(pt->HasLeftChild()){
      NodeLnk* tmp = pt->left;
      std::swap(pt, tmp);
      tmp->left = nullptr;
      return tmp;
    }
    else if(pt->HasRightChild()){
      NodeLnk* tmp = pt->right;
      std::swap(pt, tmp);
      tmp->right = nullptr;
      return tmp;
    }
    else
      return pt;
  }else
    return nullptr;

}

//DetachMin
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& pt) noexcept{
  return SkipOnLeft(FindPointerToMin(pt));
}

//DetachMax
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& pt) noexcept{
  return SkipOnRight(FindPointerToMax(pt));
}

//SkipOnLeft
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnLeft(NodeLnk*& pt) noexcept{
  NodeLnk* tmp = nullptr;
  std::swap(tmp, pt->right);
  std::swap(tmp, pt);

  return tmp;
}

//SkipOnRight
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnRight(NodeLnk*& pt) noexcept{
  NodeLnk* tmp = nullptr;
  std::swap(tmp, pt->left);
  std::swap(tmp, pt);

  return tmp;
}

//FindPointerTo(const)
template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& pt, const Data& dat) const noexcept{
  if(pt!=nullptr && pt->info<dat && !pt->HasRightChild())
   return pt->right;
   else if(pt!=nullptr && pt->info>dat && !pt->HasLeftChild())
    return pt->left;
    else if(pt!=nullptr && pt->info<dat && pt->HasRightChild())
     return FindPointerTo(pt->right, dat);
     else if(pt!=nullptr && pt->info>dat && pt->HasLeftChild())
      return FindPointerTo(pt->left, dat);
     else
       return pt;
}


//FindPointerTo
template <typename Data>
 typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& pt, const Data& dat) noexcept{
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(pt, dat));
 }



 //FindPointerToMin
 template <typename Data>
 typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& pt) noexcept{
   return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(pt));
 }


 //FindPointerToMin(const)
 template <typename Data>
 typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& pt) const noexcept{
   if(pt==nullptr || !pt->HasLeftChild())
     return pt;
   else
    return FindPointerToMin(pt->left);
 }

 //FindPointerToMax
 template <typename Data>
 typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& pt) noexcept{
   return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(pt));
 }

//FindPointerToMax(const)
template <typename Data>
 typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& pt) const noexcept{
   if(pt==nullptr || !pt->HasRightChild())
     return pt;
   else
    return FindPointerToMax(pt->right);
 }

/* ************************************************************************** */

}

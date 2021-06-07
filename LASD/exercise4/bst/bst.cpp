
namespace lasd {

/* ************************************************************************** */


 //Specific constructor
 template <typename Data>
 BST<Data>::BST(const LinearContainer<Data>& con){
   for (ulong i = 0; i < con.Size(); i++) {
     Insert(con[i]);
   }
 }


  //Copy assignment
  template <typename Data>
  BST<Data>& BST<Data>::operator=(const BST<Data>& bt){
    BST<Data>* tmp = new BST<Data>(bt);
    std::swap(*this, *tmp);
    delete tmp;

    return *this;
  }

  //Move assignment
  template <typename Data>
  BST<Data>& BST<Data>::operator=(BST<Data>&& bt) noexcept{
    std::swap(root, bt.root);
    std::swap(size, bt.size);

    return *this;
  }

  //Comparison operators
  template <typename Data>
  bool BST<Data>::operator==(const BST<Data>& bt) const noexcept{
    if(size == bt.size){
      if(size>0){
        BTInOrderIterator<Data> it1(*this);
        BTInOrderIterator<Data> it2(bt);
        while (!it1.Terminated() && *it1==*it2) {
          ++it1;
          ++it2;
        }
        return it1.Terminated();
      }
      else
        return true;

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
   NodeLnk* tmp = Detach(FindPointerTo(root, dat));
   if(tmp!=nullptr){
     delete tmp;
     size--;
   }
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

 //MinNRemove
 template <typename Data>
 Data BST<Data>::MinNRemove(){
   if(root!=nullptr){
     NodeLnk*& tmp = FindPointerToMin(root);
     Data dat = tmp->info;
     delete Detach(tmp);
     size--;
     return dat;
   }else
    throw std::length_error("Empty");

 }

 //RemoveMin
 template <typename Data>
 void BST<Data>::RemoveMin(){
   if(root!=nullptr){
     delete Detach(FindPointerToMin(root));
     size--;
   }else
    throw std::length_error("Empty");
 }

 //Max
 template <typename Data>
 const Data& BST<Data>::Max() const{
   if(root==nullptr){
     throw std::length_error("Empty!");
   }else{
     return FindPointerToMax(root)->info;
   }
 }


 //MaxNRemove
 template <typename Data>
 Data BST<Data>::MaxNRemove(){
   if(root!=nullptr){
     NodeLnk*& tmp = FindPointerToMax(root);
     Data dat = tmp->info;
     delete Detach(tmp);
     size--;
     return dat;
   }else
    throw std::length_error("Empty");

 }


 //RemoveMax
 template <typename Data>
 void BST<Data>::RemoveMax(){
   if(root!=nullptr){
     delete Detach(FindPointerToMax(root));
     size--;
   }else
    throw std::length_error("Empty");
 }

//Predecessor
 template <typename Data>
 const Data& BST<Data>::Predecessor(const Data& dat) const{
   typename BST<Data>::NodeLnk* tmp = FindPointerToPredecessor(root, dat, nullptr);
   if(tmp != nullptr)
    return tmp->info;
    else
      throw std::length_error("Not found");
 }

 //PredecessorNRemove
 template <typename Data>
 Data BST<Data>::PredecessorNRemove(const Data& dat){
   NodeLnk* tmp = FindPointerToPredecessor(root, dat, nullptr);
   if(tmp!= nullptr){
     Data pre = tmp->info;
     Remove(tmp->info);
     return pre;
   }
   else
    throw std::length_error("Not found");
 }

 //RemovePredecessor
 template <typename Data>
 void BST<Data>::RemovePredecessor(const Data& dat){
   typename BST<Data>::NodeLnk* tmp = FindPointerToPredecessor(root, dat, nullptr);
   if(tmp!=nullptr){
     Remove(tmp->info);
   }else
    throw std::length_error("Not found");

 }

 //Successor
 template <typename Data>
 const Data& BST<Data>::Successor(const Data& dat) const{
   typename BST<Data>::NodeLnk* tmp = FindPointerToSuccessor(root, dat, nullptr);
   if(tmp != nullptr)
    return tmp->info;
    else
      throw std::length_error("Not found");
 }

 //SuccessorNRemove
 template <typename Data>
 Data BST<Data>::SuccessorNRemove(const Data& dat){
   typename BST<Data>::NodeLnk* tmp = FindPointerToSuccessor(root, dat, nullptr);
   if(tmp!= nullptr){
     Data pre = tmp->info;
     Remove(tmp->info);
     return pre;
   }
   else
    throw std::length_error("Not found");
 }

 //RemoveSuccessor
 template <typename Data>
 void BST<Data>::RemoveSuccessor(const Data& dat){
   typename BST<Data>::NodeLnk* tmp = FindPointerToSuccessor(root, dat, nullptr);
   if(tmp!=nullptr){
     Remove(tmp->info);
   }else
    throw std::length_error("Not found");

 }


 //Exists
 template <typename Data>
 bool BST<Data>::Exists(const Data& dat) const noexcept{
   return (FindPointerTo(root,dat)!=nullptr);
 }

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
      return SkipOnLeft(pt);
    }
    else if(pt->HasRightChild()){
      return SkipOnRight(pt);
    }
    else{
      NodeLnk* tmp = pt;
      pt = nullptr;
      return tmp;
    }

  }else
    return nullptr;

}

//DetachMin
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& pt) noexcept{
  return SkipOnRight(FindPointerToMin(pt));
}

//DetachMax
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& pt) noexcept{
  return SkipOnLeft(FindPointerToMax(pt));
}

//SkipOnLeft
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnLeft(NodeLnk*& pt) noexcept{
  NodeLnk* tmp = pt;
  pt = tmp->left;
  tmp->left = nullptr;

  return tmp;
}

//SkipOnRight
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::SkipOnRight(NodeLnk*& pt) noexcept{
  NodeLnk* tmp = pt;
  pt = tmp->right;
  tmp->right = nullptr;

  return tmp;
}

//FindPointerTo(const)
template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& pt, const Data& dat) const noexcept{
  if(pt!=nullptr && pt->info<dat)
     return FindPointerTo(pt->right, dat);
     else if(pt!=nullptr && pt->info>dat)
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

template <typename Data>
 typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(NodeLnk*& pt, const Data& dat, NodeLnk*& stima) noexcept{
   return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(pt,dat,stima));
 }

 template <typename Data>
 typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(NodeLnk* const& pt, const Data& dat, NodeLnk* const& stima) const noexcept{
   if (pt != nullptr){
     if(pt->info < dat)
      return FindPointerToPredecessor(pt->right, dat, pt);
     else if(pt->info > dat)
      return FindPointerToPredecessor(pt->left, dat, stima);
     else{
       if(pt->HasLeftChild())
      return FindPointerToMax(pt->left);

     }
   }
    return stima;
 }

 template <typename Data>
  typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(NodeLnk*& pt, const Data& dat, NodeLnk*& stima) noexcept{
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(pt,dat,stima));
  }

  template <typename Data>
  typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(NodeLnk* const& pt, const Data& dat, NodeLnk* const& stima) const noexcept{
    if (pt != nullptr){
      if(pt->info < dat)
       return FindPointerToSuccessor(pt->right, dat, stima);
      else if(pt->info > dat)
       return FindPointerToSuccessor(pt->left, dat, pt);
      else{
        if(pt->HasRightChild())
        return FindPointerToMin(pt->right);
      }
    }
     return stima;
  }

/* ************************************************************************** */

}

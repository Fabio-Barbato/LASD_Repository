
namespace lasd {

/* ************************************************************************** */

  //Specific constructor
  template <typename Data>
  BinaryTreeVec<Data>::NodeVec::NodeVec(const Data& dat, const ulong new_index, Vector<NodeVec*>* vec){
    info = dat;
    index = new_index;
    vec_node = vec;
  }

  // Copy assignment
  template<typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec& node){
    info = node.info;
    index = node.index;
    vec_node = new Vector<Data>(node.vec_node);
  }

  // Move assignment
  template<typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& node) noexcept{
    std::swap(info, node.info);
    std::swap(index, node.index);
    vec_node = new Vector<Data>(std::move(node.vec_node));
  }

  /* ********************************************************************** */

  // Specific member functions

  //Element
  template<typename Data>
   Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept{
     return info;
   }

   //Element (Immutable)
   template<typename Data>
   const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept{
     return info;
   }

   //IsLeaf
   template<typename Data>
   bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept{
     return (!HasLeftChild() && !HasRightChild());
   }

   //HasLeftChild
   template<typename Data>
   bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept{
     return 2*index+1 < vec_node->Size();
   }

   //HasRightChild
   template<typename Data>
   bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
     return 2*index+2 < vec_node->Size();
   }

   //LeftChild
   template<typename Data>
   struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const{
     return *(vec_node->operator[](2*index+1));
   }

   //RightChild
   template<typename Data>
   struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const{
     return *(vec_node->operator[](2*index+2));
   }

/* ************************************************************************** */

//BinaryTreeVec

  //Specific constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& con): vec_bt(con.Size()){
    for (ulong i = 0; i < con.Size(); i++) {
      vec_bt[i] = new NodeVec(con[i], i, &vec_bt);
    }
  }

  //Copy constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& binarytree){
    size = binarytree.size;
    vec_bt = binarytree.vec_bt;
  }

  //Move constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& binarytree) noexcept{
    std::swap(size, binarytree.size);
    vec_bt = std::move(binarytree.vec_bt);
  }

  //Copy assignment
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& binarytree ){
    BinaryTreeVec<Data>* tmp = new BinaryTreeVec<Data>(binarytree);
    std::swap(*this, *tmp);
    delete tmp;
    return *this;
  }

  //Move assignment
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& binarytree ) noexcept{
    std::swap(size, binarytree.size);
    vec_bt = std::move(binarytree.vec_bt);

    return *this;
  }

  //Root
  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const{
    if(size>0)
      return *vec_bt[0];
    else
      throw std::length_error("length_error");
  }

  //Clear
  template <typename Data>
  void BinaryTreeVec<Data>::Clear(){
    vec_bt.Clear();
    size=0;
  }
}

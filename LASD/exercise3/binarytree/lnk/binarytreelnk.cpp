
namespace lasd {

/* ************************************************************************** */

//NodeLnk


  //Specific constructor
  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const LinearContainer<Data>& con, ulong index){
    info = con[index];
    if (2*index+1< con.Size()) {
      left = new NodeLnk(con,2*index+1);
    }
    if (2*index+2< con.Size()) {
      right = new NodeLnk(con,2*index+2);
    }
  }

  // Destructor
  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::~NodeLnk(){
    delete left;
    delete right;
  }

  /* ********************************************************************** */

  // Copy assignment
  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& node){
    info = node.info;
    left = node.left;
    right = node.right;

    return *this;
  }

  // Move assignment
  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& node) noexcept{
    std::swap(info,node.info);
    std::swap(left,node.left);
    std::swap(right,node.right);

    return *this;
  }

  /* ********************************************************************** */

  // Specific member functions

  // Mutable access to the element
  template <typename Data>
  Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept{
    return info;
  }

  // Immutable access to the element
  template <typename Data>
  const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept{
    return info;
  }

  //IsLeaf
  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::IsLeaf() const noexcept{
    return (left==nullptr && right==nullptr);
  }

  //HasLeftChild
  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept{
    return (left!=nullptr);
  }

  //HasRightChild
  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept{
    return (right!=nullptr);
  }

  //LeftChild
  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const{
    if(left==nullptr){
      throw std::out_of_range("Out of range!");
    }
    else{
      return *left;
    }
  }

  //RightChild
  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const{
    if(right==nullptr){
      throw std::out_of_range("Out of range!");
    }
    else{
      return *right;
    }
  }

/* ************************************************************************** */

//BinaryTreeLnk


// Specific constructors
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& con){
  if(con.Size()>0){
    root = new NodeLnk(con, 0);
    size = con.Size();
  }
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& bt){
  root = bt.root;
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& bt) noexcept{
  std::swap(root, bt.root);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk(){
  delete root;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt){
  BinaryTreeLnk<Data>* tmp = new BinaryTreeLnk<Data>(bt);
  std::swap(*this, *tmp);
  delete tmp;

  return *this;
}

// Move assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) noexcept{
  std::swap(root, bt.root);

  return *this;
}

/* ************************************************************************ *

// Comparison operators
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>&) const noexcept;
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>&) const noexcept;

/* ************************************************************************ */

// Specific member functions (inherited from BinaryTree)


//Root
template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const{
  if(root==nullptr){
    throw std::length_error("Empty");
  }
  else{
    return *root;
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

//Clear
template <typename Data>
void BinaryTreeLnk<Data>::Clear(){
  delete root;
  }

}

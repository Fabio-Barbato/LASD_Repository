
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec: virtual public BinaryTree<Data> { // Must extend BinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  // ...

  struct NodeVec: virtual public BinaryTree<Data>::Node { // Must extend Node

  private:

    // ...

  protected:

    Data info;
    ulong index = 0;
    Vector<NodeVec*> vec_node;

  public:

    // Destructor
    ~NodeVec() = default;

    /* ********************************************************************** */

    // Copy assignment
    NodeVec& operator=(const NodeVec&);

    // Move assignment
    NodeVec& operator=(NodeVec&&) noexcept;

    /* ********************************************************************** */

    // Specific member functions

     Data& Element() noexcept;
     const Data& Element() const noexcept;

     bool IsLeaf() const noexcept;
     bool HasLeftChild() const noexcept;
     bool HasRightChild() const noexcept;

     NodeVec& LeftChild() const;
     NodeVec& RightChild() const;

  };

  Vector<NodeVec*> vec_bt;;

public:

  // Default constructor
    BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
    BinaryTreeVec(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
    BinaryTreeVec(const BinaryTreeVec<Data>&);

  // Move constructor
    BinaryTreeVec(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
    ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec<Data>& operator=(const BinaryTreeVec<Data>&);

  // Move assignment
  BinaryTreeVec<Data>& operator=(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data>&) const noexcept;
  bool operator!=(const BinaryTreeVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif

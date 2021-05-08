
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk: virtual public BinaryTree<Data> { // Must extend BinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  // ...

  struct NodeLnk: virtual public BinaryTree<Data>::Node { // Must extend Node

  private:

    // ...

  protected:

    Data info;
    NodeLnk* left = nullptr;
    NodeLnk* right = nullptr;

    //Specific constructor
    NodeLnk(const LinearContainer<Data>&, ulong);

  public:

    // Destructor
    ~NodeLnk();

    /* ********************************************************************** */

    // Copy assignment
    NodeLnk& operator=(const NodeLnk&); // Copy assignment of abstract types should not be possible.

    // Move assignment
    NodeLnk& operator=(NodeLnk&&) noexcept; // Move assignment of abstract types should not be possible.

    /* ********************************************************************** */

    // Specific member functions

   Data& Element() noexcept; // Mutable access to the element (concrete function should not throw exceptions)
   Data& Element() const noexcept; // Immutable access to the element (concrete function should not throw exceptions)

   bool IsLeaf() const noexcept; // (concrete function should not throw exceptions)
   bool HasLeftChild() const noexcept; // (concrete function should not throw exceptions)
   bool HasRightChild() const noexcept; // (concrete function should not throw exceptions)

   NodeLnk& LeftChild() const; // (concrete function must throw std::out_of_range when not existent)
   NodeLnk& RightChild() const; // (concrete function must throw std::out_of_range when not existent)

  };

  NodeLnk* root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk<Data>& operator=(const BinaryTreeLnk<Data>&);

  // Move assignment
  BinaryTreeLnk<Data>& operator=(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ *

  // Comparison operators
  bool operator==(const BinaryTreeLnk<Data>&) const noexcept;
  bool operator!=(const BinaryTreeLnk<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif

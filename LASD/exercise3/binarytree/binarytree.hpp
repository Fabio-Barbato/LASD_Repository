
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

#include "../iterator/iterator.hpp"

#include "../queue/vec/queuevec.hpp"

#include "../stack/vec/stackvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree: virtual public InOrderMappableContainer<Data>, virtual public BreadthMappableContainer<Data>, virtual public InOrderFoldableContainer<Data>, virtual public BreadthFoldableContainer<Data> { // Must extend InOrder/BreadthMappableContainer<Data> and InOrder/BreadthFoldableContainer<Data>

private:

  // ...

protected:

  using BreadthMappableContainer<Data>::size;

public:

  struct Node {

  private:

    // ...

  protected:

    // Comparison operators
    bool operator==(const Node&) const noexcept; // Comparison of abstract types is possible, but should not be visible.
    bool operator!=(const Node&) const noexcept; // Comparison of abstract types is possible, but should not be visible.

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node& operator=(const Node&) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    Node& operator=(Node&&) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)
    virtual Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

    virtual bool IsLeaf() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual Node& LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual Node& RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree<Data>& operator=(const BinaryTree<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BinaryTree<Data>& operator=(BinaryTree<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree<Data>&) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree<Data>&) const noexcept; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Node& Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void MapPreOrder(const MapFunctor, void*) override; // Override MappableContainer member
  void MapPostOrder(const MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

   using typename FoldableContainer<Data>::FoldFunctor;

   void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member
   void FoldPostOrder(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from InOrderMappableContainer)

  void MapInOrder(const MapFunctor, void*) override; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from InOrderFoldableContainer)

  void FoldInOrder(const FoldFunctor, const void*, void*) const override; // Override InOrderFoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

   void MapBreadth(const MapFunctor, void*) override; // Override BreadthMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)

  void FoldBreadth(const FoldFunctor, const void*, void*) const override; // Override BreadthFoldableContainer member

protected:

  // Auxiliary member functions (for MappableContainer)

  void MapPreOrderAux(const MapFunctor, Node*, void*); // Accessory function executing from one node of the tree
  void MapPostOrderAux(const MapFunctor, Node*, void*); // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member functions (for FoldableContainer)

  void FoldPreOrderAux(const FoldFunctor, Node*, const void*, void*) const; // Accessory function executing from one node of the tree
  void FoldPostOrderAux(const FoldFunctor, Node*, const void*, void*) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member functions (for InOrderMappableContainer)

  void MapInOrderAux(const MapFunctor, Node*, void*); // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member functions (for InOrderFoldableContainer)

  void FoldInOrderAux(const FoldFunctor, Node*, const void*, void*) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member functions (for BreadthMappableContainer)

  // type MapBreadth(arguments) specifiers; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member functions (for BreadthFoldableContainer)

  // type FoldBreadth(arguments) specifiers; // Accessory function executing from one node of the tree

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator: virtual public ForwardIterator<Data> { // Must extend ForwardIterator<Data>

private:

  // ...

protected:

  struct BinaryTree<Data>::Node* node = nullptr;
  StackVec<Data> stack;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator<Data>&);

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTPreOrderIterator();

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator<Data>& operator=(const BTPreOrderIterator<Data>&);

  // Move assignment
  BTPreOrderIterator<Data>& operator=(BTPreOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTPreOrderIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  struct BinaryTree<Data>::Node& operator++(); // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator: virtual public ForwardIterator<Data> { // Must extend ForwardIterator<Data>

private:

  // ...

protected:

  struct BinaryTree<Data>::Node* node = nullptr;
  StackVec<Data> stack;

  struct BinaryTree<Data>::Node& LeftMostLeaf(struct BinaryTree<Data>::Node&) const noexcept;

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator<Data>&);

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderIterator();

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator<Data>& operator=(const BTPostOrderIterator<Data>&);

  // Move assignment
  BTPostOrderIterator<Data>& operator=(BTPostOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTPostOrderIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  struct BinaryTree<Data>::Node& operator++(); // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator: virtual public ForwardIterator<Data> { // Must extend ForwardIterator<Data>

private:

  // ...

protected:

  struct BinaryTree<Data>::Node* node = nullptr;
  StackVec<Data> stack;

  struct BinaryTree<Data>::Node& LeftMostChild(struct BinaryTree<Data>::Node&) const noexcept;

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator<Data>&);

  // Move constructor
  BTInOrderIterator(BTInOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTInOrderIterator();

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator<Data>& operator=(const BTInOrderIterator<Data>&);

  // Move assignment
  BTInOrderIterator<Data>& operator=(BTInOrderIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator<Data>&) const noexcept;
  bool operator!=(const BTInOrderIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  struct BinaryTree<Data>::Node& operator++(); // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator: virtual public ForwardIterator<Data> { // Must extend ForwardIterator<Data>

private:

  // ...

protected:

  struct BinaryTree<Data>::Node* node = nullptr;
  QueueVec<Data> queue;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator<Data>&);

  // Move constructor
  BTBreadthIterator(BTBreadthIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthIterator();

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator<Data>& operator=(const BTBreadthIterator<Data>&);

  // Move assignment
  BTBreadthIterator<Data>& operator=(BTBreadthIterator<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator<Data>&) const noexcept;
  bool operator!=(const BTBreadthIterator<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  struct BinaryTree<Data>::Node& operator++(); // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif

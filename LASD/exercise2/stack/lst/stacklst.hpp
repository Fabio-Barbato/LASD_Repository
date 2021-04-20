
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst: virtual public Stack<Data>, virtual protected List<Data> { // Must extend Stack<Data> and List<Data>

private:

  // ...

protected:

  using List<Data>::size;

  using List<Data>::head;

public:

  // Default constructor
   StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const LinearContainer<Data>&); // A stack obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
   StackLst(const Stack<Data>&);

  // Move constructor
  StackLst(Stack<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~StackLst();

  /* ************************************************************************ */

  // Copy assignment
  Stack<Data>& operator=(const Stack<Data>&);

  // Move assignment
  Stack<Data>& operator=(Stack<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Stack<Data>&) const noexcept;
  bool operator!=(const Stack<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  void Push(const Data&) override; // Override Stack member (copy of the value)
  void Push(Data&&) noexcept override; // Override Stack member (move of the value)
  Data& Top() const override; // Override Stack member (must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif

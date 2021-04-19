
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack: virtual public Container { // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Stack() = default;

  /* ************************************************************************ */

  // Copy assignment
  virtual Stack& operator=(const Stack<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Stack& operator=(Stack<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Stack<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Stack<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  void Push(const Data&); // Copy of the value
  void Push(Data&&) noexcept; // Move of the value
  Data& Top() const; // (concrete function must throw std::length_error when empty)
  void Pop(); // (concrete function must throw std::length_error when empty)
  Data TopNPop(); // (concrete function must throw std::length_error when empty)

};

/* ************************************************************************** */

}

#endif

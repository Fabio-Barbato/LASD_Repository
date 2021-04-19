
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue: virtual public Container { // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Queue() = default;

  /* ************************************************************************ */

  // Copy assignment
  Queue& operator=(const Queue<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Queue& operator=(Queue<Data>&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Queue<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Queue<Data>&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  void Enqueue(const Data&); // Copy of the value
  void Enqueue(Data&&) noexcept; // Move of the value
  Data& Head() const; // (concrete function must throw std::length_error when empty)
  void Dequeue(); // (concrete function must throw std::length_error when empty)
  Data HeadNDequeue(); // (concrete function must throw std::length_error when empty)

};

/* ************************************************************************** */

}

#endif


#ifndef MATRIXVEC_HPP
#define MATRIXVEC_HPP

/* ************************************************************************** */

#include "../matrix.hpp"

 #include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MatrixVec: virtual public Matrix<Data> { // Must extend Matrix<Data>

private:

  // ...

protected:

   using Matrix<Data>::size;
   using Matrix<Data>::rows;
   using Matrix<Data>::columns;
   Vector<Data> vec;

public:

  // Default constructor
   MatrixVec() = default;

  /* ************************************************************************ */

  // Specific constructors
   MatrixVec(const ulong, const ulong); // A matrix of some specified dimension

  /* ************************************************************************ */

  // Copy constructor
   MatrixVec(const MatrixVec<Data>&);

  // Move constructor
  MatrixVec(MatrixVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
   ~MatrixVec();

  /* ************************************************************************ */

  // Copy assignment
  MatrixVec<Data>& operator=(const MatrixVec<Data>&);

  // Move assignment
  MatrixVec<Data>& operator=(MatrixVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MatrixVec<Data>&) const noexcept;
  bool operator!=(const MatrixVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Matrix)

  void RowResize(const ulong) override; // Override Matrix member
  void ColumnResize(const ulong) override; // Override Matrix member

  bool ExistsCell(const ulong, const ulong) noexcept; // Override Matrix member (should not throw exceptions)

  Data& operator()(const ulong, const ulong); // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
  const Data& operator()(const ulong, const ulong) const; // Override Matrix member (immutable access to the element; throw out_of_range when out of range and length_error when not present)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

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

};

/* ************************************************************************** */

}

#include "matrixvec.cpp"

#endif

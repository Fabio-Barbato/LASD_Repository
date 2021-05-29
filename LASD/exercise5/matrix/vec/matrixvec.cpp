
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template <typename Data>
 MatrixVec<Data>::MatrixVec(const ulong row, const ulong col): vec(row*col){
   rows = row;
   columns = col;
   size = rows*columns;
 }

/* ************************************************************************ */

// Copy constructor
template <typename Data>
 MatrixVec<Data>::MatrixVec(const MatrixVec<Data>& mat): vec(mat.vec){
   rows = mat.rows;
   columns = mat.columns;
   size = mat.size;
 }

// Move constructor
template <typename Data>
 MatrixVec<Data>::MatrixVec(MatrixVec<Data>&& mat) noexcept: vec(std::move(mat.vec)){
  std::swap(rows , mat.rows);
  std::swap(columns , mat.columns);
  std::swap(size , mat.size);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
 MatrixVec<Data>::~MatrixVec(){
   Clear();
 }

/* ************************************************************************ */

// Copy assignment
template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(const MatrixVec<Data>& mat){
  MatrixVec<Data>* tmp = new MatrixVec<Data>(mat);
  std::swap(*this, *tmp);
  delete tmp;
  return *this;
}

// Move assignment
template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec<Data>&& mat) noexcept: vec(std::move(mat.vec)){
  std::swap(rows , mat.rows);
  std::swap(columns , mat.columns);
  std::swap(size , mat.size);
  return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool MatrixVec<Data>::operator==(const MatrixVec<Data>& mat) const noexcept{
  return (rows==mat.rows && columns==mat.columns && size==mat.size && vec == mat.vec);
}

template <typename Data>
bool MatrixVec<Data>::operator!=(const MatrixVec<Data>& mat) const noexcept{
  return !(*this==mat);
}

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
/* ************************************************************************** */

}

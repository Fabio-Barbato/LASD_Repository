
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
MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec<Data>&& mat) noexcept{
  std::swap(rows , mat.rows);
  std::swap(columns , mat.columns);
  std::swap(size , mat.size);
  vec = std::move(mat.vec);
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


template <typename Data>
void MatrixVec<Data>::RowResize(const ulong new_rows) {
  rows = new_rows;
  size = new_rows*columns;
  vec.Resize(size);
}

template <typename Data>
void MatrixVec<Data>::ColumnResize(const ulong new_col) {

  if(vec.Size()>0){
    Vector<Data> tmp(new_col*rows);
    if(new_col<columns){
      for (ulong i = 0; i < rows; i++) {
        for (ulong j = 0; j < new_col; j++) {
          tmp[i*new_col+j] = vec[i*columns+j];
        }
      }
      vec = std::move(tmp);
    }
    else{
      for (ulong i = 0; i < rows; i++) {
        for (ulong j = 0; j < columns; j++) {
          tmp[i*new_col+j] = vec[i*columns+j];
        }
      }
      vec = std::move(tmp);
    }

  }
  else
    vec.Resize(new_col*rows);

    columns = new_col;
    size = rows*columns;


}


template <typename Data>
bool MatrixVec<Data>::ExistsCell(const ulong row, const ulong col) const noexcept{
  return (size>0 && row<rows && col<columns);
}


template <typename Data>
Data& MatrixVec<Data>::operator()(const ulong row, const ulong col){
  return const_cast<Data&>(static_cast<const MatrixVec<Data>*>(this)->operator()(row, col));
}


template <typename Data>
const Data& MatrixVec<Data>::operator()(const ulong row, const ulong col) const{
  if(ExistsCell(row,col))
    return vec[row*columns+col];
  else
    throw std::out_of_range("Out of range!");
}
/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void MatrixVec<Data>::Clear(){
  vec.Clear();
  size = 0;
  rows = 0;
  columns = 0;
}

/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)
template <typename Data>
void MatrixVec<Data>::MapPreOrder(const MapFunctor fun, void* par) {
  vec.MapPreOrder(fun, par);
}
template <typename Data>
void MatrixVec<Data>::MapPostOrder(const MapFunctor fun, void* par) {
  vec.MapPostOrder(fun, par);
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void MatrixVec<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const{
  vec.FoldPreOrder(fun, par, acc);
}

template <typename Data>
void MatrixVec<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
  vec.FoldPostOrder(fun, par, acc);
}
/* ************************************************************************** */

}

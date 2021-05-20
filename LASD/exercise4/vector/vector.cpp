
namespace lasd {

/* ************************************************************************** */


template<typename Data>
Vector<Data>::Vector(const ulong newsize){
  Elements = new Data[newsize] {};
  size = newsize;
}


template<typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& con){
  size = con.Size();
  Elements = new Data[size];

  for(ulong index = 0; index < size; index++){
    Elements[index] = con[index];
  }
}

// Copy constructor
template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vec){
  Elements = new Data[vec.size];
  std::copy(vec.Elements, vec.Elements + vec.size, Elements);
  size = vec.size;
}

// Move constructor
template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept{
    std::swap(Elements, vec.Elements);
    std::swap(size, vec.size);
}

/* ************************************************************************** */

// Destructor
template<typename Data>
Vector<Data>::~Vector(){
  delete[] Elements;
}

/* ************************************************************************** */

// Copy assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec){
  Vector<Data>* tmpvec = new Vector<Data>(vec);
  std::swap(*tmpvec, *this);
  delete tmpvec;
  return *this;
}

// Move Assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept{
  std::swap(Elements, vec.Elements);
  std::swap(size, vec.size);
  return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept{
  if(size==vec.size){
    for(uint index = 0; index < size; index++){
      if(Elements[index] != vec.Elements[index]){
        return false;
      }
    }
    return true;
  }
  else{
    return false;
  }
}


template<typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& vec) const noexcept{
  return !(*this == vec);
}

/* ************************************************************************** */

// Resize
template<typename Data>
void Vector<Data>::Resize(const ulong newsize){
  if(newsize == 0) {
    Clear();
  }
  else if(size != newsize) {
    ulong limit;
    limit = (size < newsize) ? size : newsize;

    Data* TmpElements = new Data[newsize]{};

    for(ulong index = 0; index < limit; index++){
      std::swap(Elements[index], TmpElements[index]);
    }

    std::swap(Elements, TmpElements);
    size = newsize;
    delete[] TmpElements;
  }
}

// Clear
template<typename Data>
void Vector<Data>::Clear(){
  delete[] Elements;
  Elements = nullptr;
  size = 0;
}

// Front
template<typename Data>
Data& Vector<Data>::Front() const{
  if(size != 0) {
    return Elements[0];
  }
  else {
      throw std::length_error("Empty vector");
  }
}

// Back
template<typename Data>
Data& Vector<Data>::Back() const{
  if(size != 0){
    return Elements[size - 1];
  }
  else{
    throw std::length_error("Empty vector");
  }
}

// Operator []
template<typename Data>
Data& Vector<Data>::operator[](const ulong index) const{
  if(index < size) {
    return Elements[index];
  }
  else {
    throw std::out_of_range("Out of range! Vector size: "+ std::to_string(size));
  }
}

/* ************************************************************************** */

// MapPreOrder
template<typename Data>
void Vector<Data>::MapPreOrder(MapFunctor fun, void* par){
  for(ulong index = 0; index < size; index++){
    fun(Elements[index], par);
  }
}

// MapPostOrder
template<typename Data>
void Vector<Data>::MapPostOrder(MapFunctor fun, void* par){
  ulong index = size;
  while(index>0) {
    fun(Elements[--index], par);
  }
}

/* ************************************************************************** */


//FoldPreOrder
template <typename Data>
void Vector<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc) const{
  for(ulong index = 0; index<size; index++) {
    fun(Elements[index], par, acc);
  }
}

// FoldPostOrder
template<typename Data>
void Vector<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc) const{
  ulong index = size;
  while(index>0) {
    fun(Elements[--index], par, acc);
  }

}

/* ************************************************************************** */

}

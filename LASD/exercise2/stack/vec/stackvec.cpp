
namespace lasd {

/* ************************************************************************** */

//Specific constructor
template <typename Data>
StackVec<Data>::StackVec(const LinearContainer<Data>& con){
  size = con.Size();
  real_size = con.Size();
  Elements = new Data[size];

  for(ulong index = 0; index < size; index++){
    Elements[index] = con[index];
  }
}

//Copy constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& stk){
  Elements = new Data[stk.size];
  std::copy(stk.Elements, stk.Elements + stk.real_size, Elements);
  real_size = stk.real_size;
  size = stk.size;
}

//Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& stk) noexcept{
  std::swap(Elements, stk.Elements);
  std::swap(size, stk.size);
  std::swap(real_size, stk.real_size);
}

//Destructor
template <typename Data>
StackVec<Data>::~StackVec(){
  Clear();
}

//Copy assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stk){
  StackVec<Data>* tmpvec = new StackVec<Data>(stk);
  std::swap(*tmpvec, *this);
  delete tmpvec;
  return *this;
}

//Move assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& stk) noexcept{
  std::swap(Elements, stk.Elements);
  std::swap(size, stk.size);
  std::swap(real_size, stk.real_size);

  return *this;
}

//Comparison operator
template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& stk) const noexcept{
  if(real_size==stk.real_size){
    for (ulong i = 0; i < real_size; i++) {
      if(Elements[i] != stk.Elements[i]){
        return false;
      }
    }
    return true;
  }else{
    return false;
  }
}

template <typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data>& stk) const noexcept{
  return !(*this==stk);
}

//Empty
template <typename Data>
bool StackVec<Data>::Empty() const noexcept{
  return real_size==0;
}

//Size
template <typename Data>
ulong StackVec<Data>::Size() const noexcept{
  return real_size;
}

//Clear
template <typename Data>
void StackVec<Data>::Clear() {
  Vector<Data>::Clear();
  real_size = 0;
}


//Push(copy)
template <typename Data>
void StackVec<Data>::Push(const Data& value){
  if(size==0){
    Elements = new Data[3];
    size=3;
    Elements[real_size] = value;
    real_size++;
  }
  else{
    Elements[real_size] = value;
    real_size++;
    if(real_size==size){
      Expand();
    }
  }

}

//Push(move)
template <typename Data>
void StackVec<Data>::Push(Data&& value) noexcept{
  if(size==0){
    Elements = new Data[3];
    size=3;
    Elements[real_size] = std::move(value);
    real_size++;
  }
  else{
    Elements[real_size] = value;
    real_size++;
    if(real_size==size){
      Expand();
    }
  }
}

//Pop
template <typename Data>
void StackVec<Data>::Pop(){
  if(real_size==0){
    throw std::length_error("Empty");
  }
  else{
    real_size--;
    if(real_size==size/4 && size>3){
      Reduce();
    }
  }
}

//Reduce
template <typename Data>
void StackVec<Data>::Reduce(){
  Vector<Data>::Resize(size/2);
}

//Expand
template <typename Data>
void StackVec<Data>::Expand(){
  Vector<Data>::Resize(size*2);
}

//Top
template <typename Data>
Data& StackVec<Data>::Top() const{
  if(real_size==0){
    throw std::length_error("Empty!");
  }else{
    return Elements[real_size-1];
  }

}

//TopNPop
template <typename Data>
Data StackVec<Data>::TopNPop(){
    Data dat = Top();
    real_size--;
    return dat;
  }




/* ************************************************************************** */

}

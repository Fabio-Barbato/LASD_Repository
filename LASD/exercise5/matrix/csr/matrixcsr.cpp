
namespace lasd {

/* ************************************************************************** */

//Default constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(): vec(1){
  vec[0] = &head;
}

//Specific constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(const ulong row, const ulong col): vec(row+1){
  rows = row;
  columns = col;
  size = rows*columns;
  for (ulong i = 0; i < row+1; i++) {
    vec[i] = &head;
  }
}

  /*// Copy constructor
  template <typename Data>
  MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data>& mat){

  }*/

  // Move constructor
  template <typename Data>
   MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data>&& mat) noexcept: vec(std::move(mat.vec)){
     std::swap(size, mat.size);
     std::swap(rows, mat.rows);
     std::swap(columns, mat.columns);
     std::swap(head, mat.head);
   }

  //Destructor
  template <typename Data>
  MatrixCSR<Data>::~MatrixCSR(){
    Clear();
  }

  //Copy assignment
  template <typename Data>
  MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR<Data>& mat){
    MatrixCSR<Data>* tmp = new MatrixCSR<Data>(mat);
    std::swap(*this, *tmp);
    delete tmp;
    return *this;
  }

  //Move assignment
  template <typename Data>
  MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR<Data>&& mat) noexcept{
    std::swap(size, mat.size);
    std::swap(rows, mat.rows);
    std::swap(columns, mat.columns);
    std::swap(head, mat.head);
    vec = std::move(mat.vec);

    return *this;
  }

  //Comparison operators
  template <typename Data>
  bool MatrixCSR<Data>::operator==(const MatrixCSR<Data>& mat) const noexcept{
    return (rows == mat.rows && columns == mat.columns && size == mat.size && List<std::pair<Data,ulong>>::operator==(mat));
  }

  template <typename Data>
  bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data>& mat) const noexcept{
    return !(*this==mat);
  }


  //ExistsCell
  template <typename Data>
  bool MatrixCSR<Data>::ExistsCell(const ulong row, const ulong col) const noexcept{
    if(row<rows && col<columns){
      if (vec[row]==vec[row+1]) {
        return false;
      } else {
        Node* tmp = vec[row];
        while (tmp!=vec[row+1] && tmp->info.second<col) {
          tmp = tmp->next;
        }
        return tmp!=vec[row+1] && tmp->info.second==col;
      }
    }
    else
      return false;
  }

  //Operator ()
  template <typename Data>
  Data& MatrixCSR<Data>::operator()(const ulong row, const ulong col){
    if(row<rows && col<columns){
      Node* tmp = vec[row];
      if(ExistsCell(row,col)){
        while (tmp->info.second<col) {
          tmp = tmp->next;
        }
        return tmp->info.first;
      }
      else{
        Node new_node;
        if(vec[row]!=vec[row+1]){
          while (tmp->next!=vec[row+1] && tmp->info.second<col) {
            tmp = tmp->next;
          }
          new_node->next = tmp->next->next;
          tmp->next = &new_node;
        }
        else{
          ulong index = row;
          while (vec[index]==vec[index+1]) {
            index++;
          }
        }
      }

    }
    else
      throw std::out_of_range("Out of range!");
  }

  //Operator () (const)
  template <typename Data>
  const Data& MatrixCSR<Data>::operator()(const ulong row, const ulong col) const{
    if(row<rows && col<columns){
      if(ExistsCell(row,col)){
        Node* tmp = vec[row];
        while (tmp->info.second<col) {
          tmp = tmp->next;
        }
        return tmp->info.first;
      }
      else{
        throw std::length_error("Element not present!");
      }
    }
    else
      throw std::out_of_range("Out of range!");
  }


  //Clear
  template <typename Data>
  void MatrixCSR<Data>::Clear(){
    for (ulong i = 0; i < vec.Size(); i++) {
      vec[i] = nullptr;
    }
    vec.Clear();
    while (head!=nullptr) {
      Node* tmp = head;
      head = tmp->next;
      delete tmp;
    }
    size=0;
    columns=0;
    rows=0;
  }

  //MapPreOrder
  template <typename Data>
  void MatrixCSR<Data>::MapPreOrder(const MapFunctor fun, void* par){
    List<std::pair<Data,ulong>>::MapPreOrder([&fun](std::pair<Data,ulong>& dat, void* parx){fun(dat.first, parx);},par);
  }

  //MapPostOrder
  template <typename Data>
  void MatrixCSR<Data>::MapPostOrder(const MapFunctor fun, void* par){
    List<std::pair<Data,ulong>>::MapPostOrder([&fun](std::pair<Data,ulong>& dat, void* parx){fun(dat.first, parx);},par);
  }

  //FoldPreOrder
  template <typename Data>
  void MatrixCSR<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const{
    List<std::pair<Data,ulong>>::FoldPreOrder([&fun](std::pair<Data,ulong>& dat,const void* parx, void* accx){fun(dat.first, parx, accx);},par, acc);
  }

  //FoldPostOrder
  template <typename Data>
  void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
    List<std::pair<Data,ulong>>::FoldPostOrder([&fun](std::pair<Data,ulong>& dat,const void* parx, void* accx){fun(dat.first, parx, accx);},par, acc);
  }

}
/* ************************************************************************** */

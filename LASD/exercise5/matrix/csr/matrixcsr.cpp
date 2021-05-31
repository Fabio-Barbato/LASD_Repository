
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

  /*// Copy constructor
  template <typename Data>
  MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data>& mat){

  }*/

  // Move constructor
  template <typename Data>
   MatrixCSR(MatrixCSR<Data>&& mat) noexcept: vec(std::move(mat.vec)){
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
  MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR<Data>&& mat){
    std::swap(size, mat.size);
    std::swap(rows, mat.rows);
    std::swap(columns, mat.columns);
    std::swap(head, mat.head);
    vec = std::move(mat.vec);

    return *this;
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

      }
    }
    else
      throw std::out_of_range("Out of range!");
  }

  //Operator ()
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
        throw std::length_error("Element not present!")
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

}
/* ************************************************************************** */

}

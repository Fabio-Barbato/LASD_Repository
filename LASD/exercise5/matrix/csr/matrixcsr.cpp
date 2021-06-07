
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
  for (ulong i = 0; i < row+1; i++) {
    vec[i] = &head;
  }
}

  // Copy constructor
  template <typename Data>
  MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data>& mat): MatrixCSR(mat.rows, mat.columns){
    Node** tmp = mat.vec[0];
    for (ulong i = 0; i < mat.rows; i++) {
      while (tmp!=mat.vec[i+1]) {
        (*this)(i,(*tmp)->info.second) = (*tmp)->info.first;
        tmp = &((*tmp)->next);
      }
    }

  }

  // Move constructor
  template <typename Data> //da rivedere
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
    vec[0]=&head;
    return *this;
  }

  //Move assignment
  template <typename Data> //da rivedere
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
  bool MatrixCSR<Data>::operator==(const MatrixCSR<Data>& mat) const noexcept{ //da rivedere
    if(size==mat.size && rows == mat.rows && columns == mat.columns){
      if(size>0){
        Node** riga1 = vec[0];
        Node** riga2 = mat.vec[0];
        ulong curr_row1 = 0;
        ulong curr_row2 = 0;
        while (curr_row1==curr_row2 && curr_row1<rows && *riga1!=nullptr && *riga2!=nullptr) {
          if ((*riga1)->info.first!=(*riga2)->info.first || (*riga1)->info.second!=(*riga2)->info.second) {
            return false;
          }
          riga1 = &(*riga1)->next;
          riga2 = &(*riga2)->next;
          if (riga1==vec[curr_row1+1]) {
            curr_row1++;
          }
          if (riga2==mat.vec[curr_row2+1]) {
            curr_row2++;
          }
        }
        return curr_row1==curr_row2 && (*riga1==nullptr && *riga2==nullptr);
      }
      else
        return false;
    }
    else
      return false;

  }

  template <typename Data>
  bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data>& mat) const noexcept{
    return !(*this==mat);
  }

  //ExistsCell
  template <typename Data>
  bool MatrixCSR<Data>::ExistsCell(const ulong row, const ulong col) const noexcept{
    if(row<rows && col<columns){
        Node** tmp = vec[row];
        while (tmp!=vec[row+1] && (*tmp)->info.second<col) {
          tmp = &((*tmp)->next);
        }
        return tmp!=vec[row+1] && (*tmp)->info.second==col;
    }
    else
      return false;
  }

  //RowResize
  template <typename Data>
  void MatrixCSR<Data>::RowResize(const ulong new_row){
    if (new_row>rows) {
      vec.Resize(new_row+1);
      for (ulong i = rows+1; i < new_row+1; i++) {
        vec[i] = vec[rows];
      }
    }else if(new_row<rows){
      Node** tmp = vec[new_row];
      Node* tmp_del = *tmp;
      while (tmp_del!=nullptr) {
        *tmp = tmp_del->next;
        delete tmp_del;
        size--;
        tmp_del = *tmp;
      }
      vec.Resize(new_row+1);
    }
    rows = new_row;

  }

  //ColumnResize
  template <typename Data>
  void MatrixCSR<Data>::ColumnResize(const ulong new_column){
    if(new_column==0){
      vec.Clear();
      List<std::pair<Data,ulong>>::Clear();
      vec.Resize(1);
      vec[0] = &head;
    }
    else if(new_column<columns){
      Node** tmp = vec[0];
      Node* tmp_del;
      ulong curr_row=0;
      ulong index;
      while (*tmp!=nullptr && curr_row<rows) {
        index=curr_row+1;
        if((*tmp)->info.second>=new_column){
          tmp_del = *tmp;
          *tmp = tmp_del->next;
          while (index<=rows && &tmp_del->next==vec[index]) {
            vec[index] = tmp;
            index++;
          }
          delete tmp_del;
          size--;
          if (tmp==vec[curr_row+1]) {
            curr_row++;
          }
        }
        else{
          tmp = &(*tmp)->next;
          if (tmp==vec[curr_row+1]) {
            curr_row++;
          }
        }

      }



    }
    columns = new_column;
  }

  //Operator ()
  template <typename Data>
  Data& MatrixCSR<Data>::operator()(const ulong row, const ulong col){

    if(row<rows && col<columns){
      Node** tmp = vec[row];
     while (tmp!=vec[row+1] && (*tmp)->info.second <= col) {
       if((*tmp)->info.second == col)
           return (*tmp)->info.first;

       tmp = &(*tmp)->next;
     }

     Node* new_node = new Node();
     new_node->info.second = col;
     new_node->next = *tmp;
     *tmp = new_node;
     size++;

     if(tmp==vec[row+1]) {
         ulong index = row+1;
         while (index < rows && vec[index] == vec[index+1]) {
             vec[index] = &new_node->next;
             index++;
         }
         vec[index] = &new_node->next;
     }

    return new_node->info.first;
    }
    else
      throw std::out_of_range("Out of range!");
  }

  //Operator () (const)
  template <typename Data>
  const Data& MatrixCSR<Data>::operator()(const ulong row, const ulong col) const{
    if(row<rows && col<columns){
      Node** tmp = vec[row];
      while (tmp!=vec[row+1] && (*tmp)->info.second <= col) {
       if((*tmp)->info.second == col)
           return (*tmp)->info.first;

       tmp = &(*tmp)->next;
     }
      throw std::length_error("Element not present!");
      }
    else
      throw std::out_of_range("Out of range!");
  }


  //Clear
  template <typename Data>
  void MatrixCSR<Data>::Clear(){
    vec.Clear();
    List<std::pair<Data,ulong>>::Clear();
    vec.Resize(1);
    vec[0] = &head;
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
    List<std::pair<Data,ulong>>::FoldPreOrder([&fun](const std::pair<Data,ulong>& dat,const void* parx, void* accx){fun(dat.first, parx, accx);},par, acc);
  }

  //FoldPostOrder
  template <typename Data>
  void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
    List<std::pair<Data,ulong>>::FoldPostOrder([&fun](const std::pair<Data,ulong>& dat,const void* parx, void* accx){fun(dat.first, parx, accx);},par, acc);
  }

}
/* ************************************************************************** */

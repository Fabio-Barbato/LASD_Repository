
namespace lasd {

/* ************************************************************************** */

//Default constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(){
  vec.Resize(1);
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
      while (tmp!=vec[i+1]) {
        (*this)(i,(*tmp)->info.second) = (*tmp)->info.first;
        tmp = &((*tmp)->next);
      }
    }

  }

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
      Node* head_tmp = (*tmp)->next;
      while (head_tmp!=nullptr) {
        (*tmp)->next = head_tmp->next;
        head_tmp->next = nullptr;
        delete head_tmp;
        head_tmp = (*tmp)->next;
      }
      vec.Resize(new_row+1);
    }
    rows = new_row;
    size = rows*columns;

  }

  //ColumnResize
  template <typename Data>
  void MatrixCSR<Data>::ColumnResize(const ulong new_column){
    if(new_column==0){
      Node* tmp = head;
      while (tmp!=nullptr) {
        head = tmp->next;
        delete tmp;
        tmp = head;
      }
      size = 0;
    }
    else if(new_column<columns){
      Node** tmp = vec[0];
      Node* tmp_del;
      ulong index;
      ulong i=0;
      while (i<=rows && size>0) {
          if((*tmp)->info.second>=new_column){
            tmp_del = (*tmp)->next;
            index=i+1;
            while (index<=rows && &tmp_del->next==vec[index]) {
              vec[index] = tmp;
              index++;
            }
            (*tmp)->next = tmp_del->next;
            tmp_del->next=nullptr;
            delete tmp_del;
            size--;
            if (tmp==vec[i+1]) {
              i++;
            }
          }
      }
    }
    columns = new_column;
  }

  //Operator ()
  template <typename Data>
  Data& MatrixCSR<Data>::operator()(const ulong row, const ulong col){

    if(row<rows && col<columns){ //cella nel range
      Node** tmp = vec[row];
      if (ExistsCell(row,col)) { //la cella esiste
        while ((*tmp)->info.second<col) {
          tmp = &((*tmp)->next);
        }
        return (*tmp)->info.first;
      } else { //la cella non esiste
        Node* new_node = new Node();
        new_node->info.second = col;
        while (tmp!=vec[row+1] && (*tmp)->info.second<col) {
          tmp = &((*tmp)->next);
        }
        std::cout << "head: "<<&head << '\n';
        std::cout << "vec: "<<vec[0] << '\n';
        std::cout << "tmp: "<<(tmp) << '\n';
        std::cout << "head->next: "<<head->next << '\n';
        std::cout << "*tmp->next: "<<(*tmp)->next << '\n';
        if((*tmp)->next!=nullptr)
          new_node->next = (*tmp)->next;

        (*tmp)->next = new_node;

        if (tmp==vec[row+1]) {//riga vuota o cella tra due righe
          ulong index = row+1;
          while (vec[index]==vec[index+1]) {
            vec[index] = &new_node->next;
            index++;
          }
          vec[index] = &new_node->next;
        }
        size++;
        return new_node->info.first;
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
        Node** tmp = vec[row];
        while ((*tmp)->info.second<col) {
          tmp = &((*tmp)->next);
        }
        return (*tmp)->info.first;
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
    vec.Clear();
    Node* tmp = head;
    while (tmp!=nullptr) {
      head = tmp->next;
      delete tmp;
      tmp = head;
    }

    vec.Resize(1);
    vec[0] = &head;
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
    List<std::pair<Data,ulong>>::FoldPreOrder([&fun](const std::pair<Data,ulong>& dat,const void* parx, void* accx){fun(dat.first, parx, accx);},par, acc);
  }

  //FoldPostOrder
  template <typename Data>
  void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const{
    List<std::pair<Data,ulong>>::FoldPostOrder([&fun](const std::pair<Data,ulong>& dat,const void* parx, void* accx){fun(dat.first, parx, accx);},par, acc);
  }

}
/* ************************************************************************** */

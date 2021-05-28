
namespace lasd {

/* ************************************************************************** */

template <typename Data>
ulong Matrix<Data>::RowNumber() const noexcept{
  return rows;
}

template <typename Data>
ulong Matrix<Data>::ColumnNumber() const noexcept{
  return columns;
}
/* ************************************************************************** */

}

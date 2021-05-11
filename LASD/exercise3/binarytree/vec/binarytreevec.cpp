
namespace lasd {

/* ************************************************************************** */

  // Copy assignment
  template<typename Data>
  NodeVec& operator=(const NodeVec&){

  }

  // Move assignment
  NodeVec& operator=(NodeVec&&) noexcept;

  /* ********************************************************************** */

  // Specific member functions

   Data& Element() noexcept;
   const Data& Element() const noexcept;

   bool IsLeaf() const noexcept;
   bool HasLeftChild() const noexcept;
   bool HasRightChild() const noexcept;

   NodeVec& LeftChild() const;
   NodeVec& RightChild() const;

/* ************************************************************************** */

}

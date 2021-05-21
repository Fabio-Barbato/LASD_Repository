
//#include "zlasdtest/test.hpp"

//#include "zmytest/test.hpp"
#include "bst/bst.hpp"
#include "vector/vector.hpp"
#include "binarytree/binarytree.hpp"

/* ************************************************************************** */
using namespace lasd;
#include <iostream>

/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2020" << std::endl;
  //lasdtest(); // To call in the menu of your library test!
  Vector<int> vec(7);
  vec[0] = 10;
  vec[1] = 8;
  vec[2] = 15;
  vec[3] = 6;
  vec[4] = 4;
  vec[5] = 5;
  vec[6] = 14;
  BST<int> bst(vec);
  bst.Remove(5);
  //std::cout << "Minimo: "<<bst.MinNRemove() << '\n';
  BTBreadthIterator<int> it(bst);
  try{
  std::cout << *it << '\n';
  ++it;
  std::cout << *it << '\n';
  ++it;
  std::cout << *it << '\n';
  ++it;
  std::cout << *it << '\n';
  ++it;
  std::cout << *it << '\n';
  ++it;
  std::cout << *it << '\n';
  ++it;
  std::cout << *it << '\n';
  ++it;
}catch(std::out_of_range e){
  std::cout << "empty" << '\n';
}



  return 0;
}

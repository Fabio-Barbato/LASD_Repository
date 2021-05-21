
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
  vec[0] = 8;
  vec[1] = 15;
  vec[2] = 7;
  vec[3] = 14;
  vec[4] = 13;
  vec[5] = 10;
  vec[6] = 12;
  BST<int> bst(vec);
  bst.Remove(9);
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


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
  vec[0] = 2;
  vec[1] = 3;
  vec[2] = 1;
  vec[3] = 0;
  vec[4] = 4;
  vec[5] = 6;
  vec[6] = 5;
  BST<int> bst(vec);
  BTInOrderIterator<int> it(bst);
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
  try{
    std::cout << "Minimo: "<<bst.Max() << '\n';
  }catch(std::length_error e){
    std::cout << "empty" << '\n';
  }



  return 0;
}

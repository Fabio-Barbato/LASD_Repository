
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

#include "container/container.hpp"

#include "iterator/iterator.hpp"

#include "vector/vector.hpp"

#include "list/list.hpp"

#include "binarytree/binarytree.hpp"
#include "binarytree/lnk/binarytreelnk.hpp"
#include "binarytree/vec/binarytreevec.hpp"
/* ************************************************************************** */

#include <iostream>

using namespace lasd;
/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2020" << std::endl;
  //lasdtest(); // To call in the menu of your library test!
  Vector<int> vec(4);
  std::cout << "Popolamento vettore" << '\n';
  for(int i=0;i<vec.Size();i++){
    vec[i]=rand()%50;
    std::cout << vec[i] << '\n';
  }


  BinaryTreeLnk<int> bt1(vec);
  BinaryTreeLnk<int> bt2(vec);
  BTBreadthIterator<int> it1(bt1);
  BTBreadthIterator<int> it2 (bt2);
  if(it1 == it2)
    std::cout << "uguali" << '\n';
  else
    std::cout << "diversi" << '\n';


  return 0;
}

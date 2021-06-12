
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2020" << std::endl;
  lasdtest(); // To call in the menu of your library test!

  ulong scelta;
  std::cout << "Digita 1 per eseguire il test dello studente, altrimenti digita un numero qualsiasi: ";
  std::cin >> scelta;
  if(scelta==1)
    myTest();

  return 0;
}

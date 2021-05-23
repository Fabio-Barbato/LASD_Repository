
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

#include "../bst/bst.hpp"
#include "../vector/vector.hpp"


void myTest();

template <typename Data>
void Menu(lasd::BST<Data>&);

template <typename Data>
void VisitaBinaryTree(lasd::BST<Data>&);

void OpSpecialiBinaryTree(lasd::BST<std::string>&);
void OpSpecialiBinaryTree(lasd::BST<int>&);
void OpSpecialiBinaryTree(lasd::BST<float>&);


template <typename Data>
void ExistBinaryTree(lasd::BST<Data>& );

template <typename Data>
void MapPrint(const Data& dat, void* _);

void FoldSomma(const float& dat, const void* n, void* somma)  noexcept ;

void FoldProdotto(const int& dat, const void* n, void* prodotto)  noexcept;
void FoldConcat(const std::string& dat, const void* n, void* stringaConcat)  noexcept;
std::string GenerateString();
/* ************************************************************************** */

#endif


#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"


void myTest();

std::string GenerateString();
void CreazioneBinaryTreeVec(ulong);
void CreazioneBinaryTreeLnk(ulong);

template <typename Data>
void MenuBinaryTree(lasd::BinaryTree<Data>&);

template <typename Data>
void VisitaBinaryTree(lasd::BinaryTree<Data>&);

template <typename Data>
void NavigaConNodi(lasd::BinaryTree<Data>&);

void OpSpecialiBinaryTree(lasd::BinaryTree<int>&);
void OpSpecialiBinaryTree(lasd::BinaryTree<float>&);
void OpSpecialiBinaryTree(lasd::BinaryTree<std::string>&);


template <typename Data>
void VisitaIterBT(lasd::BinaryTree<Data>&);

template <typename Data>
void ViaggiaConIter(lasd::BinaryTree<Data>&, lasd::ForwardIterator<Data>&);

template <typename Data>
void ExistBinaryTree(lasd::BinaryTree<Data>& );

template <typename Data>
void MapPrint(const Data& dat, void* _);

void FoldSomma(const float& dat, const void* n, void* somma)  noexcept ;

void FoldProdotto(const int& dat, const void* n, void* prodotto)  noexcept;
void FoldConcat(const std::string& dat, const void* n, void* stringaConcat)  noexcept;

void MapRedouble(int& value, void* par);

void MapPotenza(float& value, void* par);

void MapConcat(std::string& value, void* stringaConcat);
/* ************************************************************************** */

#endif

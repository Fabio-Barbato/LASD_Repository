
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
void MenuBinaryTree(lasd::BinaryTreeVec<Data>);

template <typename Data>
void VisitaBinaryTree(lasd::BinaryTreeVec<Data>);

/*template <typename Data>
void OpSpecialiBinaryTreeVecInt(lasd::BinaryTreeVec<int>);*/


template <typename Data>
void VisitaIterBT(lasd::BinaryTreeVec<Data>);

template <typename Data>
void ViaggiaConIter(lasd::BinaryTreeVec<Data>, lasd::BTPreOrderIterator<Data>);

template <typename Data>
void ViaggiaConIter(lasd::BinaryTreeVec<Data>, lasd::BTInOrderIterator<Data>);

template <typename Data>
void ViaggiaConIter(lasd::BinaryTreeVec<Data>, lasd::BTPostOrderIterator<Data>);

template <typename Data>
void ViaggiaConIter(lasd::BinaryTreeVec<Data>, lasd::BTBreadthIterator<Data>);

template <typename Data>
void ExistBinaryTree(lasd::BinaryTreeVec<Data> );

template <typename Data>
void MapPrint(const Data& dat, void* _);

void FoldSomma(const int& dat, const void* n, void* somma)  noexcept ;

void FoldProdotto(const float& dat, const void* n, void* prodotto)  noexcept;
void FoldConcat(const std::string& dat, const void* n, void* stringaConcat)  noexcept;

void MapRedouble(int& value, void* par);

void MapPotenza(float& value, void* par);

void MapUppercase(std::string& value, void* par);

/* ************************************************************************** */

#endif

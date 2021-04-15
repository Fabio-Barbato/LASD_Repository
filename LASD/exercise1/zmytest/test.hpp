
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

#include "../vector/vector.hpp"
#include "../list/list.hpp"
/* ************************************************************************** */

void myTest();


void CreazioneVector(unsigned long);
void CreazioneList(unsigned long);

template <typename Data>
void MenuVector(lasd::Vector<Data>);

template <typename Data>
void MenuList(lasd::List<Data>);


template <typename Data>
void OperazioniGenericheVector(int, lasd::Vector<Data>);
template <typename Data>
void OperazioniGenericheList(int , lasd::List<Data> );


void OperazioniSpecialiVector(lasd::Vector<int>*);
void OperazioniSpecialiVector(lasd::Vector<float>*);
void OperazioniSpecialiVector(lasd::Vector<std::string>*);

void OperazioniSpecialiList(lasd::List<int>*);
void OperazioniSpecialiList(lasd::List<float>*);
void OperazioniSpecialiList(lasd::List<std::string>*);

std::string GenerateString();


void FoldProdotto(const float& , const void* , void* )  noexcept ;
void FoldSomma(const int& , const void* , void* )  noexcept;
void FoldConcat(const std::string&, const void*, void*) noexcept ;


void MapRedouble(int& , void* );
void MapPotenza(float& , void* );
void MapUppercase(std::string&, void*);
template <typename Data>
void MapPrint(Data&, void*);


/* ************************************************************************** */

#endif

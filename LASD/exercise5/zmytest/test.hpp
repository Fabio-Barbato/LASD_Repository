
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */
#include "../matrix/vec/matrixvec.hpp"
#include "../matrix/csr/matrixcsr.hpp"

void myTest();


void PopolazioneRandom(lasd::Matrix<int>& mat);


void PopolazioneRandom(lasd::Matrix<float>& mat);


void PopolazioneRandom(lasd::Matrix<std::string>& mat);

template <typename Data>
void Menu(lasd::Matrix<Data>& mat);


void OpSpeciali(lasd::Matrix<int>& mat);

void OpSpeciali(lasd::Matrix<float>& mat);


  void OpSpeciali(lasd::Matrix<std::string>& mat);


    template <typename Data>
    void MapPrint(const Data& dat, void* _);

    void MapRedouble(int& value, void* par);

    void MapPotenza(float& value, void* par);

    void MapConcat(std::string& value, void* stringaConcat);


    void FoldSomma(const float& dat, const void* n, void* somma)  noexcept ;

    void FoldProdotto(const int& dat, const void* n, void* prodotto)  noexcept ;

    void FoldConcat(const std::string& dat, const void* n, void* stringaConcat)  noexcept;

    std::string GenerateString();

    template <typename Data>
    const Data& ReadData(const lasd::Matrix<Data>& mat, ulong i, ulong j);

/* ************************************************************************** */

#endif

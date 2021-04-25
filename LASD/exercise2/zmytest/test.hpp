
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */
#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

void myTest();

std::string GenerateString();
void CreazioneStackVec(ulong);
void CreazioneQueueVec(ulong);
void CreazioneStackLst(ulong);
void CreazioneQueueLst(ulong);

template <typename Data>
void MenuStackVec(lasd::StackVec<Data>);

template <typename Data>
void MenuQueueVec(lasd::QueueVec<Data>);

template <typename Data>
void MenuStackLst(lasd::StackLst<Data>);

template <typename Data>
void MenuQueueLst(lasd::QueueLst<Data>);



/* ************************************************************************** */

#endif

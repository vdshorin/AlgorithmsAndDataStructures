//
// Created by vscho on 18.09.2019.
//

#ifndef ALGORITHMS_LAB2_SIMPLYLIST_H
#define ALGORITHMS_LAB2_SIMPLYLIST_H

#include "Element.h"

template <class T>
class SimplyList {
public:
    Element<T> *_head = nullptr;
    Element<T> *_tail = nullptr;
    Element<T> *_ptr = nullptr;
    SimplyList(){}
};


#endif //ALGORITHMS_LAB2_SIMPLYLIST_H

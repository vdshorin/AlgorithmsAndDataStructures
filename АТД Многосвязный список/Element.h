//
// Created by vscho on 18.09.2019.
//

#ifndef ALGORITHMS_LAB2_ELEMENT_H
#define ALGORITHMS_LAB2_ELEMENT_H

template <class T>
class Element {
public:
    T _value;
    Element<T> **_pointers;

    Element(){}
    Element(T value, int criteriaNumber)
    {
        _value = value;
        _pointers = new Element<T>* [criteriaNumber];

        for(int i = 0; i < criteriaNumber; i++)
        {
            *(_pointers + i) = nullptr;
        }
    }

    ~Element()
    {
        for (int i = 0; i < sizeof(*_pointers); i++)
        {
            free((_pointers + i));
        }
        free(_pointers);
    }
};


#endif //ALGORITHMS_LAB2_ELEMENT_H

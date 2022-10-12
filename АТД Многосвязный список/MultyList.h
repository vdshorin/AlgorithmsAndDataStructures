//
// Created by vscho on 16.09.2019.
//

#ifndef ALGORITHMS_LAB2_MULTYLIST_H
#define ALGORITHMS_LAB2_MULTYLIST_H

#include <iostream>
#include "Entrant.h"
#include "SimplyList.h"

using namespace std;

template <class T>
class MultyList {
private:
    SimplyList<T> *_descriptors;
    int _criteriaCount;
public:
    MultyList(int criteriaCount)
    {
        _criteriaCount = criteriaCount + 1;
        _descriptors = new SimplyList<T>[_criteriaCount];
    }

    void Add(T newValue, bool *criterias)
    {
        Element<T> *newElement = new Element<T>(newValue, _criteriaCount);

        if(_descriptors->_head == nullptr)
        {
            _descriptors->_head = newElement;
        }
        else
        {
            _descriptors->_tail->_pointers[0] = newElement;
        }

        for (int i = 1; i < _criteriaCount; i++)
        {
            if(criterias[i])
            {
                if(_descriptors[i]._head == nullptr)
                {
                    _descriptors[i]._head = newElement;
                    _descriptors[i]._tail = newElement;
                }
                else
                {
                    Element<T> *prev = _descriptors[i]._tail;
                    prev->_pointers[i] = newElement;
                    _descriptors[i]._tail = newElement;
                }
            }

        }
        _descriptors->_tail = newElement;
    }

    void Delete(string secondName)
    {
        Element<T> *deletedElement = nullptr;
        Element<T> *currentElement = _descriptors[0]._head;

        if(currentElement != nullptr)
        {
            if(currentElement->_value.GetSecondName() == secondName)
            {
                _descriptors->_head = currentElement->_pointers[0];
                deletedElement = currentElement;
            }
            else
            {
                while (currentElement != nullptr)
                {
                    if(currentElement->_pointers[0]->_value.GetSecondName() == secondName)
                    {
                        deletedElement = currentElement->_pointers[0];
                        currentElement->_pointers[0] = deletedElement->_pointers[0];

                        if(currentElement->_pointers[0] == nullptr)
                        {
                            _descriptors->_tail = currentElement;
                        }
                        break;
                    }
                    currentElement = currentElement->_pointers[0];
                }
            }

            if(deletedElement != nullptr)
            {
                for (int i = 1; i < _criteriaCount; ++i)
                {
                    currentElement = _descriptors[i]._head;
                    if(currentElement == deletedElement
                        && currentElement->_pointers[i] != nullptr
                        )
                    {
                        _descriptors->_head = currentElement->_pointers[i];
                    }
                    else if (currentElement == deletedElement
                        && currentElement->_pointers[i] == nullptr
                        )
                    {
                        _descriptors[i]._head = nullptr;
                        _descriptors[i]._tail = nullptr;
                    }

                    while (currentElement != nullptr)
                    {
                        if(currentElement->_pointers[i] == deletedElement)
                        {
                            currentElement->_pointers[i] = currentElement->_pointers[i]->_pointers[i];

                            if(currentElement->_pointers[i] == nullptr)
                            {
                                _descriptors->_tail = currentElement;
                            }
                        }
                        currentElement = currentElement->_pointers[i];
                    }
                }
            }
        }
        else
        {
            cout << "Base is empty" << endl;
        }

        if(deletedElement == nullptr)
        {
            cout << "No such student" << endl;
        }
        free(deletedElement);
    }

    void DeleteAll()
    {
        Element<T> *currentElement = _descriptors[0]._head;
        if(currentElement != nullptr)
        {
            Element<T> *nextElement = currentElement->_pointers[0];

            while(nextElement != nullptr)
            {
                currentElement = nextElement;
                nextElement = nextElement->_pointers[0];
                free(currentElement);
            }

            for (int i = 0; i < _criteriaCount; ++i)
            {
                _descriptors[i]._head = nullptr;
                _descriptors[i]._tail = nullptr;
                _descriptors[i]._ptr = nullptr;
            }
        }
        else
        {
            cout << "Base is empty" << endl;
        }
    }

    void PrintByCriteria(int criteriaNumber)
    {
        Element<T> *currentElement = _descriptors[criteriaNumber]._head;

        if(currentElement != nullptr)
        {
            currentElement->_value.Print();
            currentElement = currentElement->_pointers[criteriaNumber];

            while (currentElement != nullptr)
            {
                currentElement->_value.Print();
                currentElement = currentElement->_pointers[criteriaNumber];
            }
        }
        else
        {
            cout << "There are not elemnts by this criteria" << endl;
        }
    }

    void PrintAll()
    {
        Element<T> *currentElement = _descriptors[0]._head;

        if(currentElement != nullptr)
        {
            currentElement->_value.Print();
            currentElement = currentElement->_pointers[0];

            while (currentElement != nullptr)
            {
                currentElement->_value.Print();
                currentElement = currentElement->_pointers[0];
            }
        }
        else
        {
            cout << "Base is empty" << endl;
        }
    }

    ~MultyList()
    {
        DeleteAll();
        free(_descriptors);
    }
};
#endif //ALGORITHMS_LAB2_MULTYLIST_H
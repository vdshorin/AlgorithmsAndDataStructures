#ifndef ALGORITMS_LAB1_SERIALQUEUE_H
#define ALGORITMS_LAB1_SERIALQUEUE_H

#include "ELType.h"
#include <iostream>

using namespace std;

template <class T>
class Queue {
private:
    int _head;
    int _tail;
    int _size;
    T *_myQueue;

public:
    Queue()
    {
        cout << "Enter queue size:";
        cin >> _size;
        _myQueue = new T [_size];
        _head = 1;
        _tail = 1;
    }

    bool Enqueue(T elType)
    {
        if((_tail % _size + 1) == _head)
        {
            //cout << endl << "FALSE" << endl << endl;
            return false;
        }
        else
        {
            //cout << endl << "TRUE" << endl << endl;

            _myQueue[_tail] = elType;
            _tail = (_tail % _size) + 1;
            if(_tail == _size)
            {
                _tail = 0;
            }

            return true;
        }
    }

    bool Dequeue()
    {
        if(IsEmpty())
        {
            return false;
        }
        else
        {
            T elType = _myQueue[_head];
            _head = _head % _size + 1;
            if(_head == _size)
            {
                _head = 0;
            }
            return true;
        }
    }

    bool IsEmpty()
    {
        return  _head == _tail;
    }

    bool IsFull()
    {
        return _tail % _size + 1 == _head;
    }

    T Top()
    {
        return  _myQueue[_head];
    }

    int GetCount()
    {
        if(_head > _tail)
        {
            return _size - (_head - _tail);
        }
        else
        {
            return _tail - _head;
        }
    }

    ~Queue(){}
};

#endif //ALGORITMS_LAB1_SERIALQUEUE_H
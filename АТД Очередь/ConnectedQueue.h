#ifndef ALGORITMS_LAB1_CONNECTEDQUEUE_H
#define ALGORITMS_LAB1_CONNECTEDQUEUE_H

#include "ELType.h"
#include <iostream>

using namespace std;

template <class T>
class Queue {
private:
    struct Node
    {
        T data;
        Node *next;
    };

    Node *_head;
    Node *_tail;
    int _size;

public:
    Queue()
    {
        _head = new Node;
        _head->next = NULL;
        _tail = _head;
        _size = 0;
    }

    bool Enqueue(T elType)
    {
        Node *temp = new(Node); // Выделяем память под новый хвост очереди
        temp->next = 0;         // Записываем в поле адреса нового хвоста ноль, так как за ним ничего нету
        temp->data = elType;    //Заполняем поле значения нового хвоста
        _tail->next = temp;     // Записываем в поле адреса старого хвоста адрес нового хвоста
        _tail = temp;           //Записываем в указель хвоста адрес действительного хвоста
        _size++;
    }

    bool Dequeue()
    {
        Node *temp = _head;     // записываем адрес головы
        T value = _head->data;  // записываем значение головы
        _head = _head->next;    // изменяем адрес головы
        delete temp;            // удаляем старую голову
        _size--;
    }

    bool IsEmpty()
    {
        return _head == _tail;
    }

    bool IsFull()
    {
        return false;
    }

    T Top()
    {
        return _head->next->data;
    }

    int GetCount()
    {
        return _size;
    }

    ~Queue(){}
};

#endif //ALGORITMS_LAB1_CONNECTEDQUEUE_H
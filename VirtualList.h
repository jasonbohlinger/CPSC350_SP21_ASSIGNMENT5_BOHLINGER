#ifndef VIRTUALLIST_H
#define VIRTUALLIST_H
#include <iostream>
using namespace std;

template <typename T>
class VirtualList{
    public:
        virtual void insertBack(T data) = 0;
        virtual void insertFront(T x) = 0;
        virtual T removeFront() = 0;
        virtual T removeBack() = 0;
        virtual T access(int index) = 0;
        virtual bool isEmpty() = 0;
        virtual size_t getSize() = 0;
        virtual T peekFront() = 0;
        virtual T peekBack() = 0;
};

#endif
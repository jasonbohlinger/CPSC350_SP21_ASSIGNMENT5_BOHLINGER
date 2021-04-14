#ifndef GENLIST_H
#define GENLIST_H
#include "GenLinkedList.h"
#include "VirtualList.h"
#include <iostream>
using namespace std;

//A templatized List ADT that inherits from a pure virtual list class
//The List ADT implements a LinkedList based List
template <typename T>
class GenList : VirtualList<T>{
    public:
        GenList();
        ~GenList();
        void insertBack(T data);
        void insertFront(T data);
        T removeFront();
        T removeBack();
        T access(int index);
        bool isEmpty();
        size_t getSize();
        T peekFront();
        T peekBack();
    private:
        GenLinkedList<T> *linkedList;
};

template <typename T>
GenList<T>::GenList(){
    linkedList = new GenLinkedList<T>;
}

template <typename T>
GenList<T>::~GenList(){
    delete linkedList;
}
template <typename T>
void GenList<T>::insertBack(T data){
    linkedList->insertBack(data);
}

template <typename T>
void GenList<T>::insertFront(T data){
    linkedList->insertFront(data);
}

template <typename T>
T GenList<T>::removeFront(){
    return linkedList->removeFront();
}

template <typename T>
T GenList<T>::removeBack(){
    return linkedList->removeBack();
}

template <typename T>
T GenList<T>::access(int index){
    return linkedList->access(index);
}

template <typename T>
bool GenList<T>::isEmpty(){
    return (linkedList->getSize() == 0);
}

template <typename T>
size_t GenList<T>::getSize(){
    return linkedList->getSize();
}

template <typename T>
T GenList<T>::peekFront(){
    return linkedList->getFront();
}

template <typename T>
T GenList<T>::peekBack(){
    return linkedList->getBack();
}

#endif
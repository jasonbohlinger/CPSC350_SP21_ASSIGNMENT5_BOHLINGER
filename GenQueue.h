#ifndef GENQUEUE_H
#define GENQUEUE_H
#include "GenList.h"
#include <iostream>
using namespace std;

template <typename T>
class GenQueue{
    public:
        GenQueue();
        ~GenQueue();
        void insert(T d);
        T remove();
        T peek();
        size_t getSize();
        bool isEmpty();
    private:
        GenList<T> *thisList;
};

template <typename T>
GenQueue<T>::GenQueue(){
    thisList = new GenList<T>;
}

template <typename T>
GenQueue<T>::~GenQueue(){
   delete thisList;
}

template <typename T>
void GenQueue<T>::insert(T d){
    thisList->insertBack(d);
}

template <typename T>
T GenQueue<T>::remove(){
    if(isEmpty()){
        throw runtime_error ("Queue is already empty. Cannot remove"); 
    }
    T ret = thisList->removeFront();
    return ret;
}

template <typename T>
T GenQueue<T>::peek(){
    if(isEmpty()){
        throw runtime_error ("Queue is empty. No elements to peek");
    }
    return thisList->peekFront();
}

template <typename T>
size_t GenQueue<T>::getSize(){
    return thisList->getSize();
}

template <typename T>
bool GenQueue<T>::isEmpty(){
    return (getSize() == 0);
}

#endif
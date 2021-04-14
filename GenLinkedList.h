#ifndef GENLINKEDLIST_H
#define GENLINKEDLIST_H
#include "GenList.h"
#include "GenListNode.h"
#include <iostream>
using namespace std;
// Templatized Doubly Linked List
template <typename T>
class GenLinkedList{
    public: 
        GenLinkedList();
        ~GenLinkedList();
        void insertFront(T data);
        void insertBack(T data);
        T removeFront();
        T removeBack();
        T remove(T key);
        T find(T value);
        T access(int index);
        bool isEmpty();
        size_t getSize();
        T getBack();
        T getFront();
    private:
        GenListNode<T> *front; // The node at the front of the list
        GenListNode<T> *back; // The node at the back of the list
        size_t listSize; // The number of elements in the list
};

template <typename T>
GenLinkedList<T>::GenLinkedList(){
    front = nullptr;
    back = nullptr;
    listSize = 0;
}

template <typename T>
GenLinkedList<T>::~GenLinkedList(){
    GenListNode<T> *n = this->front;
    GenListNode<T> *curr = nullptr;
    // Uses curr as a temporary variable to hold onto the current node. 
    // Sets n to it's next node
    while(n != nullptr){
        curr = n;
        n = n->next;
        delete curr;
    }
    front = nullptr;
    back = nullptr;
}

template <typename T>
void GenLinkedList<T>::insertFront(T data){
    GenListNode<T> *newNode = new GenListNode<T>(data);
    if(isEmpty()){
        back = newNode;
    } else{
        front->prev = newNode;
        newNode->next = front;
    }
    front = newNode;
    ++listSize;
}

template <typename T>
void GenLinkedList<T>::insertBack(T data){
    GenListNode<T> *newNode = new GenListNode<T>(data);
    if(isEmpty()){
        front = newNode;
    } else{
        back->next = newNode;
        newNode->prev = back;
    }
    back = newNode;
    ++listSize;
}

template <typename T>
T GenLinkedList<T>::removeFront(){
    GenListNode<T> *tp = front;
    if(isEmpty()){
        throw runtime_error ("LinkedList is already empty. Cannot remove.");
    }
    if(front->next == nullptr){
        back = nullptr;
    } else{
        front->next->prev = nullptr;
    }
    front = front->next;
    tp->next = nullptr;
    T temp = tp->data;
    --listSize;
    delete tp;
    return temp;
}

template <typename T>
T GenLinkedList<T>::removeBack(){
    GenListNode<T> *tp = back;
    if(isEmpty()){
        throw runtime_error ("LinkedList is already empty. Cannot remove");
    }  
    if(back->prev == nullptr){
        front = nullptr;
    } else{
        back->prev->next = nullptr;
    }
    back = back->prev;
    tp->prev = nullptr;
    T temp = tp->data;
    --listSize;
    delete tp;
    return temp;
}

template <typename T>
T GenLinkedList<T>::remove(T key){
    GenListNode<T> *curr = front;

    while(curr->data != key){
        curr = curr->next;
        if(curr == nullptr){
            return 0;
        }
    }
    if(curr == front){
        front = curr->next;
        front->prev = nullptr;
    } else if(curr == back){
        back = curr->prev;
        back->next = nullptr;
    } else{
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
    curr->prev = nullptr;
    curr->next = nullptr;
    listSize--;
    delete curr;
    return key;
}

template <typename T>
T GenLinkedList<T>::find(T value){
    int indx = -1;
    GenListNode<T> *curr = front;
    while(curr != nullptr){
        ++indx;
        if(curr->data == value){
            break;
        } else{
            curr = curr->next;
        }
    }
    if(curr == nullptr){
        indx = -1;
    }
    return indx;
}

template <typename T>
T GenLinkedList<T>::access(int index){
    if(index < listSize){
        GenListNode<T> *curr = front;
        for(int i = 1; i <= index; ++i){
            if(curr == nullptr){
                throw runtime_error ("Index out of bounds");
            }
            curr = curr->next;
        }
        return curr->data;
        
    } else{
        throw runtime_error ("Index out of bounds");
    }
}

template <typename T>
bool GenLinkedList<T>::isEmpty(){
    return (listSize == 0);
}

template <typename T>
size_t GenLinkedList<T>::getSize(){
    return listSize;
}

template <typename T>
T GenLinkedList<T>::getBack(){
    return this->back->data;
}

template <typename T>
T GenLinkedList<T>::getFront(){
    return this->front->data;
}
#endif


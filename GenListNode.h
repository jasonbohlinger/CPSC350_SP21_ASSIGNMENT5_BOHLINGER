#ifndef GENLISTNODE_H
#define GENLISTNODE_H
// A templatized List Node for a Linked List
template <typename T>
class GenListNode{
    public:
        GenListNode();
        GenListNode(T data);
        ~GenListNode();
        GenListNode *prev; // A pointer to this node's previous node in the LinkedList
        GenListNode *next; // A pointer to this node's next node in the LinkedList
        T data;
};

template <typename T>
GenListNode<T>::GenListNode(){
    next = nullptr;
    prev = nullptr;
    data = 0;
}

template <typename T>
GenListNode<T>::GenListNode(T data){
    next = nullptr;
    prev = nullptr;
    this->data = data;
}

template <typename T>
GenListNode<T>::~GenListNode(){
    next = nullptr;
    prev = nullptr;
    delete next;
    delete prev;
}
#endif
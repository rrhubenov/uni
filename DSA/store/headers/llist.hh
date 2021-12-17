#pragma once

#include<iostream>

using namespace std;

template<typename T>
struct Node {
    Node<T>* next;
    T data;

    Node(T data, Node<T>* next) {
        this->next = next;
        this->data = data;
    }
};

template<typename T>
class LList {
    int size;

    void insertAfterNode(Node<T>* node, T element);

    public:
        Node<T>* head;
        Node<T>* tail;
        LList();

        void insert(T element, size_t pos);
        void insertFront(T element);
        void insertSorted(T element);
        void insertBack(T element);
        void remove(const size_t pos);
        void removeFront();
        bool isEmpty();

        T front();

        int getSize();
};


template<typename T>
LList<T>::LList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template<typename T>
bool LList<T>::isEmpty() {
    return size == 0;
}

template<typename T>
int LList<T>::getSize() {
    return size;
}

template<typename T>
void LList<T>::insert(T element, size_t pos) {
    assert(pos <= size);

    Node<T>* newNode = new Node<T>(element, nullptr);

    if(pos == 0) {
        newNode->next = head;
        this->head = newNode;
        if(size == 0) {
            this->tail = newNode;
        } 
    }
    else if(pos == size) {
        this->tail->next = newNode;
        this->tail = newNode;
    } else {
        Node<T>* curr = head;
        for(unsigned i = 0; i < pos; ++i) {
            curr = curr->next;
        }
        Node<T>* pNext = curr->next;
        curr->next = newNode;

        newNode->next = pNext;
    }

    size++;
}

template<typename T>
void LList<T>::insertSorted(T element) {
    if(size == 0) {
        insertFront(element);
    } else {
        if(element < head->data) {
            insertFront(element);
        } else if(element >= tail->data) {
            insertAfterNode(tail, element); 
        } else {
            Node<T>* curr = head;
            for(int i = 0; i < size-1; ++i) {
                if(curr->data <= element && element < curr->next->data) {
                    insertAfterNode(curr, element);
                    break;
                }
                curr = curr->next;
            }
        }
    }
}

template<typename T>
void LList<T>::insertAfterNode(Node<T>* node, T element) {
    Node<T>* prevNext = node->next;
    node->next = new Node<T>(element, prevNext);

    if(node == tail)
        tail = tail->next;

    size++;
}

template<typename T>
void LList<T>::insertFront(T element) {
    insert(element, 0);
}

template<typename T>
void LList<T>::remove(const size_t pos) {
    
    assert(pos < size);

    Node<T>* iter = head;
    Node<T>* toRemove = nullptr;

    if(pos == 0 && size == 1) {
        toRemove = head;
        head = nullptr;
        tail = nullptr;
    } else if(pos == 0 && size > 1) {
        toRemove = head;
        head = head->next;
    } else {

        for(unsigned i = 0; i < pos-1; iter = iter->next) {
            assert(iter != nullptr);
        }
        Node<T>* prev = iter;
        toRemove = prev->next;
        prev->next = toRemove->next;

        if(toRemove == tail) {
            tail = prev;
        }
    }

    size--;

    delete toRemove;
} 

template<typename T>
void LList<T>::removeFront() {
    remove(0);
}

template<typename T>
T LList<T>::front() {
    return head->data;
}

template<typename T>
void LList<T>::insertBack(T element) {
    insert(element, size);
}



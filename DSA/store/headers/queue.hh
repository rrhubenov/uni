#pragma once

template<class T>
class Queue {
   
    int size;

    int end;
    int begin;

    int capacity;
    T* data;

    public:
        Queue(int capacity);
        ~Queue();

        void enqueue(T element);
        T dequeue();
        T first();

        bool isEmpty();
        bool isFull();
};

template<class T>
Queue<T>::Queue(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->begin = 0;
    this->end = 0;

    this->data = new T[capacity];
}

template<class T>
Queue<T>::~Queue() {
    delete[] data;
}

template<class T>
bool Queue<T>::isFull() {
    return size == capacity;
}

template<class T>
void Queue<T>::enqueue(T element) {
    
    assert(!isFull());

    data[end] = element;

    end = (end+1) % (capacity);

    size++;
}

template<class T>
T Queue<T>::dequeue() {
    assert(!isEmpty());

    T element = data[begin];

    begin = (begin + 1) % (capacity);

    size--;

    return element;
}

template<class T>
bool Queue<T>::isEmpty() {
    return size == 0;
}

template<class T>
T Queue<T>::first() {
    assert(!isEmpty());

    return data[begin];
}


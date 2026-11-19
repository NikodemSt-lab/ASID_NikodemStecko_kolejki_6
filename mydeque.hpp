#ifndef MYDEQUE_HPP
#define MYDEQUE_HPP

#include <cassert>
#include <cstddef>
#include <iostream>
#include <new>
#include <utility>

template <typename T>
class MyDeque {
    T* tab;
    std::size_t msize; // pojemnosc plus jedno wolne miejsce
    std::size_t head;  // pierwszy element
    std::size_t tail;  // pierwsze wolne miejsce za ostatnim elementem

public:
    MyDeque(std::size_t s = 10) : msize(s + 1), head(0), tail(0) 
    {
        if (msize == 0) 
        {
            throw std::bad_array_new_length();
        }
        tab = new T[msize];
    }
    ~MyDeque() { delete[] tab; }
    MyDeque(const MyDeque& other);
    MyDeque& operator=(const MyDeque& other);

    bool empty() const 
    { 
        return head == tail; 
    }
    bool full() const 
    { 
        return (tail + 1) % msize == head; 
    }

    std::size_t size() const
    {
        return tail >= head ? tail - head : msize - head + tail;
    }
    std::size_t max_size() const 
    {
         return msize - 1; 
    }

    void push_front(const T& item);
    void push_back(const T& item);

    T& front() 
    {    
        assert(!empty()); return tab[head]; 
    }
    T& back() 
    { 
        assert(!empty()); return tab[(tail + msize - 1) % msize]; 
    }

    void pop_front();
    void pop_back();

    void clear() 
    { 
        head = tail = 0; 
    }

    void display() const;
    void display_reversed() const;
};

template <typename T>
MyDeque<T>::MyDeque(const MyDeque& other) : MyDeque(other.max_size())
{
    for (std::size_t i = other.head; i != other.tail; i = (i + 1) % msize) 
    {
        push_back(other.tab[i]);
    }
}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque& other) 
{
    if (this != &other) 
    {
        MyDeque copy(other);
        std::swap(tab, copy.tab);
        std::swap(msize, copy.msize);
        std::swap(head, copy.head);
        std::swap(tail, copy.tail);
    }
    return *this;
}

template <typename T>
void MyDeque<T>::push_front(const T& item) 
{
    assert(!full());
    const std::size_t pos = (head + msize - 1) % msize;
    tab[pos] = item;
    head = pos;
}

template <typename T>
void MyDeque<T>::push_back(const T& item) 
{
    assert(!full());
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_front() 
{
    assert(!empty());
    head = (head + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_back() 
{
    assert(!empty());
    tail = (tail + msize - 1) % msize;
}

template <typename T>
void MyDeque<T>::display() const 
{
    for (std::size_t i = head; i != tail; i = (i + 1) % msize) 
    {
        std::cout << tab[i] << ' ';
    }
    std::cout << '\n';
}

template <typename T>
void MyDeque<T>::display_reversed() const 
{
    for (std::size_t i = tail; i != head;) 
    {
        i = (i + msize - 1) % msize;
        std::cout << tab[i] << ' ';
    }
    std::cout << '\n';
}

#endif

#ifndef QUEUE_H     //queue.h
#define QUEUE_H

#include <iostream>
#include "node.h"

template <class T>
class queue
{
public:
    // TYPES & CONSTANTS
    typedef T value_type;
    typedef std::size_t size_type;

    // CONSTRUCTORS & DESTRUCTORS

    // pre: none
    // post: creates an empty queue
    queue();

    // pre: none
    // post: creates a copy of the queue source
    queue(const queue & source);

    // pre: none
    // post: destroys this queue
    ~queue();

    // CONSTANT MEMBERS

    // pre: none
    // post: returns true if this queue is empty; false otherwise
    bool empty() const;

    // pre: none
    // post: returns the number of elements in this queue
    size_type size() const;

    // pre: this queue is not empty
    // post: returns the front (first inserted) element
    value_type front() const;

    // MUTATORS
    value_type & front();

    // pre: this queue is not empty
    // post: the front element of this queue has been removed
    void pop();

    // pre: none
    // post: a copy of entry has been added to the rear of this queue
    void push(const value_type & entry);


    // pre: none
    // post: makes this queue a copy of source
    void operator =(const queue & source);

private:
    node<T> *front_ptr, *rear_ptr;

    // class invariants:
    // the elements of this queue is maintained in a linked list
    // in order of insertion
    // front_ptr points to the head of the list
    // rear_ptr points to the last node of this list

};



template <class T>
queue<T>::queue()
{
    front_ptr = rear_ptr = nullptr;
}

template <class T>
queue<T>::~queue()
{
    list_clear(front_ptr);
    front_ptr = rear_ptr = nullptr;
}


template <class T>
queue<T>::queue(const queue &source)
{
     list_copy(source.front_ptr, front_ptr, rear_ptr);

}

template <class T>
void queue<T>::operator = (const queue & source)
{
    if (this == &source)
        return;

    list_clear(front_ptr);
    list_copy(source.front_ptr, front_ptr, rear_ptr);


}

template <class T>
bool queue<T>::empty() const
{
   return (front_ptr == nullptr);
}

template <class T>
queue<T>::size_type queue<T>::size() const
{
    return list_length(front_ptr);
}

template <class T>
T  queue<T>::front() const
{
    assert(!empty());
    return front_ptr->data();
}

template <class T>
T & queue<T>::front()
{
    assert(!empty());
    return front_ptr->data();
}

template <class T>
void queue<T>::pop()
{
    assert(!empty());
    list_head_remove(front_ptr);
}

template <class T>
void queue<T>::push(const value_type &entry)
{
    if (empty())
    {
        list_head_insert(front_ptr, entry);
        rear_ptr = front_ptr;
    }
    else
    {
        list_insert(rear_ptr, entry);
        rear_ptr = rear_ptr->link();
    }
}








#endif // QUEUE_H

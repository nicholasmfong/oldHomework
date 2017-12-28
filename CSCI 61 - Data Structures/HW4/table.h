#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <list>

template <class T, std::size_t TABLE_SIZE>
class table
{
public:

    typedef std::size_t size_type;

    table();
    ~table();

    // pre: none
    // post: returns the number of items in this table
    size_type size() const;

    // pre: none
    // post: returns true iff value is in this table
    bool find(T &value);


    // pre: none
    // post: if value is already in this table, do nothing
    //       else add value to this table
    void insert( T & value);

    // pre: none
    // post: remove value from this table if it is present; else do nothing
    void erase(const T & value);

private:
    std::list<T> *data;
    size_type used;

    // pre: none
    // post: returns an index between 0 and TABLE_SIZE-1
    size_type hash(const T & value);

    // invariants: data is a chained hash table

};

template <class T, std::size_t TABLE_SIZE>
table<T, TABLE_SIZE>::table()
{
    data = new std::list<T>[TABLE_SIZE];
    used = 0;
    for (size_type i = 0; i < TABLE_SIZE; ++i)
        data[i] = std::list<T>();
}

template <class T, std::size_t TABLE_SIZE>
table<T, TABLE_SIZE>::~table()
{
    delete [] data;
    used = 0;
}

template <class T, std::size_t TABLE_SIZE>
typename table<T, TABLE_SIZE>::size_type table<T, TABLE_SIZE>::size() const
{
    return used;
}

template <class T, std::size_t TABLE_SIZE>
bool table<T, TABLE_SIZE>::find( T &value)
{
    size_t pos = hash(value);
    std::list<T> l = data[pos];

    for (auto i = l.begin(); i != l.end(); ++i)
        if (*i == value)
            return true;
    return false;
}

template <class T, std::size_t TABLE_SIZE>
void table<T, TABLE_SIZE>::insert(T &value)
{
    if (find(value))
        return;

    size_type pos = hash(value);
    data[pos].push_front(value);
    ++used;
}

template <class T, std::size_t TABLE_SIZE>
void table<T, TABLE_SIZE>::erase(const T &value)
{
    if (!find(value))
        return;

    size_type pos = hash(value);
    for (auto i = data[pos].begin(); i != data[pos].end(); ++i)
        if (*i == value)
        {
            data[pos].erase(i);
            --used;
            return;
        }
}

template <class T, std::size_t TABLE_SIZE>
typename table<T, TABLE_SIZE>::size_type table<T, TABLE_SIZE>::hash(const T &value)
{
    size_type sum(0);
    for (size_t i = 0; i < value.size(); ++i)
        sum = (((sum << 5) + sum) + value[i]) % TABLE_SIZE;

    return sum;
}

#endif // TABLE_H

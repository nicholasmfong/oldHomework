#ifndef NODE_H      //node.h
#define NODE_H

template <class T>
class node
{
public:
    typedef T value_type;

    node(const value_type & init_data = value_type(),
         node * init_link = nullptr)
    {
        data_field = init_data;
        link_field = init_link;
    }

    // MUTATORS
    value_type & data()
    {
        return data_field;

    }

    node * link()
    {
        return link_field;
    }

    // CONSTANT members

    const value_type & data() const
    {
        return data_field;
    }


    const node * link() const
    {
        return link_field;
    }




private:
    value_type data_field;
    node *     link_field;;
};


template <class T>
class node_iterator
{
public:
    // constructor
    explicit node_iterator(node<T> *initial = nullptr)
    {
        p = initial;
    }

    node_iterator(const node_iterator & source)
    {
        p = source.p;
    }

    T & operator *() const
    {
        return p->data();
    }

    // pre-increment operator
    node_iterator & operator ++()
    {
        p = p->link();
        return p;
    }

    // post-increment
    node_iterator operator ++(int)
    {
        node_iterator original(p);
        p = p->link();
        return original;
    }

    bool operator ==(const node_iterator & source)
    {
        return (p == source.p);
    }
    bool operator !=(const node_iterator & source)
    {
        return (p != source.p);
    }


private:
    node<T> *p;
};


template <class T>
class const_node_iterator
{
public:
    // constructor
    const_node_iterator(const node<T> *initial = nullptr)
    {
        p = initial;
    }

    const_node_iterator(const const_node_iterator & source)
    {
        p = source.p;
    }

    const T & operator *() const
    {
        return p->data();
    }

    // pre-increment operator
    const_node_iterator & operator ++()
    {
        p = p->link();
        return p;
    }

    // post-increment
    const_node_iterator operator ++(int)
    {
        const_node_iterator original(p);
        p = p->link();
        return original;
    }

    bool operator ==(const const_node_iterator & source)
    {
        return (p == source.p);
    }
    bool operator !=(const const_node_iterator & source)
    {
        return (p != source.p);
    }


private:
    const node<T> *p;
};





template <class T>
void list_clear(node<T> * & head);

template <class T>
void list_copy(const node<T> * source,
               node<T>* & head,
               node<T>* & tail);

template <class T>
void list_head_insert(node<T> * &head, const T & entry);

template <class T>
void list_head_remove(node<T> * &head);

template <class T>
void list_insert(node<T> * prev, const T & entry);

template <class T>
void list_remove(node<T> * prev);

template <class T>
std::size_t list_length(const node<T> * head);

// generates both const and regular versions of node *
template<class T, class NodePtr>
NodePtr list_search(NodePtr head, const T & target);

template <class NodePtr, class SizeType>
SizeType list_locate(NodePtr head, SizeType pos);

template <class T>
std::size_t list_length(const node<T> * head)
{
    std::size_t ans(0);
    for (const node<T> *p = head; p != nullptr; p = p->link())
        ++ans;

    return ans;
}

template <class T, class NodePtr>
NodePtr list_search(NodePtr head, const T & target)
{
    for (NodePtr p = head; p != nullptr; p = p->link())
    {
        if (target == p->data())
            return p;
    }
    return nullptr;
}

template <class NodePtr, class SizeType>
NodePtr list_locate(NodePtr head, SizeType pos)
{
    assert(pos > 0);
    SizeType i(1);
    NodePtr p;
    for (p = head; (i < pos) && p != nullptr; p = p->link())
        ++i;
    return p;
}



#endif // NODE_H

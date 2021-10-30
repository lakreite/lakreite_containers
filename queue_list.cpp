#ifndef LAKREITE_QUEUE_LIST_CPP
#define LAKREITE_QUEUE_LIST_CPP

#include"queue_list.hpp"
#include<utility>
#include<cassert>


template<class T_type>
inline
uint64_t lakreite_containers::queue_list<T_type>::
size() const{
    return this->amount;
}

template<class T_type>  lakreite_containers::
bilist<T_type>*         lakreite_containers::queue_list<T_type>::
add_next(bilist<T_type>* to, const T_type& from)
{
    assert(to != nullptr);
    to->next = new bilist<T_type>;
    to->next->prev = to;

    to->next->value = from;
    return to->next;
}

template<class T_type>  lakreite_containers::queue_list<T_type>::
queue_list()
{
    amount    = 0;
    in_queue  = nullptr;
    out_queue = nullptr;
}

template<class T_type>  lakreite_containers::queue_list<T_type>::
queue_list(const queue_list<T_type>& origin)
{
    amount = origin.amount;

    auto origin_iter = origin.in_queue;
    auto this_iter   = new bilist<T_type>;
    
    in_queue        = this_iter;
    in_queue->prev  = nullptr;
    in_queue->value = origin_iter->value;
    
    origin_iter = origin_iter->next;

    while (origin_iter != nullptr){
        this_iter   = add_next(this_iter, origin_iter->value);
        origin_iter = origin_iter->next;
    }

    this_iter->next = nullptr;
    out_queue       = this_iter;
}

template<class T_type>  lakreite_containers::queue_list<T_type>::
queue_list(queue_list<T_type>&& origin)
{
    in_queue  = origin.in_queue;
    out_queue = origin.out_queue;
    amount    = origin.amount;

    origin.in_queue  = nullptr;
    origin.out_queue = nullptr;
    origin.amount    = 0;  
}

template<class T_type>  lakreite_containers::queue_list<T_type>::
queue_list(const std::initializer_list<T_type>& init_list)
{
    amount = init_list.size();
    if (amount == 0){
        in_queue  = nullptr;
        out_queue = nullptr;
        return;
    }

    auto origin_iter = init_list.begin();
    
    in_queue        = new bilist<T_type>;
    in_queue->prev  = nullptr;
    in_queue->value = *origin_iter;

    auto this_iter  = in_queue;
    ++origin_iter;

    for (int i = 1; i < amount; ++i, ++origin_iter){
        this_iter = add_next(this_iter, *origin_iter);
    } 

    this_iter->next = nullptr;
    out_queue       = this_iter;
}

template<class T_type>  lakreite_containers::queue_list<T_type>::
~queue_list()
{
    while (in_queue != nullptr){
        auto temp = in_queue;
        in_queue  = in_queue->next;
        delete temp;
    }
    amount = 0;
}

template<class T_type>  lakreite_containers::
queue_list<T_type>&     lakreite_containers::queue_list<T_type>::
push(const T_type& value)
{
    if (amount == 0){
        in_queue       = new bilist<T_type>;
        in_queue->prev = nullptr;
        in_queue->next = nullptr;
        out_queue      = in_queue;
    }
    else {
        in_queue->prev       = new bilist<T_type>;
        in_queue->prev->next = in_queue;
        in_queue             = in_queue->prev;
        in_queue->prev       = nullptr;
    }

    in_queue->value = value;
    ++amount;

    return *this;
}

template<class T_type>
T_type                  lakreite_containers::queue_list<T_type>::
pop()
{
    assert(out_queue != nullptr);
    T_type value = out_queue->value;

    if (amount == 1){
        delete out_queue;
        in_queue  = nullptr;
        out_queue = nullptr;
    }
    else{
        out_queue = out_queue->prev;
        delete out_queue->next;
        out_queue->next = nullptr;
    }
    --amount;
    return value;
}

template<class T_type>
T_type*                 lakreite_containers::queue_list<T_type>::
operator[](uint64_t i)
{
    if (i > amount)
        return nullptr;
    auto iter = out_queue;
    while (i > 1)
    {
        --i;
        iter = iter->prev;
    }
    return &(iter->value);
}

template<class T_type>
const T_type*           lakreite_containers::queue_list<T_type>::
operator[](uint64_t i) const
{
    if (i > amount)
        return nullptr;
    auto iter = out_queue;
    while (i > 1)
    {
        --i;
        iter = iter->prev;
    }
    return &(iter->value);
}

template<class T_type>
bool            lakreite_containers::queue_list<T_type>::
operator==(const queue_list<T_type>& arg) const
{
    if (amount != arg.amount)
        return false;
    auto iter1 = in_queue;
    auto iter2 = arg.in_queue;
    bool retvalue = true;

    while (iter1 != nullptr){
        if (iter1->value != iter2->value)
            return false;
        iter1 = iter1->next;
        iter2 = iter2->next;
    }

    return true;
}

template<class T_type>
bool                    lakreite_containers::queue_list<T_type>::
operator!=(const queue_list<T_type>& arg) const
{
    return !(this->operator==(arg));
}

template<class T_type>  lakreite_containers::
queue_list<T_type>&     lakreite_containers::queue_list<T_type>::
operator=(const queue_list<T_type>& origin)
{
    while (amount > origin.amount){
        (void)this->pop();
    }
    
    while (amount < origin.amount){
        (void)this->push(0);
    }

    auto iter_to   = in_queue;
    auto iter_from = origin.in_queue;
    while (iter_to != nullptr){
        iter_to->value = iter_from->value;

        iter_to   = iter_to->next;
        iter_from = iter_from->next;
    }

    return *this;
}

template<class T_type>  lakreite_containers::
queue_list<T_type>&     lakreite_containers::queue_list<T_type>::
operator=(queue_list<T_type>&& origin)
{
    while (in_queue != nullptr){
        auto temp = in_queue;
        in_queue = in_queue->next;
        delete temp;
    }
    in_queue  = origin.in_queue;
    out_queue = origin.out_queue;
    amount    = origin.amount;

    origin.in_queue  = nullptr;
    origin.out_queue = nullptr;
    origin.amount    = 0;

    return *this;
}

template<class T_type>  lakreite_containers::
queue_list<T_type>&     lakreite_containers::queue_list<T_type>::
push_front(const T_type& value)
{
    if (amount == 0){
        return this->push(value);
    }

    out_queue = add_next(out_queue, value);
    out_queue->next = nullptr;
    ++amount;

    return *this;
}

template<class T_type>
T_type                  lakreite_containers::queue_list<T_type>::
pop_back()
{
    assert(in_queue != nullptr);

    T_type retvalue = in_queue->value;

    auto temp = in_queue;
    in_queue  = in_queue->next;
    delete temp;

    if (in_queue == nullptr){
        out_queue = nullptr;
    }
    else{
        in_queue->prev = nullptr;
    }
    --amount;

    return retvalue;
}

template<class T_type>
T_type                  lakreite_containers::queue_list<T_type>::
pop_from(uint64_t i)
{
    assert(i > 0 && i <= amount);
    if (i == amount)
        return this->pop_back();
    if (i == 1)
        return this->pop();
    
    auto iter = out_queue;
    for (int j = 1; j < i; ++j){
        iter = iter->prev;
    }

    T_type retval = iter->value;
    auto parent = iter->prev;
    parent->next = iter->next;
    iter->next->prev = parent;
    delete iter;
    --amount;

    return retval;
}

template<class T_type>  lakreite_containers::
queue_list<T_type>&     lakreite_containers::queue_list<T_type>::
push_to(uint64_t i, const T_type& value){
    if (i > amount){
        while (i > amount + 1){
            (void)this->push(value);
        }
        return this->push(value);
    }

    if (i == 1)
        return this->push_front(value);
    

    auto iter = out_queue;
    for (int j = 1; j < i; j++){
        iter = iter->prev;
    }

    auto new_member = new bilist<T_type>;
    new_member->value      = value;
    new_member->prev       = iter;
    new_member->next       = iter->next;
    new_member->next->prev = new_member;
    iter->next = new_member;
    ++amount;
    
    return *this;
}

#endif

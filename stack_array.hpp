////
////    queue_list.hpp
////    
////    Created by Maxim Kuznetsov
////

//!
//! \file stack_array.hpp
//! \brief Header file with definition of class template of queue container
//!

#ifndef LAKREITE_STACK_ARRAY_HPP
#define LAKREITE_STACK_ARRAY_HPP

#include<initializer_list>
#include<cstdint>
#include<algorithm>
#include<cassert>
#include<clocale>
#include<utility>

namespace lc
{
    template <class T_type>
    struct stack_array final
    {
        #ifndef DBG_stack_array

        private:

        #endif
            
            T_type *array;
    
            uint64_t   amount;
            uint64_t capacity;

        public:
            
            //! \brief default constructor
            stack_array();

            //! \brief constructor with initializer_list
            //! \param[in] lst - list of values, last element is new top of stack
            stack_array(const std::initializer_list<T_type>& lst);

            //! \brief copy constructor
            //! \param[in] origin - copyable stack_array
            stack_array(const stack_array<T_type>& origin);

            //! \brief copy-move consturcor
            //! \param[in] origin - movable value of stack_array
            explicit
            stack_array(stack_array<T_type>&& origin);

            ~stack_array();

            stack_array<T_type>&
            operator=(const stack_array<T_type>& origin);

            stack_array<T_type>&
            operator=(stack_array<T_type>&& origin);

            bool
            operator==(const stack_array<T_type>& arg) 
            const;

            bool
            operator!=(const stack_array<T_type>& arg)
            const;

            inline
            T_type&
            operator[](uint64_t i);

            const
            inline
            T_type&
            operator[](uint64_t i) 
            const;

            stack_array<T_type>&
            push(const T_type& new_top_value);

            T_type
            pop();

            inline
            uint64_t
            get_capacity() 
            const;
    
            void
            add_capacity();

            inline
            uint64_t
            size() 
            const;

    };
};

template<class T_type> lc::stack_array<T_type>::
stack_array()
{
    array = new T_type[10];
    amount   = 0;
    capacity = 10;
}

template<class T_type> lc::stack_array<T_type>::
stack_array(const std::initializer_list<T_type>& lst)
{
    if (lst.size() == 0)
    {
        array = new T_type[10];
        amount   = 0;
        capacity = 10;
        return;
    }

    amount   = 0;
    capacity = lst.size() + 10;
    array    = new T_type[capacity];

    for (auto iter: lst)
    {
        array[amount] = iter;
        ++amount;
    }
    
}

template<class T_type> lc::stack_array<T_type>::
stack_array(const stack_array<T_type>& origin)
{
    array = nullptr;
    *this = origin;
}

template<class T_type> lc::stack_array<T_type>::
stack_array(stack_array<T_type>&& origin)
{
    array = nullptr;
    *this = std::move(origin);
}

template<class T_type> lc::
stack_array<T_type>&   lc::stack_array<T_type>::
operator=(const stack_array<T_type>& origin)
{
    if (array != nullptr)
        delete[] array;

    amount   = origin.amount;
    capacity = origin.capacity;
    array    = new T_type[capacity];
    
    for (int i = 0; i < amount; ++i)
        array[i] = origin.array[i];

    return *this;
}

template<class T_type> lc::
stack_array<T_type>&   lc::stack_array<T_type>::
operator=(stack_array<T_type>&& origin)
{
    if (array != nullptr)
        delete[] array;
    amount   = origin.amount,   origin.amount   = 0;
    capacity = origin.capacity, origin.capacity = 0;
    array    = origin.array,    origin.array    = nullptr;

    return *this;
}

template<class T_type> lc::stack_array<T_type>::
~stack_array()
{
    if (array != nullptr)
        delete[] array;
    amount   = 0;
    capacity = 0;
    array    = nullptr;
}

template<class T_type>
bool             lc::stack_array<T_type>::
operator==(const stack_array<T_type>& arg)
const
{
    if (amount != arg.amount)
        return false;
    for (int i = 0; i < amount; ++i)
        if (array[i] != arg.array[i])
            return false;
    return true;
}

template<class T_type>
bool                   lc::stack_array<T_type>::
operator!=(const stack_array<T_type>& arg)
const
{
    return !(*this == arg);
}

template<class T_type>
inline
T_type&                lc::stack_array<T_type>::
operator[](uint64_t i)
{
    assert(i < amount);
    return array[amount - i - 1];
}


template<class T_type>
const
inline
T_type&          lc::stack_array<T_type>::
operator[](uint64_t i)
const
{
    assert(i < amount);
    return array[amount - i - 1];
}

template<class T_type> lc::
stack_array<T_type>&   lc::stack_array<T_type>::
push(const T_type& new_top_value)
{
    if (amount + 1 > capacity)
        add_capacity();
    array[amount] = new_top_value;
    ++amount;
    return *this;
}

template<class T_type> 
T_type                 lc::stack_array<T_type>::
pop()
{
    assert(amount > 0);
    --amount;
    return array[amount];
}

template<class T_type>
inline
uint64_t              lc::stack_array<T_type>::
get_capacity()
const
{
    return capacity;
}

template<class T_type>
void                   lc::stack_array<T_type>::
add_capacity()
{
    uint64_t new_capacity = capacity + 10;
    T_type *temp = new T_type[new_capacity];

    for (int i = 0; i < amount; ++i)
        temp[i] = array[i];
    delete[] array;
    array    = temp;
    temp     = nullptr;
    
    capacity = new_capacity;
}


template<class T_type>
inline
uint64_t               lc::stack_array<T_type>::
size()
const
{
    return amount;
}


#endif

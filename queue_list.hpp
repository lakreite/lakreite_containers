////
////    queue_list.hpp
////    
////    Created by Maxim Kuznetsov xx/07/2021
////

//!
//! \file queue_list.hpp
//! \brief Header file with definition of class template of queue container
//!


#ifndef LAKREITE_QUEUE_LIST_HPP
#define LAKREITE_QUEUE_LIST_HPP

#include<initializer_list>
#include<cstdint>

namespace lc
{
    template<class T_type>
    struct bilist
    {
        T_type value;

        bilist<T_type> *prev;
        bilist<T_type> *next;
    };

    template<class T_type>
    struct queue_list
    {   
        #ifndef DBG_queue_list
        private:         
        #endif

            bilist<T_type>  *in_queue;
            bilist<T_type> *out_queue;

            uint64_t amount;

        public:
            queue_list();
            
            queue_list(const std::initializer_list<T_type>& init_list);

            queue_list(const queue_list<T_type>& origin);

            queue_list(queue_list<T_type>&& origin);

            ~queue_list();

            queue_list<T_type>&
            push(const T_type& value);

            T_type
            pop();

            T_type*
            operator[](uint64_t i);

            const
            T_type*
            operator[](uint64_t i) const;

            bool
            operator==(const queue_list<T_type>& arg) const;

            bool
            operator!=(const queue_list<T_type>& arg) const;

            queue_list<T_type>&
            operator=(const queue_list<T_type>& origin);

            queue_list<T_type>&
            operator=(queue_list<T_type>&& origin);

            queue_list<T_type>&
            push_front(const T_type& value);

            T_type
            pop_back();

            T_type
            pop_from(uint64_t i);

            queue_list<T_type>&
            push_to(uint64_t i, const T_type& value);

            static
            bilist<T_type>*
            add_next(bilist<T_type>* to, const T_type& from);

            inline
            uint64_t 
            size() const;
    };
};

#endif
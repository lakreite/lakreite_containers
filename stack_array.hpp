#ifndef LAKREITE_STACK_ARRAY_HPP
#define LAKREITE_STACK_ARRAY_HPP

#include<initializer_list>
#include<cstdint>

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

            stack_array();

            stack_array(const std::initializer_list<T_type>& lst);

            stack_array(const stack_array<T_type>& origin);

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

#endif

#ifndef LAKREITE_STACK_LIST_HPP
#define LAKREITE_STACK_LIST_HPP

#include<initializer_list>

namespace lakreite_containers
{
    template<class T_type>
    struct list_elem
    {
        T_type value;
        list_elem<T_type>* next;
    };

    template<class T_type>
    struct stack_list final
    {
        #ifndef DBG_stack_list

        private:
        
        #endif

            list_elem<T_type>* top;
        
        public:
        
            static
            list_elem<T_type>
            *add_next(list_elem<T_type> *to, T_type value);

            stack_list();

            stack_list(const std::initializer_list<T_type>& lst);

            stack_list(const stack_list<T_type>& origin);

            explicit
            stack_list(stack_list<T_type>&& origin);
                
            ~stack_list();

            stack_list<T_type> 
            copy();

            T_type 
            pop();

            stack_list<T_type>&
            push(const T_type& new_top_value);

            bool 
            is_empty();

            bool 
            operator==(const stack_list<T_type>& arg);

            bool 
            operator!=(const stack_list<T_type>& arg);

            stack_list<T_type>& 
            operator=(const stack_list<T_type>& origin);

            
            stack_list<T_type>&
            operator=(stack_list<T_type>&& origin);
    };
}
#endif
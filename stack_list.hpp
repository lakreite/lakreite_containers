#ifndef LAKREITE_STACK_LIST_HPP
#define LAKREITE_STACK_LIST_HPP

#include<initializer_list>
#include<utility>
#include<cassert>
namespace lc
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

            //! \brief default constructor
            stack_list();

            //! \brief initializer_list constructor
            //! \param[in] lst - list of values, last value is top
            stack_list(const std::initializer_list<T_type>& lst);

            //! \brief copy constructor
            //! \param[in] origin - copyable stack_list
            stack_list(const stack_list<T_type>& origin);

            //! \brief copy-move constructor
            //! \param[in] origin - movable stack_list
            explicit
            stack_list(stack_list<T_type>&& origin);
                
            ~stack_list();
            
            //! \brief returns copy of stack_list
            stack_list<T_type> 
            copy();

            //! \brief delete top of stack
            //! \return top of stack
            T_type 
            pop();

            //! \brief add value to top of stack
            //! \param[in] new_top_value - new top value
            //! \return lvalue reference to stack_list
            stack_list<T_type>&
            push(const T_type& new_top_value);

            //! \brief function detect if stack_list is empty
            //! \return true if stack_list is empty and false if not
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


template<class T_type>
inline                  lc::
list_elem<T_type>*      lc::stack_list<T_type>::
add_next(lc::list_elem<T_type> *to, 
         T_type value)
{
    to->next = new list_elem<T_type>;
    to->next->value = value; 
    return to->next;
}

template<class T_type>  lc::stack_list<T_type>::
stack_list()
{
    top = nullptr;
}

template<class T_type>  lc::stack_list<T_type>::
stack_list(const std::initializer_list<T_type>& lst)
{
    if (lst.size() == 0)
    {
        top = nullptr;
        return;
    }

    top = new list_elem<T_type>;

    auto jiter = top;
    auto iter  = lst.begin();
                    
    top->value = *iter;
    ++iter;
    for(; iter != lst.end(); ++iter)
        jiter = add_next(jiter, *iter);
    jiter->next = nullptr;
}

template<class T_type>  lc::stack_list<T_type>::
stack_list(const stack_list<T_type>& origin)
{
    if (origin.top == nullptr)
    {
        top = nullptr;
        return;
    }

    list_elem<T_type> *iter1 = new list_elem<T_type>,
                       *iter2 = origin.top;
    top = iter1;
    iter1->value = iter2->value;
    iter2 = iter2->next;

    while(iter2 != nullptr)
    {
        iter1 = add_next(iter1, iter2->value);
        iter2 = iter2->next;
    }
    iter1->next = nullptr;
}

template<class T_type>  lc::stack_list<T_type>::
stack_list(stack_list<T_type>&& origin)
{
    top = origin.top;
    origin.top = nullptr;
}

template<class T_type>  lc::stack_list<T_type>::
~stack_list()
{
    while(top != nullptr)
    {
        auto iter = top->next;
        delete top;
        top = iter;
    }
}

template<class T_type>  lc::
stack_list<T_type>      lc::stack_list<T_type>::
copy()
{
    stack_list<T_type> result;

    if (top == nullptr)
        return std::move(result);
    //copying of first element
    auto i_from = top;
    result.top = new list_elem<T_type>;
    auto i_to  = result.top;
    i_to->value = i_from->value;

    //copying other
    for (i_from = i_from->next; i_from != nullptr; i_from = i_from->next)
        i_to = add_next(i_to, i_from->value);
    i_to->next = nullptr;

    return std::move(result);
}

template<class T_type>
T_type                  lc::stack_list<T_type>::
pop()
{
    assert(top != nullptr);
    T_type value = top->value;
    auto new_top = top->next;
    delete top;
    top = new_top;
    return std::move(value);
}

template<class T_type>  lc::
stack_list<T_type>&     lc::stack_list<T_type>::
push(const T_type& new_top_value)
{
    list_elem<T_type>* new_top = new list_elem<T_type>;
    new_top->value = new_top_value;
    new_top->next  = top;
    top = new_top;

    return *this;
}

template<class T_type>
bool 
    lc::stack_list<T_type>::
is_empty()
{
    return top == nullptr;
}

template<class T_type>
bool                    lc::stack_list<T_type>::
operator==(const stack_list<T_type>& arg)
{
    lc::
    list_elem<T_type> *iter1 = top, 
                      *iter2 = arg.top;
    while (iter1 != nullptr && iter2 != nullptr)
    {
        if (iter1->value != iter2->value)
            return false;
        iter1 = iter1->next;
        iter2 = iter2->next;   
    }
    return true;
}

template<class T_type>
bool                    lc::stack_list<T_type>::
operator!=(const stack_list<T_type>& arg)
{
    return !(*this == arg);
}

template<class T_type>  lc::
stack_list<T_type>&     lc::stack_list<T_type>::
operator=(const stack_list<T_type>& origin)
{
    while (top != nullptr)
    {
        auto temp_pointer = top;
        top = top->next;
        delete temp_pointer;
    }

    top = new list_elem<T_type>;
    auto i_to   = top;
    auto i_from = origin.top;
    
    i_to->value = i_from->value;
    
    i_from = i_from->next;
    while(i_from != nullptr)
    {
        i_to = add_next(i_to, i_from -> value);
        i_from = i_from->value;
    }
    i_to->next = nullptr;

    return *this;
}

template<class T_type>  lc::
stack_list<T_type>&     lc::stack_list<T_type>::
operator=(stack_list<T_type>&& origin)
{
    top = origin.top;
    origin.top = nullptr;
    return *this;
}

#endif
#define DBG_stack_list

#include"stack_list.cpp"
#include<iostream>


#define test(expression) \
[&]() -> uint64_t \
{ \
    std::cerr<<"checking: " \
             <<#expression \
             <<" ... "; \
    bool retval = 0; \
    retval = expression; \
    if (retval) \
        std::cerr<<"test passed\n"; \
    else \
        std::cerr<<"test failed on line: " \
                 <<__LINE__ << "\n"; \
    return static_cast<uint64_t>(!retval); \
}()



uint64_t 
test_stack_list_equal()
{
    using namespace lakreite_containers;
    stack_list<int64_t> a, b;
    a.top = new list_elem<int64_t>;
    b.top = new list_elem<int64_t>;
    list_elem<int64_t> *iter1 = a.top,
                       *iter2 = b.top;
    iter1->value = 0;
    iter2->value = iter1->value;
    iter1->next = new list_elem<int64_t>;
    iter2->next = new list_elem<int64_t>;
    iter1->next->next = nullptr;
    iter2->next->next = nullptr;
    iter1->next->value = 1;
    iter2->next->value = iter1->next->value;

    uint64_t result = 0;
    result += test(a == b);
    //assert(a==b);

    iter1->value = 1;
    result += test(a != b);
    //assert(a!=b);

    iter1->value = iter2->value;
    iter2->value = 1;
    result += test(a != b);
    //assert(a!=b);

    iter1->value = iter2->value;
    iter1->next->value = iter2->next->value + 1;
    result += test(a != b);
    //assert(a!=b);

    return result;
}

uint64_t 
test_stack_list_constructor()
{
    uint64_t result = 0;
    using namespace lakreite_containers;
    stack_list<int64_t> a;
    result += test(a.is_empty());
    //assert(a.is_empty());

    stack_list<int64_t> b(a);
    result += test(b.is_empty());
    //assert(b.is_empty());

    a.top = new list_elem<int64_t>;
    auto iter = a.top;
    iter->value = 1;
    iter->next = new list_elem<int64_t>;
    iter->next->value = 2;
    iter->next->next = nullptr;
    result += test(a == (stack_list<int64_t>{1 , 2}));
    result += test(b == stack_list<int64_t>{});
    //assert(a == (stack_list<int64_t>{1,2}));
    //assert(b == stack_list<int64_t>{});

    return result;
}

uint64_t
test_stack_list_copy()
{
    uint64_t result = 0;
    using namespace lakreite_containers;
    stack_list<int64_t> a{1, 2, 3, 4};
    stack_list<int64_t> a_copy(static_cast<stack_list<int64_t>&&>(a.copy()));
    result += test(a == a_copy);

    stack_list<int64_t> b{};
    stack_list<int64_t> b_copy(std::move(b.copy()));
    result += test(b == b_copy);

    return result;
}

uint64_t
test_stack_list_push()
{
    uint64_t result = 0;
    using namespace lakreite_containers;
    stack_list<int64_t> a;
    a.push(1);
    stack_list<int64_t> b{1};
    result += test(a == b);

    a.push(2);
    b.push(2);
    result += test(a == b);

    return result;
}

uint64_t
test_stack_list_pop()
{
    uint64_t result = 0;
    using namespace lakreite_containers;
    stack_list<int64_t> a;
    a.push(1).push(2).push(3);

    result += test(a.pop() == 3);
    result += test(a.pop() == 2);
    result += test(a.pop() == 1);

    return result;
}

int 
main()
{
    std::cerr<<"testing stack_list template:\n";

    uint64_t result =
        test_stack_list_equal()       
        +test_stack_list_constructor() 
        +test_stack_list_copy()        
        +test_stack_list_push()        
        +test_stack_list_pop();

    std::cerr<<"summary "
             << result
             << " errors\n";
}
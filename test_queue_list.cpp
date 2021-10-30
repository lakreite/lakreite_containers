#define DBG_queue_list

#include"queue_list.cpp"

#include<initializer_list>
#include<iostream>

#include"test_macro.hpp"

uint64_t
test_queue_list_constructor()
{
    uint64_t result = 0;
    using namespace lakreite_containers;
    std::cerr<<"testing constructor of queue without arguments\n\n"
             <<"prediction:\n"
             <<"            a.in_queue  is null\n"
             <<"            a.out_queue is null\n"
             <<"            a.amount    is zero\n";
    queue_list<uint64_t> a;
    result += test(a.in_queue  == nullptr);
    result += test(a.out_queue == nullptr);
    result += test(a.amount    == 0      );

    if (result != 0){
        std::cerr<<"TEST FAILED\n\n";
        return result;
    }
    std::cerr<<"TEST PASSED\n\n";

    std::cerr<<"testing constructor of queue with std::initializer_list\n\n"
             <<"  testing with empty list\n"
             <<"prediction:\n"
             <<"            b.in_queue  is null\n"
             <<"            b.out_queue is null\n"
             <<"            b.amount    is zero\n";
    queue_list<uint64_t> b{std::initializer_list<uint64_t>{}};
    result += test(b.in_queue  == nullptr);
    result += test(b.out_queue == nullptr);
    result += test(b.amount    == 0      );

    if (result != 0){
        std::cerr<<"TEST FAILED\n\n";
        return result;
    }
    std::cerr<<"TEST PASSED\n\n";

    std::cerr<<"  testing with list of 1, 2, 3\n"
             <<"prediction:\n"
             <<"            c.in_queue->       1\n"
             <<"            c.in_queue-> ->    2\n"
             <<"            c.in_queue-> -> -> 3\n";
    queue_list<uint64_t> c{1, 2, 3};
    result += test(c.in_queue        != nullptr);
    result += test(c.out_queue       != nullptr);
    result += test(c.in_queue->prev  == nullptr);
    result += test(c.in_queue->value == 1      );
    result += test(c.in_queue->next  != nullptr);

    result += test(c.in_queue->next->prev  == c.in_queue);
    result += test(c.in_queue->next->value == 2         );
    result += test(c.in_queue->next->next  != nullptr   );

    result += test(c.in_queue->next->next->prev  == c.in_queue->next);
    result += test(c.in_queue->next->next->value == 3               );
    result += test(c.in_queue->next->next->next  == nullptr         );
    result += test(c.in_queue->next->next        == c.out_queue     );

    result += test(c.amount == 3);

    if (result != 0){
        std::cerr<<"TEST FAILED\n\n";
        return result;
    }
    std::cerr<<"TEST PASSED\n\n";

    std::cerr<<"testing move constructor\n"
             <<"prediction:\n"
             <<"            d.in_queue->       1\n"
             <<"            d.in_queue-> ->    2\n"
             <<"            d.in_queue-> -> -> 3\n"
             <<"c is same\n";
    queue_list<uint64_t> d(c);
    result += test(d.in_queue  != c.in_queue );
    result += test(d.out_queue != c.out_queue);

    result += test(d.in_queue        != nullptr);
    result += test(d.out_queue       != nullptr);
    result += test(d.in_queue->prev  == nullptr);
    result += test(d.in_queue->value == 1      );
    result += test(d.in_queue->next  != nullptr);

    result += test(d.in_queue->next->prev  == d.in_queue);
    result += test(d.in_queue->next->value == 2         );
    result += test(d.in_queue->next->next  != nullptr   );

    result += test(d.in_queue->next->next->prev  == d.in_queue->next);
    result += test(d.in_queue->next->next->value == 3               );
    result += test(d.in_queue->next->next->next  == nullptr         );
    result += test(d.in_queue->next->next        == d.out_queue     );

    result += test(d.amount == 3);



    result += test(c.in_queue        != nullptr);
    result += test(c.out_queue       != nullptr);
    result += test(c.in_queue->prev  == nullptr);
    result += test(c.in_queue->value == 1      );
    result += test(c.in_queue->next  != nullptr);

    result += test(c.in_queue->next->prev  == c.in_queue);
    result += test(c.in_queue->next->value == 2         );
    result += test(c.in_queue->next->next  != nullptr   );

    result += test(c.in_queue->next->next->prev  == c.in_queue->next);
    result += test(c.in_queue->next->next->value == 3               );
    result += test(c.in_queue->next->next->next  == nullptr         );
    result += test(c.in_queue->next->next        == c.out_queue     );

    result += test(c.amount == 3);

    if (result != 0){
        std::cerr<<"TEST FAILED\n";
        return result;
    }
    std::cerr<<"TEST PASSED\n";
    
    std::cerr<<"testing move constructor\n"
             <<"  testing with copying data from c to d\n"
             <<"prediction:\n"
             <<"            d.in_queue  is null"
             <<"            d.out_queue is null"
             <<"            d.amount    is zero"
             <<"prediction:\n"
             <<"            e.in_queue->       1\n"
             <<"            e.in_queue-> ->    2\n"
             <<"            e.in_queue-> -> -> 3\n";
    queue_list<uint64_t> e(std::move(d));
    result += test(d.in_queue  == nullptr);
    result += test(d.out_queue == nullptr);
    result += test(d.amount    ==       0);


    result += test(e.in_queue  != c.in_queue );
    result += test(e.out_queue != c.out_queue);

    result += test(e.in_queue        != nullptr);
    result += test(e.out_queue       != nullptr);
    result += test(e.in_queue->prev  == nullptr);
    result += test(e.in_queue->value == 1      );
    result += test(e.in_queue->next  != nullptr);

    result += test(e.in_queue->next->prev  == e.in_queue);
    result += test(e.in_queue->next->value == 2         );
    result += test(e.in_queue->next->next  != nullptr   );

    result += test(e.in_queue->next->next->prev  == e.in_queue->next);
    result += test(e.in_queue->next->next->value == 3               );
    result += test(e.in_queue->next->next->next  == nullptr         );
    result += test(e.in_queue->next->next        == e.out_queue     );

    result += test(d.amount == 0);

    if (result != 0){
        std::cerr<<"TEST FAILED\n";
        return result;
    }
    std::cerr<<"TEST PASSED\n";

    return result;
}

uint64_t
test_queue_list_comparison()
{
    using namespace lakreite_containers;
    queue_list<uint64_t> a{1, 2, 3};
    uint64_t result = 0;
    result += test(a == a);

    queue_list<uint64_t> b{1, 2, 3, 4, 5, 6};
    result += test(b == b);
    result += test(a != b);
    result += test(b != a);

    queue_list<uint64_t> c;
    result += test(c == c);
    result += test(a != c);
    result += test(c != a);
    result += test(b != c);
    result += test(c != a);

    return result;
}

uint64_t
test_queue_list_push()
{
    using namespace lakreite_containers;
    queue_list<uint64_t> a;
    uint64_t result = 0;
    result += test(a.push(1)         == (queue_list<uint64_t>{1})         );
    result += test(a.push(2)         == (queue_list<uint64_t>{2, 1})      );
    result += test(a.push(3).push(4) == (queue_list<uint64_t>{4, 3, 2, 1}));

    return result;
}

uint64_t
test_queue_list_pop()
{
    using namespace lakreite_containers;
    queue_list<uint64_t> a{1, 2, 3, 4};
    uint64_t result = 0;
    result += test(a.pop() == 4);
    result += test(a == (queue_list<uint64_t>{1, 2, 3}));
    result += test(a.pop() == 3);
    result += test(a == (queue_list<uint64_t>{1, 2}));
    result += test(a.pop() == 2);
    result += test(a == (queue_list<uint64_t>{1}));
    result += test(a.pop() == 1);
    result += test(a == (queue_list<uint64_t>{}));
    
    return result;
}

uint64_t
test_queue_list_operator_at()
{
    using namespace lakreite_containers;
    uint64_t result = 0;
    queue_list<uint64_t> a{1, 2, 3, 4};
    result += test(*(a[1]) == 4);
    result += test(*(a[2]) == 3);
    result += test(*(a[3]) == 2);
    result += test(*(a[4]) == 1);
    result += test(a[5]    == nullptr);

    return result;
}

uint64_t
test_queue_list_operator_at_const()
{
    using namespace lakreite_containers;
    uint64_t result = 0;
    const queue_list<uint64_t> a{1, 2, 3, 4};
    result += test(*(a[1]) == 4);
    result += test(*(a[2]) == 3);
    result += test(*(a[3]) == 2);
    result += test(*(a[4]) == 1);
    result += test(a[5]    == nullptr);

    return result;
}

uint64_t
test_queue_list_operator_eq_copy()
{
    using namespace lakreite_containers;
    uint64_t result = 0;
    queue_list<uint64_t> a{1, 2, 3, 4};
    queue_list<uint64_t> b;
    result += test((b = a) == a);
    result += test(a       == b);

    queue_list<uint64_t> c;
    result += test((a = c) == c);
    result += test(a       == c);

    return result;
}

uint64_t
test_queue_list_operator_eq_move()
{
    using namespace lakreite_containers;
    uint64_t result = 0;
    queue_list<uint64_t> a{1, 2, 3, 4};
    queue_list<uint64_t> b;
    b = std::move(a);
    result += test(a == (queue_list<uint64_t>{}          ));
    result += test(b == (queue_list<uint64_t>{1, 2, 3, 4}));

    return result;
}

uint64_t
test_queue_list_push_front()
{
    using namespace lakreite_containers;
    uint64_t result = 0;
    queue_list<uint64_t> a{1, 2, 3, 4};
    result += test(a.push_front(5) == (queue_list<uint64_t>{1, 2, 3, 4, 5}   ));
    result += test(a.push_front(6) == (queue_list<uint64_t>{1, 2, 3, 4, 5, 6}));

    return result;
}

uint64_t
test_queue_list_pop_back()
{
    using namespace lakreite_containers;
    uint64_t result = 0;
    queue_list<uint64_t> a{1, 2, 3, 4, 5};
    result += test(a.pop_back() == 1);
    result += test(a.amount == 4);
    result += test(a == (queue_list<uint64_t>{2, 3, 4, 5}));
    result += test(a.pop_back() == 2);
    result += test(a.pop_back() == 3);
    result += test(a.pop_back() == 4);
    result += test(a.pop_back() == 5);
    result += test(a == (queue_list<uint64_t>{}));

    return result;
}

uint64_t
test_queue_list_pop_from()
{
    using namespace lakreite_containers;
    uint64_t result = 0;
    queue_list<uint64_t> a{1, 2, 3, 4, 5, 6};
    result += test(a.pop_from(2) == 5);
    result += test(a == (queue_list<uint64_t>{1, 2, 3, 4, 6}));
    result += test(a.pop_from(4) == 2);
    result += test(a == (queue_list<uint64_t>{1, 3, 4, 6}));
    result += test(a.pop_from(4) == 1);
    result += test(a == (queue_list<uint64_t>{3, 4, 6}));
    result += test(a.pop_from(1) == 6);
    result += test(a == (queue_list<uint64_t>{3, 4}));
    result += test(a.pop_from(2) == 3);
    result += test(a == (queue_list<uint64_t>{4}));
    result += test(a.pop_from(1) == 4);
    result += test(a == (queue_list<uint64_t>{}));

    return result;
}

uint64_t
test_queue_list_push_to()
{
    using namespace lakreite_containers;
    uint64_t result = 0;
    queue_list<uint64_t> a;
    a.push_to(8, 8);
    result += test(a == (queue_list<uint64_t>{8, 8, 8, 8, 8, 8, 8, 8}));
    a.push_to(1, 0);
    result += test(a == (queue_list<uint64_t>{8, 8, 8, 8, 8, 8, 8, 8, 0}));
    a.push_to(10, 10);
    result += test(a == (queue_list<uint64_t>{10, 8, 8, 8, 8, 8, 8, 8, 8, 0}));
    a.push_to(8, 7);
    result += test(a == (queue_list<uint64_t>{10, 8, 8, 7, 8, 8, 8, 8, 8, 8, 0}));

    return result;
}

auto main()->int
{
    uint64_t result = 0;
    result += test_queue_list_constructor();
    result += test_queue_list_comparison();
    result += test_queue_list_push();
    result += test_queue_list_pop();
    result += test_queue_list_operator_at();
    result += test_queue_list_operator_at_const();
    result += test_queue_list_operator_eq_copy();
    result += test_queue_list_operator_eq_move();
    result += test_queue_list_push_front();
    result += test_queue_list_pop_back();
    result += test_queue_list_pop_from();
    result += test_queue_list_push_to();
    std::cerr<<result<<"\n";
}
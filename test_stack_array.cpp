#define DBG_stack_array
#include<iostream>
#include"test_macro.hpp"
#include<cstdint>
#include"stack_array.hpp"
#include"stack_array.cpp"

uint64_t
test_constructor_default()
{
    uint64_t result = 0;
    using namespace lakreite_containers;
    std::cerr << "testing constructor default:\n"
              << "prediction:\n"
              << "              a.array != nullptr\n"
              << "              a.amount == 0\n"
              << "              a.capacity == 10\n";
    stack_array<uint64_t> a;
    result += test(a.array    != nullptr);
    result += test(a.amount   ==       0);
    result += test(a.capacity ==      10);

    if (result != 0)
    {
        std::cerr<<"TEST FAILED\n";
        return result;
    }
    std::cerr << "TEST PASSED\n";
    std::cerr << "testing counstructor copy:\n"
              << "prediction:\n"
              << "             b.array != nullptr\n"
              << "             b.amount == 0\n"
              << "             b.capacity == 10\n";
    stack_array<uint64_t> b(a);
    result += test(b.array != nullptr);
    result += test(b.amount == 0);
    result += test(b.capacity == 10);

    stack_array<uint64_t> c{1, 2, 3};
    result += test(c.array != nullptr);
    result += test(c.array[0] == 1);
    result += test(c.array[1] == 2);
    result += test(c.array[2] == 3);
    result += test(c.amount == 3);

    stack_array<uint64_t> d(c);
    result += test(d.array != nullptr);
    result += test(d[0] == c[0]);
    result += test(d[1] == c[1]);
    result += test(d[2] == c[2]);
    result += test(d.amount == c.amount);

    stack_array<uint64_t> e(std::move(d));
    result += test(e.array != nullptr);
    result += test(e[0] == c[0]);
    result += test(e[1] == c[1]);
    result += test(e[2] == c[2]);
    result += test(e.amount == c.amount);

    return result;
}

uint64_t
test_operator_eq()
{
    using namespace lakreite_containers;
    uint64_t result = 0;
    stack_array<uint64_t> a{1,2,3,4}, b{1,2,3,4}, c{1,2,3};
    result += test(a == b);
    result += test(b == a);
    result += test(a != c);
    result += test(c != a);
    
    return result;
}

uint64_t
test_operator_at()
{
    uint64_t result = 0;
    using namespace lakreite_containers;
    stack_array<uint64_t> a{1, 2, 3};
    result += test(a[0] == 3);
    result += test(a[1] == 2);
    result += test(a[2] == 1);

    return result;
}

uint64_t 
test_push_pop()
{
    uint64_t result = 0;
    using namespace lakreite_containers;
    stack_array<uint64_t> a{1, 2, 3}, b{1, 2, 3, 4}, c(a);
    a.push(4);
    result += test(a == b);
    result += test(b.pop() == 4);
    result += test(a != b);
    result += test(b == c);
    return result;
}

auto main() -> int
{
    uint64_t result = 0;
    result += test_constructor_default();
    result += test_operator_at();
    result += test_operator_eq();
    result += test_push_pop();
    std::cout<<result<<std::endl;
}

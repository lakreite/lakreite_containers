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
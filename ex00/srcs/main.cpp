#include <iostream>

#include "adder.h"

int main(int ac, char** av)
{
    if (ac != 3)
    {
        std::cerr << "Usage: ./adder uint1 uint2" << std::endl;
    }
    uint32_t a = static_cast<uint32_t>(atoi(av[1]));
    uint32_t b = static_cast<uint32_t>(atoi(av[1]));
    std::cout << adder(a, b) << std::endl;
}
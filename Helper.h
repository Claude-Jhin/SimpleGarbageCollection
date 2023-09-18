#pragma once
#include <iostream>

// Help function : assertion
inline void Check(bool Condition, const char* Message)
{
    if (!Condition)
    {
        std::cout << Message << std::endl;
        std::exit(1);
    }
}
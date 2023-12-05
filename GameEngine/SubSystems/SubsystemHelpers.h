#pragma once
#include <vcruntime_typeinfo.h>

struct SubsystemHelpers
{
    template <typename T>
    static int GetType()
    {
        return typeid(T).hash_code();
    }
};

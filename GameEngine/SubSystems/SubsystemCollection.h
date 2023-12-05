#pragma once
#include <map>
#include <vcruntime_typeinfo.h>

class SubSystem;

class SubsystemCollection
{
public:
    SubsystemCollection();
    ~SubsystemCollection();

    template<class T>
    T* GetSubSystem();

private:
    std::map<int, SubSystem*> subsystems;
};

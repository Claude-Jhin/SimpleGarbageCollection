#include "Object.h"

#include <iostream>

#include "VirtualMachine.h"

UObject::UObject(): Reachablity(false), Type(ObjectType::OBJ_INT), Next(nullptr), Value(0)
{
}

UObject::UObject(VirtualMachine* InVM, ObjectType InType): Reachablity(false), Type(InType), Value(0)
{
    if (InVM)
    {
        Next = InVM->FirstObject;
        InVM->FirstObject = this;
    }
}

UObject* UObject::NewObject(VirtualMachine* VM, ObjectType Type)
{
    if (VM->NumObjects == VM->MaxObjects)
    {
        VM->GC();
    }

    UObject* Obj = new UObject(VM, Type);
    VM->NumObjects++;
    return Obj;
}

void UObject::Mark()
{
    if (Reachablity) return;

    Reachablity = true;

    if (Type == ObjectType::OBJ_PAIR)
    {
        Head->Mark();
        Tail->Mark();
    }
}

void UObject::Print()
{
    switch (Type)
    {
    case ObjectType::OBJ_INT:
        {
            std::cout << Value;
            break;
        }
    case ObjectType::OBJ_PAIR:
        {
            std::cout << "(";
            Head->Print();
            std::cout << ", ";
            Tail->Print();
            std::cout << ")";
            break;
        }
    }
}

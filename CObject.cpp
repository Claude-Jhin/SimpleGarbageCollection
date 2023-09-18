#include "CObject.h"

#include <iostream>

#include "GCManager.h"

GCObject::GCObject(): Reachablity(false), Type(ObjectType::OBJ_INT), Next(nullptr), Value(0)
{
}

GCObject::GCObject(GCManager* InVM, ObjectType InType): Reachablity(false), Type(InType), Value(0)
{
    if (InVM)
    {
        Next = InVM->FirstObject;
        InVM->FirstObject = this;
    }
}

GCObject* GCObject::NewObject(GCManager* VM, ObjectType Type)
{
    if (VM->NumObjects == VM->MaxObjects)
    {
        VM->GC();
    }

    GCObject* Obj = new GCObject(VM, Type);
    VM->NumObjects++;
    return Obj;
}

void GCObject::Mark()
{
    if (Reachablity) return;

    Reachablity = true;

    if (Type == ObjectType::OBJ_PAIR)
    {
        Head->Mark();
        Tail->Mark();
    }
}

void GCObject::Print()
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

#include "GCManager.h"

#include "Helper.h"
#include "CObject.h"

GCManager::GCManager(): StackSize(0), FirstObject(nullptr), NumObjects(0), MaxObjects(INIT_OBJ_NUM_MAX)
{
}

GCManager::~GCManager()
{
}

GCManager* GCManager::NewVM()
{
    GCManager* vm = new GCManager;
    return vm;
}

void GCManager::DeleteVM(GCManager* VM)
{
    VM->StackSize = 0;
    VM->GC();
    delete VM;
}

void GCManager::Push(GCObject* Obj)
{
    Check(StackSize < STACK_MAX, "Stack overflow!");
    Stack.push_back(Obj);
    StackSize++;
}

GCObject* GCManager::Pop()
{
    Check(StackSize > 0, "Stack underflow!");
    GCObject* Obj = Stack.back();
    Stack.pop_back();
    StackSize--;
    return Obj;
}

void GCManager::PushInt(int Val)
{
    GCObject* Obj = GCObject::NewObject(this, ObjectType::OBJ_INT);
    Obj->Value = Val;
    Push(Obj);
}

GCObject* GCManager::PushPair()
{
    GCObject* Obj = GCObject::NewObject(this, ObjectType::OBJ_PAIR);
    Obj->Tail = Pop();
    Obj->Head = Pop();
    Push(Obj);
    return Obj;
}

void GCManager::Mark()
{
    for (int i = 0; i < StackSize; i++)
    {
        Stack[i]->Mark();
    }
}

void GCManager::Sweep()
{
    GCObject** object = &FirstObject;
    while (*object)
    {
        if (!(*object)->Reachablity)
        {
            GCObject* unreached = *object;
            *object = unreached->Next;

            delete unreached;
            NumObjects--;
        }
        else
        {
            (*object)->Reachablity = false;
            object = &(*object)->Next;
        }
    }
}

void GCManager::GC()
{
    int NumCache = NumObjects;
    Mark();
    Sweep();
    MaxObjects = (NumObjects == 0) ? INIT_OBJ_NUM_MAX : NumObjects * 2;
    std::cout << "Collected " << NumCache - NumObjects << " objects, " << NumObjects << " remaining." << std::endl;
}

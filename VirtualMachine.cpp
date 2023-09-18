#include "VirtualMachine.h"

#include "Helper.h"
#include "Object.h"

VirtualMachine::VirtualMachine(): StackSize(0), FirstObject(nullptr), NumObjects(0), MaxObjects(INIT_OBJ_NUM_MAX)
{
}

VirtualMachine::~VirtualMachine()
{
}

VirtualMachine* VirtualMachine::NewVM()
{
    VirtualMachine* vm = new VirtualMachine;
    return vm;
}

void VirtualMachine::DeleteVM(VirtualMachine* VM)
{
    VM->StackSize = 0;
    VM->GC();
    delete VM;
}

void VirtualMachine::Push(UObject* Obj)
{
    Check(StackSize < STACK_MAX, "Stack overflow!");
    Stack.push_back(Obj);
    StackSize++;
}

UObject* VirtualMachine::Pop()
{
    Check(StackSize > 0, "Stack underflow!");
    UObject* Obj = Stack.back();
    Stack.pop_back();
    StackSize--;
    return Obj;
}

void VirtualMachine::PushInt(int Val)
{
    UObject* Obj = UObject::NewObject(this, ObjectType::OBJ_INT);
    Obj->Value = Val;
    Push(Obj);
}

UObject* VirtualMachine::PushPair()
{
    UObject* Obj = UObject::NewObject(this, ObjectType::OBJ_PAIR);
    Obj->Tail = Pop();
    Obj->Head = Pop();
    Push(Obj);
    return Obj;
}

void VirtualMachine::Mark()
{
    for (int i = 0; i < StackSize; i++)
    {
        Stack[i]->Mark();
    }
}

void VirtualMachine::Sweep()
{
    UObject** object = &FirstObject;
    while (*object)
    {
        if (!(*object)->Reachablity)
        {
            UObject* unreached = *object;
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

void VirtualMachine::GC()
{
    int NumCache = NumObjects;
    Mark();
    Sweep();
    MaxObjects = (NumObjects == 0) ? INIT_OBJ_NUM_MAX : NumObjects * 2;
    std::cout << "Collected " << NumCache - NumObjects << " objects, " << NumObjects << " remaining." << std::endl;
}

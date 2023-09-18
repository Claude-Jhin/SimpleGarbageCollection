#pragma once

#define STACK_MAX 256
#define INIT_OBJ_NUM_MAX 8
#include <vector>

class UObject;

class VirtualMachine
{
public:
    VirtualMachine();

    ~VirtualMachine();

    static VirtualMachine* NewVM();

    static void DeleteVM(VirtualMachine* VM);

    void Push(UObject* Obj);

    UObject* Pop();
    
    void PushInt(int Val);

    UObject* PushPair();

    void Mark();
    
    void Sweep();
    
    void GC();

    std::vector<UObject*> Stack;
    
    int StackSize;

    // The first object in the linked list of all objects on the heap.
    UObject* FirstObject;

    // The total number of currently allocated objects.
    int NumObjects;

    // The number of objects required to trigger a GC.
    int MaxObjects;
};


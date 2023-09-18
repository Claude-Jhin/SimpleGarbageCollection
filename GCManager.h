#pragma once

#define STACK_MAX 256
#define INIT_OBJ_NUM_MAX 8
#include <vector>

class GCObject;

class GCManager
{
public:
    GCManager();

    ~GCManager();

    static GCManager* NewVM();

    static void DeleteVM(GCManager* VM);

    void Push(GCObject* Obj);

    GCObject* Pop();
    
    void PushInt(int Val);

    GCObject* PushPair();

    void Mark();
    
    void Sweep();
    
    void GC();

    std::vector<GCObject*> Stack;
    
    int StackSize;

    // The first object in the linked list of all objects on the heap.
    GCObject* FirstObject;

    // The total number of currently allocated objects.
    int NumObjects;

    // The number of objects required to trigger a GC.
    int MaxObjects;
};


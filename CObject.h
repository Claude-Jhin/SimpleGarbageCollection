#pragma once

class GCManager;

enum class ObjectType
{
    OBJ_INT,
    OBJ_PAIR
};

/**
 * \brief Base type which support GC, like UObject in unreal engine
 */
class GCObject
{
public:
    GCObject();

    GCObject(GCManager* InVM, ObjectType InType);

    ~GCObject()
    {
    }

    static GCObject* NewObject(GCManager* VM, ObjectType Type);

    void Mark();

    bool Reachablity;

    ObjectType Type;

    // The next object in the linked list of heap allocated objects.
    GCObject* Next;

    // Data
    union
    {
        // OBJ_INT
        int Value;

        // OBJ_PAIR
        struct
        {
            GCObject* Head;
            GCObject* Tail;
        };
    };

    void Print();
};

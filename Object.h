#pragma once

class VirtualMachine;

enum class ObjectType
{
    OBJ_INT,
    OBJ_PAIR
};

/**
 * \brief Base type which support GC, like UObject in unreal engine
 */
class UObject
{
public:
    UObject();

    UObject(VirtualMachine* InVM, ObjectType InType);

    ~UObject()
    {
    }

    static UObject* NewObject(VirtualMachine* VM, ObjectType Type);

    void Mark();

    bool Reachablity;

    ObjectType Type;

    // The next object in the linked list of heap allocated objects.
    UObject* Next;

    // Data
    union
    {
        // OBJ_INT
        int Value;

        // OBJ_PAIR
        struct
        {
            UObject* Head;
            UObject* Tail;
        };
    };

    void Print();
};

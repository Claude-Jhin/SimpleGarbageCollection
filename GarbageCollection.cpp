#include <iostream>

#include "Helper.h"
#include "Object.h"
#include "VirtualMachine.h"

void test1()
{
    std::cout << "Test 1: Objects on stack are preserved." << std::endl;
    VirtualMachine* VM = VirtualMachine::NewVM();
    VM->PushInt(1);
    VM->PushInt(2);
    VM->GC();
    Check(VM->NumObjects == 2, "Should have preserved objects.");
    VirtualMachine::DeleteVM(VM);
}

void test2()
{
    std::cout << "Test 2: Unreached objects are collected." << std::endl;
    VirtualMachine* VM = VirtualMachine::NewVM();
    VM->PushInt(1);
    VM->PushInt(2);
    VM->Pop();
    VM->Pop();
    VM->GC();
    Check(VM->NumObjects == 0, "Should have collected objects.");
    VirtualMachine::DeleteVM(VM);
}

void test3()
{
    std::cout << "Test 3: Reach nested objects." << std::endl;
    VirtualMachine* VM = VirtualMachine::NewVM();
    VM->PushInt(1);
    VM->PushInt(2);
    VM->PushPair();
    VM->PushInt(3);
    VM->PushInt(4);
    VM->PushPair();
    VM->PushPair();

    VM->GC();
    Check(VM->NumObjects == 7, "Should have reached objects.");
    VirtualMachine::DeleteVM(VM);
}

void test4()
{
    std::cout << "Test 4: Handle cycles." << std::endl;
    VirtualMachine* VM = VirtualMachine::NewVM();

    VM->PushInt(1);
    VM->PushInt(2);
    UObject* a = VM->PushPair();
    a->Print();
    VM->PushInt(3);
    VM->PushInt(4);
    UObject* b = VM->PushPair();
    b->Print();
    a->Tail = b;
    a->Print();
    b->Tail = a;
    // Can't print because of Cycle Reference
    // objectPrint(b);
    VM->GC();
    Check(VM->NumObjects == 4, "Should have collected objects.");
    VirtualMachine::DeleteVM(VM);
}

void perfTest()
{
    std::cout << "Performance Test." << std::endl;
    VirtualMachine* VM = VirtualMachine::NewVM();

    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            VM->PushInt(i);
        }

        for (int k = 0; k < 20; k++)
        {
            VM->Pop();
        }
    }
    VirtualMachine::DeleteVM(VM);
}

int main()
{
    // test1();
    // test2();
    // test3();
    test4();
    // perfTest();

    return 0;
}

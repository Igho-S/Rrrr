#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "Sourse.h"
#include "RBTree1.h"
#include <random>
#pragma warning(disable : 4996)

// #define BSTREE_EXCEPTION_BAD_INDEX "\nException: key not found.\n"
#ifndef BSTREE_EXCEPTION_BAD_INDEX
#define BSTREE_EXCEPTION_BAD_INDEX "\nException: key not found.\n"
#endif
// #define BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE "\nException: iterator not set.\n"
#ifndef BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE
#define BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE "\nException: iterator not set.\n"
#endif

// #define BSTREE_EXCEPTION_COPY_NULLPTR "\nException: root = nullptr.\n"
#ifndef BSTREE_EXCEPTION_COPY_NULLPTR
#define BSTREE_EXCEPTION_COPY_NULLPTR "\nException: root = nullptr.\n"
#endif

using namespace std;
typedef int Tk;
typedef int Td;
typedef unsigned long long INT_64;

void sRand();
INT_64 LineRand();
void test_rand(int n);
void test_ord(int n);

void PrintMenu()
{
    printf("\n\n\t----------------------------------------MENU----------------------------------------------\n");
    printf("\t1) Constructor\n");
    printf("\t2) Copy Constructor\n");
    printf("\t3) Destructor\n");
    printf("\t4) Query tree size\n");
    printf("\t5) Clear tree\n");
    printf("\t6) Check if tree is empty\n");
    printf("\t7) Read data by key\n");
    printf("\t8) Write data by key\n");
    printf("\t9) Include data with given key\n");
    printf("\t10) Remove data with given key\n");
    printf("\t12) Request forward iterator begin()\n");
    printf("\t13) Request reverse iterator rbegin()\n");
    printf("\t14) Request 'unset' forward iterator end()\n");
    printf("\t15) Request 'unset' reverse iterator rend()\n");
    printf("\t16) Additional operation: determine the ordinal number for an element with a given key\n");
    printf("\t------------------------------------ITERATORS---------------------------------------------\n");
    printf("\t17) Read access operation to the current value *\n");
    printf("\t18) Write access operation to the current value *\n");
    printf("\t19) Increment operation to move to the next (to the previous for reverse iterator) value in the tree ++\n");
    printf("\t20) Decrement operation to move to the previous (to the next for reverse iterator) value in the tree --\n");
    printf("\t21) Check equality of identical iterators ==\n");
    printf("\t22) Check inequality of identical iterators !=\n");
    printf("\t-------------------------------------DEBUGGING---------------------------------------------\n");
    printf("\t23) Request the number of tree elements viewed by the previous operation\n");
    printf("\t24) Display the tree on the screen\n");
    printf("\t25) Fill the tree with standard keys\n");
    printf("\t26) Testing: Fill n random keys, deletion, insertion, search\n");
    printf("\t27) Testing (degenerate): Fill n keys, deletion, insertion, search\n");
}

int MenuUserInput()
{
    int i = 0;
    printf("\nSelect a menu option: ");
    scanf("%d", &i);
    return i;
}

int InputValue()
{
    int t;
    printf("Enter a value: ");
    std::cin >> t;
    return t;
}

int InputIndex()
{
    int t;
    printf("Enter the key number: ");
    std::cin >> t;
    return t;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int selectedItem = 0;
    BST<Tk, Td> *UBSTree = new RBTree<Tk, Td>();
    BST<Tk, Td> *UBSTree2 = nullptr;
    BST<Tk, Td>::BST_Iterator iter = UBSTree->begin();
    BST<Tk, Td>::BST_R_Iterator r_iter = UBSTree->rbegin();
    int standardKeys[7] = {60, 20, 70, 10, 40, 30, 50};
    bool useReverseIter = false;
    srand(time(0));

    while (true)
    {
        PrintMenu();
        selectedItem = MenuUserInput();
        if (selectedItem != 23 && UBSTree != nullptr)
            UBSTree->ClearCounter();
        try
        {
            switch (selectedItem)
            {
            case 1:
            {
                delete UBSTree;
                UBSTree = new RBTree<Tk, Td>();
                iter = UBSTree->begin();
                r_iter = UBSTree->rbegin();
                break;
            }
            case 2:
            {
                if (UBSTree2 != nullptr)
                    delete UBSTree2;
                // UBSTree2 = new RBTree<Tk, Td>(*UBSTree);//changed
                UBSTree2 = new RBTree<Tk, Td>(*UBSTree);

                break;
            }
            case 3:
                delete UBSTree;
                UBSTree = nullptr;
                break;
            case 4:
                printf("%li\n", UBSTree->GetSizeT()); // use longint so the sizes match
                break;
            case 5:
                UBSTree->ClearTree();
                break;
            case 6:
                printf(UBSTree->IsEmpty() ? "true\n" : "false\n");
                break;
            case 7:
                try
                {
                    printf("\n%i\n", UBSTree->FindByKey(InputIndex()));
                }
                catch (int)
                {
                    printf(BSTREE_EXCEPTION_BAD_INDEX);
                }
                break;
            case 8:
                printf(UBSTree->Replace(InputValue(), InputIndex()) ? "true\n" : "false\n");
                break;
            case 9:
                printf(UBSTree->InsertByKey(InputValue(), InputIndex()) ? "true\n" : "false\n");
                break;
            case 10:
                printf(UBSTree->DeleteByKey(InputIndex()) ? "true\n" : "false\n");
                break;
            case 12:
                iter = UBSTree->begin();
                useReverseIter = false;
                break;
            case 13:
                r_iter = UBSTree->rbegin();
                useReverseIter = true;
                break;
            case 14:
                iter = UBSTree->end();
                useReverseIter = false;
                break;
            case 15:
                r_iter = UBSTree->rend();
                useReverseIter = true;
                break;
            case 16:
                try
                {
                    printf("%li\n", UBSTree->FindOrder(InputIndex())); // likewise here longint
                }
                catch (int)
                {
                    printf("Exception: key not found.\n");
                }
                break;
            case 17:
                try
                {
                    // if ((useReverseIter ? *r_iter : *iter) == NULL)
                    if ((useReverseIter ? r_iter == UBSTree->rend() : iter == UBSTree->end()))
                        printf("\nnullptr\n");
                    else
                        printf("\n%i\n", useReverseIter ? *r_iter : *iter);
                }
                catch (const char *msg)
                {
                    printf("%s", msg);
                }
                break;
            case 18:
                try
                {
                    if (useReverseIter)
                    {
                        *r_iter = InputValue();
                    }
                    else
                    {
                        *iter = InputValue();
                    }
                }
                catch (const char *msg)
                {
                    printf("%s", msg);
                }
                break;
            case 19:
                try
                {
                    if (useReverseIter)
                        ++r_iter;
                    else
                        ++iter;
                    printf("%i", useReverseIter);
                }
                catch (const char *msg)
                {
                    printf("%s", msg);
                }
                break;
            case 20:
                try
                {
                    if (useReverseIter)
                        --r_iter;
                    else
                        --iter;
                    printf("%i", useReverseIter);
                }
                catch (const char *msg)
                {
                    printf("%s", msg);
                }
                break;
            case 21:
                if (useReverseIter)
                {
                    RBTree<Tk, Td>::BST_R_Iterator iterCompare = UBSTree->rend();
                    printf(r_iter == iterCompare ? "true\n" : "false\n");
                }
                else
                {
                    RBTree<Tk, Td>::BST_Iterator iterCompare = UBSTree->end();
                    printf(iter == iterCompare ? "true\n" : "false\n");
                }
                break;
            case 22:
                if (useReverseIter)
                {
                    RBTree<Tk, Td>::BST_R_Iterator iterCompare = UBSTree->rend();
                    printf(r_iter != iterCompare ? "true\n" : "false\n");
                }
                else
                {
                    RBTree<Tk, Td>::BST_Iterator iterCompare = UBSTree->end();
                    printf(iter != iterCompare ? "true\n" : "false\n");
                }
                break;
            case 23:
                printf("%li\n", UBSTree->GetCounter()); // and here
                break;
            case 24:
                printf("\n//-------Tree 1---------//\n");
                printf("\n\n");
                UBSTree->Print();
                printf("\n//-------Tree 2---------//\n");
                if (UBSTree2 != nullptr)
                    UBSTree2->Print();
                break;
            case 25:
                UBSTree->ClearTree();
                for (int i = 0; i < 7; i++)
                {
                    UBSTree->InsertByKey(i, standardKeys[i]);
                }
                break;
            case 26:
                test_rand(InputValue());
                break;
            case 27:
                test_ord(InputValue());
                break;
            default:
                return 0;
            }
        }
        catch (const char *msg)
        {
            printf("%s", msg);
        }
    }
}

void test_rand(int n)
{
    RBTree<int, int> t;
    sRand();
    int m = 0;
    clock_t start;
    start = clock();
    for (int i = 0; i < n; i++)
    {
        INT_64 r = LineRand();
        t.InsertByKey((int)r, (int)(r >> 32));
    }
    for (int i = 0; i < 1000000; i++)
    {
        INT_64 r = LineRand();
        switch (r % 3)
        {
        case 0:
            t.InsertByKey((int)r, (int)(r >> 32));
            break;
        case 1:
            t.DeleteByKey((int)r);
            break;
        case 2:
            m += t.FindByKey((int)r);
            break;
        }
    }
    printf("time = %f,  m = %d\n", (double)(clock() - start) / CLOCKS_PER_SEC, m);
}

void test_ord(int n)
{
    RBTree<int, int> t;
    sRand();
    int m = 0;
    clock_t start;
    start = clock();
    for (int i = 0; i < n; i++)
    {
        t.InsertByKey(i, -i);
    }
    for (int i = 0; i < 1000000; i++)
    {
        INT_64 r = LineRand();
        switch (r % 3)
        {
        case 0:
            t.InsertByKey((int)r, (int)(r >> 32));
            break;
        case 1:
            t.DeleteByKey((int)r);
            break;
        case 2:
            m += t.FindByKey((int)r);
            break;
        }
    }
    printf("time = %f,  m = %d\n", (double)(clock() - start) / CLOCKS_PER_SEC, m);
}

void sRand()
{
    srand((unsigned)time(NULL));
}

INT_64 LineRand()
{
    return ((INT_64)rand() << 32) | rand();
}

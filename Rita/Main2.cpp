#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "Sourse.h"
#include "RBTree1.h"
#pragma warning(disable : 4996)

// #define BSTREE_EXCEPTION_BAD_INDEX "\nИсключение: ключ не найден.\n"
#ifndef BSTREE_EXCEPTION_BAD_INDEX
#define BSTREE_EXCEPTION_BAD_INDEX "\nИсключение: ключ не найден.\n"
#endif
// #define BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE "\nИсключение: итератор не установлен.\n"
#ifndef BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE
#define BSTREE_EXCEPTION_ITERATOR_OUT_OF_TREE "\nИсключение: итератор не установлен.\n"
#endif

// #define BSTREE_EXCEPTION_COPY_NULLPTR "\nИсключение: root = nullptr.\n"
#ifndef BSTREE_EXCEPTION_COPY_NULLPTR
#define BSTREE_EXCEPTION_COPY_NULLPTR "\nИсключение: root = nullptr.\n"
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
    printf("\n\n\t-----------------------------------------МЕНЮ----------------------------------------------\n");
    printf("\t1) Конструктор\n");
    printf("\t2) Конструктор копирования\n");
    printf("\t3) Деструктор\n");
    printf("\t4) Опрос размера дерева\n");
    printf("\t5) Очистка дерева\n");
    printf("\t6) Проверка дерева на пустоту\n");
    printf("\t7) Чтение данных по ключу\n");
    printf("\t8) Запись данных по ключу\n");
    printf("\t9) Включение данных с заданным ключом\n");
    printf("\t10) Удаление данных с заданным ключом\n");
    printf("\t12) Запрос прямого итератора begin()\n");
    printf("\t13) Запрос обратного итератора rbegin()\n");
    printf("\t14) Запрос «неустановленного» прямого итератора end()\n");
    printf("\t15) Запрос «неустановленного» обратного итератора rend()\n");
    printf("\t16) Дополнительная операция: определение порядкового номера для элемента с заданным ключом\n");
    printf("\t------------------------------------ИТЕРАТОРЫ---------------------------------------------\n");
    printf("\t17) Операция доступа по чтению к текущему значению *\n");
    printf("\t18) Операция доступа по записи к текущему значению *\n");
    printf("\t19) Операция инкремента для перехода к следующему (к предыдущему для обратного итератора) значению в дереве++\n");
    printf("\t20) Операция декремента для перехода к предыдущему (к следующему для обратного итератора) значению в дереве--\n");
    printf("\t21) Проверка равенства однотипных итераторов ==\n");
    printf("\t22) Проверка неравенства однотипных итераторов !=\n");
    printf("\t-------------------------------------ОТЛАДКА----------------------------------------------\n");
    printf("\t23) Запрос числа элементов дерева, просмотренных предыдущей операцией\n");
    printf("\t24) Вывод на экран дерева\n");
    printf("\t25) Заполнить дерево стандартными ключами\n");
    printf("\t26) Тестирование: Заполнить n случайных ключей, удаление, вставка, поиск\n");
    printf("\t27) Тестирование (вырожденное): Заполнить n ключей, удаление, вставка, поиск\n");
}

int MenuUserInput()
{
    int i = 0;
    printf("\nВыберите вариант меню: ");
    scanf("%d", &i);
    return i;
}

int InputValue()
{
    int t;
    printf("Введите значение: ");
    std::cin >> t;
    return t;
}

int InputIndex()
{
    int t;
    printf("Введите номер ключа: ");
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
                printf("%i\n", UBSTree->GetSizeT());
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
                    printf("%i\n", UBSTree->FindOrder(InputIndex()));
                }
                catch (int)
                {
                    printf("Исключение: ключ не найден.\n");
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
                printf("%i\n", UBSTree->GetCounter());
                break;
            case 24:
                printf("\n//-------Дерево 1---------//\n");
                printf("\n\n");
                UBSTree->Print();
                printf("\n//-------Дерево 2---------//\n");
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

#include <iostream>
#include <iomanip>
#include <new>
#include "lists.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Константи програми (Лабораторна робота 2.5, Варіант 3)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const int  FIRST_LIST_SIZE               = 6;   // Кількість елементів 1-го списку
const char SOURCE_CHARS[FIRST_LIST_SIZE] = {    // Вихідні символьні значення
    'A', 'B', 'C', 'D', 'E', 'F'
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Закрита підпрограма 1: формування елемента першого списку
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Включення нового елемента до початку односпрямованого списку
bool insertSinglyFront(SinglyNode*& pHead, char cValue)
{
    SinglyNode* pNewNode = new (std::nothrow) SinglyNode;
    if (pNewNode == nullptr)
    {
        std::cout << "  [OVERFLOW] Memory allocation failed while inserting '"
                  << cValue << "' into singly linked list.\n";
        return false;
    }

    pNewNode->cData = cValue;
    pNewNode->pNext = pHead;
    pHead           = pNewNode;

    return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Закрита підпрограма 2: формування другого списку
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Включення нового елемента в кінець двоспрямованого списку
bool appendDoublyBack(DoublyNode*& pHead, DoublyNode*& pTail, char cValue)
{
    DoublyNode* pNewNode = new (std::nothrow) DoublyNode;
    if (pNewNode == nullptr)
    {
        std::cout << "  [OVERFLOW] Memory allocation failed while appending '"
                  << cValue << "' into doubly linked list.\n";
        return false;
    }

    pNewNode->cData = cValue;
    pNewNode->pNext = nullptr;
    pNewNode->pPrev = nullptr;

    if (pHead == nullptr)
    {
        pHead = pNewNode;
        pTail = pNewNode;
    }
    else
    {
        DoublyNode* pLast = pHead;
        while (!isNextNull(pLast))
        {
            pLast = pLast->pNext;
        }

        pLast->pNext    = pNewNode;
        pNewNode->pPrev = pLast;
        pTail           = pNewNode;
    }

    return true;
}

// Перетворення односпрямованого списку у двоспрямований (з використанням inline-функції)
bool convertSinglyToDoubly(const SinglyNode* pSinglyHead,
                           DoublyNode*&      pDoublyHead,
                           DoublyNode*&      pDoublyTail)
{
    if (pSinglyHead == nullptr)
    {
        std::cout << "  [EMPTY]    Source singly linked list is empty.\n";
        return true;
    }

    const SinglyNode* pCurrent = pSinglyHead;
    int               nIndex   = 0;

    while (pCurrent != nullptr)
    {
        if (!appendDoublyBack(pDoublyHead, pDoublyTail, pCurrent->cData))
        {
            return false;
        }

        std::cout << "  [APPEND]   Node #" << std::right << std::setw(2) << (nIndex + 1)
                  << " | value: '" << pCurrent->cData << "'"
                  << " | pNext == nullptr: "
                  << (isNextNull(pCurrent) ? "true" : "false") << "\n";

        if (isNextNull(pCurrent))
        {
            break;
        }

        pCurrent = pCurrent->pNext;
        ++nIndex;
    }

    return true;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Допоміжні закриті підпрограми виведення та звільнення пам'яті
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Виведення таблиці та ланцюжка односпрямованого списку
void printSinglyList(const SinglyNode* pHead)
{
    if (pHead == nullptr)
    {
        std::cout << "  [EMPTY]    Singly linked list is empty.\n";
        return;
    }

    std::cout << "  +-------+-------+------------+------------------+\n";
    std::cout << "  | Index | Value | ASCII Code | pNext == nullptr |\n";
    std::cout << "  +-------+-------+------------+------------------+\n";

    const SinglyNode* pCurrent = pHead;
    int               nIndex   = 0;

    while (pCurrent != nullptr)
    {
        std::cout << "  | " << std::right << std::setw(5) << nIndex
                  << " |   '" << pCurrent->cData << "' | "
                  << std::right << std::setw(10) << static_cast<int>(pCurrent->cData)
                  << " | " << std::left << std::setw(16)
                  << (isNextNull(pCurrent) ? "true" : "false") << " |\n";

        if (isNextNull(pCurrent))
        {
            break;
        }

        pCurrent = pCurrent->pNext;
        ++nIndex;
    }

    std::cout << std::right;
    std::cout << "  +-------+-------+------------+------------------+\n";
    std::cout << "  Chain (Head -> Tail): ";

    pCurrent = pHead;
    while (pCurrent != nullptr)
    {
        std::cout << "[" << pCurrent->cData << "]";
        std::cout << (isNextNull(pCurrent) ? " -> nullptr\n" : " -> ");

        if (isNextNull(pCurrent))
        {
            break;
        }

        pCurrent = pCurrent->pNext;
    }
}

// Виведення таблиці та ланцюжків двоспрямованого списку
void printDoublyList(const DoublyNode* pHead, const DoublyNode* pTail)
{
    if (pHead == nullptr)
    {
        std::cout << "  [EMPTY]    Doubly linked list is empty.\n";
        return;
    }

    std::cout << "  +-------+-------+------------+-------+------------------+\n";
    std::cout << "  | Index | Value | ASCII Code | pPrev | pNext == nullptr |\n";
    std::cout << "  +-------+-------+------------+-------+------------------+\n";

    const DoublyNode* pCurrent = pHead;
    int               nIndex   = 0;

    while (pCurrent != nullptr)
    {
        std::cout << "  | " << std::right << std::setw(5) << nIndex
                  << " |   '" << pCurrent->cData << "' | "
                  << std::right << std::setw(10) << static_cast<int>(pCurrent->cData)
                  << " | " << std::left << std::setw(5)
                  << (pCurrent->pPrev == nullptr ? "null" : "set")
                  << " | " << std::left << std::setw(16)
                  << (isNextNull(pCurrent) ? "true" : "false") << " |\n";

        if (isNextNull(pCurrent))
        {
            break;
        }

        pCurrent = pCurrent->pNext;
        ++nIndex;
    }

    std::cout << std::right;
    std::cout << "  +-------+-------+------------+-------+------------------+\n";
    std::cout << "  Forward  (Head -> Tail): nullptr <- ";

    pCurrent = pHead;
    while (pCurrent != nullptr)
    {
        std::cout << "[" << pCurrent->cData << "]";
        std::cout << (isNextNull(pCurrent) ? " -> nullptr\n" : " <-> ");

        if (isNextNull(pCurrent))
        {
            break;
        }

        pCurrent = pCurrent->pNext;
    }

    std::cout << "  Backward (Tail -> Head): nullptr <- ";

    const DoublyNode* pBack = pTail;
    while (pBack != nullptr)
    {
        std::cout << "[" << pBack->cData << "]";
        std::cout << (pBack->pPrev == nullptr ? " -> nullptr\n" : " <-> ");
        pBack = pBack->pPrev;
    }
}

// Підрахунок кількості елементів односпрямованого списку
int countSinglyNodes(const SinglyNode* pHead)
{
    int               nCount   = 0;
    const SinglyNode* pCurrent = pHead;

    while (pCurrent != nullptr)
    {
        ++nCount;
        if (isNextNull(pCurrent))
        {
            break;
        }
        pCurrent = pCurrent->pNext;
    }

    return nCount;
}

// Підрахунок кількості елементів двоспрямованого списку
int countDoublyNodes(const DoublyNode* pHead)
{
    int               nCount   = 0;
    const DoublyNode* pCurrent = pHead;

    while (pCurrent != nullptr)
    {
        ++nCount;
        if (isNextNull(pCurrent))
        {
            break;
        }
        pCurrent = pCurrent->pNext;
    }

    return nCount;
}

// Звільнення динамічної пам'яті односпрямованого списку
void clearSinglyList(SinglyNode*& pHead)
{
    while (pHead != nullptr)
    {
        SinglyNode* pTemp = pHead;
        pHead             = pHead->pNext;
        delete pTemp;
        pTemp             = nullptr;
    }
}

// Звільнення динамічної пам'яті двоспрямованого списку
void clearDoublyList(DoublyNode*& pHead, DoublyNode*& pTail)
{
    while (pHead != nullptr)
    {
        DoublyNode* pTemp = pHead;
        pHead             = pHead->pNext;
        delete pTemp;
        pTemp             = nullptr;
    }

    pTail = nullptr;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Сценарій виконання підзадач
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void executeListOperations()
{
    SinglyNode* pSinglyHead = nullptr;   // Голова 1-го (односпрямованого) списку
    DoublyNode* pDoublyHead = nullptr;   // Голова 2-го (двоспрямованого) списку
    DoublyNode* pDoublyTail = nullptr;   // Хвіст 2-го (двоспрямованого) списку

    std::cout << "-----------------------------------------------------------------------------------------------\n";
    std::cout << "                           Part 1: Source Array (" << FIRST_LIST_SIZE << " char elements)\n";
    std::cout << "-----------------------------------------------------------------------------------------------\n\n";
    std::cout << "  Elements: ";
    for (int i = 0; i < FIRST_LIST_SIZE; ++i)
    {
        std::cout << "'" << SOURCE_CHARS[i] << "'"
                  << (i + 1 < FIRST_LIST_SIZE ? ", " : "\n\n");
    }

    std::cout << "-----------------------------------------------------------------------------------------------\n";
    std::cout << "                  Part 2: Building First List (Singly Linked, Insert at Front)\n";
    std::cout << "-----------------------------------------------------------------------------------------------\n\n";
    bool bFirstOk = true;
    for (int i = 0; i < FIRST_LIST_SIZE; ++i)
    {
        if (insertSinglyFront(pSinglyHead, SOURCE_CHARS[i]))
        {
            std::cout << "  [INSERT]   Step #" << std::setw(2) << (i + 1)
                      << " | value: '" << SOURCE_CHARS[i] << "'"
                      << " | new head pNext == nullptr: "
                      << (isNextNull(pSinglyHead) ? "true" : "false") << "\n";
        }
        else
        {
            bFirstOk = false;
            break;
        }
    }

    std::cout << "\n  Resulting First List:\n";
    printSinglyList(pSinglyHead);
    std::cout << "\n";

    std::cout << "-----------------------------------------------------------------------------------------------\n";
    std::cout << "               Part 3: Converting to Second List (Doubly Linked, Append at Back)\n";
    std::cout << "-----------------------------------------------------------------------------------------------\n\n";
    bool bSecondOk = false;
    if (bFirstOk)
    {
        bSecondOk = convertSinglyToDoubly(pSinglyHead, pDoublyHead, pDoublyTail);
    }

    std::cout << "\n  Resulting Second List:\n";
    printDoublyList(pDoublyHead, pDoublyTail);
    std::cout << "\n";

    int nSinglyCount = countSinglyNodes(pSinglyHead);
    int nDoublyCount = countDoublyNodes(pDoublyHead);

    std::cout << "-----------------------------------------------------------------------------------------------\n";
    std::cout << "                                    Part 4: Summary \n";
    std::cout << "-----------------------------------------------------------------------------------------------\n\n";
    std::cout << "  - First list type:    Singly linked list (insert at front)\n";
    std::cout << "  - Second list type:   Doubly linked list (append at back)\n";
    std::cout << "  - Inline predicate:   isNextNull(pNode)\n";
    std::cout << "  - First list count:   " << nSinglyCount << "\n";
    std::cout << "  - Second list count:  " << nDoublyCount << "\n";
    std::cout << "  - Status:             "
              << ((bFirstOk && bSecondOk && nSinglyCount == FIRST_LIST_SIZE && nDoublyCount == nSinglyCount)
                  ? "[CORRECT] Lists built and converted successfully."
                  : "[ERROR]   List conversion mismatch or allocation failure.")
              << "\n\n";

    clearSinglyList(pSinglyHead);
    clearDoublyList(pDoublyHead, pDoublyTail);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Головна функція main
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "             LABORATORY WORK 2.5: SUBPROGRAMS IN LINEAR DATA STRUCTURES (VARIANT 3)\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    executeListOperations();

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "                         Laboratory work 2.5 completed successfully.\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    return 0;
}

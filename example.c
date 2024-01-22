#include <stdio.h>

#define  LL_IMPLEMENTATION
#include "ll.h"

#define llPrint(type, format, list) do {            \
    for (size_t i = 0; i < llLen(list); ++i)        \
    {                                               \
        printf(format"\n", llGet(type, list, i));   \
    }                                               \
} while (0)

int main(void)
{
    llList list = llCreateList();

    llAppend(list, 75);
    llAppend(list, 120);
    llAppend(list, 2377);

    llPrepend(list, 665);

    int x = llGet(int, list, 0);
    printf("x: %d\n", x);

    int * y = llGetRef(int, list, 1);
    printf("*y: %d\n", *y);

    printf("%zu\n", llLen(list));

    llPrint(int, "%d", list);

    llList list2 = llCreateList();

    llAppend(list2, 'H');
    llAppend(list2, 'i');
    llAppend(list2, ' ');
    llAppend(list2, 'o');
    llAppend(list2, 'm');
    llAppend(list2, '!');

    llInsert(list2, 3, 'm');

    for (size_t i = 0; i < llLen(list2); ++i)
    {
        printf("%c", llGet(char, list2, i));
    }
    printf("\n");

    llFree(&list);
    llFree(&list2);

    return 0;
}

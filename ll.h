#ifndef LL_H_
#define LL_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct llNode llNode;
typedef struct llList llList;

struct llNode {
    void * data;
    llNode * next;
};

struct llList {
    llNode * nodes;
};

llList llCreateList();
llNode * _llCreateNode(void * value);
void llFree(llList * list);
void _llAppend(llList * list, void * value);
llList * _llPrepend(llList * list, void * value);
llList * _llInsert(llList * list, size_t id, void * value);
llList * _llDelete(llList * list, size_t id);
size_t _llGet(llList * list, size_t id);
void * _llGetRef(llList * list, size_t id);
size_t llLen(llList list);

#define llAppend(list, value) _llAppend(&list, (void *) value)
#define llPrepend(list, value) list = *_llPrepend(&list, (void *) value)
#define llInsert(list, id, value) list = *_llInsert(&list, id, (void *) value)
#define llDelete(list, id) list = *_llDelete(&list, id)
#define llGet(type, list, id) (type) _llGet(&list, id)
#define llGetRef(type, list, id) (type *) _llGetRef(&list, id)
#define llCreateNode(value) _llCreateNode((void *) value)

#ifdef LL_IMPLEMENTATION

llList llCreateList()
{
    return (llList) {
        .nodes = NULL,
    };
}

llNode * _llCreateNode(void * value)
{
    llNode * node = malloc(sizeof(llNode));

    node->data = value;
    node->next = NULL;

    return node;
}

void llFreeNodes(llNode * node)
{
    if (node->next != NULL)
        llFreeNodes(node->next);

    free(node);
}

void llFree(llList * list)
{
    if (list->nodes == NULL) return;

    llNode * node = list->nodes;

    if (node->next != NULL)
        llFreeNodes(node);
    else
        free(node);
}

void _llAppend(llList * list, void * value)
{
    if (list->nodes == NULL)
    {
        list->nodes = llCreateNode(value);
        return;
    }

    llNode * node = list->nodes;

    while (node->next != NULL)
        node = node->next;

    node->next = llCreateNode(value);
}

llList * _llPrepend(llList * list, void * value)
{
    llNode * node = llCreateNode(value);

    node->next = list->nodes;
    list->nodes = node;

    return list;
}

llList * _llInsert(llList * list, size_t id, void * value)
{
    llNode * prev = NULL;
    llNode * node = list->nodes;

    if (id == 0)
    {
        list->nodes = llCreateNode(value);
        list->nodes->next = node;

        return list;
    }

    while (id > 0)
    {
        if (node->next == NULL && id > 1)
        {
            fprintf(stderr, "RUNTIME ERROR: Index out of bounds\n");
            llFree(list);
            exit(1);
        }

        prev = node;
        node = node->next;
        --id;
    }

    prev->next = _llCreateNode(value);
    prev->next->next = node;

    return list;
}

llList * _llDelete(llList * list, size_t id)
{
    llNode * prev = NULL;
    llNode * node = list->nodes;

    if (list->nodes == NULL) return list;

    if (id == 0)
    {
        list->nodes = node->next;
        free(node);

        return list;
    }

    while (id > 0)
    {
        if (node->next == NULL)
        {
            fprintf(stderr, "RUNTIME ERROR: Index out of bounds\n");
            llFree(list);
            exit(1);
        }

        prev = node;
        node = node->next;
        --id;
    }

    prev->next = node->next;

    free(node);

    return list;
}

size_t _llGet(llList * list, size_t id)
{
    llNode * node = list->nodes;

    while (id > 0)
    {
        if (node->next == NULL)
        {
            fprintf(stderr, "RUNTIME ERROR: Index out of bounds\n");
            llFree(list);
            exit(1);
        }

        node = node->next;
        --id;
    }

    return (size_t) node->data;
}

void * _llGetRef(llList * list, size_t id)
{
    llNode * node = list->nodes;

    while (id > 0)
    {
        if (node->next == NULL)
        {
            fprintf(stderr, "RUNTIME ERROR: Index out of bounds\n");
            llFree(list);
            exit(1);
        }

        node = node->next;
        --id;
    }

    return (void *) &node->data;
}

size_t llLen(llList list)
{
    llNode * node = list.nodes;

    size_t len = 0;

    while (node != NULL)
    {
        ++len;
        node = node->next;
    }

    return len;
}

#endif // LL_IMPLEMENTATION

#endif // LL_H_

#include "../inc/struct.h"
#include "../inc/return_codes.h"
#include "../inc/node_funcs.h"

#include <stdio.h>
#include <stdlib.h>

#define EMPTY 1
#define NOT_EMPTY 0
#define FALSE 1

node_t *init_node(const int num)
{
    node_t *node = malloc(sizeof(node_t));

    if (node)
    {
        node->data = num;
        node->next = NULL;
    }
    return node;
}

size_t list_stack_push(node_t **node, const int num)
{
    size_t rc = OK; // код возврата
    
    if (num)
    {
        node_t *temp_node = init_node(num);

        if (temp_node)
        {
            temp_node->next = *node;
            *node = temp_node;
        }
        else
        {
            printf("\tОшибка: Не удалось выделить память!\n");
            rc = ALLOCATE_ERROR;
        }
    }
    else
    {
        printf("\tОшибка: Неправильно ввели число!\n");
        rc = DATA_ERROR;
    }
    return rc;
}

int list_pop(node_t **node)
{
    int value = 0;

    if (*node)
    {
        node_t *temp_node = *node;

        value = temp_node->data;
        *node = (*node)->next;
        
        free(temp_node);
    }
    return value;
}

void free_list(node_t *node)
{
    node_t *next;

    for (; node; node = next)
    {
        next = node->next;
        free(node);
    }
}

size_t list_stack_copy(node_t **node, node_t **copy_list, node_t **temp_list)
{
    int value;
    size_t rc = OK; // код возврата

    while (rc == OK && empty_list(*node) == NOT_EMPTY)
    {
        value = list_pop(node);

        if (list_stack_push(temp_list, value) != OK)
            rc = FALSE;
    }

    while (rc == OK && empty_list(*temp_list) == NOT_EMPTY)
    {
        value = list_pop(temp_list);

        if (list_stack_push(node, value) != OK)
            rc = FALSE;

        if (rc == OK && list_stack_push(copy_list, value) != OK)
            rc = FALSE;
    }
    return rc;
}

size_t empty_list(node_t *list)
{
    size_t rc = NOT_EMPTY; // код возврата

    if (list == NULL)
        rc = EMPTY;

    return rc;
}
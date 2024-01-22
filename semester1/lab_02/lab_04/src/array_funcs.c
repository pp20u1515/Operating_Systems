#include "../inc/return_codes.h"
#include "../inc/struct.h"
#include "../inc/array_funcs.h"

#include <stdio.h>
#include <stdlib.h>

#define INIT_TOP 0
#define MAX_STACK_SIZE 1000
#define NOT_EMPTY 0
#define EMPTY 1
#define FALSE 1

size_t init_array_stack(array_stack_t *array_stack)
{
    size_t rc = OK; // код возврата
    
    array_stack->top = INIT_TOP;
    array_stack->size = MAX_STACK_SIZE;
    array_stack->data = malloc(array_stack->size * sizeof(int));
    
    if (array_stack->data == NULL)
        rc = ALLOCATE_ERROR;
    
    return rc;
}

size_t array_stack_push(array_stack_t *array_stack, const int num)
{
    size_t rc = OK; // код возврата

    if (num)
    {
        if (array_stack->top < array_stack->size)
        {
            array_stack->data[array_stack->top] = num;
            array_stack->top++;
        }
        else
        {
            printf("\tОшибка: Произошло переполнение в массиве!\n");
            rc = OVERFLOW_ERROR;
        }
    }
    else
    {
        printf("\tОшибка: Неправильно ввели число!\n");
        rc = DATA_ERROR;
    }
    return rc;
}

int array_pop(array_stack_t *array_stack)
{
    int rc = OK; // код возврата

    if (array_stack->top > 0)
    {
        array_stack->top--;
        rc = array_stack->data[array_stack->top];
    }
    else
        rc = UNDERFLOW_ERROR;    
    
    return rc;
}

size_t empty_array(array_stack_t *array_stack)
{
    size_t rc = NOT_EMPTY; // код возврата

    if (array_stack->top < 1)
        rc = EMPTY;

    return rc;
}

size_t array_stack_copy(array_stack_t *array_stack, array_stack_t *copy_array_stack, array_stack_t *temp_array_stack)
{
    int value; 
    size_t rc = OK; // код возврата

    while (rc == OK && empty_array(array_stack) == NOT_EMPTY)
    {
        value = array_pop(array_stack);

        if (array_stack_push(temp_array_stack, value) != OK)
            rc = FALSE;
    } 
    while (rc == OK && empty_array(temp_array_stack) == NOT_EMPTY)
    {
        value = array_pop(temp_array_stack);

        if (array_stack_push(array_stack, value) != OK)
            rc = FALSE;

        if (array_stack_push(copy_array_stack, value) != OK)
            rc = FALSE;
    }
    return rc;
}
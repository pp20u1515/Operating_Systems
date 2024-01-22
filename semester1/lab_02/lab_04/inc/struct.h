#ifndef STRUC_H
#define STRUC_H

#include <stdio.h>

// Структура стека в виде списка
typedef struct node_t
{
    int data; // данные стека
    struct node_t *next; // указатель на следующая ячейка памяти
}node_t;

// Структура стека в виде массива
typedef struct array_stack_t
{
    int *data; // массив
    size_t top; // верхный узел 
    size_t size; // длина массива
}array_stack_t;

#endif
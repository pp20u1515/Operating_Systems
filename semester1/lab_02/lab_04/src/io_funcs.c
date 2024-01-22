#include "../inc/io_funcs.h"
#include "../inc/return_codes.h"
#include "../inc/struct.h"
#include "../inc/array_funcs.h"
#include "../inc/node_funcs.h"

#include <stdlib.h>
#include <limits.h>

#define NOT_EMPTY 0

void condition()
{
    printf("\n\n\tРазработать программу работы со стеком, реализующую операции добавления и\n\
    \tудаления элементов из стека и отображения текущего состояния стека. Реализовать\n\
    \tстек: а) массивом; б) списком.\n");
}

void menu()
{
    printf("\n\t\t\tМеню\n");
    printf("\n\t1) Добавить элемент в стек.\n\
    \t2) Удалить элемент из стека.\n\
    \t3) Распечатайте убывающие серии последовательности целых чисел в обратном порядке.\n\
    \t4) Вывести стек.\n\
    \t5) Сравнить время.\n\
    \t6) Заполнить стек автоматически.\n\
    \t0) Выйти из программы.\n\n");
}

void fill_stack(array_stack_t *array_stack, node_t **node)
{
    char symb[CHAR_MAX]; // введенный элемент
    size_t rc = OK; // код возврата
    
    if (*node == NULL)
        rc = init_array_stack(array_stack);
    
    if (rc == OK)
    {
        scanf("%s", symb);
        rc = array_stack_push(array_stack, atoi(symb));

        if (rc == OK)
        {
            rc = list_stack_push(node, atoi(symb));

            if (rc != OK)
                free(array_stack->data);
        }
    }
    else
        printf("\tОшибка: Не удалось выделить память!\n");
}

void fill_stack_auto(array_stack_t *array_stack, node_t **node)
{
    size_t rc = OK; // код возврата
    size_t elem; // количество элементов стека
    int num; // элемент стека

    if (*node == NULL)
        rc = init_array_stack(array_stack);
    
    if (rc == OK)
    {
        printf("\tВведите количество элементов: ");

        if (scanf("%zu", &elem) == 1)
        {
            
            for (size_t index_i = 0; rc == OK && index_i < elem; index_i++)
            {
                num = rand() % 100 + 1;
                rc = array_stack_push(array_stack, num);

                if (rc == OK)
                {
                    rc = list_stack_push(node, num);

                    if (rc != OK)
                        free(array_stack->data);
                }
            }
        }
        else
        {
            printf("\tОшибка: Неправильный ввод!\n");
        }
    }
    else
        printf("\tОшибка: Не удалось выделить память!\n");
}

void print_array_stack(array_stack_t *array_stack)
{
    array_stack_t copy_array_stack, temp_array_stack;

    init_array_stack(&copy_array_stack);
    init_array_stack(&temp_array_stack);
    array_stack_copy(array_stack, &copy_array_stack, &temp_array_stack);

    printf("\tСтек представен в виде массива: ");
    while (empty_array(&copy_array_stack) == NOT_EMPTY)
    {
        printf("%d ", array_pop(&copy_array_stack));
    }
    printf("\n");

    free(copy_array_stack.data);
    free(temp_array_stack.data);
}

void print_list_stack(node_t **node)
{
    node_t *copy_list = NULL, *temp_list = NULL;

    list_stack_copy(node, &copy_list, &temp_list);

    printf("\tСтек представен в виде списка: ");
    while (empty_list(copy_list) == OK)
    {
        printf("%d ", list_pop(&copy_list));
    }
    printf("\n");

    list_stack_copy(node, &copy_list, &temp_list);
    printf("\tАдресса элементов стека: ");
    node_t *temp = *node;

    while (temp)
    {
        printf("%p ", (void *)temp);
        temp = temp->next;
    }
    printf("\n");

    free_list(copy_list);
    free_list(temp_list);
}

void print_descending_seq_arr(array_stack_t *array_stack)
{
    int left_elem = array_pop(array_stack);

    printf("\tПоследовательности стека в виде массива:\n");
    while (empty_array(array_stack) == NOT_EMPTY)
    {
        int *arr = malloc(array_stack->top * sizeof(int));
        int right_elem = array_pop(array_stack);
        size_t index = 0; // индекс

        arr[index] = left_elem;
        index++;

        while (right_elem > left_elem)
        {
            arr[index] = right_elem;
            index++;
            left_elem = right_elem;

            if (empty_array(array_stack) == NOT_EMPTY)
                right_elem = array_pop(array_stack);
        }
        left_elem = right_elem;

        if (index != 1)
        {
            for (size_t j = 0; j < index; j++)
            {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }
        free(arr);
    }
}

void print_descending_seq_list(node_t **list, int size)
{
    int left_elem = list_pop(list);
    int count = 0; // счетчик

    printf("\n\tПоследовательности стека в виде списка:\n");
    while (empty_list(*list) == NOT_EMPTY)
    {
        int *arr = malloc(size * sizeof(int));
        int right_elem = list_pop(list);
        size_t index = 0; // индекс

        arr[index] = left_elem;
        index++;

        while (right_elem > left_elem)
        {
            arr[index] = right_elem;
            index++;
            left_elem = right_elem;

            if (empty_list(*list) == NOT_EMPTY)
                right_elem = list_pop(list);
        }
        left_elem = right_elem;

        if (index != 1)
        {
            count++;

            for (size_t j = 0; j < index; j++)
            {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }
        free(arr);
    }

    if (count == 0)
        printf("\tНет последовательности!\n");
}

void compare_time(double *array_time)
{
    printf("\tСкорость работы стека, представленный списком: %.6lf sec.\n", array_time[0]);
    printf("\tОбъем памяти: %.1f bytes.\n", sizeof(node_t) * array_time[2]);
    printf("\tСкорость работы стека, представленный массивом: %.6lf sec.\n", array_time[1]);
    printf("\tОбъем памяти: %.1f bytes.\n", sizeof(int) * array_time[2]);
}

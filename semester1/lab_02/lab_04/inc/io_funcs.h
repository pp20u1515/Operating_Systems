#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#include "struct.h"

/**
 * @brief Меню
 * 
 */
void menu();

/**
 * @brief fill_stack - Функция, которая заполняет стек числами
 * 
 * @param array_stack Структура стека в виде массива
 * @param node Структура стека в виде списка
 */
void fill_stack(array_stack_t *array_stack, node_t **node);

/**
 * @brief print_list_stack - Вывод стека в виде списка
 * 
 * @param node Структура стека
 */
void print_list_stack(node_t **node);

/**
 * @brief print_array_stack - Вывод стека 
 * 
 * @param array_stack Структура стека
 */
void print_array_stack(array_stack_t *array_stack);

/**
 * @brief print_descending_seq_arr - Функция, которая выводить убывающую последовательность в обратном порядке из массива
 * 
 * @param array_stack Структура стека
 */
void print_descending_seq_arr(array_stack_t *array_stack);

/**
 * @brief print_descending_seq_list - Функция, которая выводить убывающую последовательность в обратном порядке из списка
 * 
 * @param list Структура стека(списка)
 * @param array_stack Структура стека(массива)
 */
void print_descending_seq_list(node_t **list, int size);

/**
 * @brief condition - Условие задачи 
 * 
 */
void condition();

/**
 * @brief Функция, которая сравнивает объем и скорость работы стека как а) массивом и б) списком
 * 
 * @param array_time Массив, содержащии скорость  работы стека
 */
void compare_time(double *array_time);

/**
 * @brief fill_stack_auto - Функция, которая автоматически заполняет стек произвольными числами
 * 
 * @param array_stack Структура стекка в виде массива
 * @param node Структура стека в виде списка
 */
void fill_stack_auto(array_stack_t *array_stack, node_t **node);

#endif // IO_FUNCS_H
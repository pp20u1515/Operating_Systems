#ifndef NODE_FUNCS_H
#define NODE_FUNCS_H

#include "struct.h"

#include <stdio.h>

/**
 * @brief list_stack_push - Функция, которая добавляet элемент в стек
 * 
 * @param node Структура стека в виде списка
 * @param num Элемент для добавления в стек
 * @return Код ошибки или код успеха
 */
size_t list_stack_push(node_t **node, const int num);

/**
 * @brief init_node - Функция, которая создает узел списка
 * 
 * @param num Число, которое добавляется в список
 * @return Результат инициализированного списка
 */
node_t *init_node(const int num);

/**
 * @brief list_pop - Функция, которая удаляет элемент из стека(список)
 * 
 * @param node Структура стека(список)
 * @return Удаленый элемент
 */
int list_pop(node_t **node);

/**
 * @brief free_list - Функция, которая освобождает память списка
 * 
 * @param node Структура стека(список)
 */
void free_list(node_t *node);

/**
 * @brief empty_list - Функция, проверяющая является ли стек пустым
 * 
 * @param list Структура стека
 * @return Код успеха или код ошибки
 */
size_t empty_list(node_t *list);

/**
 * @brief list_stack_copy - Функция, которая копирует данные из старого стека в новый
 * 
 * @param node Структура исходного стека
 * @param copy_list Струкура нового стека
 * @param temp_list Структура вспомагательного стека
 * @return Код успеха или код ошибки
 */
size_t list_stack_copy(node_t **node, node_t **copy_list, node_t **temp_list);

#endif
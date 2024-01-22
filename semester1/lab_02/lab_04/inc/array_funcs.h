#ifndef ARRAY_FUNCS_H
#define ARRAY_FUNCS_H

#include "struct.h"

#include <stdio.h>
#include <inttypes.h>

/**
 * @brief array_stack_push - Функция, которая добавляет элемент в стек(массив)
 * 
 * @param array_stack Структура стека(массив)
 * @param num Символ для добавления
 * @return Код ошибки или код успеха
 */
size_t array_stack_push(array_stack_t *array_stack, const int num);

/**
 * @brief init_array_stack - Функция, инициализирующая стек(массив)
 * 
 * @param array_stack Структура стека(массив)
 * @return Код успеха или код ошибки
 */
size_t init_array_stack(array_stack_t *array_stack);

/**
 * @brief array_pop - Функция, которая удаляет элемент из стека(массив)
 * 
 * @param array_stack Структура стекка(массив)
 * @return Код ошибки или удаляемый элемент
 */
int array_pop(array_stack_t *array_stack);

/**
 * @brief array_stack_copy - Функция, которая копирует данные из исходного стека в новый
 * 
 * @param array_stack Структура исходного стека
 * @param copy_array_stack Структура нового стека
 * @param temp_array_stack Вспомагательная структура стека
 * @return size_t 
 */
size_t array_stack_copy(array_stack_t *array_stack, array_stack_t *copy_array_stack, array_stack_t *temp_array_stack);

/**
 * @brief empty_array - Функция, проверяющая является ли стек пустым
 * 
 * @param array_stack Структура стека
 * @return Код пустого стека или код полого стека
 */
size_t empty_array(array_stack_t *array_stack);

uint64_t tick(void);

#endif // ARRAY_FUNCS_H
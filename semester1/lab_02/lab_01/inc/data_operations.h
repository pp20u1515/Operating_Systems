#ifndef DATA_OPERATIONS_H
#define DATA_OPERATIONS_H

#include "struct.h"

// Функция, преобразующая введеное число в вещественное
int parsing(char *num, number_t *number, int is_second);

// Деление двух чисел
void divide(const number_t a, const number_t b, number_t *c);

//Функция, подготавливающая числа к делению
void prepare_for_division(number_t *first_num, number_t *second_num, int *final_base);

// Функция, сравнивающая элементы массива двух чисел 
int compare_num(number_t *dividend, number_t *divider);

#endif // DATA_OPERATIONS_H
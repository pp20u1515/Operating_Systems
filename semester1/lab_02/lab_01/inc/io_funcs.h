#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#include "struct.h"

// Меню
void menu();

// Ввод целого числа
int input_int(number_t *number, int is_second);

// Ввод вещественого числа
int input_float(number_t *number, int is_second);

// Вывод результата
int print_result(number_t c);

// Чтение числа
int read_line(char *num);

#endif // IO_FUNCS_H
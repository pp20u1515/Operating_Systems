#ifndef CHECK_NUM_H
#define CHECK_NUM_H

#include "struct.h"

// Проверка ввода целого числа
int check_int(const char *num);

// Функция, проверяющая коректность веществоеного числа 
int check_float(const char *num);

// Функция, проверяющая количество eps
int check_eps(const char *num);

// Проверка количество точек в числе
int check_points(const char *num);

// Проверка числа на допустимые символы
int check_allowed_symbs(const char *num);

// Функция, проверяющая является ли символ число
int is_digit(char ch);

// Проверка вводимых символов на корректность
int check_symbs(const char *num);

// Функция, проверяющая явлаяется ли число нулю
int is_zero(const number_t *dividend);

#endif // CHECK_NUM_H
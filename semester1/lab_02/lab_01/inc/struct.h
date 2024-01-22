#ifndef STRUCT_H
#define STRUCT_H

#include "return_codes.h"

typedef struct number 
{
    int sign; // знак мантиссы
    int mantissa[MAX_MANTISSA_LENGTH + 1]; // мантисса
    int mantissa_length; // длинна мантиссы
    int point_index; // индекс точки
    int base; // порядок
    int base_sign; // знак порядка
    int start_index; // индекс начала числа(массива)
    int end_index; // индекс конца числа(массива)
}number_t;

#endif // STRUCT_H
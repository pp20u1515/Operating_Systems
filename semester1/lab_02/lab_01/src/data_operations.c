#include "../inc/data_operations.h"
#include "../inc/struct.h"
#include "../inc/return_codes.h"
#include "../inc/check_num.h"

#include <stdio.h>

// Сдвиг
void shift(number_t *number)
{
    for (int i = 0; i < number->mantissa_length - 1; i++)
        number->mantissa[i] = number->mantissa[i + 1];
    
    number->mantissa[number->mantissa_length - 1] = 0;
}

// Функция, которая делает число без точки
void make_number_without_dot(number_t *number)
{
    number->base -= (number->mantissa_length - number->point_index);
    
    int index = 0; // индекс

    while (number->mantissa[index] == 0)
    {
        shift(number);
        number->mantissa_length -= 1;
    }
    number->point_index = 0;
}

// Функция, сравнивающая элементы массива двух чисел 
int compare_num(number_t *dividend, number_t *divider)
{
    int rc = 0; // код возврата

    // если количество цифр двух чисел равно, то 
    if ((dividend->end_index - dividend->start_index) == (divider->end_index - divider->start_index))
    {
        int i = dividend->start_index; // индекс делимого
        int j = divider->start_index; // индекс делителя

        // пока индексы делителя и делимого меньше индекс последной цифры и цифры одинаковы, то
        while (i < dividend->end_index - 1 && j < divider->end_index - 1 && dividend->mantissa[i] == divider->mantissa[j])
        {
            i++; // индексы увеличиваются
            j++;
        }
        if (dividend->mantissa[i] > divider->mantissa[j])
            rc = 1;
        else if (dividend->mantissa[i] < divider->mantissa[j])
            rc = -1;
    }
    else if ((dividend->end_index - dividend->start_index) > (divider->end_index - divider->start_index))
        rc = 1;
    else if ((dividend->end_index - dividend->start_index) < (divider->end_index - divider->start_index))
        rc = -1;
    
    return rc;
}

// Вычитание
void subract(number_t *dividend, number_t *divider)
{
    if ((dividend->end_index - dividend->start_index) >= (divider->end_index - divider->start_index))
    {
        int i = dividend->end_index - 1; // индекс последной цифры делимого
        int j = divider->end_index - 1; // индекс последной цифры делителя
        int debt = 0;
        int current_digit = divider->mantissa[j]; // текущая цифра

        // пока остаток не равен нулю
        while (i >= 0 && j >= 0 && i >= dividend->start_index && j >= divider->start_index)
        {
            if (debt < 0)
            {
                if (dividend->mantissa[i] > 0)
                {
                    dividend->mantissa[i]--;
                    debt++;
                }
                else
                    dividend->mantissa[i] = 9;
            }
            if (dividend->mantissa[i] >= current_digit)
                dividend->mantissa[i] -= current_digit;
            else 
            {
                dividend->mantissa[i] = 10 + dividend->mantissa[i] - current_digit;
                debt -= 1;
            }
            i -= 1;
            
            if ((j - 1) < divider->start_index) // если в делителе только одна цифра
                current_digit = 0;
            else // иначе 
            {
                j -= 1; // уменьшаем индекс делителя
                current_digit = divider->mantissa[j]; // и присваиваем самая чифра
            }
        }
    }
    while(dividend->mantissa[dividend->start_index] == 0 && dividend->start_index <= MAX_MANTISSA_LENGTH)
        dividend->start_index++;
}

//Функция, подготавливающая числа к делению
void prepare_for_division(number_t *first_num, number_t *second_num, int *final_base)
{
    if (first_num->point_index != -1)
        make_number_without_dot(first_num);

    if (second_num->point_index != -1)
        make_number_without_dot(second_num);
    
    first_num->start_index = 0;
    first_num->end_index = first_num->mantissa_length;
    second_num->start_index = 0;
    second_num->end_index = second_num->mantissa_length;
    
    while(first_num->mantissa[first_num->mantissa_length - 1] == 0) // пока последные цифры числа равны нулю
    {
        first_num->mantissa_length--;                         // уменьшаем длинну мантиссы на одно число и
        first_num->end_index--;                               // уменьшаем индекс последной цифры, а
        (*final_base) += 1;                                   // увеличиваем конечный порядок
    }
    
    while (compare_num(first_num, second_num) < 0)
    {
        (*final_base) -= 1;
        first_num->end_index += 1;
        first_num->mantissa_length++;
    }

    while (compare_num(first_num, second_num) >= 0)
        first_num->end_index -= 1;
    
    first_num->end_index += 1;
}

// Округление числа
int round_num(number_t *result, int *final_base)
{
    int i = MAX_MANTISSA_LENGTH - 1;
    
    if (result->mantissa[i] == 1 && result->mantissa[i - 1] != 1)
    {
        i--;
        result->mantissa[i]++;

        while (result->mantissa[i] == 10 && i > 0)
        {
            result->mantissa[i] = 0;
            i--;
            result->mantissa[i]++;
        }

        if (i == 0 && result->mantissa[i] == 10)
        {
            result->mantissa[i] = 1;
            final_base++;
        }
    }
    else if (result->mantissa[i] >= 5)
    {
        i--;
        result->mantissa[i]++;

        while (result->mantissa[i] == 10 && i > 0)
        {
            result->mantissa[i] = 0;
            i--;
            result->mantissa[i]++;
        }

        if (i == 0 && result->mantissa[i] == 10)
        {
            result->mantissa[i] = 1;
            final_base++;
        }
    }

    return i;
}

// Функция, преврящающая десятичное число в идеальную форму
void make_float_normal(number_t a, number_t b, number_t *c, int final_base, int i)
{
    c->mantissa_length--;
    c->sign = (a.sign + b.sign) % 2;
    c->base = final_base - (b.base) + a.base;
    
    if (c->base < 0)
        c->base_sign = 1;
    else
        c->base_sign = 0;

    c->end_index = c->mantissa_length;
    i = c->end_index - 1;

    while(c->mantissa[i--] == 0)
    {
        c->end_index--;
        c->base++;
    }
}

// Деление
void divide(number_t first_num, number_t second_num, number_t *result)
{
    if (is_zero(&first_num))
    {
        result->mantissa_length = 1;
        result->end_index = 1;
        result->base = 0;
    } 
    else
    {
        int final_base = 0; // конечный порядок
        int i = 0;
        int current_digit = 0; // текушая цифра
        result->mantissa_length = 0;

        prepare_for_division(&first_num, &second_num, &final_base);
        
        while(result->mantissa_length != MAX_MANTISSA_LENGTH)
        {
            while (compare_num(&first_num, &second_num) >= 0)   
            {
                subract(&first_num, &second_num);
                current_digit++;
            }
            
            while(first_num.mantissa[first_num.start_index] == 0 && first_num.start_index <= MAX_MANTISSA_LENGTH)
                first_num.start_index++;

            if (i < MAX_MANTISSA_LENGTH - 2 && first_num.end_index >= first_num.mantissa_length)
                final_base--;

            if (first_num.end_index != MAX_MANTISSA_LENGTH)
                first_num.end_index++;
            else
            {
                shift(&first_num);
                first_num.start_index--;
            }
            if (current_digit > 10)
                current_digit /= 10;
            
            result->mantissa[i] = current_digit;
            result->mantissa_length++;
            current_digit = 0;
            i++;
        }

        i = round_num(result, &final_base);
        make_float_normal(first_num, second_num, result, final_base, i);
    }
}

// Функция, преобразующая введеное число в вещественное
int parsing(char *num, number_t *number, int is_second)
{
    int rc = OK, index = 0;

    number->point_index = -1;

    if (num[index] == '-')
        number->sign = 1;
    
    if (num[index] == '-' || num[index] == '+' || num[index] =='.')
        index++;
    
    int j = 0;

    while (num[index] == '0' && num[index + 1] != '.')
        index++;
     
    while (is_digit(num[index]))
        number->mantissa[j++] = num[index++] - '0';
    
    if (num[index] == '.')
    {
        number->point_index = j;
        index++;
        
        while(is_digit(num[index]))
            number->mantissa[j++] = num[index++] - '0';
    }
    
    if (num[index] == 'e' || num[index] == 'E')
        number->mantissa_length = j;
    else
        number->mantissa_length = j;
    
    index++;
    
    if (num[index] == '-')
        number->base_sign = 1;
    
    if (num[index] == '-' || num[index] == '+')
        index++;
    
    while (is_digit(num[index]))
        number->base = number->base * 10 + (num[index++] - '0');
    
    if (number->base_sign)
        number->base *= -1;
    
    if (num[index] != 0)
        rc = READ_ERROR;
    
    if (is_second == OK)
    {
        int is_zeroes = 1;
        
        for (index = 0; index < number->mantissa_length; index++)
            if (number->mantissa[index] != 0)
                is_zeroes = 0;
        
        if (is_zeroes)
            rc = ZERO_ERROR;
    }
    
    return rc;
}
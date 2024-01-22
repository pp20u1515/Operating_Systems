#include "../inc/check_num.h"
#include "../inc/return_codes.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Массив разрешенных символов
const char allowed_symbs[ALLOWED_SYMBS] = {'+', '-', '.', 'e', 'E'};

// Функция, проверяющая является ли символ число
int is_digit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

// Проверка ввода целого числа
int check_int(const char *num)
{
    int rc = OK; // код возврата
    
    if (strlen(num) <= MAX_INT_LENGTH)
        for (int i = 0; rc == OK && i < strlen(num); i++)
            if (i == 0 && strlen(num) == MAX_INT_LENGTH && num[i] != '+' && num[i] != '-')
                rc = INPUT_ERROR;
            else if (i == 0 && (num[i] == '+' || num[i] == '-' || isdigit(num[i]) != 0))
                rc = OK;
            else if (isdigit(num[i]) != 0)
                rc = OK;
            else
                rc = INPUT_ERROR;
    else
        rc = INPUT_ERROR;

    return rc;
}

// Проверка числа на допустимые символы
int check_allowed_symbs(const char *num)
{
    int rc = OK; // код возврата
    int count = 0; // счетчик
    
    for (int i = 0; rc == OK && i < strlen(num); i++)
    {
        for (int j = 0; j < ALLOWED_SYMBS; j++)
            if (num[i] != allowed_symbs[j] && !is_digit(num[i]))
                count++;

        if (count == ALLOWED_SYMBS)
            rc = SYMB_ERROR;
    }
    return rc;
}

// Проверка количество точек в числе
int check_points(const char *num)
{
    int count = 0; // счетчик

    for (int i = 0; i < strlen(num); i++)
        if (num[i] == '.')
            count++;
    
    return count;
}

// Функция, проверяющая количество eps
int check_eps(const char *num)
{
    int rc = OK; // код возврата
    int count  = 0; //счетчик

    for (int i = 0; i < strlen(num); i++)
        if (num[i] == 'e' || num[i] == 'E')
            count++;

    if (count > AMOUNT_OF_EPS)
        rc = AMOUNT_OF_EPS_ERROR;
    
    return rc;
}

// Проверка вводимых символов на корректность
int check_symbs(const char *num)
{
    int rc = check_allowed_symbs(num);

    if (rc == OK)
    {
        rc = check_points(num);

        if (rc <= AMOUNT_OF_POINTS)
        {
            rc = check_eps(num);

            if (rc != OK)
                printf("\tОшибка: В числе неправильно введено eps!\n");
        }
        else
        {
            printf("\tОшибка: В числе введено неправильное количество точек!\n");
            rc = AMOUNT_OF_POINTS_ERROR;
        }
    }
    else
        printf("\tОшибка: В числе введено недопустимые символы!\n");
     
    return rc;
}

// Функция, проверяющая коректность веществоеного числа
int check_float(const char *num)
{
    int rc = check_symbs(num);

    if (rc == OK)
    {
        if (strlen(num) > NUM_LENGTH)
        {
            printf("\tОшибка: Мантисса числа содержить больше 30 цифр!\n");
            rc = MANTISSA_ERROR;
        }
    }
    return rc;
}

// Функция, проверяющая явлаяется ли число нулю
int is_zero(const number_t *dividend)
{
    int flag = 1; // флаг

    for (int i = 0; i < dividend->mantissa_length; i++) // проходим через все символы
        if (dividend->mantissa[i] != 0) // если последнее число не равно нулю, то
            flag = 0;                  // число не != 0
    
    return flag;
}

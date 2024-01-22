#include "../inc/return_codes.h"
#include "../inc/struct.h"
#include "../inc/check_num.h"
#include "../inc/data_operations.h"

#include <stdio.h>
#include <string.h>

// Меню
void menu()
{
    printf("\n\n\t\t\tМеню\n\n\
        Смоделировать операцию деления целого числа на действительное.\n\n\
        1) Сначало вводится целое число, потом вещественое.\n\
        2) Числа вводятся без пробелов.\n\
        3) Числа вводятся как с знаком так и без.\n\
        4) Длинна целого числа должна быть до 30 значащих чисел.\n\
        5) Длинна вещественого числа дожна быть до 30 значащих чисел.\n\
        6) Величина порядка не должна превышать 5 цифр.\n\n");
    printf("\t\t\t\t   ±|--------|---------|---------|E±|---|\n");
}

// Чтение числа
int read_line(char *num)
{
    int rc = OK; // код возврата
    char ch = 0; // символ
    int index = 0; // индекс

    scanf("%c", &ch);
    
    while (rc == OK && ch != '\n')
        if (strlen(num) <= MAX_FLOAT_LENGTH + 1)
        {
            num[index++] = ch;
            scanf("%c", &ch);   
        }
        else
            rc = INPUT_ERROR;

    num[index] = '\0';

    if (index <= 0)
        rc = INPUT_ERROR;
    
    return rc;
}

// Ввод вещественого числа
int input_float(number_t *number, int is_second)
{
    int rc = OK;
    char str[MAX_FLOAT_LENGTH + 1] = { 0 };
    
    printf("\tВведите вещественое число: ");
    rc = read_line(str);
    
    if (rc == OK)
    {
        rc = check_float(str);
        
        if (rc == OK)
        {
            rc = parsing(str, number, is_second);

            if (rc == ZERO_ERROR)
                printf("\tОшибка: Числа не делятся на 0!\n");
            else if (rc == READ_ERROR)
                printf("\tОшибка: Неправильно ввели десятичное число!\n");
        }
    }
    else
        printf("\tОшибка: Неправильно ввели десятичное число!\n");

    return rc;
}

// Ввод целого числа
int input_int(number_t *number, int is_second)
{
    int rc = OK;
    int flag = 0;
    char str[MAX_FLOAT_LENGTH + 1] = { 0 };
    
    printf("\tВведите целое число:       ");
    rc = read_line(str);
    
    if (rc == OK)
    {
        rc = check_int(str); 
        
        if (rc == OK)
            rc = parsing(str, number, is_second);
        else
        {
            printf("\tОшибка: Неправильно ввели целое число!\n");
            rc = INPUT_ERROR;
        }
    }
    else
        printf("\tОшибка: Неправильно ввели целое число!\n");
    
    return rc;
}

// Вывод результата
int print_result(number_t c)
{
    c.base += c.end_index;

    if (c.base < -99999 || c.base > 99999)
        printf("\tОшибка: Произошло переполнение порядка!\n");
    else
    {
        printf("\n\tРезультат: ");
        
        if (c.sign)
            printf("-");

        printf("0.");

        for (int i = 0; i < c.end_index && i < MAX_MANTISSA_LENGTH - 1; i++)
            printf("%d", c.mantissa[i]);
            
        printf("E");
        printf("%d\n", c.base);
    }
    printf("\n");
    
    return OK;
}
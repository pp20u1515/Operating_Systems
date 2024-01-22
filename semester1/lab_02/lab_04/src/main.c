#include "../inc/return_codes.h"
#include "../inc/io_funcs.h"
#include "../inc/struct.h"
#include "../inc/node_funcs.h"
#include "../inc/array_funcs.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFF_LEN 3
#define TRUE 1
#define FALSE 1
#define ARRAY_TIME_LEN 3

int main()
{
    node_t *node = NULL, *temp_node = NULL;
    array_stack_t array_stack;
    int choice = -1, size;
    char choice_buff[BUFF_LEN];
    clock_t start, end;
    double array_time[ARRAY_TIME_LEN];
    size_t flag = FALSE;

    condition();

    while (choice != 0)
    {
        menu();

        printf("\n\tВыберите действие: ");
        
        scanf("%s", choice_buff);
        choice = atoi(choice_buff);

        while (!choice)
        {
            if (strcmp(choice_buff, "0") == 0)
                break;

            printf("\tОшибка: Неправильный ввод!\n");
            printf("\n\tВыберите действие: ");
        
            scanf("%s", choice_buff);
            choice = atoi(choice_buff);
        }

        switch (choice)
        {
            case (0):
                printf("\n\n\tПрограмма завершена!\n");
                return OK;
            case (1):
                printf("\n\tВведите элемент стека: ");
                fill_stack(&array_stack, &node);
                break;
            case (2):
                if (array_stack.top < 1 && node == NULL)
                    printf("\tОшибка: Произошло опустошение стека!\n");
                else
                {
                    printf("\tВы удалили элемент: %d\n", array_pop(&array_stack));
                    temp_node = node;
                    list_pop(&node);
                    printf("\tАдресс удаленного элемента: %p\n", (void *)temp_node);
                    //temp_node = temp_node->next;
                }
                break;
            case (3):
                if (array_stack.top < 1 && node == NULL)
                {
                    printf("\tСтек пустой!\n");
                    flag = FALSE;
                }
                else
                {
                    array_time[2] = array_stack.top;
                    size = array_stack.top;
                    start = clock();
                    print_descending_seq_list(&node, size);
                    end = clock();
                    array_time[0] = (end - start) / (CLOCKS_PER_SEC * 1.0);

                    start = clock();
                    print_descending_seq_arr(&array_stack);
                    end = clock();
                    array_time[1] = (end - start) / (CLOCKS_PER_SEC * 1.0);
                    flag = OK;
                }
                break;
            case (4):
                if (array_stack.top < 1 && node == NULL)
                    printf("\tСтек пустой!\n");
                else
                {
                    print_array_stack(&array_stack);
                    print_list_stack(&node);
                }
                break;
            case (5):
                if (flag == FALSE)
                    printf("\tВы не нашли убывающую последовательность!\n");
                else
                    compare_time(array_time);
                break;
            case (6):
                fill_stack_auto(&array_stack, &node);
                break;
            default:
                printf("\tОшибка: Неправильный ввод!\n");
                break;
        }
    }
}

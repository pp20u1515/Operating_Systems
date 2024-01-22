#include "../inc/return_codes.h"
#include "../inc/io_funcs.h"
#include "../inc/struct.h"
#include "../inc/data_operations.h"

#include <stdio.h>

int main(void)
{
    int rc = OK; // return_code
    number_t first_num = { 0 }, second_num = { 0 }, result = { 0 };
     
    menu();
    rc = input_int(&first_num, 1); 
    
    if (rc == OK)
    {
        rc = input_float(&second_num, 0);

        if (rc == OK)
        {
            divide(first_num, second_num, &result);
            print_result(result);
        }
    }

    return rc;
}
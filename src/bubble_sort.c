#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define SEE_HEX_FUCN
void die(const char *message)
{
    if(errno)
        perror(message);
    else
        printf("ERROR: %s\n", message);
    exit(1);
}

typedef int (*compare_cb)(int a ,int b);
/* using function pointer to realize bubble_sort */
int *bubble_sort(int *numbers, int count, compare_cb compare)
{
    int temp = 0;
    int i, j;
    i = j = 0;
    int *target = malloc(count * sizeof(int));
    if(!target)
        die("Memory error!\n");
    memcpy(target, numbers, count * sizeof(int));
    for(i = 0; i < count; i++)
    {
        for(j = 0; j < count - 1; j++)
        {
            if((compare(target[j], target[j+1])) > 0)
            {
                temp = target[j+1];
                target[j+1] = target[j];
                target[j] = temp;
            }
        }
    }
    return target;
}

int sorted_order(int a, int b)
{
    return a - b;

}

int reverse_order(int a, int b)
{
    return b - a;
}

void test_sorting(int *numbers, int count, compare_cb compare)
{
    int i = 0;
    int *sorted = bubble_sort(numbers, count, compare);

    if(!sorted)
        die("Memory errror.\n");
    
    for(i = 0; i < count; i++)
    {
        printf("%d ", sorted[i]);
    }
    printf("\n");
    free(sorted);
    #ifdef SEE_HEX_FUCN
        printf("The hex data of function compare is: \n");
        unsigned char *data = (unsigned char *)compare;
        for(i = 0; i < 15; i++) 
        {
            printf("%02x ", data[i]);
        } 
        printf("\n");
    #endif
}

int main(int argc, char *argv[])
{
    if(argc < 2)
        die("USAGE: bubble_sort 1 3 5 4 9");
    int count = argc - 1;
    char **inputs = argv + 1;
    int i = 0;
    printf("origin inputs are:  ");
    for(i = 0; i < count; i++)
        printf("%s ", inputs[i]);
    printf("\nsorted:\n");
    int *numbers = malloc(count * sizeof(int));
    if(!numbers)
        die("Memory error\n");
    for(i = 0; i < count; i++)
    {
        numbers[i] = atoi(inputs[i]);
    }
    // test_sorting(numbers, count, NULL);/* crush test */
    test_sorting(numbers, count, sorted_order);
    test_sorting(numbers, count, reverse_order);
    free(numbers);

    return 0;
}
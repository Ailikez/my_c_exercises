#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
typedef int element_type;
/* construct a node type of stack */
typedef struct Node
{
    element_type data;
    struct Node *pNext;
}NODE, *PNODE;
/* construct a stack type */
typedef struct stack
{
    PNODE pTop;
    PNODE pBottom;
}STACK, *PSTACK;

bool is_empty(PSTACK stack)
{
    if(stack->pTop == stack->pBottom)
        return true;
    else
        return false;
}

void clear_stack(PSTACK stack)
{
    if(is_empty(stack))
        printf("stack is already empty!!!\n");
    else
    {
        PNODE p = NULL;
        while(stack->pTop != stack->pBottom)
        {
            p = stack->pTop;
            stack->pTop = stack->pTop->pNext;
            free(p);
            p = NULL;
        }
    }
}

void destory_stack(PSTACK stack)
{
    clear_stack(stack);
    if(stack->pTop)
        free(stack->pTop);
}

void die(PSTACK stack, const char *message)
{
    destory_stack(stack);
    if(errno)
        perror(message);
    else
        printf("ERROR: %s\n", message);
    exit(1);
}

void create_stack(PSTACK stack)
{
    stack->pBottom = (NODE*)malloc(sizeof(NODE));
    if(NULL == stack->pBottom)
        die(stack, "Memory allocation failed!");
    stack->pTop = stack->pBottom;
    stack->pTop->data = 0;
    stack->pTop->pNext = NULL;
}

void push_stack(PSTACK stack, element_type data)
{
    PNODE p = (NODE*)malloc(sizeof(NODE));
    if(NULL == stack->pBottom)
        die(stack, "Memory allocation failed!");
    p->pNext = stack->pTop;
    p->data = data;
    stack->pTop = p;
}

bool pop_stack(PSTACK stack, element_type *value)
{
    if(is_empty(stack))
        die(stack, "stack is already empty!!!");
    PNODE p = stack->pTop;
    *value = p->data;
    stack->pTop = stack->pTop->pNext;
    free(p);
    p = NULL;

    return true;
}

void list_stack(PSTACK stack)  
{  
    PNODE p=stack->pTop;  
    printf("stack elements are: \n");  
    while(p!=stack->pBottom)  
    {
        printf("%d ",p->data);  
        p=p->pNext;  
    }
    printf("\n");  
}

STACK mystack;

int main(int argc, char * argv[])
{
    create_stack(&mystack);
    printf("push 1 into stack.\n");
    push_stack(&mystack, (element_type)1);
    list_stack(&mystack);
    printf("push 2 into stack.\n");
    push_stack(&mystack, (element_type)2);
    list_stack(&mystack);
    element_type val = 0;
    pop_stack(&mystack, &val);
    printf("pop %d out\n", val);
    list_stack(&mystack);
    printf("test if stack is empty:\n");
    printf("%d\n", is_empty(&mystack));
    list_stack(&mystack);
    printf("clear the stack now.\n");
    clear_stack(&mystack);
    list_stack(&mystack);

    destory_stack(&mystack);

    return 0;
}
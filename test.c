#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *ptr;

    

    ptr = malloc(10);
    char *p;
    p = ptr;

    ptr = "hello";

    printf("%s", p);
}
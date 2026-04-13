// Source - https://stackoverflow.com/q/9469790
// Posted by Vikram, modified by community. See post 'Timeline' for change history
// Retrieved 2026-04-13, License - CC BY-SA 3.0

#include<stdio.h>

int main()
{
    char *name = "Vikram";
    printf("%s\n",name);

    name[1]='s';
    printf("%s\n",name);
    return 0;
}

#include <stdio.h>

int main(void)
{
    char a[5];
    char *ptr;
    ptr=&a[0];
    void display(char *);
    scanf("%s", a);

    display(ptr);
}

void display(char *ptr)
{
    int i;
    for(i=0;i<5;i++)
    {
    printf("%c", *(ptr+i));
    }
}
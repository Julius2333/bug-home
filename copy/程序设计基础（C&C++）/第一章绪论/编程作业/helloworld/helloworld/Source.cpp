//#define DEBUG

#include <stdio.h>

#ifdef DEBUG
#include <stdlib.h>
#endif

int main(void)
{
    printf("hello! welcome to computer world!");

#ifdef DEBUG
    system("pause");
#endif

    return 0;
}
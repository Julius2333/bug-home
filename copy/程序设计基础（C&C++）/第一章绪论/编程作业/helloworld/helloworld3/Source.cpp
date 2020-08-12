//#define DEBUG3

#include <stdio.h>

#ifdef DEBUG3
#include <stdlib.h>
#endif

int main(void)
{
printf("Please display these words:\n\
1. press return keyboard to enter the game.\n\
2. press esc keyboard to exist the game.");

#ifdef DEBUG3
    system("pause");
#endif

    return 0;
}
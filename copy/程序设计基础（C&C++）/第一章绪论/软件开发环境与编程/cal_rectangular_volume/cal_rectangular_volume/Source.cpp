#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x, y, z;
    long sum;

    printf("Please input : x, y, z\r\n");
    scanf_s("%d, %d, %d", &x, &y, &z);
    sum = x * y * z;
    printf("sum = %d", sum);

    system("pause");
    return 0;
}
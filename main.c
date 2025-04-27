#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

typedef struct NODE{
    int data;
    struct NODE *leftChild;
    struct NODE *rightChild;
}NODE;


int main(void)
{
    int n, i;
    printf("Hello Niagra Fall!\nDe cate ori sa repet un mesaj?");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Miaw Miaw\n");
    }

    return 0;
}
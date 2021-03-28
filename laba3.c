#include <stdio.h>

#define ARRAY_SIZE 4

void transp(short int *);

int main(void)
{
    int i, j;
    short int a, array[4][4]={11, 12, 13, 14, 
                              21, 22, 23, 24, 
                              31, 32, 33, 34, 
                              41, 42, 43, 44};

   

    for(i=0; i<ARRAY_SIZE; i++)
    {
        for(j=0; j<ARRAY_SIZE; j++)
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    transp(&array[0][0]);

    for(i=0; i<ARRAY_SIZE; i++)
    {
        for(j=0; j<ARRAY_SIZE; j++)
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void transp(short int *data)
{
    char a=ARRAY_SIZE-1;
    long int b=ARRAY_SIZE*2;
    char c=ARRAY_SIZE;

    __asm__
    (
        "movq %1, %%r8\n\t"
        "movq %2, %%r9\n\t"
        "movq $2, %%r10\n\t"
        "movq %%r8, %%r11\n\t"

        "m1:\n\t"
        "xorl %%ebx, %%ebx\n\t"
        "xorl %%eax, %%eax\n\t"
        "addq %%r10, %%r8\n\t"
        "movw %%cx, %%bx\n\t"
        "movw %%si, %%ax\n\t"
        "subw %%bx, %%ax\n\t"
        "movw %%ax, %%bx\n\t"
        "movq %%rcx, %%r13\n\t"

        "m2:\n\t"
        "jrcxz m3\n\t"
        "decl %%ecx\n\t"
        "movq %%r11, %%r12\n\t"
        "mulw %%si\n\t"
        "movw $2, %%di\n\t"
        "mulw %%di\n\t"
        "addq %%rax, %%r12\n\t"
        "addq %%r10, %%r12\n\t"
        "subq $2, %%r12\n\t"
        "movw (%%r8), %%di\n\t"
        "movw (%%r12), %%dx\n\t"
        "movw %%di, (%%r12)\n\t"
        "movw %%dx, (%%r8)\n\t"
        "addq $2, %%r8\n\t"
        "incw %%bx\n\t"
        "movw %%bx, %%ax\n\t"
        "jmp m2\n\t"
        
        "m3:\n\t"
        "movq %%r13, %%rcx\n\t"
        "addq $2, %%r10\n\r"
        "movq %%r11, %%r8\n\t"
        "addq %%r9, %%r8\n\t"
        "addq %%r9, %%r9\n\t"
        "loop m1\n\t"
        :
        :"c"(a), "r"(data), "r"(b), "S"(c)
        :
    );
}

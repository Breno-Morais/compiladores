#include <stdio.h>

// char* vasco() {
//     return "are you";
// }
int x = 6;

int main() {
    // printf("seguro\n");
    // printf("%c\n", 'a');
    // printf("%d\n", 5);
    // printf("%d\n", x);
    // printf("%.2f\n", 5.12345);

    x = x * x;
}

// gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm
// cd ./exp/; gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm; cd ..
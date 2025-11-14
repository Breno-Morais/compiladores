#include <stdio.h>

// char* vasco() {
//     return "are you";
// }
int x = 1;
int y = 1;
int z = 1;

int main() {
    z = x && y;
    // printf("seguro\n");
    // printf("%c\n", 'a');
    // printf("%d\n", 5);
    // printf("%d\n", x);
    // printf("%.2f\n", 5.12345);

    // printf("%s\n", (x) ? "true" : "false");
}

// gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm
// cd ./exp/; gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm; cd ..
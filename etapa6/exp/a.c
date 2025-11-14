#include <stdio.h>

// char* vasco() {
//     return "are you";
// }
int x = 1;

int main() {
    scanf("%d", &x);
}

// gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm
// cd ./exp/; gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm; cd ..
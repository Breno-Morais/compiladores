#include <stdio.h>

int x = 11231;

int main() {
    x = x / 8;
}

// gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm
/*
cd ./exp/; gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm; cd ..
*/
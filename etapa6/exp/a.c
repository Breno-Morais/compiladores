#include <stdio.h>

int v[3] = {'a', 0, 'c'};
int x = 1;

int main() {
    v[1] = v[0];
    x = v[3];
}

// gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm
/*
cd ./exp/; gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm; cd ..
*/
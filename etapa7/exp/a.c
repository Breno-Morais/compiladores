#include <stdio.h>

int v[3] = {'a', 0, 'c'};
int z = 2;
int x = 1;

int main() {
    x = v[x];
}

// gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm
/*
cd ./exp/; gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm; cd ..
*/
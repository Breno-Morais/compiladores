#include <stdio.h>

int x = 5;
int y = 2;

int A() {
    int dga = 13;
    return dga + 'A';
}

int B(int b1, char b2, int b3, int b4, int b5, int b6) {
    return A(b1) + b2 + b3;
}

int main() {
    x = A();
    y = B(x, 5, 4, 1, 2, 4);
}


// gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm
// cd ./exp/; gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm; cd ..
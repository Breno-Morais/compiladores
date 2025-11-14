#include <stdio.h>

// char* vasco() {
//     return "are you";
// }
int x = 1;
int y = 1;
int z = 1;

int A() {
    // print "A\n";
    return 65;
}

int B() {
    // print "B\n";
    return 66;
}

int main() {
    x = A();
    // print "main\n";
    y = B();
}

// gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm
// cd ./exp/; gcc -S a.c -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm; cd ..
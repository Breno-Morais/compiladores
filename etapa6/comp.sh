#!/bin/bash

make
./etapa6 tests/$1
gcc tests/$1.s
./a.out
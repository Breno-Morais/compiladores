#!/bin/bash

./etapa7 tests/$1
gcc tests/$1.s
./a.out
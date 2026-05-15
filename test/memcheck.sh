#!/bin/bash
gcc -g -o program src/main.c
valgrind --leak-check=full -error-exitcode=1 ./program
if [$? -eq 0]; then
    echo"valgrind said yes!!"
else
    echo"valgrind said no!!"
    exit 1
fi

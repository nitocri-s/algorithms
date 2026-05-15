#!/bin/bash
gcc -g -o program src/main.c
hyperfine --warmup 3 './program' --export-markdown result.md
echo "hyperfine is done!!!!!!"

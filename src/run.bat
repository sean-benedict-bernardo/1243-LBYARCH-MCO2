@echo off

nasm -f win64 kernel.asm
gcc -c main.c -o main.c.obj -m64
gcc main.c.obj kernel.obj -o main.exe -m64
main.exe
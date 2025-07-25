@echo off
@REM for /l %%i in (1,1,30) do gcc -Wall -std=c99 main.c -o main.exe && main.exe    

nasm -f win64 kernel.asm
gcc -c main.c -o main.c.obj -m64
gcc main.c.obj kernel.obj -o main.exe -m64
main.exe
@echo off


nasm -f win64 kernel.asm
gcc -c main.c -o main.c.obj -m64
gcc main.c.obj kernel.obj -o main.exe -m64

echo.
for /l %%i in (1,1,30) do (
    echo ==============================
    echo.
    echo Running %%i
    echo.
    main.exe
    echo.
)
echo ==============================

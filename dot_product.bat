nasm -f win64 dot_product.asm
gcc -c main.c -o main.obj -m64
gcc main.obj dot_product.obj -o main.exe -m64
main.exe
pause
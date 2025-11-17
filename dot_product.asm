; assuming C call will be float dot_product(long long int, float array, float array)

section .data
zero dd 0.0
section .text
default rel
bits 64
global dot_product
dot_product:
    movss xmm0, [zero]
    cmp rcx, 0
    jle done
    
    L1:
        movss xmm4, [rdx]
        movss xmm5, [r8]
        mulss xmm4, xmm5
        addss xmm0, xmm4
        add rdx, 4
        add r8, 4
        dec rcx
        jnz L1
    
    done:
    ret
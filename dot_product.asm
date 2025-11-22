; assuming C call will be float dot_product(long long int, float array, float array)
; example: dot_product(length_of_vectors, vector_A, vector_B)

; thereafter, these get converted to our registers:
; first  param (long long int) =  rcx 
; second param (float array)   =  rdx
; third  param (float array)   =  r8

section .data
zero dd 0.0

section .text
default rel
bits 64
global dot_product

dot_product:
    movss xmm0, [zero]  ; initialize our accumulator xmm0 (this is our sdot) to zero via move scalar single precision 
    cmp rcx, 0          ; check if length left to process is zero
    jle done            ; jump, if so
    
    L1:
        movss xmm4, [rdx]   ; store current scalar Ai to our scratch register xmm4
        movss xmm5, [r8]    ; store current scalar Bi to our scratch register xmm4
        mulss xmm4, xmm5    ; xmm4 = Ai * Bi
        addss xmm0, xmm4    ; accumulator xmm0 += xmm4
        add rdx, 4          ; i+=1 preparation for Ai
        add r8, 4           ; i+=1 preparation for Bi
        dec rcx             ; length left to process-=1
        jnz L1              ; rinse and repeat.
    
    done:
        ret
global testAsm
global memmove_asm

%define str_ptr_1 rsi
%define str_ptr_2 rdi
%define str_len rdx
section .text
testAsm:
    mov eax, 7
    ret
memmove_asm:
    ; rdi - str_ptr_1 (src)
    ; rsi - str_ptr_2 (dst)
    ; rdx - str_len
    ; str_ptr_1 должен быть в rsi, str_ptr_2 должен быть rdi
    mov rax, rdi
    mov rdi, rsi 
    mov rsi, rax

    cmp str_ptr_1, str_ptr_2
    ; Если адреса строк равны, то копирование не нужно
    je memmove_asm_exit 
    ; Есди адрес dst > src, то записываем слева направо
    jg forward_memmove_asm
    
    ; В rax записываем str_ptr_1 + str_len
    mov rax, str_ptr_1
    add rax, str_len

    cmp rax, str_ptr_2
    ; Если конец str_ptr_1 Болше dst, то строки пересекаются, записываем справа налево
    jg backward_memmove_asm
    ; Если конец строки str_ptr_1 <= dst, то строки не пересекаются, записываем слева направо
    jmp forward_memmove_asm

    backward_memmove_asm:
        mov rcx, str_len

        add str_ptr_1, str_len
        add str_ptr_2, str_len

        dec str_ptr_1
        dec str_ptr_2

        std
        rep movsb
        cld

        jmp memmove_asm_exit

    forward_memmove_asm:

        mov rcx, str_len
        rep movsb
        jmp memmove_asm_exit

    memmove_asm_exit:
    ret
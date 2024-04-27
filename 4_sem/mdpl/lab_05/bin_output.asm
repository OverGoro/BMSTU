.386
OK          equ 0
ERR_IO      equ 1
ERR_COMMAND equ 2

PUBLIC num_print_signed_bin_16
PUBLIC num_print_unsigned_bin_16

BIN_OUTPUT_CS SEGMENT PARA PUBLIC USE16 'CODE'
    assume cs:BIN_OUTPUT_CS
; вывод знакового 16 битного двоичного числа
; Параметры
; word num[out] - число
; far вызов
num_print_signed_bin_16:
    num_offset equ bp + 6
    num equ word ptr ss:[num_offset]
    push bp
    mov bp, sp
    
    mov ah, 02h

    mov cx, 15
    mov bx, num
    shl bx, 1
    jnc num_print_signed_bin_16_loop
    num_print_signed_bin_16_minus:
        mov dl, '-'
        int 21h
        mov bx, num
        neg bx
        shl bx, 1
        jmp num_print_signed_bin_16_loop

    num_print_signed_bin_16_loop:
        shl bx, 1
        jnc num_print_signed_bin_16_loop_0
        num_print_signed_bin_16_loop_1:
            mov dl, '1'
            int 21h
            jmp num_print_signed_bin_16_loop_end
        num_print_signed_bin_16_loop_0:
            mov dl, '0'
            int 21h
            jmp num_print_signed_bin_16_loop_end
        num_print_signed_bin_16_loop_end:
            loop num_print_signed_bin_16_loop
    mov dl, 10
    int 21h

    mov dl, 13
    int 21h

    pop bp
    retf

; вывод беззнакового 16 битного двоичного числа
; Параметры
; word num[out] - число
; far вызов
num_print_unsigned_bin_16:
    num_offset equ bp + 6
    num equ word ptr ss:[num_offset]
    push bp
    mov bp, sp
    
    mov ah, 02h

    mov cx, 16
    num_print_unsigned_bin_16_loop:
        dec cx
        bt num, cx
        inc cx
        jnc num_print_unsigned_bin_16_loop_0
        num_print_unsigned_bin_16_loop_1:
            mov dl, '1'
            int 21h
            jmp num_print_unsigned_bin_16_loop_end
        num_print_unsigned_bin_16_loop_0:
            mov dl, '0'
            int 21h
            jmp num_print_unsigned_bin_16_loop_end
        num_print_unsigned_bin_16_loop_end:
            loop num_print_unsigned_bin_16_loop
    mov dl, 10
    int 21h

    mov dl, 13
    int 21h

    pop bp
    retf

BIN_OUTPUT_CS ENDS
END
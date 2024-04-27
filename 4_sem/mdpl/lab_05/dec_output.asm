OK          equ 0
ERR_IO      equ 1
ERR_COMMAND equ 2

PUBLIC num_print_unsigned_dec_16


DEC_OUTPUT_CS SEGMENT PARA PUBLIC USE16 'CODE'
    assume cs:DEC_OUTPUT_CS
; вывод беззнакового 8-битного 16-ричного числа
; Параметры
; word num[in] - число
; far вызов
num_offset equ bp + 6
num equ word ptr ss:[num_offset]
num_print_unsigned_dec_16:
    push bp
    mov bp, sp

    mov ax, num
    mov dx, 0
    mov cx, 0

    mov bx, 10
    num_print_unsigned_dec_16_loop_1:
        mov dx, 0
        div bx
        add dl, '0'
        push dx
        inc cx
        cmp ax, 0
        jg num_print_unsigned_dec_16_loop_1

    mov ah, 02h
    num_print_unsigned_dec_16_loop_2:
        pop dx
        int 21h
        loop num_print_unsigned_dec_16_loop_2

    mov dl, 10
    int 21h
    mov dl, 13
    int 21h
    
    pop bp
    retf

DEC_OUTPUT_CS ENDS
END
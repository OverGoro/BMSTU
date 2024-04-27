.386
OK          equ 0
ERR_IO      equ 1
ERR_COMMAND equ 2

PUBLIC num_print_unsigned_oct_16

OCT_OUTPUT_CS SEGMENT PARA PUBLIC USE16 'CODE'
    assume cs:OCT_OUTPUT_CS
; вывод беззнакового 16-битного восьмиричного числа
; Параметры
; word num[out] - число
; far вызов
num_print_unsigned_oct_16:
    num_offset equ bp + 6
    num equ word ptr ss:[num_offset]
    push bp
    mov bp, sp
    
    mov ah, 02h
    mov dh, 0

    mov bx, num
    mov dl, bh

    and dl, 10000000b
    shr dl, 7
    add dl, '0'

    shl bx, 1
    int 21h
    mov cx, 5
    num_print_oct_16_loop:
        mov dl, bh
        and dl, 11100000b
        shr dl, 5
        add dl, '0'
        int 21h
        shl bx, 3
        loop num_print_oct_16_loop

    mov dl, 10
    int 21h
    mov dl, 13
    int 21h

    pop bp
    retf
OCT_OUTPUT_CS ENDS
END
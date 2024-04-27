.386
OK          equ 0
ERR_IO      equ 1
ERR_COMMAND equ 2

PUBLIC num_print_signed_hex_8

HEX_OUTPUT_CS SEGMENT PARA PUBLIC USE16 'CODE'
    assume cs:HEX_OUTPUT_CS
; вывод беззнакового 8-битного 16-ричного числа
; Параметры
; word num[out] - число
; far вызов
num_print_signed_hex_8:
    num_offset equ bp + 6
    num equ word ptr ss:[num_offset]
    push bp
    mov bp, sp

    mov ah, 02h

    mov bx, num
    num_print_signed_hex_8_sign:
    shl bl, 1
    jnc num_print_signed_hex_8_digits_1
    mov dl, '-'
    int 21h
    mov bx, num
    neg bx
    shl bx, 1
    num_print_signed_hex_8_digits_1:
        mov dl, bl
        and dl, 11100000b
        shr dl, 5
        add dl, '0'
        cmp dl, '9'
    num_print_signed_hex_8_digits_2:
        shl bl, 3
        int 21h
        mov dl, bl
        and dl, 11110000b
        shr dl, 4
        add dl, '0'
        cmp dl, '9'
        jle num_print_signed_hex_8_digits_end
        sub dl, '9'
        add dl, 'A' - 1
    num_print_signed_hex_8_digits_end:
    int 21h

    mov dl, 10
    int 21h
    mov dl, 13
    int 21h

    pop bp
    retf
HEX_OUTPUT_CS ENDS
END
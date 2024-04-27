.386
OK          equ 0
ERR_IO      equ 1
ERR_COMMAND equ 2
INPUT_INTERRUPTED equ 3

PUBLIC num_input

NUM_INPUT_CS SEGMENT PARA PUBLIC USE16 'CODE'
    assume cs:NUM_INPUT_CS
; Ввод знака двоичного числа
; Параметры:
; word err[out] - Код ошибки
; word num[in, out] - число
; word cur_bit [in, out]- номер текущего бита
; word less_zero [out] - меньше/больше нуля
; near вызов
num_input_sign:
    err_offset equ bp + 4
    err equ word ptr ss:[err_offset]
    num_offset equ bp + 6
    num equ word ptr ss:[num_offset]
    cur_bit_offset equ bp + 8
    cur_bit equ word ptr ss:[cur_bit_offset]
    less_zero_offset equ bp + 10
    less_zero equ word ptr ss:[less_zero_offset]
    ; Сохранение старого bp
    push bp
    ; Установка bp на вершину стека
    mov bp, sp

    mov ah, 01
    int 21h

    cmp al, '-'
    je num_input_sign_minus

    cmp al, '0'
    je num_input_sign_0

    cmp al, '1'
    je num_input_sign_1

    cmp al, '+'
    je num_input_sign_plus

    jmp num_input_sign_error

    num_input_sign_minus:   ; Введен знак -
        mov less_zero, 15
        mov err, OK
        jmp num_input_sign_end
    num_input_sign_plus:    ; Введен знак +
        mov less_zero, 0
        btr num, 15
        mov err, OK
        jmp num_input_sign_end
    num_input_sign_1:       ; Введено 1
        mov less_zero, 0
        btr num, 15
        bts num, 14
        inc cur_bit
        mov err, OK
        jmp num_input_sign_end
    num_input_sign_0:       ; Введено 0
        mov less_zero, 0
        btr num, 15
        btr num, 14
        inc cur_bit
        mov err, OK
        jmp num_input_sign_end
    num_input_sign_error:   ; Введен неправильный знак
        mov err, ERR_IO
        jmp num_input_sign_end
    num_input_sign_end:
        pop bp
        ret

; Ввод цифры двоичного числа
; Параметры:
; word err[out] - Код ошибки
; word num[out] - число
; word cur_bit [in]- номер текущего бита
; near
num_input_digit:
    err_offset equ bp + 4
    err equ word ptr ss:[err_offset]
    num_offset equ bp + 6
    num equ word ptr ss:[num_offset]
    cur_bit_offset equ bp + 8
    cur_bit equ word ptr ss:[cur_bit_offset]
    push bp
    mov bp, sp

    mov ah, 01
    int 21h

    cmp al, '0'
    je num_input_digit_0

    cmp al, '1'
    je num_input_digit_1

    cmp al, 13
    je num_input_digit_enter

    jne num_input_digit_error

    num_input_digit_1:       ; Введено 1
        push cx
        mov cx, 14
        sub cx, cur_bit
        bts num, cx
        pop cx
        mov err, OK
        jmp num_input_digit_end
    num_input_digit_0:       ; Введено 0
        push cx
        mov cx, 14
        sub cx, cur_bit
        btr num, cx
        pop cx

        mov err, OK
        jmp num_input_digit_end
    num_input_digit_error:   ; Некорректный ввод
        mov err, ERR_IO
        jmp num_input_digit_end
    num_input_digit_enter:
        push cx

        mov err, INPUT_INTERRUPTED
        bt num, 15
        btr num, 15
        mov cx, 15
        sub cx, cur_bit

        shr num, cl

        pop cx
        jnc num_input_digit_end
        bts num, 15
    num_input_digit_end:
        pop bp
        ret

; Чтение знакового двоичного 16 битного числа
; Параметры
; word err[out] - код ошибки
; word num[out] - прочитанное число
; far вызов
num_input:
    err_offset equ bp + 6
    err equ word ptr ss:[err_offset]
    num_offset equ bp + 8
    num equ word ptr ss:[num_offset]
    push bp
    mov bp, sp

    mov num, 0
    mov cx, 0   ; Текущий бит
    mov dx, 0   ; 0 - больше нуля, 1 - меньше нуля

    ; ввод знака
    push dx
    push cx
    push num
    push err
    call num_input_sign
    pop err
    pop num
    pop cx
    pop dx

    ; проверка ошибки
    cmp err, OK
    jne num_input_end


    num_input_loop:
        num_input_loop_digit:
            push cx
            push num
            push err
            call num_input_digit
            pop err
            pop num
            pop cx

            cmp err, OK 
            je num_input_loop_end

            cmp err, INPUT_INTERRUPTED
            jne num_input_end

            mov err, OK
            jmp num_input_set_num_sign

        num_input_loop_end:
            inc cx
            cmp cx, 15
            jl num_input_loop
    
    num_input_set_num_sign:
    cmp dx, 0
    je num_input_end
    neg num

    num_input_end:
    mov ah, 02h
    mov dl, 10
    int 21h
    mov dl, 13
    int 21h
    pop bp
    retf
NUM_INPUT_CS ENDS

END


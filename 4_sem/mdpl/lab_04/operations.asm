public modify_matrix

MATRIX_SEG SEGMENT PARA COMMON 'DATA'
    matrix_rows byte 0
    matrix_cols byte 0
    matrix_data db 81 dup(0)
MATRIX_SEG ENDS

CS_EDIT_MATRIX SEGMENT PARA PUBLIC 'CODE'
    assume cs:CS_EDIT_MATRIX, ds:MATRIX_SEG

mov ax, MATRIX_SEG
mov ds, ax

; Добавляет к числу в ax 1, если число четное
; Убавляет число на 1, если нет
modify_num:
    mov dx, ax
    and dx, 1   ; Проверка четности ax

    jz modify_num_even ; Число четное
    jmp modify_num_odd ; Число нечетное
    modify_num_even:
        cmp ax, 9
        jge modify_num_even_overflow
        modify_num_even_inc:    ; Число < 9, +1
            inc ax
            jmp modify_num_end
        modify_num_even_overflow:  ; Число равно 9, в результутае 0 
            mov ax, 0
            jmp modify_num_end
    modify_num_odd:
        cmp ax, 0
        jle modify_num_odd_overflow
        modify_num_odd_dec:         ; Число !=0, -1
            dec ax
            jmp modify_num_end
        modify_num_odd_overflow:    ; Число = 0, получится 1
            mov ax, 1
            jmp modify_num_end
    modify_num_end:
        ret

; Применение modify_num к каждому элементу матрицы
modify_matrix:
    mov cx, 0
    mov cl, [matrix_rows]
    mov di, 0
    mov ax, 0
    mov bx, 0
    matrix_loop:
        mov bl, 0
        row_loop:
            mov al, [matrix_data + bx + di]
            call modify_num ; модификация числа
            mov [matrix_data + bx + di], al

            inc bl  ; Переход к следующему элементу
            cmp bl, [matrix_cols]
            jl row_loop    ; Следющих шаг по строке

            add di, 9  ; Переход к следующей строке
            dec cx  ; Уменьшение количества оставшихся строк
            jnz matrix_loop ; Следющий шаг по строкам матрицы
    retf
    
CS_EDIT_MATRIX ENDS

END


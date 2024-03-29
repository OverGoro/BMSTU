public print_matrix, print_matrix_message, print_result_message

MATRIX_SEG SEGMENT PARA COMMON 'DATA'
    matrix_rows byte 0
    matrix_cols byte 0
    matrix_data db 81 dup(0)
MATRIX_SEG ENDS

DS_MESSAGES SEGMENT PARA PUBLIC 'DATA'
    matrix_out_message db  "Matrix: $"
    matrix_result_message db "Result: $"
DS_MESSAGES ENDS

CS_OUTPUTT_MATRIX SEGMENT PARA PUBLIC 'CODE'
    assume cs:CS_OUTPUTT_MATRIX, ds:MATRIX_SEG

print_matrix_message:
    mov ax, DS_MESSAGES
    mov ds, ax
    mov ah, 09h
    mov dx, OFFSET matrix_out_message
    int 21h
    retf
print_result_message:
    mov ax, DS_MESSAGES
    mov ds, ax
    mov ah, 09h
    mov dx, OFFSET matrix_result_message
    int 21h
    retf

print_new_line: ; Переход на новую строку
    mov ah, 02h
    mov dl, 13 
    int 21h    
    mov dl, 10 
    int 21h    
    ret

print_matrix:   ; вывод матрицы
    mov ax, MATRIX_SEG
    mov ds, ax

    mov cx, 0
    mov cl, [matrix_rows]
    mov di, 0
    mov bx, 0
    mov ah, 02h;
    matrix_loop:
        mov bl, 0
        call print_new_line
        row_loop:
            ; Вывод элемента
            mov dl, [matrix_data + bx + di]
            add dl, '0'
            int 21h
            mov dl, ' '
            int 21h

            inc bl  ; Переход к следующему элементу
            cmp bl, [matrix_cols]
            jl row_loop    ; Следющих шаг по строке

            add di, 9  ; Переход к следующей строке
            dec cx  ; Уменьшение количества оставшихся строк
            jnz matrix_loop ; Следющий шаг по строкам матрицы
    call print_new_line
    retf
 

CS_OUTPUTT_MATRIX ENDS
END

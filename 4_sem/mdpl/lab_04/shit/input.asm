EXTRN matrix_rows:byte, matrix_cols:byte, matrix_data:byte

PUBLIC read_matrix

MATRIX_SEG SEGMENT PARA COMMON 'DATA'
    
MATRIX_SEG ENDS

DS_INPUT_MESSAGES SEGMENT PARA PUBLIC 'DATA'
    MATRIX_ROWS_MESSAGE db "Enter rows num: $"
    MATRIX_COLS_MESSAGE db "Enter cols num: $"
    ERR_MESSAGE db "Enter 1-9!!!$"
DS_INPUT_MESSAGES ENDS


DS_INPUT_PARAMS SEGMENT PARA PUBLIC 'DATA'
    CUR_ROW byte 0
    CUR_COL byte 0
DS_INPUT_PARAMS ENDS


CS_INPUT SEGMENT PARA PUBLIC 'CODE'
    assume cs:CS_INPUT, ds:MATRIX_SEG

print_new_line: ; Вывод новой строки
    mov ah, 02h
    mov dl, 13 
    int 21h    
    mov dl, 10 
    int 21h    
    ret

print_err:      ; Вывод сообщения об ошибке
    assume ds:DS_INPUT_MESSAGES
    mov ax, DS_INPUT_MESSAGES
    mov ds, ax
    mov ah, 09
    mov dx, OFFSET ERR_MESSAGE
    int 21h
    ret

print_cur_id:   ; Вывод индекса текущего элмента матрицы
    assume ds:DS_INPUT_PARAMS
    mov ax, DS_INPUT_PARAMS
    mov ds, ax

    ; Вывод строки
    mov ah, 02h       
    mov dl, [CUR_ROW]
    add dl, '0'       
    int 21h           

    ; Вывод пробела
    mov dl, ' '        
    int 21h            

    ; Вывод столбца
    mov ah, 02h       
    mov dl, [CUR_COL]
    add dl, '0'       
    int 21h           

    ; Вывод двоеточия
    mov dl, ':'        ; Двоеточие
    int 21h            ; Вывод символа
    ret

reset_cur_id:   ; Зануление индекса текущего элемента
    assume ds:DS_INPUT_PARAMS
    mov ax, DS_INPUT_PARAMS
    mov ds, ax
    mov [CUR_ROW], 0
    mov [CUR_COL], 0
    ret

inc_cur_id:     ; Увеличение индекса текущего элемента
    assume ds:MATRIX_SEG
    ; Сохранение размера строки в bx
    mov ax, MATRIX_SEG
    mov ds, ax
    mov bl, [matrix_cols]

    ; Увеличение индекса текщего элемента
    mov ax, DS_INPUT_PARAMS
    mov ds, ax

    ; Увеличение столбца
    inc_cur_id_col:
        mov al, [CUR_COL]
        inc al
        mov [CUR_COL], al
        cmp al, bl
        jb inc_cur_id_end ; если индекс остался в пределах текущей строки, то завершить inc
    ; Увеличение строки
    inc_cur_id_row:
        mov al, [CUR_ROW]
        inc al
        mov [CUR_ROW], al
    inc_cur_id_end:
        ret


read_matrix_size:
    assume ds:MATRIX_SEG
    read_rows_num:
        ; Вывод приглашения
        mov ax, DS_INPUT_MESSAGES
        mov ds, ax

        mov ah, 09
        mov dx, OFFSET MATRIX_ROWS_MESSAGE
        int 21h

        ; Ввод числа
        mov ah, 01
        int 21h    

        ; Проверка, что введено 1-9
        read_rows_check_less_1:
            cmp al, '1'
            jnb read_rows_check_more_9
            call print_new_line
            call print_err
            call print_new_line
            jmp read_rows_num 

        read_rows_check_more_9:
            cmp al, '9'   
            jna read_rows_succes
            call print_new_line
            call print_err
            call print_new_line 
            jmp read_rows_num 

        ; Проверка пройдена
        read_rows_succes:
            mov dl, al        
            mov ax, MATRIX_SEG
            mov ds, ax
            sub dl, '0'
            mov bx, OFFSET matrix_rows
            mov [bx], dl

    ; Переход на новую строку
    call print_new_line

    read_cols_num:
        ; Вывод приглашения
        mov ax, DS_INPUT_MESSAGES
        mov ds, ax

        mov ah, 09
        mov dx, OFFSET MATRIX_COLS_MESSAGE
        int 21h

        ; Ввод числа
        mov ah, 01
        int 21h    

        ; Проверка, что введено 1-9
        read_cols_check_less_1:
            cmp al, '1'
            jnb read_cols_check_more_9
            call print_new_line
            call print_err
            call print_new_line
            jmp read_cols_num 

        read_cols_check_more_9:
            cmp al, '9'   
            jna read_cols_succes
            call print_new_line
            call print_err
            call print_new_line 
            jmp read_cols_num 

        ; Проверка пройдена
        read_cols_succes:
            mov dl, al        
            mov ax, MATRIX_SEG
            mov ds, ax
            sub dl, '0'
            mov bx, OFFSET matrix_cols
            mov [bx], bl
    call print_new_line
    ret

read_matrix_data: ; Чтение элемеентов матрицы
    assume ds:MATRIX_SEG

    mov ax, MATRIX_SEG
    mov ds, ax

    ; Вычисление числа элементов в матрице
    mov al, [matrix_rows]
    mov bl, [matrix_cols]
    mul bl

    mov cx, ax
    ; Обнуление индекса текущего элемента
    call reset_cur_id

    ; Чтение элементов 
    read_element_cycle:
        read_element:           ; Ввод элемента
            call print_cur_id   ; Вывод приглашения 
            mov ah, 01          ; Ввод числа
            int 21h    
        ; Проверки введенного элемента
        read_element_check_less_1:
            cmp al, '0'
            jnb read_element_check_more_9
            call print_new_line
            call print_err
            call print_new_line
            jmp read_element

        read_element_check_more_9:
            cmp al, '9'   
            jna read_element_succes
            call print_new_line
            call print_err
            call print_new_line 
            jmp read_element
        read_element_succes:
            mov dl, al
            mov ax, MATRIX_SEG
            mov ds, ax
            
            mov [matrix_data], dl          ; Запись значения bl по вычисленному адресу

            call print_new_line
            call inc_cur_id
        loop read_element_cycle
    ret
read_matrix:
    call read_matrix_size
    call read_matrix_data
    retf

CS_INPUT ENDS

END

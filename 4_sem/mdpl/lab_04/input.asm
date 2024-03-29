public read_matrix


DS_MESSAGES SEGMENT PARA PUBLIC 'DATA'
    matrix_rows_message db  "Enter rows num: $"
    matrix_cols_message db  "Enter cols num: $"
    err_message         db  "Enter 1-9!!!$"
DS_MESSAGES ENDS

MATRIX_INPUT_PARAMS SEGMENT PARA PUBLIC 'DATA'
    cur_element_column  byte    0
    cur_element_row     byte    0
MATRIX_INPUT_PARAMS ENDS

MATRIX_SEG SEGMENT PARA COMMON 'DATA'
    matrix_rows byte 0
    matrix_cols byte 0
    matrix_data db 81 dup(0)
MATRIX_SEG ENDS

CS_READ_MATRIX SEGMENT PARA PUBLIC 'CODE'
    assume cs:CS_READ_MATRIX
print_new_line: ; Вывод новой строки
    mov ah, 02h
    mov dl, 13 
    int 21h    
    mov dl, 10 
    int 21h    
    ret

print_err: ; Вывод сообщения об ошибке
    mov ax, DS_MESSAGES
    mov ds, ax
    mov dx, OFFSET err_message
    mov ah, 09h
    int 21h
    ret
print_cols_input_message: ; Вывод сообщения 
    mov ax, DS_MESSAGES
    mov ds, ax
    mov dx, OFFSET matrix_cols_message
    mov ah, 09h
    int 21h
    ret
print_rows_input_message: ; Вывод приглашения к вводу количества строк матрицы
    mov ax, DS_MESSAGES
    mov ds, ax
    mov dx, OFFSET matrix_rows_message
    mov ah, 09h
    int 21h
    ret

read_rows_num: ; Ввод количества строк матрицы
    call print_rows_input_message

    ; Ввод символа
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
        mov ds:[matrix_rows], dl
    ret
read_cols_num:
    call print_cols_input_message

    ; Ввод символа
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
        mov ds:[matrix_cols], dl
    ret
; Индекс элемента в матрицу
print_cur_id:   ; Вывод индекса элемента матрицы
    mov ax, MATRIX_INPUT_PARAMS
    mov es, ax
    ; Вывод текущей строки
    mov ah, 02h       
    mov dl, es:[cur_element_row]
    add dl, '0'       
    int 21h           

    ; Вывод пробела
    mov dl, ' '        
    int 21h            

    ; Вывод текущего столбца
    mov ah, 02h       
    mov dl, es:[cur_element_column]
    add dl, '0'       
    int 21h           

    ; Вывод двоеточия
    mov dl, ':'        ; Двоеточие
    int 21h            ; Вывод символа
    ret

null_cur_id:    ; Занулить индекс текущего элемента
    mov ax, MATRIX_INPUT_PARAMS
    mov es, ax
    mov dh, 0
    mov es:[cur_element_row], dh
    mov es:[cur_element_column], dh
    ret
inc_cur_id:     ; Увеличить индекс текущего элемента
    mov ax, MATRIX_INPUT_PARAMS
    mov es, ax

    mov ax, MATRIX_SEG
    mov ds, ax

    mov dl, es:[cur_element_column]
    mov dh, ds:[matrix_cols]
    inc_cur_id_old_line:    ;  Перехода на новую строку не было
        inc dl
        inc bx ; Инкремент адреса текущего элемента
        mov es:[cur_element_column], dl
        cmp dl, dh
        jge inc_cur_id_new_line
        jmp inc_cur_id_end
    inc_cur_id_new_line:    ; Произошел переход на новую строку
        mov es:[cur_element_column], 0
        mov dl, es:[cur_element_row]
        inc dl
        mov es:[cur_element_row], dl
        ; Вычисление нового адреса
        mov ax, 9
        mul es:[cur_element_row]
        add ax, 2
        mov bx, ax
    inc_cur_id_end:
    ret

get_matrix_elements_num: ; Получение количества элементов матрицы
    mov ax, MATRIX_SEG
    mov ds, ax
    mov ax, 00h
    mov cx, 00h
    mov al, ds:[matrix_rows]
    mov cl, ds:[matrix_cols]
    mul cx
    mov cx, ax
    ret

read_matrix_element:    ; чтение текщего элемента матрицы
    call print_cur_id
    ; Ввод символа
    mov ah, 01
    int 21h    

    ; Проверка, что введено 1-9
    read_matrix_element_check_less_0:
        cmp al, '0'
        jnb read_matrix_element_check_more_9
        call print_new_line
        call print_err
        call print_new_line
        jmp read_matrix_element

    read_matrix_element_check_more_9:
        cmp al, '9'   
        jna read_matrix_element_succes
        call print_new_line
        call print_err
        call print_new_line 
        jmp read_matrix_element

    ; Проверка пройдена
    read_matrix_element_succes:
        mov dl, al        
        mov ax, MATRIX_SEG
        mov ds, ax
        sub dl, '0'
        mov ds:[bx], dl
    ret

read_matrix_elements: ; Чтение элементов матрицы
    call null_cur_id
    mov ax, MATRIX_SEG
    mov ds, ax
    
    mov bx, OFFSET matrix_data
    call get_matrix_elements_num
    read_element_loop:
        call read_matrix_element
        call inc_cur_id
        call print_new_line
        loop read_element_loop
    ret

    
read_matrix:
    call read_rows_num
    call print_new_line
    call read_cols_num
    call print_new_line
    call read_matrix_elements
    retf

CS_READ_MATRIX ENDS

END

.386
PUBLIC operation_get_min_degree

OK          equ 0
ERR_IO      equ 1
ERR_COMMAND equ 2

OPERATIONS_CS SEGMENT PARA PUBLIC USE16 'CODE'
    assume cs:OPERATIONS_CS
; Получить минимальную степень 2, превышающую число
; в беззнаковой интерпретации
; Параметры
; word degree[out]  - степень двойки
; word num[in]      - число
; far вызов
operation_get_min_degree:
    degree_offset equ bp + 6
    degree equ word ptr ss:[degree_offset]
    num_offset equ bp + 8
    num equ word ptr ss:[num_offset]

    push bp 
    mov bp, sp
    mov degree, 0
    mov cx, 15
    mov dx, num
    ; Поиск старшей 1
    operation_get_min_degree_loop:
        bt dx, cx
        jnc operation_get_min_degree_loop_0
        operation_get_min_degree_loop_1:
            mov degree, cx
            add degree, 1
            jmp operation_get_min_degree_end
        operation_get_min_degree_loop_0:
        loop operation_get_min_degree_loop
    ; Проверка последнего бита
    bt dx, cx
    jnc operation_get_min_degree_end
    mov degree, cx
    add degree, 1

    operation_get_min_degree_end:
    pop bp
    retf

OPERATIONS_CS ENDS
END
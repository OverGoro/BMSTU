EXTRN num_input : far

EXTRN num_print_signed_bin_16   : far
EXTRN num_print_unsigned_bin_16   : far
EXTRN num_print_unsigned_oct_16 : far
EXTRN num_print_signed_hex_8    : far
EXTRN num_print_unsigned_dec_16 : far

EXTRN operation_get_min_degree : far

EXTRN menu_print : far
EXTRN menu_get_command : far
EXTRN menu_handle_rc : far

STACK_SS SEGMENT PARA STACK 'STACK'
    db 1000 dup(0)
STACK_SS ENDS

OK          equ 0
ERR_IO      equ 1
ERR_COMMAND equ 2

MAIN_DS SEGMENT PARA PUBLIC 'DATA'
    num_data word 0
    command_data word 0
    error_data word OK
    degree_data word 0

    commands_list word 0
    ORG commands_list
    command_exit                        word OFFSET handle_command_exit
    command_num_input                   word OFFSET handle_command_num_input
    command_num_print_signed_bin_16     word OFFSET handle_command_num_print_signed_bin_16
    command_num_print_unsigned_bin_16   word OFFSET handle_command_num_print_unsigned_bin_16
    command_num_print_unsigned_oct_16   word OFFSET handle_command_num_print_unsigned_oct_16
    command_num_print_signed_hex_8      word OFFSET handle_command_num_print_signed_hex_8
    command_get_min_degree              word OFFSET handle_command_get_min_degree
MAIN_DS ENDS


MAIN_CS SEGMENT PARA PUBLIC 'CODE'
    assume cs:MAIN_CS
main:
    num equ ds:[num_data]
    command equ ds:[command_data]
    err equ ds:[error_data]
    degree equ ds:[degree_data]

    mov ax, MAIN_DS
    mov ds, ax


    ; Вывод меню
    call menu_print

    ; Ввод команды
    push command
    push err
    call menu_get_command
    pop err
    pop command

    ; Обработка ошибки ввода команды
    push err
    call menu_handle_rc
    pop err

    cmp err, OK
    jne main

    ; Выполнение команды
    mov ax, command
    add ax, ax
    add ax, OFFSET commands_list

    mov bx, ax
    mov dx, word ptr ds:[bx]
    call dx

    ; Обработка ошибки ввода команды
    push err
    call menu_handle_rc
    pop err

    jmp main

handle_command_exit:
    mov ax, 4C00h
    int 21h
handle_command_num_input:
    push num
    push err
    call num_input
    pop err
    pop num
    ret

handle_command_num_print_signed_bin_16:
    push num
    call num_print_signed_bin_16
    pop num
    ret

handle_command_num_print_unsigned_bin_16:
    push num
    call num_print_unsigned_bin_16
    pop num
    ret
handle_command_num_print_unsigned_oct_16:
    push num
    call num_print_unsigned_oct_16
    pop num
    ret
handle_command_num_print_signed_hex_8:
    push num
    call num_print_signed_hex_8
    pop num
    ret
handle_command_get_min_degree:
    push num
    push degree
    call operation_get_min_degree
    pop degree
    pop num

    push degree 
    call num_print_unsigned_dec_16
    pop degree
    ret
    
MAIN_CS ENDS
END main

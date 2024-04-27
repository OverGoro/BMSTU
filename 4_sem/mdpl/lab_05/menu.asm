public menu_print
public menu_get_command
public menu_handle_rc

OK          equ 0
ERR_IO      equ 1
ERR_COMMAND equ 2

command_min_symbol equ '0'
command_max_symbol equ '6'

MENU_TEXT_DS SEGMENT PARA PUBLIC 'DATA'
    menu_text db 'Menu: ', 10, 13
    db  '1) read signed bin num', 10, 13
    db  '2) print signed bin 16-bit num', 10, 13
    db  '3) print unsigned bin 16-bit num', 10, 13
    db  '4) print unsigned oct', 10, 13
    db  '5) print signed hex num', 10, 13
    db  '6) get min degree', 10, 13
    db  '0) EXIT', 10, 13
    db  'Command: $'

    error_io_text db 'Input error', 10, 13, '$'
    error_command_text db 'Wrong command', 10, 13, '$'
    error_unknown_text db 'Unknown error', 10, 13, '$'
    error_ok_text db '$'
MENU_TEXT_DS ENDS



MENU_CS SEGMENT PARA PUBLIC 'CODE'
    assume cs:MENU_CS
; Вывод текста меню
menu_print:
    push ds

    mov ax, MENU_TEXT_DS
    mov ds, ax
    
    mov ah, 09h
    lea dx, menu_text
    int 21h

    pop ds
    retf
    
; Ввод команды
; word err[out] - код ошибки
; word command[out] - комманда
; far вызов
menu_get_command:
    err_offset equ bp + 6
    err equ word ptr ss:[err_offset]
    command_offset equ bp + 8
    command equ word ptr ss:[command_offset]

    push bp
    mov bp, sp

    mov ah, 01
    int 21h

    cmp al, command_min_symbol
    jl menu_get_command_error

    cmp al, command_max_symbol
    jg menu_get_command_error

    jmp menu_get_command_succes

    menu_get_command_error:
        mov err, ERR_COMMAND
        jmp menu_get_command_end
    menu_get_command_succes:
        mov err, OK
        sub al, '0'
        mov ah, 0
        mov command, ax
    menu_get_command_end:
        mov ah, 02h
        mov dl, 10
        int 21h
        mov dl, 13
        int 21h
        pop bp
        retf

; Ввод команды
; word err[out] - код ошибки
; word command[out] - комманда
; far вызов
menu_handle_rc:
    err_offset equ bp + 6
    err equ word ptr ss:[err_offset]

    push bp
    mov bp, sp

    push ds
    mov ax, MENU_TEXT_DS
    mov ds, ax

    ; OK
    lea dx, error_ok_text
    cmp err, OK
    je menu_handle_rc_print

    ; Неправильная команда
    lea dx, error_command_text
    cmp err, ERR_COMMAND
    je menu_handle_rc_print

    ; Ошибка ввода - вывода
    lea dx, error_io_text
    cmp err, ERR_IO
    je menu_handle_rc_print

    ; Неизвестная ошибка
    lea dx, error_unknown_text
    jmp menu_handle_rc_print


    menu_handle_rc_print:
        mov ah, 09h
        int 21h

    pop ds
    pop bp
    retf

MENU_CS ENDS
END

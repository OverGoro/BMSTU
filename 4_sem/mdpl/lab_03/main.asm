DSEG SEGMENT PARA PUBLIC 'DATA'
    string_data db 103 dup('?')
    ORG 0h
    string_max_len byte 100
    ORG 1h
    string_len byte 0
    ORG 2h
    string byte '?'
DSEG ENDS

SSEG SEGMENT PARA STACK 'STACK'
    db 1000 dup(0)
SSEG ENDS


CSEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CSEG, DS:DSEG
input:
    mov ax, DSEG
    mov ds, ax

    mov dx, OFFSET string_data      ; Адрес троки в dx

    mov ah, 0Ah                     ; Ввод строки
    int 21h
    ret

print_new_line: ; Вывод новой строки
    mov ah, 02h
    mov dl, 13 
    int 21h    
    mov dl, 10 
    int 21h    
    ret

output:
    mov ax, DSEG
    mov ds, ax

    mov ah, 02h             ; Вывод символа
    mov cx, 10              ; Количество символов
    mov bx, OFFSET string   ; смещение строки
    
    call print_new_line
    ; Вывод 10 символов
    printLoop:    
        cmp cx, 0                   ; Напечаталось 10 символов
        je endPrintLoop
        mov dl, [bx]                ; Загрузка символа
        int 21h                     ; Вывод символа
        inc bx                      
        dec cx                      
        jmp printLoop
    endPrintLoop:
    ret
main:
    call input
    call output
    mov ax, 4c00h
	int 21h
CSEG ENDS

END main

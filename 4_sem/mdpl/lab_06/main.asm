.386
.model tiny
VIDEO_S SEGMENT AT 0b800h
	ORG 80 * 2 - 8 * 2
	TIME_SYMB LABEL byte
VIDEO_S ENDS

MAIN_S SEGMENT USE16
    assume cs:MAIN_S, ds:MAIN_S   
    org 100h
main:
    jmp init

    module_state            byte 1

    init_msg_data           db 'module added!$'
    uninit_msg_data         db 'module removed!$'
    previous_second_data    byte 0
    previous_value_data     byte 0

    old_1c_bx_data          word 0
    old_1c_es_data          word 0

    cur_second_data         byte 0
    cur_minute_data         byte 0
    cur_hour_data           byte 0

    previous_second equ byte ptr cs:[previous_second_data]
    previous_value  equ byte ptr cs:[previous_value_data]

    cur_second      equ byte ptr cs:[cur_second_data]
    cur_minute      equ byte ptr cs:[cur_minute_data]
    cur_hour        equ byte ptr cs:[cur_hour_data]

    old_1c_bx       equ word ptr cs:[old_1c_bx_data]
    old_1c_es       equ word ptr cs:[old_1c_es_data]
    old_1c          equ dword ptr cs:[old_1c_bx_data]

get_time:
    ; Сохранение предыдущего времени
    mov al, cur_second
    mov previous_second, al
    ; Получение текущего времени
    mov ah, 2Ch
    int 21h

    ; Получаем часы, минуты и секунды из регистров
    mov cur_hour, ch
    mov cur_minute, cl
    mov cur_second, dh
    ret

print_time:
    mov ax, VIDEO_S
    mov es, ax
    mov bl, 10

    mov es:[TIME_SYMB + 1], 00011111b
    mov es:[TIME_SYMB + 3], 00011111b
    mov es:[TIME_SYMB + 5], 00011111b
    mov es:[TIME_SYMB + 7], 00011111b
    mov es:[TIME_SYMB + 9], 00011111b
    mov es:[TIME_SYMB + 11], 00011111b
    mov es:[TIME_SYMB + 13], 00011111b
    mov es:[TIME_SYMB + 15], 00011111b

    mov ah, 0
    mov al, cur_hour
    div bl
    add ah, '0'
    add al, '0'
    mov es:[TIME_SYMB + 0], al
    mov es:[TIME_SYMB + 2], ah
    mov es:[TIME_SYMB + 4],':'

    mov ah, 0
    mov al, cur_minute
    div bl
    add ah, '0'
    add al, '0'
    mov es:[TIME_SYMB + 6], al
    mov es:[TIME_SYMB + 8], ah
    mov es:[TIME_SYMB + 10],':'

    mov ah, 0
    mov al, cur_second
    div bl
    add ah, '0'
    add al, '0'
    mov es:[TIME_SYMB + 12], al
    mov es:[TIME_SYMB + 14], ah

    ret
change_speed:
    mov al, previous_second
    mov ah, cur_second

    cmp ah, al
    je change_speed_end

    mov al, previous_value
    add al, 10b
    mov previous_value, al
    and al, 00011111b

    mov ah, al
    mov al, 0f3h
    out 60h, al

    mov al, ah
    out 60h, al

    change_speed_end: 
    ret
new_1c:

    pushf
    call old_1c

    pusha
    call get_time
    call print_time
    call change_speed
    popa
    iret

init:
    ; Получение адреcа прерывания
    mov ax, 351ch
    int 21h

    mov al, es:[module_state]
    cmp al, 1
    je unint
    
    ; Вывод cообщения о запуcке резидента
    mov ah, 09h
    mov dx, OFFSET init_msg_data
    int 21h

    ; cохранение адреcа прерывания
    mov old_1c_bx, bx
    mov old_1c_es, es 

    ; Уcтановка нового адреcа прерывания
    mov ax, 251ch
    lea dx, new_1c
    int 21h
    lea dx, init
    int 27h
unint:
    mov dx, OFFSET uninit_msg_data
    mov ah, 09h
    int 21h

    mov dx, es:old_1c_bx_data
    mov ds, es:old_1c_es_data
    mov ax, 251ch
    int 21h

    ; Освобождение выделеной памяти
    mov ah, 49h
    int 21h

    mov ax, 4c00h
    int 21h

MAIN_S ENDS
END main
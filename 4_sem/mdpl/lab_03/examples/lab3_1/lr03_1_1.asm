EXTRN output_X: near ; Подключение из 2 файла

STK SEGMENT PARA STACK 'STACK' ; Выделение стека
	db 100 dup(0)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA' 
	X db 'R'  ; Переменная х
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:DSEG, SS:STK
main:
	mov ax, DSEG ;Установил дата сегмент
	mov ds, ax

	call output_X	; Вызвал функцию из другого модуля

	mov ax, 4c00h 	; Закончить с 0 кодом возврата
	int 21h
CSEG ENDS

PUBLIC X

END main
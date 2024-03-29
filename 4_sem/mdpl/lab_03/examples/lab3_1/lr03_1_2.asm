PUBLIC output_X
EXTRN X: byte

DS2 SEGMENT AT 0b800h		; Сегмент с текстом видеокарты
	ORG 80 * 2 * 2 + 2 * 2 	; Установили позицию символа
	SYMB LABEL word			; Назвали эту позицую 
DS2 ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, ES:DS2
output_X proc near
	mov ax, DS2
	mov es, ax
	mov ah, 10	; Установка цветовых параметров символа
	mov al, X	; установка символа
	mov symb, ax	; Вывод символа в буфер видеадаптера
	ret
output_X endp
CSEG ENDS
END
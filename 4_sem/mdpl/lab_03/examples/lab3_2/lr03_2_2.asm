SD1 SEGMENT para common 'DATA' ; Сегмент наложится на SD1 из первого файла
	C1 LABEL byte	; "назвали" первый байт в дате
	ORG 1h			; Сдвиг вправо в 2-й байт
	C2 LABEL byte	; "Назвали" второй байт в дате
SD1 ENDS
; Сегмент SD1 объединиться как union с сегментом SD1 из lr03_2_1

CSEG SEGMENT para 'CODE'
	ASSUME CS:CSEG, DS:SD1
main:
	mov ax, SD1
	mov ds, ax
	mov ah, 2
	mov dl, C1
	int 21h
	mov dl, C2
	int 21h
	mov ax, 4c00h
	int 21h
CSEG ENDS
END main
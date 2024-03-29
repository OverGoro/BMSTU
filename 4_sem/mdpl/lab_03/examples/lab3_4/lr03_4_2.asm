EXTRN X: byte
PUBLIC exit

SD2 SEGMENT para 'DATA'
	Y db 'Y'
SD2 ENDS

SC2 SEGMENT para public 'CODE'
	assume CS:SC2, DS:SD2
exit:
	mov ax, seg X 	; Записываем в es SD1
	mov es, ax
	mov bh, es:X	; Записываем в bh Х

	mov ax, SD2
	mov ds, ax

	xchg ah, Y		; Поменяли местами y и ah
	xchg ah, ES:X	; Поменяли местами x и ah
	xchg ah, Y		; Поменяли местами y и ah

	mov ah, 2
	mov dl, Y
	int 21h	
	
	mov ax, 4c00h
	int 21h
SC2 ENDS
END
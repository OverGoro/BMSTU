PUBLIC matrix_cols, matrix_rows, matrix_data

EXTRN read_matrix:far
EXTRN modify_matrix:far
EXTRN print_matrix:far
EXTRN print_matrix_message:far
EXTRN print_result_message:far

MATRIX_SEG SEGMENT PARA COMMON 'DATA'
    matrix_rows byte 0
    matrix_cols byte 0
    matrix_data db 81 dup(0)
MATRIX_SEG ENDS

SSEG SEGMENT PARA STACK 'STACK'
    db 1000 dup(0)
SSEG ENDS

CS_MAIN SEGMENT PARA PUBLIC 'CODE'
    assume ds:MATRIX_SEG, cs:CS_MAIN, ss:SSEG
main:
    call read_matrix
    call print_matrix_message
    call print_matrix

    call modify_matrix

    call print_result_message
    call print_matrix

    mov ax, MATRIX_SEG
    mov ds, ax
    mov ax, 4c00h
	int 21h
CS_MAIN ENDS

END main

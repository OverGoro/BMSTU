global get_root

%define x_start xmm0
%define x_end xmm1
%define eps xmm2
section .data 
epsilon dq 0
fmt_double db "%lf", 10, 0  ; Формат для вывода double с новой строкой
x dq 0
answer dq 0
sin_k dq 5
tmp_a dq 0
tmp_b dq 0

tmp_x_start dq 0
tmp_x_end dq 0
section .text

    extern printf              ; Объявление внешней функции printf

global print_double
print_double:
    movsd xmm3, xmm0
    push rbp                   ; Сохраняем текущий указатель на базу
    mov rbp, rsp               ; Устанавливаем новый указатель на базу

    sub rsp, 8                 ; Резервируем место для одного double на стеке
    movsd [rsp], xmm0          ; Копируем значение double из xmm0 на стек

    lea rdi, [fmt_double]      ; Загружаем адрес формата в rdi
    mov rax, 1                 ; Устанавливаем количество аргументов на 1 (в данном случае)
    call printf                ; Вызываем функцию printf

    add rsp, 8                 ; Освобождаем место для double на стеке
    pop rbp                      ; Восстанавливаем указатель на базу и освобождаем стек
    movsd xmm0, xmm3
    ret                        ; Возвращаемся


delta_func:
    ; a
    fld qword [tmp_a]
    ; b -a
    fld qword [tmp_b]
    fld qword [tmp_a]
    fsubp
    

    ; (b - a) * f(a)
    fld qword [tmp_a]
    fstp qword [x]
    call func
    fmulp

    ; f(b) - f(a)
    fld qword [tmp_b]
    fstp qword [x]
    call func

    fld qword [tmp_a]
    fstp qword [x]
    call func

    fsubp

    ; (b - a) * f(x) / (f(b) - f(a))
    fdivp
    ;a - (b - a) * f(a) / (f(b) - f(a))
    fsubp
    ret
func:
    ;x * x
    fld qword [x] 
    fld qword [x] 
    fmulp
    ; x * 5
    fld qword [x] 
    fild qword [sin_k]
    fmulp
    ; x * x + x * 5
    faddp
    ; sin(x * x + x * 5)
    fsin
    ret
get_root:


    movsd [epsilon], eps
    movsd [tmp_x_start], x_start
    movsd [tmp_x_end], x_end

    ; movsd xmm0, qword [epsilon]
    ; call print_double

    get_root_loop:

    ; while (fabs(b - a) > eps)
    fld qword [tmp_x_end]
    fld qword [tmp_x_start]
    fsubp
    fabs
    fld qword [epsilon]
    fcompp
    fstsw ax 
    fwait    
    sahf     
    jnb exit


    mov rax, qword [tmp_x_start]
    mov [tmp_a], rax
    mov rax, qword [tmp_x_end]
    mov [tmp_b],  rax
    call delta_func
    fstp qword [tmp_x_start]

    mov rax, qword [tmp_x_end]
    mov [tmp_a], rax
    mov  rax ,  qword [tmp_x_start]
    mov [tmp_b], rax
    call delta_func
    fstp qword [tmp_x_end]

    ; movsd xmm0, qword [tmp_x_start]
    ; call print_double
    ; movsd xmm0, qword [tmp_x_end]
    ; call print_double

    jmp get_root_loop

    exit:

    movsd xmm0, qword [tmp_x_end]
    ret
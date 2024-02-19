import tkinter as tk
import ctypes as ct
lib = ct.CDLL('./out/libarray.so')

# void array_cycle_shift(int *arr, size_t n, size_t k)
array_cycle_shift = lib.array_cycle_shift
array_cycle_shift.argtypes = (ct.POINTER(ct.c_int), ct.c_size_t, ct.c_size_t)


# void array_form_sqr(const int *arr, size_t n, int *arr_sqr, size_t *n_sqr)
array_form_sqr = lib.array_form_sqr
array_form_sqr.argtypes = (ct.POINTER(ct.c_int), ct.c_size_t, ct.POINTER(ct.c_int), ct.POINTER(ct.c_size_t))
array_form_sqr.restype = ct.c_int

array_1, array_2 = [], []

def shift_array(arr, n):
    pa = (ct.c_int * len(arr))(*arr)
    array_cycle_shift(pa, len(arr), n)
    return [x for x in pa]
def select_squares_max_mem(arr):
    n_1 = ct.c_size_t(len(arr))
    n_2 = ct.c_size_t(len(arr))

    pa_1 = (ct.c_int * len(arr))(*arr)
    pa_2 = (ct.c_int * len(arr))()

    array_form_sqr(pa_1, n_1, pa_2, ct.byref(n_2))
    return [pa_2[i] for i in range(n_2.value)]
def select_squares_necessary_mem(arr):
    n_1 = ct.c_size_t(len(arr))
    n_2 = ct.c_size_t(0)

    pa_1 = (ct.c_int * len(arr))(*arr)

    array_form_sqr(pa_1, n_1, ct.c_int(0), ct.byref(n_2))

    pa_2 = (ct.c_int * n_2.value)()

    array_form_sqr(pa_1, n_1, pa_2, ct.byref(n_2))
    return [pa_2[i] for i in range(n_2.value)]

def clear_arrays():
    global array_1, array_2
    array_1 = []
    array_2 = []
    update_text()

def arr_to_string(arr):
    res = ""
    for x in arr:
        res += str(x) + " "
    return res

def update_arrays():
    global array_1
    array_1 = list([int(x) for x in array1_text.get().split()])

def update_text():
    global array_1, array_2
    array1_text.delete(0, "end")
    array1_text.insert(0, arr_to_string(array_1))
    array2_text.config(text=arr_to_string(array_2))

def shift_button_command():
    global array_1, array_2
    update_arrays()
    array_1 = shift_array(array_1, int(shift_entry.get()))
    update_text()

def select_button_necessary_command():
    global array_1, array_2
    update_arrays()
    array_2 = select_squares_necessary_mem(array_1)
    update_text()
def select_button_max_command():
    global array_1, array_2
    update_arrays()
    array_2 = select_squares_max_mem(array_1)
    update_text()



root = tk.Tk()
root.title("Операции с массивом")

array1_label = tk.Label(root, text="Массив 1:")
array1_label.grid(row=0, column=0)

array1_text = tk.Entry(root)
array1_text.grid(row=0, column=1)

array2_label = tk.Label(root, text="Массив 2:")
array2_label.grid(row=1, column=0)

array2_text = tk.Label(root, text=arr_to_string(array_2))
array2_text.grid(row=1, column=1)

shift_entry = tk.Entry(root)
shift_entry.grid(row=2, column=1)

shift_button = tk.Button(root, text="Циклический сдвиг на ", command=shift_button_command)
shift_button.grid(row=2, column=0)

select_necessary_button = tk.Button(root, text="Выделить полные квадраты\nнеобх. кол-во памяти", command=select_button_necessary_command)
select_necessary_button.grid(row=3, column=0)

select_max_button = tk.Button(root, text="Выделить полные квадраты\nмакс. кол-во памяти", command=select_button_max_command)
select_max_button.grid(row=4, column=0)

clear_button = tk.Button(root, text="Очистить", command=clear_arrays)
clear_button.grid(row=3, column=1, rowspan=2)

update_text()

root.mainloop()


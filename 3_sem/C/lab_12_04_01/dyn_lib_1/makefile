SRC := src/
INC := inc/
OUT_NAME := out
OUT := $(OUT_NAME)/
UNIT_TESTS := unit_tests/
MEASURES := measures/

# Компилятор
CC := gcc

#Компилятор для санитайзеров
CCS := clang

# Опции компиляции для санитайзеров
SFLAGS := -std=c99 -g3 -O0 -fno-omit-frame-pointer -Wall -Wextra -Wpedantic -Werror

# Опции для valgrind
VFLAGS := -std=c99 -g3 -O0 -Wall -Wextra -Werror -Wpedantic

DYNAMIC_DEPS = $(OUT)main.o 
DYNAMIC_LIBS = $(OUT)libarray.so $(OUT)libsort.so
DYNAMIC_FLAGS = -L$(OUT) -larray -lsort -Wl,-rpath=$(OUT)


# Опции для юнит тестов
UFLAGS := -std=c99 -g -O0 -Wpedantic -Werror -Wextra -Wall
ULIBS := -lcheck -lm -lpthread -lrt -lsubunit


# Опции для релизной версии
RFLAGS := -std=c99 -O3 -Wall -Wextra -Werror -Wpedantic

DFLAGS := -std=c99 -g3 -Wall -Wextra -Werror -Wpedantic

CFLAGS = -std=c99 -g3 -Wall -Wextra -Werror -Wpedantic


app.exe: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CC) $(CFLAGS) -o app.exe $(DYNAMIC_DEPS) $(DYNAMIC_FLAGS)

debug: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CC) $(DFLAGS) -o app.exe $(DYNAMIC_DEPS) $(DYNAMIC_FLAGS)

msan: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CCS) $(SFLAGS) -fsanitize=memory -o app.exe $< $(DYNAMIC_FLAGS)

asan: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CCS) $(SFLAGS) -fsanitize=address -o app.exe $< $(DYNAMIC_FLAGS)

ubsan: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CCS) $(SFLAGS) -fsanitize=undefined -o app.exe $< $(DYNAMIC_FLAGS)

release: $(OUT)main.o $(DYNAMIC_LIBS)
	$(CC) $(RFLAGS) -o app.exe $< $(DYNAMIC_FLAGS)

valgrind: $(OUT)main.o $(DYNAMIC_LIBS)
	$(CC) $(VFLAGS) -o app.exe $< $(DYNAMIC_FLAGS)

# Unit tests
unit_tests.exe: $(OUT)check_sort.o $(OUT)check_key.o $(OUT)check_main.o $(OUT)check_cmp.o $(DYNAMIC_LIBS) 
	$(CC) $(UFLAGS) -o $@ $^ $(ULIBS)
unit: unit_tests.exe
	./unit_tests.exe

# Прогон функциональных тестов
func: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	make clean
	echo "Address sanitizer: "
	make asan
	./func_tests/scripts/func_tests.sh -v

	echo "Memory sanitizer: "
	make msan
	./func_tests/scripts/func_tests.sh -v

	echo "Undefined behaviour sanitizer: "
	make ubsan
	./func_tests/scripts/func_tests.sh -v
	make clean

	make debug
	./func_tests/scripts/func_tests.sh -v

	make release
	./func_tests/scripts/func_tests.sh -v

	make valgrind
	./func_tests/scripts/func_tests.sh -v --valgrind

	make clean


# Объектные файлы
$(OUT)main.o: $(SRC)main.c $(INC)array.h $(INC)sort.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

# Объектные файлы динамических библиотек
$(OUT)array.o: $(SRC)array.c $(INC)array.h
	$(CC) $(CFLAGS) -I $(INC) -fPIC -c $< -o $(OUT)array.o
$(OUT)sort.o: $(SRC)sort.c $(INC)sort.h
	$(CC) $(CFLAGS) -I $(INC) -fPIC -c $< -o $(OUT)sort.o

# Динамические библиотеки
$(OUT)libarray.so: $(OUT)array.o
	$(CC) -o $@ -shared $(OUT)array.o
$(OUT)libsort.so: $(OUT)sort.o
	$(CC) -o $@ -shared $(OUT)sort.o

# Объектные файлы unit тестов
$(OUT)check_sort.o: $(UNIT_TESTS)check_sort.c $(SRC)sort.c $(INC)sort.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)check_cmp.o: $(UNIT_TESTS)check_cmp.c $(UNIT_TESTS)check_cmp.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)check_key.o: $(UNIT_TESTS)check_key.c $(SRC)sort.c $(INC)sort.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)check_main.o:$(UNIT_TESTS)check_main.c $(OUT)check_key.o $(OUT)check_sort.o
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@


.PHONY:
clean:
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda $(OUT)*.so $(OUT)*.a prog_out.txt


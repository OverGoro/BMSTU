SRC := src/
INC := inc/
OUT := out/
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

STATIC_DEPS = $(OUT)main.o
STATIC_LIBS = $(OUT)array.a $(OUT)sort.a


# Опции для юнит тестов
UFLAGS := -std=c99 -g -O0 -Wpedantic -Werror -Wextra -Wall
ULIBS := -lcheck -lm -lpthread -lrt -lsubunit


# Опции для релизной версии
RFLAGS := -std=c99 -O3 -Wall -Wextra -Werror -Wpedantic


app.exe: $(STATIC_DEPS) $(STATIC_LIBS)
	$(CC) $(CFLAGS) -o app.exe $(STATIC_DEPS) $(STATIC_LIBS)

debug: $(STATIC_DEPS) $(STATIC_LIBS)
	$(CC) $(CFLAGS) -o app.exe $(STATIC_DEPS) $(STATIC_LIBS)

msan: $(STATIC_DEPS) $(STATIC_LIBS)
	$(CCS) $(SFLAGS) -fsanitize=memory -o app.exe $^

asan: $(STATIC_DEPS) $(STATIC_LIBS)
	$(CCS) $(SFLAGS) -fsanitize=address -o app.exe $^

ubsan: $(STATIC_DEPS) $(STATIC_LIBS)
	$(CCS) $(SFLAGS) -fsanitize=undefined -o app.exe $^

release: $(OUT)main.o $(OUT)array.o $(OUT)sort.o
	$(CC) $(RFLAGS) -o app.exe $^

valgrind: $(OUT)main.o $(OUT)array.o $(OUT)sort.o
	$(CC) $(VFLAGS) -o app.exe $^

.PHONY:
coverage: CFLAGS += --coverage
coverage: $(STATIC_DEPS) $(STATIC_LIBS)
	$(CC) $(CFLAGS) -o app.exe $^


# Unit tests
unit_tests.exe: $(OUT)check_sort.o $(OUT)check_key.o $(OUT)check_main.o $(OUT)check_cmp.o $(STATIC_LIBS) 
	$(CC) $(UFLAGS) -o $@ $^ $(ULIBS)
unit: unit_tests.exe
	./unit_tests.exe

# Прогон функциональных тестов
func: $(STATIC_DEPS) $(STATIC_LIBS)
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
	make coverage


	# Тестирование с выводом
	./collect_coverage.sh


# Объектные файлы
$(OUT)array.o: $(SRC)array.c $(INC)array.h $(INC)error.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)sort.o: $(SRC)sort.c $(INC)sort.h $(INC)error.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)main.o: $(SRC)main.c $(INC)array.h $(INC)sort.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

# Статические библиотеки
$(OUT)array.a: $(OUT)array.o
	ar cr $(OUT)array.a $(OUT)array.o
	ranlib $(OUT)array.a
$(OUT)sort.a: $(OUT)sort.o
	ar cr $(OUT)sort.a $(OUT)sort.o
	ranlib $(OUT)sort.a

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
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda


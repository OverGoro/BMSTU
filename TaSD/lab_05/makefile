SRC := src/
INC := inc/
OUT := out/
UNIT_TESTS := unit_tests/
MEASURES := measures/
HEADERS := inc/*.h
# Компилятор
CC := gcc

#Компилятор для санитайзеров
CCS := clang

# Опции компиляции
CFLAGS := -std=c99 -g -O0 -Wall -Wextra -Werror -Wpedantic

# Опции компиляции для санитайзеров
SFLAGS := -std=c99 -g3 -O0 -fno-omit-frame-pointer -Wall -Wextra -Wpedantic -Werror

# Опции для valgrind
VFLAGS := -std=c99 -g3 -O0 -Wall -Wextra -Werror -Wpedantic


# Опции для юнит тестов
UFLAGS := -std=c99 -g3 -O0 -Wpedantic -Werror -Wextra -Wall
ULIBS := -lcheck -lm -lpthread -lrt

# Опции для релизной версии
RFLAGS := -std=c99 -O3 -Wall -Wextra -Werror -Wpedantic

PROG_DEPS = $(OUT)main.o
PROG_DEPS += $(OUT)menu.o
PROG_DEPS += $(OUT)object.o
PROG_DEPS += $(OUT)queue_array.o
PROG_DEPS += $(OUT)process.o
PROG_DEPS += $(OUT)process_array.o
PROG_DEPS += $(OUT)queue_list.o
PROG_DEPS += $(OUT)queue_list_node.o
PROG_DEPS += $(OUT)address_node.o
PROG_DEPS += $(OUT)address_list.o
PROG_DEPS += $(OUT)measure.o

PROG_LIBS = -lm

CHECK_DEPS = $(OUT)check_main.o $(OUT)check_matrix_summ.o $(OUT)check_matrix_summ.o $(OUT)check_matrix_multiply.o
CHECK_DEPS += $(OUT)matrix.o $(OUT)matrix_io.o $(OUT)slae.o $(OUT)matrix_operations.o
CHECK_DEPS += $(OUT)check_slae.o

app.exe: $(PROG_DEPS)
	$(CC) $(CFLAGS) -o app.exe $^ $(PROG_LIBS)
debug: $(PROG_DEPS)
	$(CC) $(CFLAGS) -o app.exe $^
msan: $(PROG_DEPS)
	$(CCS) $(SFLAGS) -fsanitize=memory -o app.exe $^
asan: $(PROG_DEPS)
	$(CCS) $(SFLAGS) -fsanitize=address -o app.exe $^
ubsan: $(PROG_DEPS)
	$(CCS) $(SFLAGS) -fsanitize=undefined -o app.exe $^
release: $(PROG_DEPS)
	$(CC) $(RFLAGS) -o app.exe $^
valgrind: $(PROG_DEPS)
	$(CC) $(VFLAGS) -o app.exe $^

.PHONY:
coverage: CFLAGS += --coverage
coverage: $(PROG_DEPS)
	$(CC) $(CFLAGS) -o app.exe $^


# Unit tests
unit_tests.exe: $(CHECK_DEPS)
	$(CC) $(UFLAGS) -o $@ $^ $(ULIBS)
unit: unit_tests.exe
	./unit_tests.exe

# Прогон функциональных тестов
func: $(PROG_DEPS)
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
$(OUT)%.o: $(SRC)%.c $(HEADERS)
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

clean:
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda


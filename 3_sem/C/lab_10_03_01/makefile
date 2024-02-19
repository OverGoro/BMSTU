SRC := ./
INC := ./
OUT := out/
UNIT_TESTS := unit_tests/
MEASURES := measures/
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
#
# PROG_DEPS = $(OUT)node.o
# PROG_DEPS += $(OUT)associative_array.o

CHECK_DEPS = $(OUT)node.o
CHECK_DEPS += $(OUT)associative_array.o
CHECK_DEPS += $(OUT)check_main.o
CHECK_DEPS += $(OUT)check_min.o
CHECK_DEPS += $(OUT)check_max.o
CHECK_DEPS += $(OUT)check_each.o
CHECK_DEPS += $(OUT)check_find.o
CHECK_DEPS += $(OUT)check_remove.o
CHECK_DEPS += $(OUT)check_insert.o
CHECK_DEPS += $(OUT)check_clear.o
CHECK_DEPS += $(OUT)check_create.o
CHECK_DEPS += $(OUT)check_destroy.o

# app.exe: $(PROG_DEPS)
# 	$(CC) $(CFLAGS) -o app.exe $^
# debug: $(PROG_DEPS)
# 	$(CC) $(CFLAGS) -o app.exe $^
# msan: $(PROG_DEPS)
# 	$(CCS) $(SFLAGS) -fsanitize=memory -o app.exe $^
# asan: $(PROG_DEPS)
# 	$(CCS) $(SFLAGS) -fsanitize=address -o app.exe $^
# ubsan: $(PROG_DEPS)
# 	$(CCS) $(SFLAGS) -fsanitize=undefined -o app.exe $^
# release: $(PROG_DEPS)
# 	$(CC) $(RFLAGS) -o app.exe $^
# valgrind: $(PROG_DEPS)
# 	$(CC) $(VFLAGS) -o app.exe $^

# .PHONY:
# coverage: CFLAGS += --coverage
# coverage: $(PROG_DEPS)
# 	$(CC) $(CFLAGS) -o app.exe $^


# Unit tests
unit_tests.exe: $(CHECK_DEPS)
	# $(CC) $(SFLAGS) -fsanitize=address -o $@ $^ $(ULIBS)	
	$(CC) $(CFLAGS) -o $@ $^ $(ULIBS)	
unit: unit_tests.exe
	./unit_tests.exe

# Прогон функциональных тестов
func: $(PROG_DEPS)
	make clean
	echo "Address sanitizer: "
	make valgrind
	./func_tests/scripts/func_tests.sh -v --valgrind
	make clean
	make asan
	./func_tests/scripts/func_tests.sh -v
	make clean
	echo "Memory sanitizer: "
	make msan
	./func_tests/scripts/func_tests.sh -v
	make clean
	echo "Undefined behaviour sanitizer: "
	make ubsan
	./func_tests/scripts/func_tests.sh -v
	make clean
	make debug
	./func_tests/scripts/func_tests.sh -v
	make release
	./func_tests/scripts/func_tests.sh -v
	make clean
	make coverage


	# Тестирование с выводом
	./collect_coverage.sh
$(OUT)associative_array.o: $(SRC)associative_array_impl_1.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

$(OUT)%.o: $(SRC)%.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

# Unit тесты

clean:
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda


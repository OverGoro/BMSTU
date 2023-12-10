SRC := src/
INC := inc/
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

PROG_DEPS = $(OUT)main.o $(OUT)film.o $(OUT)film_array.o

CHECK_DEPS = $(OUT)film.o $(OUT)film_array.o
CHECK_DEPS += $(OUT)check_fa_find_place.o
CHECK_DEPS += $(OUT)check_cmp.o
CHECK_DEPS += $(OUT)check_fa_bin_search.o
CHECK_DEPS += $(OUT)check_fa_paste.o
CHECK_DEPS += $(OUT)check_main.o 

app.exe: $(PROG_DEPS)
	$(CC) $(CFLAGS) -o app.exe $^
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
	make valgrind
	./func_tests/scripts/func_tests.sh -v --valgrind
	make clean
	echo "Address sanitizer: "
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
$(OUT)main.o: $(SRC)main.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

$(OUT)film.o: $(SRC)film.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

$(OUT)film_array.o: $(SRC)film_array.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

$(OUT)check_fa_find_place.o: $(UNIT_TESTS)check_fa_find_place.c $(UNIT_TESTS)*.h $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) -I $(UNIT_TESTS) $< -o $@

$(OUT)check_fa_bin_search.o: $(UNIT_TESTS)check_fa_bin_search.c $(UNIT_TESTS)*.h $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) -I $(UNIT_TESTS) $< -o $@

$(OUT)check_fa_paste.o: $(UNIT_TESTS)check_fa_paste.c $(UNIT_TESTS)*.h $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) -I $(UNIT_TESTS) $< -o $@

$(OUT)check_cmp.o: $(UNIT_TESTS)check_cmp.c $(UNIT_TESTS)*.h $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) -I $(UNIT_TESTS) $< -o $@

$(OUT)check_main.o: $(UNIT_TESTS)check_main.c $(UNIT_TESTS)*.h $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) -I $(UNIT_TESTS) $< -o $@

clean:
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda


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

PROG_DEPS = $(OUT)main.o
PROG_DEPS += $(OUT)node.o
PROG_DEPS += $(OUT)list.o
PROG_DEPS += $(OUT)polynome.o

CHECK_DEPS = $(OUT)node.o
CHECK_DEPS += $(OUT)list.o
CHECK_DEPS += $(OUT)polynome.o
CHECK_DEPS += $(OUT)check_cmp.o
CHECK_DEPS += $(OUT)check_pop_back.o
CHECK_DEPS += $(OUT)check_pop_front.o
CHECK_DEPS += $(OUT)check_polynome_count.o
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
$(OUT)main.o: $(SRC)main.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)node.o: $(SRC)node.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)list.o: $(SRC)list.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)polynome.o: $(SRC)polynome.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

# Unit тесты
$(OUT)check_pop_front.o: $(UNIT_TESTS)check_pop_front.c $(UNIT_TESTS)check_pop_front.h $(UNIT_TESTS)check_cmp.h $(INC)list.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)check_pop_back.o: $(UNIT_TESTS)check_pop_back.c $(UNIT_TESTS)check_pop_back.h $(UNIT_TESTS)check_cmp.h $(INC)list.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)check_polynome_count.o: $(UNIT_TESTS)check_polynome_count.c $(UNIT_TESTS)check_polynome_count.h $(UNIT_TESTS)check_cmp.h $(INC)list.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

$(OUT)check_main.o:$(UNIT_TESTS)check_main.c $(UNIT_TESTS)check_cmp.h 
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)check_cmp.o:$(UNIT_TESTS)check_cmp.c $(UNIT_TESTS)check_cmp.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

clean:
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda


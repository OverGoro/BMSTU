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
UFLAGS := -std=c99 -g -O0 -Wpedantic -Werror -Wextra -Wall
ULIBS := -lcheck -lm -lpthread -lrt 

# Опции для релизной версии
RFLAGS := -std=c99 -O3 -Wall -Wextra -Werror -Wpedantic

app.exe: $(OUT)main.o $(OUT)array.o $(OUT)sort.o	
	$(CC) $(CFLAGS) -o app.exe $^
debug: $(OUT)main.o $(OUT)array.o $(OUT)sort.o
	$(CC) $(CFLAGS) -o app.exe $^
msan: $(OUT)main.o $(OUT)array.o $(OUT)sort.o
	$(CCS) $(SFLAGS) -fsanitize=memory -o app.exe $^
asan: $(OUT)main.o $(OUT)array.o $(OUT)sort.o
	$(CCS) $(SFLAGS) -fsanitize=address -o app.exe $^
ubsan: $(OUT)main.o $(OUT)array.o $(OUT)sort.o
	$(CCS) $(SFLAGS) -fsanitize=undefined -o app.exe $^
release: $(OUT)main.o $(OUT)array.o $(OUT)sort.o
	$(CC) $(RFLAGS) -o app.exe $^
valgrind: $(OUT)main.o $(OUT)array.o $(OUT)sort.o
	$(CC) $(VFLAGS) -o app.exe $^

.PHONY:
coverage: CFLAGS += --coverage
coverage: $(OUT)main.o $(OUT)array.o $(OUT)sort.o
	$(CC) $(CFLAGS) -o app.exe $^


# Unit tests
unit_tests.exe: $(OUT)sort.o $(OUT)check_sort.o $(OUT)check_key.o $(OUT)check_main.o $(OUT)check_cmp.o
	$(CC) $(UFLAGS) -o $@ $^ $(ULIBS)
unit: unit_tests.exe
	./unit_tests.exe

# Замерный эксперимент
measure.exe: $(OUT)measure_main.o $(OUT)time_test.o $(OUT)sort.o
	$(CC) $(RFLAGS) -o measure.exe $^ -lm
	#$(CC) $(SFLAGS) -fsanitize=address -o measure.exe $^ -lm
	#$(CC) $(VFLAGS) -o measure.exe $^ -lm
measure: measure.exe
	./measure.exe
	gnuplot $(MEASURES)graph.gpi

# Прогон функциональных тестов
func: $(OUT)main.o $(OUT)array.o $(OUT)sort.o
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

$(OUT)array.o: $(SRC)array.c $(INC)array.h $(INC)error.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)sort.o: $(SRC)sort.c $(INC)sort.h $(INC)error.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)main.o: $(SRC)main.c $(INC)array.h $(INC)sort.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@


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


$(OUT)time_test.o: $(MEASURES)time_test.c $(MEASURES)time_test.h $(INC)sort.h $(SRC)sort.c
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)measure_main.o: $(MEASURES)measure_main.c $(OUT)time_test.o
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
clean:
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda


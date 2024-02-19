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
CFLAGS := -std=c99 -g3 -O0 -Wall -Wextra -Werror -Wpedantic

# Опции компиляции для санитайзеров
SFLAGS := -std=c99 -g3 -O0 -fno-omit-frame-pointer -Wall -Wextra -Wpedantic -Werror

# Опции для valgrind
VFLAGS := -std=c99 -g3 -O0 -Wall -Wextra -Werror -Wpedantic


# Опции для юнит тестов
UFLAGS := -std=c99 -g -O0 -Wpedantic -Werror -Wextra -Wall
ULIBS := -lcheck -lm -lpthread -lrt

# Опции для релизной версии
RFLAGS := -std=c99 -O3 -Wall -Wextra -Werror -Wpedantic

app.exe: $(OUT)main.o $(OUT)student.o 
app.exe: $(OUT)student_io.o $(OUT)student_array.o 
app.exe: $(OUT)student_sort.o $(OUT)menu.o $(OUT)student_filter.o	
app.exe: $(OUT)student_keys.o
app.exe: $(OUT)str_io.o
app.exe: $(OUT)measure.o
	$(CC) $(CFLAGS) -o app.exe $^
debug: $(OUT)main.o $(OUT)student.o
	$(CC) $(CFLAGS) -o app.exe $^
msan: $(OUT)main.o $(OUT)student.o
	$(CCS) $(SFLAGS) -fsanitize=memory -o app.exe $^
asan: $(OUT)main.o $(OUT)student.o
	$(CCS) $(SFLAGS) -fsanitize=address -o app.exe $^
ubsan: $(OUT)main.o $(OUT)student.o
	$(CCS) $(SFLAGS) -fsanitize=undefined -o app.exe $^
release: $(OUT)main.o $(OUT)student.o
	$(CC) $(RFLAGS) -o app.exe $^
valgrind: $(OUT)main.o $(OUT)student.o
	$(CC) $(VFLAGS) -o app.exe $^

.PHONY:
coverage: CFLAGS += --coverage
coverage: $(OUT)main.o $(OUT)student.o
	$(CC) $(CFLAGS) -o app.exe $^


# Unit tests
# unit_tests.exe: $(OUT)sort.o $(OUT)check_sort.o $(OUT)check_key.o $(OUT)check_main.o $(OUT)student_filter.o $(OUT)student_keys.o
# 	$(CC) $(UFLAGS) -o $@ $^ $(ULIBS)
# unit: unit_tests.exe
# 	./unit_tests.exe
#
# # Замерный эксперимент
# measure.exe: $(OUT)measure_main.o $(OUT)time_test.o $(OUT)sort.o
# 	$(CC) $(RFLAGS) -o measure.exe $^

# Прогон функциональных тестов
# func: $(OUT)main.o $(OUT)student.o
# 	make clean
# 	echo "Address sanitizer: "
# 	make asan
# 	./func_tests/scripts/func_tests.sh -v
#
# 	echo "Memory sanitizer: "
# 	make msan
# 	./func_tests/scripts/func_tests.sh -v
#
# 	echo "Undefined behaviour sanitizer: "
# 	make ubsan
# 	./func_tests/scripts/func_tests.sh -v
# 	make clean
#
# 	make debug
# 	./func_tests/scripts/func_tests.sh -v
#
# 	make release
# 	./func_tests/scripts/func_tests.sh -v
#
# 	make valgrind
# 	./func_tests/scripts/func_tests.sh -v --valgrind
#
# 	make clean
# 	make coverage


	# Тестирование с выводом
	./collect_coverage.sh

$(OUT)student.o: $(SRC)student.c $(INC)student.h $(INC)error.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)main.o: $(SRC)main.c $(INC)student.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

$(OUT)student_io.o: $(SRC)student_io.c $(INC)student_io.h $(INC)student.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)student_array.o: $(SRC)student_array.c $(INC)student_io.h $(INC)student.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)student_sort.o: $(SRC)student_sort.c $(INC)student_sort.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)menu.o: $(SRC)menu.c $(INC)menu.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)student_filter.o: $(SRC)student_filter.c $(INC)student_filter.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)student_keys.o: $(SRC)student_keys.c $(INC)student_keys.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)str_io.o: $(SRC)str_io.c $(INC)str_io.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@
$(OUT)measure.o: $(SRC)measure.c $(INC)measure.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

clean:
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda


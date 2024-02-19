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
SFLAGS := -std=c99 -g3 -O0 -fno-omit-frame-pointer -Wall -Wextra  -Werror

# Опции для valgrind
VFLAGS := -std=c99 -g3 -O0 -Wall -Wextra -Werror 

DYNAMIC_DEPS = $(OUT)main.o 
DYNAMIC_LIBS = $(OUT)libarray.so $(OUT)libsort.so
DYNAMIC_FLAGS = -ldl 

# Опции для юнит тестов
UFLAGS := -std=c99 -g3 -O0 -Werror -Wextra -Wall
ULIBS := -lcheck -lm -lpthread -lrt -lsubunit


CFLAGS := -std=c99 -g3 -Wall -Wextra -Werror 

# Опции для релизной версии
RFLAGS := -std=c99 -g3 -Wall -Wextra -Werror 


app.exe: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CC) $(RFLAGS) -o app.exe $(DYNAMIC_DEPS) $(DYNAMIC_FLAGS)

debug: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CC) $(RFLAGS) -o app.exe $(DYNAMIC_DEPS) $(DYNAMIC_FLAGS)

msan: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CCS) $(SFLAGS) -fsanitize=memory -o app.exe $< $(DYNAMIC_FLAGS)

asan: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CCS) $(SFLAGS) -fsanitize=address -o app.exe $< $(DYNAMIC_FLAGS)

ubsan: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CCS) $(SFLAGS) -fsanitize=undefined -o app.exe $< $(DYNAMIC_FLAGS)

release: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CC) $(RFLAGS) -o app.exe $< $(DYNAMIC_FLAGS)

valgrind: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CC) $(VFLAGS) -o app.exe $< $(DYNAMIC_FLAGS)

.PHONY:
coverage: CFLAGS += --coverage
coverage: $(DYNAMIC_DEPS) $(DYNAMIC_LIBS)
	$(CC) $(CFLAGS) -o app.exe $^


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
	make clean

	make release
	./func_tests/scripts/func_tests.sh -v
	make clean

	make valgrind
	./func_tests/scripts/func_tests.sh -v --valgrind
	make clean

	make coverage


	# Тестирование с выводом
	./collect_coverage.sh


# Объектные файлы
$(OUT)main.o: $(SRC)main.c
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

.PHONY:
clean:
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda $(OUT)*.a



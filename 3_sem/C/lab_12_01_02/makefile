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

DYNAMIC_LIBS = $(OUT)libarray.so
DYNAMIC_FLAGS = -L $(OUT) -larray -Wl,-rpath=$(OUT)

UNIT_OBJECTS = $(OUT)check_main.o $(OUT)check_cmp.o $(OUT)check_form.o $(OUT)check_shift.o


# Опции для юнит тестов
UFLAGS := -std=c99 -g -O0 -Wpedantic -Werror -Wextra -Wall
ULIBS := -lcheck -lm -lpthread -lrt -lsubunit


# Опции для релизной версии
RFLAGS := -std=c99 -O3 -Wall -Wextra -Werror -Wpedantic

unit_test.exe: $(OUT)libarray.so $(UNIT_OBJECTS)
	$(CC) $(UFLAGS) -o $@ $(UNIT_OBJECTS) $(ULIBS) $(DYNAMIC_FLAGS)

# Библиотеки
$(OUT)libarray.so: $(SRC)array.c $(INC)array.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -I $(INC) -fPIC -c $< -o $(OUT)array.o
	$(CC) -o $@ -shared $(OUT)array.o

# Объектные файлы модульных тестов
$(OUT)check_cmp.o: $(UNIT_TESTS)check_cmp.c $(UNIT_TESTS)check_cmp.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

$(OUT)check_form.o: $(UNIT_TESTS)check_form.c $(UNIT_TESTS)check_form.h $(INC)array.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

$(OUT)check_shift.o: $(UNIT_TESTS)check_shift.c $(UNIT_TESTS)check_shift.h $(INC)array.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

$(OUT)check_main.o: $(UNIT_TESTS)check_main.c $(OUT)check_form.o $(OUT)check_shift.o
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

.PHONY:
clean:
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda $(OUT)*.o $(OUT)*.so $(OUT)*.a


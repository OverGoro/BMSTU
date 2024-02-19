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
ULIBS := -lcheck -lm -lpthread -lrt #-lsubunit

# Опции для релизной версии
RFLAGS := -std=c99 -O3 -Wall -Wextra -Werror -Wpedantic
#
PROG_DEPS = $(OUT)main.o
PROG_DEPS += $(OUT)my_snprintf.o

CHECK_DEPS = $(OUT)check_ho.o
CHECK_DEPS += $(OUT)check_s.o
CHECK_DEPS += $(OUT)check_all.o
CHECK_DEPS += $(OUT)check_main.o
CHECK_DEPS += $(OUT)my_snprintf.o

app.exe: $(PROG_DEPS)
	$(CC) $(CFLAGS) -o app.exe $^
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

$(OUT)my_snprintf.o: $(SRC)my_snprintf.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

$(OUT)main.o: $(SRC)main.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

$(OUT)%.o: $(UNIT_TESTS)%.c $(INC)*.h
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

# Unit тесты

clean:
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda


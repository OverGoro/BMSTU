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

# Опции для релизной версии
RFLAGS := -std=c99 -O3 -Wall -Wextra -Werror -Wpedantic

PROG_DEPS = $(OUT)main.o
PROG_DEPS += $(OUT)tree.o
PROG_DEPS += $(OUT)tree_node.o
PROG_DEPS += $(OUT)menu.o
PROG_DEPS += $(OUT)measure.o
PROG_LIBS = -lm

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

$(OUT)%.o: $(SRC)%.c $(HEADERS)
	mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -I $(INC) $< -o $@

clean:
	$(RM) *.exe $(OUT)*.o $(OUT)*.gcno $(OUT)*.gcov $(OUT)*gcda *.gv *.png


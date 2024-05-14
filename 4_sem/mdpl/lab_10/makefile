FILES = $(wildcard) *.s
LIBS = `pkg-config --cflags --libs gtk+-3.0`
app.exe:
	nasm -f elf64 -o main.o main.s
	nasm -f elf64 -o root.o root.s
	gcc root.o main.o $(LIBS) -o $@ -no-pie
clean:
	$(RM) *.o *.exe


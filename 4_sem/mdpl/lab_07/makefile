COMP = g++ -masm=intel
EXAMPLE_FILES = example.cpp
EXAMPLE_FILES_2 = example_2.cpp
main.exe: main.cpp memmove.asm
	nasm -f elf64 memmove.asm -o memmove_asm.o
	$(COMP) main.cpp -S -o main.asm
	$(COMP) main.cpp -c -o main.o
	$(COMP) main.o memmove_asm.o -o $@ -no-pie

example_2.exe: $(EXAMPLE_FILES_2)
	$(COMP) $^ -o $@
example.exe: $(EXAMPLE_FILES)
	$(COMP) $^ -o $@
clean:
	$(RM) *.o *.exe

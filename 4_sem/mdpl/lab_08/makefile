FILES = $(wildcard) *.cpp *.h *.hpp
task_1:
	g++ -O0 -std=c++20 -mno-80387 -Wall -masm=intel task_1_1.cpp -S -o task_1_1_no.s
	g++ -O0 -std=c++20 -m80387 -Wall -masm=intel task_1_1.cpp -S -o task_1_1_yes.s
	g++ -O0 -std=c++20 -m80387 -Wall -masm=intel task_1_1.cpp -o app.exe
	diff task_1_1_no.s task_1_1_yes.s >> difference.txt
	./app.exe
task_2:
	g++ -g3  -std=c++20 -Wall -masm=intel task_2.cpp -o app.exe
	./app.exe
task_3:
	nasm -f elf64 root.s -o root.o
	g++ -g3 -std=c++20 -Wall -masm=intel -c task_3.cpp -o task_3.o
	g++ -g3 -std=c++20  root.o task_3.o -o app.exe -no-pie
	./app.exe
clean:
	$(RM) *.o *.exe


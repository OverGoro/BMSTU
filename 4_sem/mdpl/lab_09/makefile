FILES = $(wildcard) *.cpp *.h *.hpp
task_1:
	g++ -g3 -O0 -std=c++20 -m80387 -Wall -fPIE -masm=intel task_1.cpp -S -o task_1_1.s
	g++ -g3 -O0 -std=c++20 -m80387 -Wall -fPIE -masm=intel task_1.cpp -o app.exe 
	./app.exe
clean:
	$(RM) *.o *.exe


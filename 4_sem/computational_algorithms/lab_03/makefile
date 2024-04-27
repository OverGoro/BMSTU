FILES = $(wildcard) ./source/*.cpp ./headers/*
FLAGS = -std=c++20 -g3 -Wall -Wno-unknown-pragmas
app.exe: $(FILES)
	g++ $(FLAGS) ./source/*.cpp -I ./headers/ -o $@
clean:
	$(RM) app.exe
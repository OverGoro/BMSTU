OBJECTS = $(wildcard) src/* include/*
FLAGS = -std=c++20 -g3 -Wall -Werror -Wpedantic -Wno-unknown-pragmas
app.exe: $(OBJECTS)
	clear
	g++ $(FLAGS) src/*.cpp -I ./include -o $@ -lgtest -lgmock -pthread
clean:
	$(RM) app.exe
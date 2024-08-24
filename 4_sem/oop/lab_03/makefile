# Находим все директории, содержащие .h файлы
HEADER_DIRS := $(shell find code -type f -name '*.h' | xargs -n 1 dirname | sort | uniq)

# Переменная для включения директорий в команду компиляции
INCLUDE_DIRS := $(foreach dir, $(HEADER_DIRS), -I $(dir))
INCLUDE_PRT := $(foreach dir, $(HEADER_DIRS), INCLUDEPATH += $(dir)"\n")

# Добавляем пути для Qt
# QT_INCLUDE_DIRS := -I /usr/include/x86_64-linux-gnu/qt6/QtWidgets/ -I /usr/include/x86_64-linux-gnu/qt6/
# INCLUDE_DIRS += $(QT_INCLUDE_DIRS)

# Переменные для компиляции
CC := g++
CFLAGS := -Wall -Wextra -O2 $(INCLUDE_DIRS)
LDFLAGS := -lQt6Widgets -lQt6Core -lQt6Gui  # Добавляем необходимые Qt библиотеки

# Находим все исходные файлы .cpp
SOURCES := $(shell find code -name '*.cpp' | sort | uniq)
SOURCES_PRT := $(foreach dir, $(SOURCES), SOURCES += $(dir)"\n")

HEADERS := $(shell find code -name '*.hpp' | sort | uniq)
HEADERS += $(shell find code -name '*.h' | sort | uniq)
HEADERS_PRT := $(foreach dir, $(HEADERS), HEADERS += $(dir)"\n")


INCLUDE_DIRS := $(foreach dir, $(HEADER_DIRS), INCLUDEPATH += $(dir)"\n")

# Создаём список объектных файлов, заменяя расширение .cpp на .o и указывая директорию build
OBJECTS := $(patsubst code/%.cpp, build/%.o, $(SOURCES))

# Имя конечного исполняемого файла
EXECUTABLE := app.exe

# Печать параметров (для отладки)
print_params:
	echo $(SOURCES_PRT)

# Правило для сборки исполняемого файла
$(EXECUTABLE): $(OBJECTS) $(SOURCES)
	clear
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Создаём объектные файлы в директории build
build/%.o: code/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: clean print_params

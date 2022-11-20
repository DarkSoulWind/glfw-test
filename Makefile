UNAME_S = $(shell uname -s)

CC = clang++
SRC_FILES = $(wildcard src/*.cpp) $(wildcard src/*.c) 
BUILD_DIR = build
OUTPUT = prog
INCLUDE_PATH = -Iinclude -Ilib/glfw/include -Iinclude/glad  -Iinclude/stb
CCFLAGS = -std=c++17 -g -Wall
LINKER_FLAGS = lib/glfw/src/libglfw3.a -lm

# MacOS required frameworks
ifeq ($(UNAME_S), Darwin)
	LINKER_FLAGS += -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
endif

OBJ = $(SRC_FILES:.cpp=.o)

.PHONY: all clean

all: dirs prog
	@echo "Built target $(BUILD_DIR)/$(OUTPUT)"

prog: $(OBJ)
	$(CC) -o $(BUILD_DIR)/$(OUTPUT) $^ $(LINKER_FLAGS) 

%.o: %.cpp
	@echo "Creating object $@"
	$(CC) -o $@ -c $< $(CCFLAGS) $(INCLUDE_PATH)

run:
	$(BUILD_DIR)/$(OUTPUT)

dirs:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(OBJ)

libs:
	cd lib/glfw && cmake . && make
CC = clang++
SRC_FILES = ${wildcard src/*.cpp} ${wildcard src/*.c} 
BUILD_DIR = build
OUTPUT = prog
INCLUDE_PATH = -I/opt/homebrew/Cellar/glfw/3.3.8/include -Iinclude
LIB_PATH = -L/opt/homebrew/Cellar/glfw/3.3.8/lib
LINKER_FLAGS = -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

all:
	${CC} ${SRC_FILES} ${INCLUDE_PATH} ${LIB_PATH} ${LINKER_FLAGS} -o ${BUILD_DIR}/${OUTPUT}

run:
	${BUILD_DIR}/${OUTPUT}
CC = gcc
CXX = g++

COMPILE_FLAGS = -Wall -ggdb -O3
LINK_FLAGS = -lglfw3 -lopengl32 -lglu32 -lgdi32

src = C:/Users/User/OneDrive/Desktop/everythingcomputerscience/Senior-Project

glfw_lib = $(src)/lib

INCLUDES = -I$(src)/include -I
LIBRARIES = -L$(glfw_lib)

cpp_files = main.cpp
objects = $(cpp_files:.cpp=.o)
headers =

all: main.exe

main.exe: $(objects) glad.o
		$(CXX) $(LIBRARIES) -o main.exe $(objects) glad.o $(LINK_FLAGS)

$(objects): %.o: %.cpp $(headers) makefile
		$(CXX) $(COMPILE_FLAGS) $(INCLUDES) -c -o $@ $<

glad.o: glad.c
		$(CC) $(COMPILE_FLAGS) $(INCLUDES) -c -o glad.o glad.c
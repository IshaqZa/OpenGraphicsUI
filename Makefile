default:
	g++ -o build/output.exe src/main.cpp src/glad.c -I include/ libglfw3.a -lgdi32
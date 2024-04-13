#include "ui/ui.h"

button::button(GLuint globalIndex, char* text, GLfloat xCoor, GLfloat yCoor, GLfloat width, GLfloat height):
    index(globalIndex),  text(text), xCoor(xCoor), yCoor(yCoor), width(width), height(height){};

void button::setText(char* text){ this->text = text; };

template<typename value, typename arg> value onClick(value (*action)(arg param, auto params...), ...){ 

    va_list args;
    va_start(args, auto);

    return action();

}


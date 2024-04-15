#include "ui/ui.h"
template<typename returnValue, typename... Args>
button<returnValue, Args...>::button(GLuint globalIndex, char* text, GLfloat xCoor, GLfloat yCoor, GLfloat width, GLfloat height):
    index(globalIndex),  text(text), xCoor(xCoor), yCoor(yCoor), width(width), height(height){};

template<typename returnValue, typename... Args>
void button<returnValue, Args...>::setText(std::string text){ this->text = text; };

template<typename returnValue, typename... Args>
void button<returnValue, Args...>::onClick(returnValue (*action)(Args...)){ 
    onClickAction = action;
}


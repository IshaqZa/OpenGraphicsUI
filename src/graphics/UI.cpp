#include "ui/ui.h"

button::button(GLuint globalIndex, char* text, GLfloat xCoor, GLfloat yCoor, GLfloat width, GLfloat height):
    index(globalIndex),  text(text), xCoor(xCoor), yCoor(yCoor), width(width), height(height){};

void button::setText(char* text){ this->text = text; };

template<typename Value, typename... Args> void button::onClick(Value (*action)(Args...), Args... params){ 

    this->action->func= action;
    this->action->params = std::make_tuple(params...);

}


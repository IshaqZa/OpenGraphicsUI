#include "ui/ui.h"
template<typename returnValue, typename... Args>
button<returnValue, Args...>::button(std::vector<GLfloat> vertices ,GLuint globalIndex, char* text, GLfloat xCoor, GLfloat yCoor, GLfloat width, GLfloat height):
    index(globalIndex),  text(text), xCoor(xCoor), yCoor(yCoor), width(width), height(height){

        vertices.insert(vector<GLfloat>(xCoor, yCoor, 0, rColor, gColor, bColor, 0, 1)); // top left
        vertices.insert(vector<GLfloat>(xCoor + width, yCoor, 0, rColor, gColor, bColor, 1, 1)); // top right
        vertices.insert(vector<GLfloat>(xCoor + width, yCoor + height, 0, rColor, gColor, bColor, 1, 0)); // bottom right
        vertices.insert(vector<GLfloat>(xCoor, yCoor + height, 0, rColor, gColor, bColor, 0, 0)); // bottom left
    };

template<typename returnValue, typename... Args>
void button<returnValue, Args...>::setText(std::string text){ this->text = text; };

template<typename returnValue, typename... Args>
void button<returnValue, Args...>::onClick(returnValue (*action)(Args...)){ 
    onClickAction = action;
}

template<typename returnValue, typename... Args>
returnValue button<returnValue, Args...>::invoke(Args...){
    return onClickAction(Args...)
}

template<typename returnValue, typename... Args>
void button<returnValue, Args...>::setPos(GLfloat x, GLfloat y){
    this->xCoor = x;
    this->yCoor = y;
}

template<typename returnValue, typename... Args>
void button<returnValue, Args...>::setSize(GLfloat width, GLfloat height){
    this->width = width;
    this->height = height;
}

template<typename returnValue, typename... Args>
void button<returnValue, Args...>::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha){
    this->xCoor = x;
    this->yCoor = y;
}

template<typename returnValue, typename... Args>
void button<returnValue, Args...>::setRenderType(int type){
    this->renderType = type;
}

template<typename returnValue, typename... Args>
void button<returnValue, Args...>::setTexture(unsigned char* bytes){
    this->image = bytes;
}

template<typename returnValue, typename... Args>
void button<returnValue, Args...>::draw(){
    
    glDrawArrays(GL_TRIANGLES, index, index + 3);
    glDrawArrays(GL_TRIANGLES, index + 1, index + 4);

}
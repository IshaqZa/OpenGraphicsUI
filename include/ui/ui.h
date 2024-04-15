#ifndef UI_CLASS_H
#define UI_CLASS_H

#include <glad/glad.h>
#include "string"
#include <vector>
#include <cstdarg>
#include <functional>
enum Texutre_Type {

    RGBA_TYPE = 0,
    IMAGE_TYPE = 1,

};

template<typename returnValue, typename... Args>
class button {

    private:
        GLuint index;
        std::string text;
        GLfloat xCoor, yCoor;
        GLfloat width, height;
        GLfloat rColor, gColor, bColor, alpha;
        std::function<returnValue(Args...)> onClickAction;

    public:
        button(GLuint globalIndex, char* text, GLfloat xCoor, GLfloat yCoor, GLfloat width, GLfloat height);
        void setText(std::string text);
        void onClick(returnValue (*action)(Args...));
        void setPos(GLfloat xCoor, GLfloat yCoor);
        void setSize(GLfloat xCoor, GLfloat yCoor);
        void setColor(GLfloat rColor, GLfloat gColor, GLfloat bColor, GLfloat alpha);
        void setTexture(GLfloat xCoor, GLfloat yCoor, unsigned char* bytes);
        returnValue invoke(Args...);
        void render();
};

#endif //UI_CLASS_H
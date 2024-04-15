#ifndef UI_CLASS_H
#define UI_CLASS_H

#include <glad/glad.h>
#include "string"
#include <vector>
#include <cstdarg>
#include <functional>
#include <glad/glad.h>

#define RGBA_TYPE 0
#define IMAGE_TYPE 1

template<typename returnValue, typename... Args>
class button {

    private:
        GLuint index;
        std::string text;
        Texture_Type renderType = RGBA_TYPE;
        GLfloat xCoor, yCoor;
        GLfloat width, height;
        GLfloat rColor, gColor, bColor, alpha;
        unsigned char* image;
        std::function<returnValue(Args...)> onClickAction;

    public:
        button(std::vector<GLfloat> vertices ,GLuint globalIndex, char* text, GLfloat xCoor, GLfloat yCoor, GLfloat width, GLfloat height);
        void setText(std::string text);
        void onClick(returnValue (*action)(Args...));
        void setPos(GLfloat xCoor, GLfloat yCoor);
        void setSize(GLfloat xCoor, GLfloat yCoor);
        void setColor(GLfloat rColor, GLfloat gColor, GLfloat bColor, GLfloat alpha);
        void setRenderType(int type);
        void setTexture(unsigned char* bytes);
        void render();
        returnValue invoke(Args...);
};

#endif //UI_CLASS_H
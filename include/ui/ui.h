#ifndef UI_CLASS_H
#define UI_CLASS_H

#include <glad/glad.h>
#include <string>
#include <vector>
#include <cstdarg>
enum Texutre_Type {

    RGBA_TYPE = 0,
    IMAGE_TYPE = 1,

};

class button {

    private:

        GLuint index;
        char* text;
        GLfloat xCoor, yCoor;
        GLfloat width, height;
        GLfloat rColor, gColor, bColor, alpha;
        
        auto action(auto param...);


    public:
        button(GLuint globalIndex, char* text, GLfloat xCoor, GLfloat yCoor, GLfloat width, GLfloat height);
        void setText(char* text);
        template<typename value, typename arg> void onClick(value (*action)(arg param...), ...);
        void setText(char* text);
        void setPos(GLfloat xCoor, GLfloat yCoor);
        void setSize(GLfloat xCoor, GLfloat yCoor);
        void setColor(GLfloat rColor, GLfloat gColor, GLfloat bColor, GLfloat alpha);
        void setTexture(GLfloat xCoor, GLfloat yCoor, unsigned char* bytes);
        void render();
};

#endif //UI_CLASS_H
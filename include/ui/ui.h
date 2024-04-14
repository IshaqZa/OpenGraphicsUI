#ifndef UI_CLASS_H
#define UI_CLASS_H

#include <glad/glad.h>
#include <string>
#include <vector>
#include <cstdarg>
#include <tuple>
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
        
        template <typename... Arg>
        struct Action {
            template<typename Value>
            using FuncPtr = Value (*)(Arg...);

            template<typename Value>
            void setFunc(FuncPtr<Value> ptr) {
                func<Value> = ptr;
            }
            std::tuple<Arg...> params;
        };
        Action<> action;


    public:
        button(GLuint globalIndex, char* text, GLfloat xCoor, GLfloat yCoor, GLfloat width, GLfloat height);
        void setText(char* text);
        template<typename Value, typename... Args> void onClick(Value (*action)(Args...), Args... params);
        void setText(char* text);
        void setPos(GLfloat xCoor, GLfloat yCoor);
        void setSize(GLfloat xCoor, GLfloat yCoor);
        void setColor(GLfloat rColor, GLfloat gColor, GLfloat bColor, GLfloat alpha);
        void setTexture(GLfloat xCoor, GLfloat yCoor, unsigned char* bytes);
        void render();
};

#endif //UI_CLASS_H
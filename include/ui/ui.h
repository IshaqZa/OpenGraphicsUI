#ifndef UI_CLASS_H
#define UI_CLASS_H

#include <glad/glad.h>
#include <string>
#include <vector>
#include <functional>
#include <glad/glad.h>

#define RGBA_TYPE 0
#define IMAGE_TYPE 1

template<typename returnValue, typename... Args>
class button {

    private:
        GLuint index;
        std::string text;
        int renderType = RGBA_TYPE;
        GLfloat xCoor, yCoor;
        GLfloat width, height;
        GLfloat rColor, gColor, bColor, alpha;
        std::function<returnValue(Args...)> onClickAction;

    public:
        button(std::vector<GLfloat> &vertices, std::vector<GLuint> &index,GLuint globalIndex, std::string text, GLfloat xCoor, GLfloat yCoor, GLfloat width, GLfloat height):
            index(globalIndex),  text(text), xCoor(xCoor), yCoor(yCoor), width(width), height(height){

            vertices.insert(vertices.end(), {

                // top left
                xCoor, yCoor, 0.0f, rColor, gColor, bColor, 0.0f, 1.0f,
                
                // top right
                xCoor + width, yCoor, 0.0f, rColor, gColor, bColor, 1.0f, 1.0f,
                
                // bottom right
                xCoor + width, yCoor - height, 0.0f, rColor, gColor, bColor, 1.0f, 0.0f,
                
                // bottom left
                xCoor, yCoor - height, 0.0f, rColor, gColor, bColor, 0.0f, 0.0f

            });

            index.insert(index.end(), {

                0, 1, 3,
                1, 2, 3

            });
        };
        void setText(std::string text){ this->text = text; }
        void onClick(returnValue (*action)(Args...)){ onClickAction = action; }
        void setPos(GLfloat xCoor, GLfloat yCoor){
            this->xCoor = xCoor;
            this->yCoor = yCoor;
        }
        void setSize(GLfloat xCoor, GLfloat yCoor){
            this->width = width;
            this->height = height;
        }
        void setColor(GLfloat rColor, GLfloat gColor, GLfloat bColor, GLfloat alpha){
            this->rColor = rColor;
            this->gColor = gColor;
            this->bColor = bColor;
            this->alpha = alpha;
        }
        void setRenderType(int type){ this->renderType = type; }
        void draw(){
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        returnValue invoke(Args... args){ return onClickAction(args...); }
};

#endif //UI_CLASS_H
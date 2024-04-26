#ifndef UI_CLASS_H
#define UI_CLASS_H

#include <glad/glad.h>
#include <string>
#include <vector>
#include <functional>
#include <glad/glad.h>
#include <Buffer/texture.h>

#define RGBA_TYPE 0
#define IMAGE_TYPE 1

class MenuElement {

    protected:
        GLuint index;
        std::string text;
        int renderType = RGBA_TYPE;
        GLfloat xCoor, yCoor;
        GLfloat width, height;
        GLfloat rColor = 0.0f, gColor = 0.0f, bColor = 0.0f, alpha=1.0f;
        Texture menuTexture = Texture("../resources/textures/placeholder.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    public:

        MenuElement(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices,GLuint globalIndex, std::string text, GLfloat xCoor, GLfloat yCoor, GLfloat width, GLfloat height):
            index(globalIndex),  text(text), xCoor(xCoor), yCoor(yCoor), width(width), height(height){};

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

        void updateColor(std::vector<GLfloat> &vertices, int colorOffSet){
            for(int i = 0; i < 4; i++){
                vertices[index + i * 9 + colorOffSet] = rColor;
                vertices[index + i * 9 + colorOffSet + 1] = gColor;
                vertices[index + i * 9 + colorOffSet + 2] = bColor;
                vertices[index + i * 9 + colorOffSet + 3] = alpha;
            }
        }

        void setRenderType(int renderType, GLuint texBool){
            this->renderType = renderType;
            glUniform1i(texBool, renderType);
        }

        //this function has been made for debugging purposes
        void printData(std::vector<GLfloat> vertices){
            
            for(int i = index; i < index + 9 * 4; i++){
                std::cout << vertices[i] << ",\t";
                if(i != 0 && (i+1)%9 == 0) std::cout << std::endl;
            }

        }

        void setText(std::string text){ this->text = text; }
        virtual void draw() = 0;
        virtual void setTexture(Texture texture, Shader& shader, const char* uniform, GLuint unit) = 0;

};

template<typename returnValue, typename... Args>
class button : public MenuElement{

    private:
        std::function<returnValue(Args...)> onClickAction;

    public:
        button(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices,GLuint globalIndex, std::string text, GLfloat xCoor, GLfloat yCoor, GLfloat width, GLfloat height):
            MenuElement(vertices, indices, globalIndex, text, xCoor, yCoor, width, height){

            vertices.insert(vertices.end(), {

                // top left
                xCoor, yCoor, 0.0f, rColor, gColor, bColor, alpha, 0.0f, 1.0f,
                
                // top right
                xCoor + width, yCoor, 0.0f, rColor, gColor, bColor, alpha, 1.0f, 1.0f,
                
                // bottom right
                xCoor + width, yCoor - height, 0.0f, rColor, gColor, bColor, alpha, 1.0f, 0.0f,
                
                // bottom left
                xCoor, yCoor - height, 0.0f, rColor, gColor, bColor, alpha, 0.0f, 0.0f

            });

            indices.insert(indices.end(), {

                index + 0, + index + 1, index + 3,
                index + 1, index + 2, index + 3

            });
        };

        void onClick(returnValue (*action)(Args...)){ onClickAction = action; }
        
        void setTexture(Texture texture, Shader& shader, const char* texLocation, GLuint unit) override{
            menuTexture = texture;
            menuTexture.texUnit(shader, texLocation, unit);
            

        }

        void draw() override{
            menuTexture.Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        returnValue invoke(Args... args){ return onClickAction(args...); }
};

#endif //UI_CLASS_H
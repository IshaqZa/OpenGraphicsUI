#ifndef UI_CLASS_H
#define UI_CLASS_H

#include <glad/glad.h>
#include <vector>
#include <functional>
#include <Buffer/texture.h>
#include <Buffer/EBO.h>
#include <memory>
#include "glm/glm.hpp"
#include "Shape.h"
#include "Json/json.hpp"
#include <TextRenderer/TextRenderer.h>

using json = nlohmann::json;


enum Shapes{
    TRIANGLE_SHAPE,
    RECTANGLE_SHAPE,
    CIRCLE_SHAPE
};

NLOHMANN_JSON_SERIALIZE_ENUM(Shapes,{
    {TRIANGLE_SHAPE, "triangle"},
    {RECTANGLE_SHAPE, "rectangle"},
    {CIRCLE_SHAPE, "circle"}
});

class Element{

    protected:
        GLuint index;
        Text text;
        Shapes shapeValue;
        std::shared_ptr<Shape> shape;
        std::shared_ptr<Appearance2D> appearance;
        std::shared_ptr<std::vector<GLuint>> indices;
        std::shared_ptr<EBO> ebo;

    public:
        Element(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::string text, std::shared_ptr<Appearance2D> appearance, Shapes shape);
        void setPos(glm::vec2 pos);
        void setSize(glm::vec2 size);
        void setColor(glm::vec4 color);
        void setRenderType(int renderType);
        bool contains(glm::vec2 pos);
        void updateVertices();
        //this function has been made for debugging purposes
        void printData(std::shared_ptr<std::vector<GLfloat>> vertices);
        void setTexture(Texture texture, Shader& shader, const char* uniform, GLuint unit);
        void setText(std::string text);
        
        virtual void draw(GLuint texBool)=0;
};

class Button : public Element{
    public:
        Button(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::string text, std::shared_ptr<Appearance2D> appearance, Shapes shape) 
        : Element(vertices, globalIndex, text, appearance, shape){};
        void draw(GLuint texBool) override;
};

class Label : public Element {
    private:
        std::shared_ptr<TextRenderer> textRenderer;
    public:
        Label(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::string text, std::shared_ptr<Appearance2D> appearance, Shapes shape, std::shared_ptr<TextRenderer> textRenderer)
        : Element(vertices, globalIndex, text, appearance, shape), textRenderer(textRenderer){}
        void draw(GLuint texBool) override;
};

#endif //UI_CLASS_H
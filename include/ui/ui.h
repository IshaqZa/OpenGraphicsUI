#ifndef UI_CLASS_H
#define UI_CLASS_H

#include <glad/glad.h>
#include <vector>
#include <functional>
#include <Buffer/texture.h>
#include <Buffer/EBO.h>
#include <memory>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shape.h"
#include "Json/json.hpp"
#include "TextRenderer/TextRenderer.h"


using json = nlohmann::json;

struct Rotation {
    float degree;
    glm::vec3 axis;
};

struct Transform
{
    glm::vec3 translate;
    Rotation rotate;
    glm::vec3 scale;
};


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

class MenuElement {

    protected:
        GLuint index;
        
        Shapes shapeValue;
        std::shared_ptr<Shape> shape;
        std::shared_ptr<Appearance2D> appearance;
        std::shared_ptr<std::vector<GLuint>> indices;
        std::shared_ptr<EBO> ebo;
        Transform transform;
        glm::mat4 model = glm::mat4(1.0f);

    public:
        MenuElement(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape);
        void setPos(glm::vec2 pos);
        void setSize(glm::vec2 size);
        void setColor(glm::vec4 color);
        void updateColor(std::shared_ptr<std::vector<GLfloat>> vertices, int colorOffSet);
        void setRenderType(int renderType);
        bool contains(glm::vec2 pos);
        void translate(glm::vec3 displace);
        void rotate(float degree, glm::vec3 axis);
        void scale(glm::vec3 scale);
        void updateModelMatrix();

        //this function has been made for debugging purposes
        void printData(std::shared_ptr<std::vector<GLfloat>> vertices);

        
        virtual void draw(GLuint texBool)=0;
        virtual void setTexture(Texture texture, Shader& shader, const char* uniform, GLuint unit)=0;

};

class Button : public MenuElement{

    private:
    public:
        Button(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape)
            : MenuElement(vertices, globalIndex, appearance, shape){};
        void setTexture(Texture texture, Shader& shader, const char* texLocation, GLuint unit) override;

        void draw(GLuint texBool) override;

        static std::shared_ptr<Button> create(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::string text, std::shared_ptr<Appearance2D> appearance, Shapes shape) {
            return std::make_shared<Button>(vertices, globalIndex, text, appearance, shape);
        }
};

class Label : public MenuElement {
    private:
        std::string text;
        std::shared_ptr<TextRenderer> textRenderer;
    public:
        Label(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape)
        : MenuElement(vertices, globalIndex, appearance, shape){};

        void setText(std::string text);
        void initTextRenderer(std::string fontPath);
        void setTextColor(glm::vec4 color);


        void draw(GLuint texBool) override;

        static std::shared_ptr<Label> create(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::string text, std::shared_ptr<Appearance2D> appearance, Shapes shape) {
            return std::make_shared<Label>(vertices, globalIndex, text, appearance, shape);
        }
};

#endif //UI_CLASS_H
#include <vector>
#include <memory>
#include "glad/glad.h"
#include "Appearance.h"
class Shape {

public:
    virtual void generateVertices(Appearance2D* appearance) = 0;
    virtual void generateIndices(std::vector<GLuint> *indices) = 0;
    virtual void draw() = 0;

};

class Square : public Shape{
    private:
        std::vector<GLfloat> *vertices;
        std::vector<GLuint> *indices;

    public:
        Square(std::vector<GLfloat> *vertices, std::vector<GLuint> *indices) : vertices(vertices), indices(indices){};

        void generateVertices(Appearance2D* appearance) override {
            vertices->insert(vertices->end(), {

                // top left
                appearance->position.x, appearance->position.y, 0.0f, appearance->color.x, appearance->color.y, appearance->color.z, appearance->color.w, 0.0f, 1.0f, 
                
                // top right
                appearance->position.x + appearance->size.x, appearance->position.y, 0.0f, appearance->color.x, appearance->color.y, appearance->color.z, appearance->color.w, 1.0f, 1.0f,
                
                // bottom right
                appearance->position.x + appearance->size.x, appearance->position.y - appearance->size.y, 0.0f, appearance->color.x, appearance->color.y, appearance->color.z, appearance->color.w, 1.0f, 0.0f,
            
                // bottom left
                appearance->position.x, appearance->position.y - appearance->size.y, 0.0f, appearance->color.x, appearance->color.y, appearance->color.z, appearance->color.w, 0.0f, 0.0f

                }
            );
        }

        
            

};
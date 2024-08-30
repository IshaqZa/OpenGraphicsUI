#include "ui/Shape.h"

Square::Square(std::shared_ptr<std::vector<GLfloat>> vertices, std::shared_ptr<std::vector<GLuint>> indices){
    this->vertices=vertices;
    this->indices=indices;
}

void Square::generateVertices(std::shared_ptr<Appearance2D> appearance){
    std::cout << "Accessed generate vertices" << std::endl;
    try {
        if(!appearance) throw std::runtime_error("appearance null");
        if(!vertices) throw std::runtime_error("Vertices null");

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
    }catch(std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    } catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < vertices->size(); i++){
        if(i%9 == 0 && i !=0) std::cout << std::endl;
        std::cout << (*vertices)[i] << ", ";
        
    }

    std::cout << "Added vertices" << std::endl;
}

void Square::generateIndices(GLuint index){
    std::cout << "Current Global Index: " <<  index << std::endl;
    indices->insert(indices->end(), {
       index + 0, index + 1, index + 3,
       index + 1, index + 2, index + 3
    });

    for(int i = 0; i < indices->size(); i++){
        if(i%3 == 0 && i!=0) std::cout << std::endl;
        std::cout << (*indices)[i] << ", ";
    }

}

void Square::draw() {
    std::cout << "calling draw elements" << std::endl;
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}



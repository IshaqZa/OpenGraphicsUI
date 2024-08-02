#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <shader/shader.h>
#include <Buffer/EBO.h>
#include <Buffer/VAO.h>
#include <Buffer/texture.h>
#include <Buffer/VBO.h>
struct Vertex{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoors;
};

struct Texture{
    unsigned int id;
    std::string type;
};

class Mesh{
    public:
        // mesh data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader &shader);
    private:
        //  render data
        VAO vao;
        VBO vbo;
        EBO ebo;

        void setupMesh();
};
#endif
#ifndef APPEARANCE_CLASS_H
#define APPEARANCE_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <vector>
#include <Buffer/EBO.h>
#include <Buffer/texture.h>
#include "glm/glm.hpp"

#define RGBA_TYPE 0
#define IMAGE_TYPE 1

struct Appearance2D {
    glm::vec2 position;
    glm::vec2 size;
    glm::vec4 color;
    glm::vec2 texturePos;
    Texture texture;
    int renderType;

    Appearance2D(glm::vec2 position, glm::vec2 size, glm::vec4 color, glm::vec2 texturePos,
      Texture texture = Texture("../resources/textures/placeholder.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE), int renderType = RGBA_TYPE)
        : position(position), color(color), texturePos(texturePos), texture(texture), renderType(renderType), size(size){}
};

#endif
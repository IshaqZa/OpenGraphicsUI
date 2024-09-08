#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <map>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <shader/shader.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>

struct Character {
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};

class TextRenderer {
private:
    FT_Library ft;
    FT_Face face;
    std::map<char, Character> Characters;
    Shader s;
    VBO vbo;
    VAO vao;

public:
    void init();
    void loadFont(std::string path);
    void setFontSize(int size);
    void setFontSize(int width, int height);
    void loadCharacters();
    void clear();
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
};
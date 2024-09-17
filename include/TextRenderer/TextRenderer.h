#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <map>
#include <glad/glad.h>
#include <shader/shader.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <TextRenderer/FontLoader.h>
#include <memory>
#include <glm/glm.hpp>

struct Text {
    std::string text;
    glm::vec3 color;
};

class TextRenderer {
private:
    FT_Face face;
    std::map<char, Character> Characters;
    Shader s;
    VBO vbo;
    VAO vao;

public:
    void setFontSize(int size);
    void setFontSize(int width, int height);
    void loadCharacters(std::string path, std::shared_ptr<FontLoader> loader);
    void clear();
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
};
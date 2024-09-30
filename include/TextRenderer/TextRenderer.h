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
#include <vector>

struct Text {
    std::string text;
    glm::vec3 color;
};

class TextRenderer {
private:
    FT_Face face;
    Shader shader;
    std::map<char, Character> Characters;
    std::shared_ptr<VBO> vbo;
    VAO vao;

public:
    TextRenderer(Shader shader) : shader(shader) {};
    void setFontSize(int size);
    void setFontSize(int width, int height);
    void loadCharacters(std::string path, std::shared_ptr<FontLoader> loader);
    void clear();
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
};
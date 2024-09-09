#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <map>
#include <glad/glad.h>
#include <shader/shader.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <TextRenderer/Character.h>

class FontLoader {

    private:
        FT_Library ft;
        FT_Face face;

    public:
        FontLoader();
        void clear();
        void loadFont(std::string path, FT_Face &face);
        void loadCharacters(std::map<char, Character> Characters);

};
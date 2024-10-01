#include <TextRenderer/TextRenderer.h>

void TextRenderer::loadCharacters(std::string path, std::shared_ptr<FontLoader> loader){
    loader->loadFont(path, face);
    std::cout << "Loaded font.ttf file" << std::endl;
    loader->loadCharacters(Characters);
    std::cout << "stored characters info from font" << std::endl;
    loader->clear();
    std::cout << "Cleared resources" << std::endl;
}

void TextRenderer::setFontSize(int size){
    FT_Set_Pixel_Sizes(face, 0, size);
}

void TextRenderer::setFontSize(int width, int height){
    FT_Set_Pixel_Sizes(face, width, height);
}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color){
    
    std::cout << "rendering text: " << text << std::endl;
    
    shader.Activate();
    std::cout << "activating shader for text rendering" << std::endl;

    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    std::cout << "Setting text color" << std::endl;

    glActiveTexture(GL_TEXTURE0);
    std::cout << "setting active texture slot to GL_TEXTURE0 in RenderText function" << std::endl;
    
    vao.Bind();
    std::cout << "Binding text render vao" << std::endl;

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        std::vector<GLfloat> vertices = {
            xpos,     ypos + h,   0.0f, 0.0f ,            
            xpos,     ypos,       0.0f, 1.0f ,
            xpos + w, ypos,       1.0f, 1.0f ,
            xpos,     ypos + h,   0.0f, 0.0f ,
            xpos + w, ypos,       1.0f, 1.0f ,
            xpos + w, ypos + h,   1.0f, 0.0f          
        };

        if(vbo == nullptr) {
            vbo = std::make_shared<VBO>(vertices.data(), vertices.size() * sizeof(vertices));
            std::cout << "set vertices vector to text vbo" << std::endl;
            vao.linkAttrib((*vbo), 0, 2, GL_FLOAT, 4, (void*)0);
            vao.linkAttrib((*vbo), 1, 2, GL_FLOAT, 4, (void*)(2 * sizeof(GLfloat)));
            std::cout << "set VAO parameters" << std::endl;
        }

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        vbo->Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());
        std::cout << "updated vbo data for new character" << std::endl;
        glCheckError();
        vbo->Unbind();
        // render quad
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        std::cout << "called draw call for glyph: " << *c << std::endl;
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        std::cout << "move cursor forward for next glyph" << std::endl;
        glCheckError();
    }
    vao.Unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();

}
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

    shader.Activate();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    vao.Bind();

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

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        vbo->Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data()); 
        vbo->Unbind();
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    vao.Unbind();
    glBindTexture(GL_TEXTURE_2D, 0);

}
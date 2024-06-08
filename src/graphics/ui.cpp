#include "ui/ui.h"

void MenuElement::setPos(glm::vec2 pos){
    appearance->position = pos;
}

void MenuElement::setSize(glm::vec2 size){
    appearance->size = size;
}

void MenuElement::setColor(glm::vec4 color){
    appearance->color = color;
}

void MenuElement::updateColor(std::vector<GLfloat> &vertices, int colorOffSet){
    for(int i = 0; i < 4; i++){
        vertices[index + i * 9 + colorOffSet] = appearance->color.x;
        vertices[index + i * 9 + colorOffSet + 1] = appearance->color.y;
        vertices[index + i * 9 + colorOffSet + 2] = appearance->color.z;
        vertices[index + i * 9 + colorOffSet + 3] = appearance->color.w;
    }
}

void MenuElement::setRenderType(int renderType){
    appearance->renderType = renderType;
}

void MenuElement::printData(std::vector<GLfloat> vertices){
    std::cout << "Vertex Data: " << std::endl;
    for(int i = index; i < index + 9 * 4; i++){
        std::cout << vertices[i] << ",\t";
        if(i != 0 && (i+1)%9 == 0) std::cout << std::endl;
    }
    std::cout << "Index Data: " << std::endl;
    for(int i = 0; i < 6; i ++){

        std::cout << indices[i] << ",\t";
        if(i!=0 && (i+1)%3 == 0) std::cout << std::endl;

    }
}

void MenuElement::setText(std::string text){ this->text = text; }

Button::Button(std::vector<GLfloat> &vertices, GLuint* globalIndex, std::string text, std::unique_ptr<Appearance2D> appearance, std::unique_ptr<Shape> shape) {
    GLuint eboIndex = *globalIndex / 9;
    indices.insert(indices.end(), {

        eboIndex + 0, eboIndex + 1, eboIndex + 3,
        eboIndex + 1, eboIndex + 2, eboIndex + 3

    });
    ebo = std::make_unique<EBO>(indices.data(), indices.size() * sizeof(indices));
    *globalIndex += 36;
};

void Button::setTexture(Texture texture, Shader& shader, const char* texLocation, GLuint unit) { 
    appearance->texture = texture;
    appearance->texture.texUnit(shader, texLocation, unit);
}

void Button::draw(GLuint texBool) {
    appearance->texture.Bind();
    glUniform1i(texBool, appearance->renderType);
    try{
        ebo->Bind();
    } catch(std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    appearance->texture.Unbind();
    ebo->Unbind();
}
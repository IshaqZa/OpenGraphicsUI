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

void MenuElement::updateColor(std::shared_ptr<std::vector<GLfloat>> vertices, int colorOffSet){
    for(int i = 0; i < 4; i++){
        (*vertices)[index + i * 9 + colorOffSet] = appearance->color.x;
        (*vertices)[index + i * 9 + colorOffSet + 1] = appearance->color.y;
        (*vertices)[index + i * 9 + colorOffSet + 2] = appearance->color.z;
        (*vertices)[index + i * 9 + colorOffSet + 3] = appearance->color.w;
    }
}

void MenuElement::setRenderType(int renderType){
    if(!appearance) std::cout << "Appearance is null" << std::endl;
    else appearance->renderType = renderType;
}

void MenuElement::printData(std::shared_ptr<std::vector<GLfloat>> vertices){
    std::cout << "Vertex Data: " << std::endl;
    for(int i = index; i < index + 9 * 4; i++){
        std::cout << (*vertices)[i] << ",\t";
        if(i != 0 && (i+1)%9 == 0) std::cout << std::endl;
    }
    std::cout << "Index Data: " << std::endl;
    for(int i = 0; i < 6; i ++){

        std::cout << (*indices)[i] << ",\t";
        if(i!=0 && (i+1)%3 == 0) std::cout << std::endl;

    }
}

void MenuElement::setText(std::string text){ this->text = text; }

Button::Button(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::string text, std::shared_ptr<Appearance2D> appearance, Shapes shape) {

    this->appearance = appearance;
    GLuint eboIndex = *globalIndex / 9;

    indices = std::make_shared<std::vector<GLuint>>();

    switch(shape){
        case RECTANGLE_SHAPE:
            std::cout<< "Inside case" << std::endl;
            this->shape = std::make_unique<Square>(vertices, indices);
            std::cout << "Created shape object shared pointer" << std::endl;
            this->shape->generateVertices(appearance);
            std::cout << "Generated vertices" << std::endl;
            this->shape->generateIndices();
            std::cout << "Generated indices" << std::endl;
        break;
    }

    std::cout << "Created Shape" << std::endl;
    ebo = std::make_shared<EBO>(indices->data(), indices->size() * sizeof(indices));
    *globalIndex += 36;
};

void Button::setTexture(Texture texture, Shader& shader, const char* texLocation, GLuint unit) { 
    appearance->texture = texture;
    appearance->texture.texUnit(shader, texLocation, unit);
}

void Button::draw(GLuint texBool) {
    appearance->texture.Bind();
    std::cout << "texture bind" << std::endl;
    glUniform1i(texBool, appearance->renderType);
    std::cout << "texBool set" << std::endl;
    try{
        ebo->Bind();
    } catch(std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "ebo bind" << std::endl;
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    std::cout << "Draw call" << std::endl;

    appearance->texture.Unbind();
    std::cout << "Unbind texutre" << std::endl;
    ebo->Unbind();
    std::cout << "Unbind ebo" << std::endl;
}
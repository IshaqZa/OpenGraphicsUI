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
    // std::cout << "Set render type for appearance attribute" << std::endl;
}

void MenuElement::printData(std::shared_ptr<std::vector<GLfloat>> vertices){
    std::cout << "Vertex Data: " << std::endl;
    for(int i = index; i < index + 9 * 4; i++){
        std::cout << "reach here" << std::endl;
        std::cout << (*vertices)[i] << ",\t";
        if(i != 0 && (i+1)%9 == 0) std::cout << std::endl;
    }
    std::cout << "Index Data: " << std::endl;
    for(int i = 0; i < 6; i ++){

        std::cout << (*indices)[i] << ",\t";
        if(i!=0 && (i+1)%3 == 0) std::cout << std::endl;

    }
}

bool MenuElement::contains(glm::vec2 pos){
    if(pos.x > appearance->position.x && pos.x < (appearance->position.x + appearance->size.x)){
        if(pos.y < appearance->position.y && pos.y > (appearance->position.y - appearance->size.y)){
            return true;
        }
    }
    return false;
}

void MenuElement::setText(std::string text){ this->text = text; }

Button::Button(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::string text, std::shared_ptr<Appearance2D> appearance, Shapes shape) {

    this->appearance = appearance;
    GLuint eboIndex = *globalIndex / 9;

    indices = std::make_shared<std::vector<GLuint>>();
    shapeValue = shape;
    switch(shapeValue){
        case RECTANGLE_SHAPE:
            this->shape = std::make_unique<Square>(vertices, indices);
            // std::cout << "Created shape object shared pointer" << std::endl;
            this->shape->generateVertices(appearance);
            // std::cout << "Generated vertices" << std::endl;
            this->shape->generateIndices(eboIndex);
            // std::cout << "Generated indices" << std::endl;
        break;
    }

    // std::cout << "Created Shape" << std::endl;
    ebo = std::make_shared<EBO>(indices->data(), indices->size() * sizeof(indices));
    *globalIndex += 36;
    // std::cout << "Created ebo and updated global index" << std::endl;
};

void Button::setTexture(Texture texture, Shader& shader, const char* texLocation, GLuint unit) { 
    appearance->texture = texture;
    appearance->texture.texUnit(shader, texLocation, unit);
    // std::cout << "Set texture for button" << std::endl;
}

void Button::draw(GLuint texBool) {
    // std::cout << "Binding texture" << std::endl;
    appearance->texture.Bind();
    // std::cout << "Setting render type" << std::endl;
    glUniform1i(texBool, appearance->renderType);
    try{
        // std::cout << "Binding EBO" << std::endl;
        ebo->Bind();
    } catch(std::runtime_error& e){

        std::cerr << "Error: " << e.what() << std::endl;

    } catch(std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    // std::cout << "calling draw from shape object" << std::endl;
    shape->draw();

    // std::cout << "Unbinding textuer and ebo" << std::endl;
    appearance->texture.Unbind();
    ebo->Unbind();
    // std::cout << "Unbinding done" << std::endl;
}
#include "ui/ui.h"

MenuElement::MenuElement(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape) {

    std::cout << "set text for menu element" << std::endl;

    index = *globalIndex;

    if(!vertices){
        std::cout << "vertices passed to Button constructor is empty" << std::endl;
        exit(EXIT_FAILURE);
    }

    this->appearance = appearance;
    std::cout << "set appearance for menu element" << std::endl;
    if(!this->appearance) {
        std::cout << "Error assigning appearance shared_ptr" << std::endl;
        exit(EXIT_FAILURE);
    }
    GLuint eboIndex = *globalIndex / 9;
    std:: cout << "normalized global index to fit eboIndex" << std::endl;

    indices = std::make_shared<std::vector<GLuint>>();
    if(!indices){
        std::cout << "Error creating shared_ptr for indices" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Made indcies shared ptr" << std::endl;
    shapeValue = shape;
    switch(shapeValue){
        case RECTANGLE_SHAPE:
            this->shape = std::make_unique<Square>(vertices, indices);
            if(!this->shape){
                std::cout << "Error making shape unique pointer in Button constructor" << std::endl;
            }
            std::cout << "Created shape object shared pointer" << std::endl;
            this->shape->generateVertices(appearance);
            std::cout << "Generated vertices" << std::endl;
            this->shape->generateIndices(eboIndex);
            std::cout << "Generated indices" << std::endl;
        break;
    }

    std::cout << "Created Shape" << std::endl;
    ebo = std::make_shared<EBO>(indices->data(), indices->size() * sizeof(GLuint));
    if(ebo==nullptr) std::cout << "Error creating EBO shared_ptr" << std::endl;
    *globalIndex += 36;
    std::cout << "Created ebo and updated global index" << std::endl;
};

void MenuElement::setPos(glm::vec2 pos){
    appearance->position = pos;
}

void MenuElement::setSize(glm::vec2 size){
    appearance->size = size;
}

void MenuElement::setColor(glm::vec4 color){
    appearance->color = color;
    std::cout << "Set new color for menu element" << std::endl;
}

void MenuElement::updateColor(std::shared_ptr<std::vector<GLfloat>> vertices, int colorOffSet){
    for(int i = 0; i < 4; i++){
        std::cout << "iteration color update number: " << (i+1) << std::endl;
        std::cout << "accessing vertex at index: " << (index + i * 9 + colorOffSet) << std::endl;
        std::cout << "current index: " << index << std::endl;
        (*vertices)[index + i * 9 + colorOffSet] = appearance->color.x;
        (*vertices)[index + i * 9 + colorOffSet + 1] = appearance->color.y;
        (*vertices)[index + i * 9 + colorOffSet + 2] = appearance->color.z;
        (*vertices)[index + i * 9 + colorOffSet + 3] = appearance->color.w;
        
    }
    std::cout << "updated color for menu element" << std::endl;
}

void MenuElement::setRenderType(int renderType){
    if(!appearance) std::cout << "Appearance is null" << std::endl;
    else appearance->renderType = renderType;
    // std::cout << "Set render type for appearance attribute" << std::endl;
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

bool MenuElement::contains(glm::vec2 pos){
    if(pos.x > appearance->position.x && pos.x < (appearance->position.x + appearance->size.x)){
        if(pos.y < appearance->position.y && pos.y > (appearance->position.y - appearance->size.y)){
            return true;
        }
    }
    return false;
}

void Button::setTexture(Texture texture, Shader& shader, const char* texLocation, GLuint unit) {
    std::cout << "accessed set texture function from button class" << std::endl;
    this->texture = std::make_shared<Texture>(texture);
    std::cout << "changed texture" << std::endl;
    this->texture->texUnit(shader, texLocation, unit);
    std::cout << "called texUnit for texture change" << std::endl;
    std::cout << "Set texture for button" << std::endl;
}

void Button::draw(GLuint texBool) {

    if(!appearance || !shape || !ebo) {
        std::cerr << "Error drawing button due to initialised data" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Binding texture" << std::endl;
    if(appearance->renderType == IMAGE_TYPE) {
        this->texture->Bind();
    }
    std::cout << "Setting render type" << std::endl;
    glUniform1i(texBool, appearance->renderType);
    try{
        std::cout << "Binding EBO" << std::endl;
        ebo->Bind();
    } catch(std::runtime_error& e){

        std::cerr << "Error: " << e.what() << std::endl;

    } catch(std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "calling draw from shape object" << std::endl;
    shape->draw();

    std::cout << "Unbinding texture and ebo" << std::endl;
    if(appearance->renderType == IMAGE_TYPE) {
        this->texture->Unbind();
    }
    // ebo->Unbind();
    std::cout << "Unbinding done" << std::endl;
}
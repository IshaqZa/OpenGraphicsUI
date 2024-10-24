#include <UI/UIBuilder.h>


UIBuilder& UIBuilder::setPosition(glm::vec2 pos){
    this->pos = pos;
    return (*this);
}

UIBuilder& UIBuilder::setColor(glm::vec4 color){
    this->color = color;
    return (*this);
}

UIBuilder& UIBuilder::setSize(glm::vec2 size){
    this->size = size;
    return (*this);
}

UIBuilder& UIBuilder::setRenderType(int type){
    this->renderType = type;
    return (*this);
}

UIBuilder& UIBuilder::setTexture(std::shared_ptr<Texture> texture){
    this->texture = texture;
    return (*this);
}

UIBuilder& UIBuilder::setTexture(std::string path){
    this->texture = std::make_shared<Texture>(path.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    return (*this);
}

UIBuilder& UIBuilder::setShape(Shapes shape){
    this->shape = shape;
    return (*this);
}

bool UIBuilder::checkNull(){
    
    bool result = true;
    if(renderType == -1) {
        std::cout << "render type has not been set in ui builder" << std::endl;
        result = false;
    }
    return result;
    
}

std::shared_ptr<Button> UIBuilder::buildButton(){
    if(checkNull()){
        std::shared_ptr<Appearance2D> app = std::make_shared<Appearance2D>(
            pos,
            size,
            color,
            renderType
        );

        std::shared_ptr<Button> btn = std::make_shared<Button>(scene->getVertices(), scene->currentIndex(), app, shape);
        btn->setTexture((*texture), (*scene->getShaderProgram()), "tex", 0);
        return btn;
    }
    return nullptr;
}

std::shared_ptr<MenuElement> UIBuilder::buildElement(std::string type){
    if(checkNull()){
        std::shared_ptr<Appearance2D> app = std::make_shared<Appearance2D>(
            pos,
            size,
            color,
            renderType
        );
        std::cout << "Appearance pointer created for element" << std::endl;
        
        uiFactory = UIFactory::getInstance();
        std::shared_ptr<MenuElement> element = uiFactory->create(type, scene->getVertices(), scene->currentIndex(), app, shape);
        std::cout << "create function called for element" << std::endl;
        if(texture != nullptr){
            element->setTexture((*texture), (*(scene->getShaderProgram())), "tex", 0);
        }
        return element;
    }
    return nullptr;
}

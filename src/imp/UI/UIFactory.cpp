#include <ui/UIFactory.h>

UIFactory* UIFactory::instance = nullptr;

void UIFactory::addType(std::string typeName, std::function<std::shared_ptr<MenuElement>(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape)> func){
    registry[typeName] = func; 
}

std::shared_ptr<MenuElement> UIFactory::create(std::string typeName, std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape){
    if(registry.find(typeName) == registry.end()) {
        std::cout << "type (" << typeName << ") is not registered in the factory" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "calling create function for type: " << typeName << std::endl;
    return (registry[typeName])(vertices, globalIndex, appearance, shape);
}

UIFactory* UIFactory::getInstance(){
    if(instance == nullptr){
        instance = new UIFactory();
    }
    return instance;
}
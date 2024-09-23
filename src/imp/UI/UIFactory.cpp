#include <ui/UIFactory.h>

void UIFactory::registerType(std::string typeName,
std::function<std::shared_ptr<MenuElement>(
    std::shared_ptr<std::vector<GLfloat>> vertices,
    GLuint* globalIndex, 
    std::shared_ptr<Appearance2D> appearance, 
    Shapes shape)> factoryFunction
){
    types[typeName] = factoryFunction;
}

std::shared_ptr<MenuElement> UIFactory::buildObject(std::string typeName, std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape){
    return (types[typeName])(vertices, globalIndex, appearance, shape);
}
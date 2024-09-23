#ifndef UIFACTORY_CLASS_H
#define UIFACTORY_CLASS_H
#include <iostream>
#include <functional>
#include <memory>
#include <ui/ui.h>

class UIFactory {
    private:
        std::unordered_map<std::string, std::function<std::shared_ptr<MenuElement>(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape)>> types;
        static UIFactory* factoryptr;
    public:
        void registerType(std::string typeName, 
        std::function<std::shared_ptr<MenuElement>(
            std::shared_ptr<std::vector<GLfloat>> vertices, 
            GLuint* globalIndex, 
            std::shared_ptr<Appearance2D> appearance, 
            Shapes shape
        )> factoryFunction);
        
        std::shared_ptr<MenuElement> buildObject(std::string typeName, std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape);
        static UIFactory& getInstance();
};

#endif
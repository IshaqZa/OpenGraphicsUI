#ifndef SCENE2D_CLASS_H
#define SCENE2D_CLASS_H
#include "Scene/Scene.h"

class Scene2D : public Scene{

    private:
        std::shared_ptr<EventHandler> events;
        std::unordered_map<std::string, std::shared_ptr<MenuElement>> elementArray;

    public:
        Scene2D();
        void addEventListener(EventType eventType, std::string elementName, std::function<void()> action);
        std::shared_ptr<MenuElement> getElementByName(std::string name);
        void addElement(std::string name, std::shared_ptr<MenuElement> element);
        void render() override;
        void update(GLFWwindow* window) override;
};

#endif
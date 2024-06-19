#ifndef CLASS_EVENT_HANDLER
#define CLASS_EVENT_HANDLER

#include <vector>
#include <functional>
#include "ui/ui.h"
#include <GLFW/glfw3.h>

class EventHandler{

private:
    struct ClickableElement {
        std::shared_ptr<MenuElement> element;
        std::function<void()> action;
    };
    std::vector<ClickableElement> onClickElements;

    GLfloat normalizeX(GLfloat value, GLfloat width);
    GLfloat normalizeY(GLfloat value, GLfloat height);
    void processOnClick(GLFWwindow* window);
public:
    void addOnClickElement(std::shared_ptr<MenuElement> element, std::function<void()> action);
    void processInputs(GLFWwindow* window);

};

#endif
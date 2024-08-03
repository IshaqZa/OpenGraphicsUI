#ifndef CLASS_EVENT_HANDLER
#define CLASS_EVENT_HANDLER

#include <vector>
#include <functional>
#include "ui/ui.h"
#include <GLFW/glfw3.h>

class EventHandler{

private:
    struct ActionElement {
        std::shared_ptr<MenuElement> element;
        std::function<void()> action;
    };
    std::vector<ActionElement> onClickElements;
    std::vector<ActionElement> OnHoverEnterElements;
    std::vector<ActionElement> OnHoverLeaveElements;
    bool isHovered = false;
    ActionElement* currentlyHovered = nullptr;
    

    GLfloat normalizeX(GLfloat value, GLfloat width);
    GLfloat normalizeY(GLfloat value, GLfloat height);
    void processOnClick(GLFWwindow* window);
    void processOnHoverEnter(GLFWwindow* window);
    void processOnHoverLeave(GLFWwindow* window);
public:
    void addOnClickElement(std::shared_ptr<MenuElement> element, std::function<void()> action);
    void addOnHoverEnterElement(std::shared_ptr<MenuElement> element, std::function<void()> action);
    void addOnHoverLeaveElement(std::shared_ptr<MenuElement> element, std::function<void()> action);
    void processInputs(GLFWwindow* window);
    

};

#endif
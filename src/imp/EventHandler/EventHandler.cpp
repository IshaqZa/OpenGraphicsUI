#include "EventHandler/EventHandler.h"
void EventHandler::addOnClickElement(std::shared_ptr<MenuElement> element, std::function<void()> action){

    onClickElements.push_back({element, action});

}

void EventHandler::addOnHoverEnterElement(std::shared_ptr<MenuElement> element, std::function<void()> action){
    OnHoverEnterElements.push_back({element, action});
}

void EventHandler::addOnHoverLeaveElement(std::shared_ptr<MenuElement> element, std::function<void()> action){
    OnHoverLeaveElements.push_back({element, action});
}

GLfloat EventHandler::normalizeX(GLfloat value, GLfloat width){
    return -1.0f + 2.0f * value / width;
}
GLfloat EventHandler::normalizeY(GLfloat value, GLfloat height){
    return 1.0f - 2.0f * value / height;
}

void EventHandler::processOnClick(GLFWwindow* window){

    static int previousMouseButtonState = GLFW_RELEASE;
    
    int currentMouseButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    if(currentMouseButtonState == GLFW_PRESS && previousMouseButtonState == GLFW_RELEASE){
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        GLfloat normalizedX = normalizeX(x, width);
        GLfloat normalizedY = normalizeY(y, height);

        glm::vec2 pos(normalizedX, normalizedY);
        
        for(const auto& clickable : onClickElements){
            if(clickable.element->contains(pos)){
                clickable.action();
                break;
            }
        }

        previousMouseButtonState = currentMouseButtonState;
    }
    if(currentMouseButtonState == GLFW_RELEASE) previousMouseButtonState = GLFW_RELEASE;
}

void EventHandler::processOnHoverEnter(GLFWwindow* window){
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    GLfloat normalizedX = normalizeX(x, width);
    GLfloat normalizedY = normalizeY(y, height);

    glm::vec2 pos(normalizedX, normalizedY);

    for(auto& hoverable : OnHoverEnterElements){
        if(hoverable.element->contains(pos)){
            isHovered = true;
            currentlyHovered = &hoverable;
            std::cout << "hovered: " << isHovered << std::endl;
            hoverable.action();
            break;
        }
    }
}

void EventHandler::processOnHoverLeave(GLFWwindow* window){
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    GLfloat normalizedX = normalizeX(x, width);
    GLfloat normalizedY = normalizeY(y, height);

    glm::vec2 pos(normalizedX, normalizedY);

    for(auto& hoverable : OnHoverLeaveElements){
        if((!hoverable.element->contains(pos)) && isHovered && hoverable.element == currentlyHovered->element){
            std::cout << "Entered if statement for hover leave" << std::endl;
            isHovered = false;
            hoverable.action();
            break;
        }
    }
}

void EventHandler::processInputs(GLFWwindow* window){
    processOnClick(window);
    std::cout << "Processed user clicks" << std::endl;
    processOnHoverEnter(window);
    processOnHoverLeave(window);
    std::cout << "Processed user mouse movements" << std::endl;
}
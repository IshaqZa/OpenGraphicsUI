#include "EventHandler/EventHandler.h"
void EventHandler::addElementEvent(EventType type, std::shared_ptr<MenuElement> element, std::function<void()> action){
    switch(type){
        case EVENT_ON_CLICK:
            onClickElements.push_back({element, action});
        break;

        case EVENT_ON_HOVER_ENTER:
            OnHoverEnterElements.push_back({element, action});
        break;

        case EVENT_ON_HOVER_LEAVE:
            OnHoverLeaveElements.push_back({element, action});
        break;
    }
}

GLfloat EventHandler::normalizeX(GLfloat value, GLfloat width){
    return -1.0f + 2.0f * value / width;
}
GLfloat EventHandler::normalizeY(GLfloat value, GLfloat height){
    return 1.0f - 2.0f * value / height;
}

void EventHandler::processOnClick(GLFWwindow* window){
    
    int MouseButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    if(MouseButtonState == GLFW_PRESS){
        std::cout << "Mouse is down" << std::endl;
        isClicked = true;
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        GLfloat normalizedX = normalizeX(x, width);
        GLfloat normalizedY = normalizeY(y, height);

        glm::vec2 pos(normalizedX, normalizedY);
        
        for(const auto& clickable : onClickElements){
            if(clickable.element->contains(pos)){
                std::cout << "mouse down click detected" << std::endl;
                clickable.action();
                break;
            }
        }
    }
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
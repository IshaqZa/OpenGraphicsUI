#include "EventHandler/EventHandler.h"

void EventHandler::addOnClickElement(std::shared_ptr<MenuElement> element, std::function<void()> action){

    onClickElements.push_back({element, action});

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

void EventHandler::processInputs(GLFWwindow* window){
    processOnClick(window);
}
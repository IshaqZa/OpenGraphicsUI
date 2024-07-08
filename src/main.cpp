#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include <shader/shader.h>
#include <stb/stb_image.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <Buffer/EBO.h>
#include <Scene/Scene.h>
#include <Scene/SceneManager.h>
#include <shader/shader.h>
#include <Buffer/texture.h>
#include <ui/ui.h>
#include <EventHandler/EventHandler.h>
#include <UIManager/UIManager.h>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);

}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// void exitInput(GLFWwindow *window)
// {
//     if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

// this function is purely for testing purposes
// void print(int a, int b){
//     cout << a + b << endl;
// }

int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Sci Hunt", glfwGetPrimaryMonitor(), NULL);
    if(window == NULL){
        cout << "An Error occured creating the window: " << endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        cout << "There was an error intialising GLAD" << endl;
        return EXIT_FAILURE;

    }

    glViewport(0, 0, 1920, 1080);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetErrorCallback(errorCallback);
    UIManager uimanager;
    SceneManager* sceneManager = SceneManager::getInstance();
    if(!sceneManager) {
        std::cout << "Scene Manager failed to initialise" << std::endl;
        return EXIT_FAILURE;
    }

    // std::cout << "Loading UI configuration" << std::endl;
    uimanager.loadUiConfig();
    std::cout << "Done loading UI configuration" << std::endl;

    std::vector<GLfloat> vertices = (*sceneManager->getCurrSceneVertexData());

    // for(GLfloat vertex: vertices){
    //     std::cout << vertex << std::endl;
    // }

    long long i = 0;
    while(!glfwWindowShouldClose(window)){
        // std::cout << "iteration number: " << i+1 << std::endl;
        i++;
        glClear(GL_COLOR_BUFFER_BIT);
        // std::cout << "starting scene update using scene manager" << std::endl;
        try {
            // sceneManager->update(window);
        //  std::cout << "starting current active scene rendering using tex bool" << std::endl;
            sceneManager->render();
        } catch(std::runtime_error& e){
            std::cerr << e.what() << std::endl;
        } catch(std::exception& e){
            std::cerr << e.what() << std::endl;
        }

        glfwPollEvents();
        // GLenum error = glGetError();
        // if(error) std::cout << "OpenGL Error Number:" << error << std::endl;
        // break;
    }

    glfwDestroyWindow(window);
    std::cout << "destroyed window" << std::endl;
    glfwTerminate();
    std::cout << "Terminated glfw" << std::endl;
    return EXIT_SUCCESS;
    
}
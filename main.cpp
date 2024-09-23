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
#include <EventHandler/Actions.h>
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
    
    SceneManager* sceneManager = SceneManager::getInstance();

    std::shared_ptr<Scene2D> MainMenu = std::make_shared<Scene2D>();
    MainMenu->createVertexData();
    MainMenu->createShader("../resources/Shaders/default.vert", "../resources/Shaders/default.frag");
    MainMenu->createEventHandler();
    MainMenu->setBackground(
        glm::vec4(
            0.5f
        )
    );

    std::shared_ptr<std::vector<GLfloat>> vertices = MainMenu->getVertices();

    Texture tex("../resources/textures/OPTIONS purple.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);

    std::shared_ptr<Appearance2D> app = std::make_shared<Appearance2D>(
        glm::vec2(0.0f),
        glm::vec2(0.1f),
        glm::vec4(1.0f),
        glm::vec2(0.0f),
        tex,
        1
    );

    std::shared_ptr<Button> play = std::make_shared<Button>(vertices, MainMenu->currentIndex(), "play", app, RECTANGLE_SHAPE);
    MainMenu->addElement("play", play);
    MainMenu->addEventListener(EVENT_ON_CLICK, "play", actions::settingsOnClick);
    MainMenu->addEventListener(EVENT_ON_HOVER_ENTER, "play", actions::settingsOnHoverEnter);
    MainMenu->addEventListener(EVENT_ON_HOVER_LEAVE, "play", actions::settingsOnHoverLeave);

    MainMenu->createVBO();
    MainMenu->createVAO(3, 4, 2, GL_FLOAT);
    sceneManager->addScene("Main Menu", MainMenu);
    
    while(!glfwWindowShouldClose(window)){
        
        std::cout << "starting scene update using scene manager" << std::endl;
        sceneManager->update(window);
        std::cout << "starting current active scene rendering" << std::endl;
        sceneManager->render();
        

        glfwSwapBuffers(window);
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
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
#include <Scene/Scene3D.h>
#include <Scene/SceneManager.h>
#include <shader/shader.h>
#include <Buffer/texture.h>
#include <ui/ui.h>
#include <EventHandler/EventHandler.h>
#include <UILoader/UILoader.h>
#include <assimp/Importer.hpp>
using namespace std;

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

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

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sci Hunt", glfwGetPrimaryMonitor(), NULL);
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
    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetErrorCallback(errorCallback);
    // UIManager uimanager;
    // SceneManager* sceneManager = SceneManager::getInstance();
    // if(!sceneManager) {
    //     std::cout << "Scene Manager failed to initialise" << std::endl;
    //     return EXIT_FAILURE;
    // }

    // // std::cout << "Loading UI configuration" << std::endl;
    // uimanager.loadUiConfig();
    // std::cout << "Done loading UI configuration" << std::endl;

    // std::shared_ptr<Scene2D> currentScenePtr = sceneManager->getCurrentScene();

    // if(!currentScenePtr){
    //     std::cerr << "Current scene is empty" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
    // if(!currentScenePtr->getShaderProgram()){
    //     std::cerr << "Current scene shader is empty" <<std::endl;
    //     exit(EXIT_FAILURE);
    // }


    // std::vector<GLfloat> vertices = (*sceneManager->getCurrSceneVertexData());

    // for(int i = 0; i < vertices.size(); i++){
    //     if(i%9 == 0 && i !=0) std::cout << std::endl;
    //     std::cout << vertices[i] << ", ";
        
    // }

    Scene3D scene(WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "Created 3D scene object" << std::endl;
    scene.createShader("../resources/Shaders/menu/3D/default.vert", "../resources/Shaders/menu/3D/default.frag");
    std::cout << "Created shader object for scene" << std::endl;
    scene.setBackgroundColor(glm::vec4(0.25f, 0.52f, 0.7f, 1.0f));
    std::cout << "Set background color for scene" << std::endl;
    std::shared_ptr<std::vector<GLfloat>> vertices = scene.getVertices();
    std::cout << "retrieved vertex data from object" << std::endl;

    GameObject obj(vertices);
    std::cout << "Created game object" << std::endl;
    scene.addObject("cube", std::make_shared<GameObject>(obj));
    std::cout << "Added game object to scene" << std::endl;
    scene.createVBO();
    std::cout << "Created VBO" << std::endl;
    scene.createVAO(3, 4, 0, GL_FLOAT);
    std::cout << "Created VAO object" << std::endl;

    scene.activate();
    std::cout << "Activated scene" << std::endl;
    while(!glfwWindowShouldClose(window)){
        
        // std::cout << "starting scene update using scene manager" << std::endl;
        // try {
        //     sceneManager->update(window);
        //     std::cout << "starting current active scene rendering" << std::endl;
        //     sceneManager->render();
        // } catch(std::runtime_error& e){
        //     std::cerr << e.what() << std::endl;
        // } catch(std::exception& e){
        //     std::cerr << e.what() << std::endl;
        // } 

        scene.update(window);
        scene.render();

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
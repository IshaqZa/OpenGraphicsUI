#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <shader/shader.h>
#include <stb/stb_image.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <Buffer/EBO.h>
#include <Scene/Scene.h>
#include <shader/shader.h>
#include <Buffer/texture.h>
#include <ui/ui.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);

}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// this function is purely for testing purposes
// void print(int a, int b){
//     cout << a + b << endl;
// }

int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "PlaceHolderTitle", glfwGetPrimaryMonitor(), NULL);
    if(window == NULL){
        cout << "An Error occured creating the window: " << endl;
        glfwTerminate();
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
    
    Scene2D testScene;
    vector<GLfloat> *vertices = testScene.getVertices();

    Shader* sceneShader = testScene.createShader("../resources/Shaders/default.vert", "../resources/Shaders/default.frag");

    Texture play_button("../resources/textures/play.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    Button play = Button<void>(*vertices, testScene.currentIndex(), "First Button", -0.9f, 0.1f, 0.4f, 0.3f);
    play.setRenderType(IMAGE_TYPE);
    play.setTexture(play_button, *sceneShader, "tex", 0);
    // play.printData(*vertices);

    Texture exit_button("../resources/textures/quit.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    Button exit = Button<void>(*vertices, testScene.currentIndex(), "Second Button", -0.9f, -0.4f, 0.4f, 0.3f);
    exit.setTexture(exit_button, *sceneShader, "tex", 0);
    exit.setRenderType(IMAGE_TYPE);
    // exit.printData(*vertices);

    testScene.addElement(&play);
    testScene.addElement(&exit);

    testScene.createVBO();
    testScene.createVAO(3, 4, 2, GL_FLOAT);
    testScene.activate();
    
    try{
        testScene.activate();
    }catch(std::exception& e){
        std::cerr << "Error: " << e.what() << endl;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GLuint isTex = glGetUniformLocation(sceneShader->ID, "isTex");
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        sceneShader->Activate();
        
        processInput(window);
        testScene.render(isTex);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    testScene.deleteResources();
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
    
}
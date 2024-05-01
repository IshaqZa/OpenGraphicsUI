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

    GLuint globalIndex = 0;

    Shader shaderProgram("../resources/Shaders/default.vert", "../resources/Shaders/default.frag");


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    vector<GLfloat> vertices;

    vector<GLuint> indices;

    Button play = Button<void, int, int>(vertices, &globalIndex, "First Button", -0.9f, 0.1f, 0.4f, 0.3f);
    
    Scene2D testScene(shaderProgram);

    testScene.createVBO(vertices);
    testScene.createVAO(3, 4, 2, GL_FLOAT);
    testScene.activate();

    Texture tex("../resources/textures/play-button.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    shaderProgram.Activate();
    GLuint isTex = glGetUniformLocation(shaderProgram.ID, "isTex");
    play.setRenderType(IMAGE_TYPE);
    play.setColor(0.76f, 0.13f, 0.53f, 1.0f);
    play.updateColor(vertices, 3);
    play.setTexture(tex, shaderProgram, "tex", 0);
    play.printData(vertices);

    Button exit = Button<void>(vertices, &globalIndex, "Second Button", 0.0f, -0.4f, 0.4f, 0.3f);
    
    exit.setTexture(tex, shaderProgram, "tex", 0);
    exit.setRenderType(RGBA_TYPE);
    exit.setColor(0.76f, 0.13f, 0.53f, 1.0f);
    exit.updateColor(vertices, 3);
    exit.printData(vertices);

    testScene.addElement(&play);
    testScene.addElement(&exit);

    try{
        testScene.activate();
    }catch(std::exception& e){
        std::cerr << "Error: " << e.what() << endl;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        
        processInput(window);

        testScene.render(isTex);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
    
}
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
#include <shader/shader.h>
#include <Buffer/texture.h>
#include <ui/ui.h>
#include <EventHandler/EventHandler.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);

}

void exitInput(GLFWwindow *window)
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
    
    std::cout << "created and speicified window and viewport" << std::endl;

    Scene2D testScene;
    testScene.createVertexData();
    std::shared_ptr<std::vector<GLfloat>> vertices = testScene.getVertices();

    if(!vertices) std::cout << "Vertices null in main" << std::endl;


    std::shared_ptr<Shader> sceneShader = testScene.createShader("../resources/Shaders/default.vert", "../resources/Shaders/default.frag");

    std::cout << "Created test scene and created shader" << std::endl;

    Texture play_button("../resources/textures/play.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    std::cout << "Created and loaded play button texture" << std::endl;

    std::shared_ptr<Appearance2D> playDisplay = std::make_shared<Appearance2D>(glm::vec2(-0.9f, 0.1f), glm::vec2(0.4f, 0.3f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));

    std::cout << "Created appearance" << std::endl;

    Button play(vertices, testScene.currentIndex(), "Play Button", playDisplay, RECTANGLE_SHAPE);
    play.setRenderType(IMAGE_TYPE);
    play.setTexture(play_button, *sceneShader, "tex", 0);
    // play.printData(vertices); don't use, needs fixing

    Texture exit_button("../resources/textures/quit.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    std::shared_ptr<Appearance2D> exitDisplay = std::make_shared<Appearance2D>(glm::vec2(-0.9f, -0.4f), glm::vec2(0.4f, 0.3f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));
    std::cout << "Created exit button" << std::endl;
    Button exit(vertices, testScene.currentIndex(), "Play Button", exitDisplay, RECTANGLE_SHAPE);
    exit.setTexture(exit_button, *sceneShader, "tex", 0);
    exit.setRenderType(IMAGE_TYPE);
    // exit.printData(vertices); don't use, needs fixing

    testScene.addElement(&play);
    testScene.addElement(&exit);

    std::cout << "Added play button to scene" << std::endl;



    EventHandler events;
    Button* playPtr = &play;
    std::shared_ptr<Button> sharedPlayPtr(playPtr);
    events.addOnClickElement(sharedPlayPtr, [](){ std::cout << "It works" << std::endl; });


    testScene.createVBO();
    testScene.createVAO(3, 4, 2, GL_FLOAT);

    glm::vec4 background(0.1f, 0.1f, 0.1f, 1.0f);

    testScene.setBackgroundColor(background);
    try{
        testScene.activate();
    }catch(std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }

    GLuint isTex = glGetUniformLocation(sceneShader->ID, "isTex");
    int i = 0;
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        sceneShader->Activate();

        events.processInputs(window);
        exitInput(window);
        testScene.render(isTex);
        
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
    
}
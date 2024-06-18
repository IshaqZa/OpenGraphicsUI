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

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "PlaceHolderTitle", NULL, NULL);
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

    SceneManager sceneManager;


    std::shared_ptr<Scene2D> mainMenu = std::make_shared<Scene2D>();
    mainMenu->createVertexData();
    mainMenu->createEventHandler();
    std::shared_ptr<std::vector<GLfloat>> vertices = mainMenu->getVertices();

    if(!vertices) std::cout << "Vertices null in main" << std::endl;

    std::shared_ptr<Shader> sceneShader = mainMenu->createShader("../resources/Shaders/default.vert", "../resources/Shaders/default.frag");

    Texture play_button("../resources/textures/play.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    std::shared_ptr<Appearance2D> playDisplay = std::make_shared<Appearance2D>(glm::vec2(-0.9f, 0.1f), glm::vec2(0.4f, 0.3f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));

    std::shared_ptr<Button> play = std::make_shared<Button>(vertices, mainMenu->currentIndex(), "Play Button", playDisplay, RECTANGLE_SHAPE);
    play->setRenderType(IMAGE_TYPE);
    play->setTexture(play_button, *sceneShader, "tex", 0);
    // play.printData(vertices); don't use, needs fixing

    Texture exit_button("../resources/textures/quit.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    std::shared_ptr<Appearance2D> exitDisplay = std::make_shared<Appearance2D>(glm::vec2(-0.9f, -0.4f), glm::vec2(0.4f, 0.3f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f));

    std::shared_ptr<Button> exit = std::make_shared<Button>(vertices, mainMenu->currentIndex(), "Play Button", exitDisplay, RECTANGLE_SHAPE);
    exit->setTexture(exit_button, *sceneShader, "tex", 0);
    exit->setRenderType(IMAGE_TYPE);
    // exit.printData(vertices); don't use, needs fixing

    mainMenu->addElement("play", play);
    mainMenu->addElement("exit", exit);

    mainMenu->addEventListener(EVENT_ON_CLICK, "play", [&sceneManager](){ sceneManager.switchCurrentScene("settings"); });

    mainMenu->createVBO();
    mainMenu->createVAO(3, 4, 2, GL_FLOAT);

    glm::vec4 background(0.1f, 0.1f, 0.1f, 1.0f);

    mainMenu->setBackgroundColor(background);
    
    sceneManager.addScene("main menu", mainMenu);

    std::shared_ptr<Scene2D> settings = std::make_shared<Scene2D>();

    sceneManager.addScene("settings", settings);
    settings->createVertexData();
    std::shared_ptr<std::vector<GLfloat>> settingsVertices = settings->getVertices();

    std::shared_ptr<Button> settingsButton = std::make_shared<Button>(settingsVertices, settings->currentIndex(), "Play Button", playDisplay, RECTANGLE_SHAPE);
    settingsButton->setRenderType(IMAGE_TYPE);
    
    settingsButton->setTexture(play_button, *sceneShader, "tex", 0);

    settings->addElement("settings", settingsButton);
    settings->createEventHandler();
    settings->linkShader(sceneShader);
    settings->createVBO();
    settings->createVAO(3, 4, 2, GL_FLOAT);
    settings->addEventListener(EVENT_ON_CLICK, "settings", [&sceneManager](){ sceneManager.switchCurrentScene("main menu"); });
    settings->setBackgroundColor(background);

    GLuint isTex = glGetUniformLocation(sceneShader->ID, "isTex");
    int i = 0;
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        
        exitInput(window);
        sceneManager.update(window);
        sceneManager.render(isTex);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
    
}
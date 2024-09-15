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
#include <UILoader/UILoader.h>
#include <EventHandler/Actions.h>
#include <Debugger/Debugger.h>


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Open UI Show Case", glfwGetPrimaryMonitor(), NULL);
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

    Shader shader = Shader("../resources/Shaders/default.vert", "../resources/Shaders/default.frag");
    Texture tex = Texture("../resources/textures/START red.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    std::cout << "Done creating texture" << std::endl;

    std::shared_ptr<std::vector<GLfloat>> vertices = std::make_shared<std::vector<GLfloat>>();
    std::cout << "created vertices" << std::endl;

    std::shared_ptr<Appearance2D> app = std::make_shared<Appearance2D>(glm::vec2(0.1, 0.1), glm::vec2(0.1, 0.1), glm::vec4(1.0f), glm::vec2(1.0f), tex, IMAGE_TYPE);
    std::cout << "created appearance" << std::endl;

    VAO vao;
    vao.Bind();

    GLuint texBool = glGetUniformLocation(shader.ID, "isTex");

    GLuint index = 0;
    Button btn = Button(vertices, &index, "test", app, RECTANGLE_SHAPE);
    std::cout << "created button" << std::endl;
    
    VBO vbo(vertices->data(), vertices->size());
    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 9 * sizeof(GLfloat), reinterpret_cast<void*>(0));
    vao.linkAttrib(vbo, 1, 4, GL_FLOAT, 9 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    vao.linkAttrib(vbo, 2, 2, GL_FLOAT, 9 * sizeof(GLfloat), reinterpret_cast<void*>(7 * sizeof(GLfloat)));
    
    vbo.Bind();

    glCheckError();
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while(!glfwWindowShouldClose(window)){
        
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Activate();
        vao.Bind();
        btn.draw(texBool);
        glfwSwapBuffers(window);
        glfwPollEvents();

        if(glCheckError() != GL_NO_ERROR) {
            break;
        }
    }

    glfwDestroyWindow(window);
    std::cout << "destroyed window" << std::endl;
    glfwTerminate();
    std::cout << "Terminated glfw" << std::endl;
    return EXIT_SUCCESS;
    
}
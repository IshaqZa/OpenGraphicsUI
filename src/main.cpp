#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <shader/shader.h>
#include <stb/stb_image.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <Buffer/EBO.h>
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

    Shader shaderProgram("../resources/Shaders/default.vert", "../resources/Shaders/default.frag");

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    vector<GLfloat> vertices;

    vector<GLuint> indices;

    button play = button<void, int, int>(vertices, indices, 0, "First Button", -0.5f, 0.5f, 1.0f, 1.0f);
    play.setColor(1.0f, 0.0f, 1.0f, 1.0f);
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices.data(), vertices.size() * sizeof(vertices));
    EBO EBO1(indices.data(), indices.size() * sizeof(indices));

    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*) 0); // location
    VAO1.linkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*) (4 * sizeof(float))); // color
    VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*) (7 * sizeof(float))); // texture
    EBO1.Bind();
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    
    Texture placeholder("../resources/textures/placeholder.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    placeholder.texUnit(shaderProgram, "tex", 0);

    Texture playButton("../resources/textures/play-button.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    playButton.texUnit(shaderProgram, "tex", 1);
    // To generate nth texture, repeat the previous process with GL_TEXTURE(N) unit

    // this part is for testing purposes
    // myButton.onClick(print);
    // myButton.invoke(3, 4);

    glBindTexture(GL_TEXTURE_2D, 1);

    GLuint texUni = glGetUniformLocation(shaderProgram.ID, "tex");
    GLuint isTex = glGetUniformLocation(shaderProgram.ID, "isTex");
    shaderProgram.Activate();
    play.setRenderType(IMAGE_TYPE, isTex);
    glUniform1i(texUni, 0);
    glUniform1i(texUni, 1);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        playButton.Bind();
        VAO1.Bind();
        processInput(window);
        play.draw();
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    placeholder.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
    
}
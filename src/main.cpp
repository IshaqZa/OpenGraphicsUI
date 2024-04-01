#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);

}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(){

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "PlaceHolderTitle", glfwGetPrimaryMonitor(), NULL);
    if(window == NULL){
        const char **error;
        glfwGetError(error);
        cout << "An Error occured creating the window: " << error << endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window)){

        processInput(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
    
}
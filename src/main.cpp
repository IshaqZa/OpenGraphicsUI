#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);

}

int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello, Window!", NULL, NULL);
    if(window == NULL){
        std::cout << "There was an error creating the window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window)){

        

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return EXIT_SUCCESS;

    
}
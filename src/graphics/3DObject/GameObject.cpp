#include "3DObject/GameObject.h"

GameObject::GameObject(std::shared_ptr<std::vector<GLfloat>> vertices){

    vertices->insert(vertices->end(), {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    });
    // indices.insert(indices.end(), 
    // {

    // })
}

void GameObject::draw(Shader& shader){


    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Camera::Camera(int width, int height, glm::vec3 position){
    this->width = width;
    this->height = height;
    this->position = position;
}

void Camera::Matrix(GLfloat FOVdeg, GLfloat nearPlane, GLfloat farPlane, Shader& shader, const char* uniform){
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(position, position + orientation, up);
    projection = glm::perspective(glm::radians(FOVdeg), (GLfloat)(width / height), nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection*view));

}

// void Camera::Inputs(GLFWwindow* window){
//     if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
//     }
// }
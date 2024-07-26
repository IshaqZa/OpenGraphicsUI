#ifndef GAMEOBJECT_CLASS_H
#define GAMEOBJECT_CLASS_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/Shader.h>

class GameObject {
    private:
        glm::mat4 model = glm::mat4(1.0f);

    public:
        GameObject(std::shared_ptr<std::vector<GLfloat>> vertices);
        void translate(glm::vec3 translate);
        void rotate(GLfloat angle, glm::vec3 axis);
        void scale(glm::vec3 axis);
};

class Camera{

    public:
        glm::vec3 position;
        glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        int width, height;

        float speed = 0.1f;
        float sensitivity = 100.0f;

        Camera(int width, int height, glm::vec3 position);

        void Matrix(GLfloat FOVdeg, GLfloat nearPlane, GLfloat farPlane, Shader& shader, const char* uniform);
        //void Inputs(GLFWwindow* window);
};

#endif
#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <ui/ui.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <shader/shader.h>
#include <EventHandler/EventHandler.h>
#include <EventHandler/EventType.h>
#include <3DObject/GameObject.h>

using json = nlohmann::json;

class EventHandler;

class Scene {

    protected:
        unsigned int index = 0;
        GLuint isTex = 0;
        std::shared_ptr<VBO> vbo;
        std::shared_ptr<VAO> vao;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<std::vector<GLfloat>> vertices;
        glm::vec4 backgroundColor;
    
    public:
        Scene();
        unsigned int* currentIndex();
        virtual void activate();
        void linkVBO(std::shared_ptr<VBO> vbo);
        void linkVAO(std::shared_ptr<VAO> vao);
        void linkShader(std::shared_ptr<Shader> shader);
        void setBackgroundColor(glm::vec4 backgroundColor);
        std::shared_ptr<std::vector<GLfloat>> getVertices();
        void createVBO();
        void createVAO(int posSize, int colorSize, int texSize, GLenum type);
        std::shared_ptr<Shader> createShader(const char* vertexFile, const char* fragmentFile);
        std::shared_ptr<Shader> getShaderProgram();
        virtual void update(GLFWwindow* window) = 0;
        virtual void render() = 0;
};

#endif //SCENE_CLASS_H
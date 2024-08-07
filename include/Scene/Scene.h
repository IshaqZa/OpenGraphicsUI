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

class Scene2D : public Scene{

    private:
        std::shared_ptr<EventHandler> events;
        std::unordered_map<std::string, std::shared_ptr<MenuElement>> elementArray;

    public:
        Scene2D();
        void addEventListener(EventType eventType, std::string elementName, std::function<void()> action);
        std::shared_ptr<MenuElement> getElementByName(std::string name);
        void addElement(std::string name, std::shared_ptr<MenuElement> element);
        void render() override;
        void update(GLFWwindow* window) override;
};

class Scene3D : public Scene{

    private:
        Camera camera;
        std::unordered_map<std::string, std::shared_ptr<GameObject>> objects;

    public:
        Scene3D(int width, int height);
        void addObject(std::string name, std::shared_ptr<GameObject> object);
        void getObjectByName(std::string name);
        void render() override;
        void update(GLFWwindow* window) override;
};



#endif //SCENE_CLASS_H
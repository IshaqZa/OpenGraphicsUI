#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <ui/ui.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <shader/shader.h>
#include <EventHandler/EventHandler.h>
#include <EventHandler/EventType.h>

class EventHandler;

class Scene {

    protected:
        GLuint index = 0;
         GLuint backgroundIndex = 0;
        GLuint isTex = 0;
        std::shared_ptr<VBO> vbo;
        std::shared_ptr<VAO> vao;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<std::vector<GLfloat>> vertices;
        std::shared_ptr<std::vector<GLuint>> backgroundIndices;
        std::shared_ptr<EBO> backgroundEBO;
        glm::vec4 backgroundColor;
        std::shared_ptr<Texture> backgroundImage;
        bool isBackgroundImage = false;
    
    public:
        unsigned int* currentIndex();
        void activate();
        void createVertexData();
        void linkVBO(std::shared_ptr<VBO> vbo);
        void linkVAO(std::shared_ptr<VAO> vao);
        void linkShader(std::shared_ptr<Shader> shader);
        void setBackground(glm::vec4 backgroundColor);
        void setBackground(Texture texture, const char* texLocation, GLuint unit);
        void setBackgroundImage(bool isImage);
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
        std::unordered_map<std::string, std::shared_ptr<Element>> elementArray;

    public:
        void createEventHandler();
        void addEventListener(EventType eventType, std::string elementName, std::function<void()> action);
        std::shared_ptr<Element> getElementByName(std::string name);
        void addElement(std::string name, std::shared_ptr<Element> element);
        void render() override;
        void update(GLFWwindow* window) override;
};
#endif //SCENE_CLASS_H
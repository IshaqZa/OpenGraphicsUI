#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <ui/ui.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <shader/shader.h>
class Scene2D {

    private:
        unsigned int index = 0;
        std::shared_ptr<VBO> vbo;
        std::shared_ptr<VAO> vao;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<std::vector<GLfloat>> vertices;
        glm::vec4 backgroundColor;        
        std::vector<MenuElement*> elementArray;

    public:
        void activate();
        void createVertexData();
        void linkVBO(std::shared_ptr<VBO> vbo);
        void linkVAO(std::shared_ptr<VAO> vao);
        void linkShader(std::shared_ptr<Shader> shader);
        void setBackgroundColor(glm::vec4 backgroundColor);
        std::shared_ptr<std::vector<GLfloat>> getVertices();
        void createVBO();
        void createVAO(int posSize, int colorSize, int texSize, GLenum type);
        std::shared_ptr<Shader> createShader(const char* vertexFile, const char* fragmentFile);
        void addElement(MenuElement* element);
        void render(GLuint texBool);
        unsigned int* currentIndex();

};

#endif //SCENE_CLASS_H
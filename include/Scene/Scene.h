#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <ui/ui.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <shader/shader.h>

class Scene2D {

    private:
        unsigned int index = 0;
        VBO *vbo;
        VAO *vao;
        Shader *shader;
        GLfloat backgroundColor[4];
        std::vector<GLfloat> vertices;
        std::vector<MenuElement*> elementArray;

    public:
        void activate();
        void linkVBO(VBO *vbo);
        void linkVAO(VAO *vao);
        void linkShader(Shader *shader);
        void setBackgroundColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);
        std::vector<GLfloat>* getVertices();
        void createVBO();
        void createVAO(int posSize, int colorSize, int texSize, GLenum type);
        Shader* createShader(const char* vertexFile, const char* fragmentFile);
        void addElement(MenuElement* element);
        void render(GLuint texBool);
        void deleteResources();
        unsigned int* currentIndex();

};

#endif //SCENE_CLASS_H
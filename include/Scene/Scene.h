#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <ui/ui.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <shader/shader.h>

class Scene2D {

    private:
        unsigned int index;
        VBO *vbo;
        VAO *vao;
        Shader shader;
        std::vector<MenuElement*> elementArray;

    public:
        Scene2D(Shader &shader) : shader(shader){};
        void activate();
        void linkVBO(VBO *vbo);
        void linkVAO(VAO *vao);
        void createVBO(std::vector<GLfloat> &vertices);
        void createVAO(int posSize, int colorSize, int texSize, GLenum type);
        void addElement(MenuElement* element);
        void render(GLuint texBool);

};

#endif //SCENE_CLASS_H
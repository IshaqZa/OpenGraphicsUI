#ifndef SCENE3D_CLASS_H
#define SCENE3D_CLASS_H
#include "Scene/Scene.h"

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

#endif
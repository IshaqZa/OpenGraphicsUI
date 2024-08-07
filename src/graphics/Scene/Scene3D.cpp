#include <Scene/Scene.h>

void Scene3D::render(){
    
}

Scene3D::Scene3D(int width, int height) : Scene(), camera(width, height, glm::vec3(0.0f, 0.0f, -1.0f)) {}
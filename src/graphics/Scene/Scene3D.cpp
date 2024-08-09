#include <Scene/Scene3D.h>

void Scene3D::update(GLFWwindow* window){}

void Scene3D::activate(){

    Scene::activate();
    std::cout << "3D scene activated" << std::endl;
    camera.Matrix(glm::radians(60.0f), 0.1f, 100.0f, (*shader), "ProjView");
    std::cout << "Projection and view matrices initialised" << std::endl;
    

}

void Scene3D::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Activate();
    vao->Bind();
    
    for(auto object : objects){
        object.second->draw((*shader));
    }
    vao->Unbind();

}

void Scene3D::addObject(std::string name, std::shared_ptr<GameObject> object){
    objects[name] = object;
}

Scene3D::Scene3D(int width, int height) : Scene(), camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f)) {}
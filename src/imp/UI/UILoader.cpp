#include <UILoader/UILoader.h>

UILoader::UILoader(){
    sceneManager = SceneManager::getInstance();
}

void UILoader::registerFunction(std::string name, std::function<void()> action){
    actionMap[name] = action;
}

json UILoader::loadJsonFile(std::string path){

    std::cout << "preparing to load ui config file" << std::endl;
    std::ifstream uiFile(path);
    if(!uiFile.is_open()){
        std::cerr << "Failed to load ui configuration file" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Finished loading uiFile" << std::endl;
    std::cout << "Preparing to parse data from json format" << std::endl;
    json uiConfig;
    try{
        uiFile >> uiConfig;
    }catch(const json::parse_error& e){
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    uiFile.close();
    std::cout << "Finished loading parsing data and closed ui configuration file" << std::endl;
    // std::cout << uiConfig.dump(4) << std::endl;
    
    return uiConfig;

}

void UILoader::printSceneData(StructScene sceneData){

    std::cout << "Current Scene Data:" << std::endl;
        std::cout << "Scene Name: " << sceneData.name << std::endl;
        std::cout << "Scene vertex shader: " << sceneData.vertexShaderPath << std::endl;
        std::cout << "Scene fragment shader: " << sceneData.fragmentShaderPath << std::endl;
        std::cout << "Background color data: " << sceneData.backgroundColor[0] << ", " << sceneData.backgroundColor[1] << ", " << sceneData.backgroundColor[2] << ", " << sceneData.backgroundColor[3] << std::endl;
        std::cout << "vertex data position offset: " << sceneData.posSize << ", " << "vertex data color offset: " << sceneData.colorSize << ", " << "vertex data texture offset: " << sceneData.texSize << std::endl;

}

void UILoader::loadUiConfig(std::string path){
    

    json uiConfig = loadJsonFile(path);

    std::cout << "Preparing to de serialize data into structure" << std::endl;
    StructScenes scenesData;
    try{
        if(!uiConfig.contains("scenes")) throw std::runtime_error("scenes is not found");
        if(uiConfig["scenes"].is_null()) throw std::runtime_error("scenes is empty/null");
        scenesData = uiConfig.template get<StructScenes>();
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }catch(const json::type_error& e){
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Finished deserializing" << std::endl;

    std::cout << "Starting object creation from data" << std::endl;
    for(auto& sceneData: scenesData.scenes){

        printSceneData(sceneData);

        std::shared_ptr<Scene2D> newScene = std::make_shared<Scene2D>();
        std::cout << "Created 2D scene shared pointer in UI configuration loading" << std::endl;
        newScene->createVertexData();
        std::cout << "Created vertex data in UI configuration loading" << std::endl;

        newScene->createShader(sceneData.vertexShaderPath.c_str(), sceneData.fragmentShaderPath.c_str());
        newScene->createEventHandler();
        newScene->setBackground(
            glm::vec4(
                sceneData.backgroundColor[0],
                sceneData.backgroundColor[1],
                sceneData.backgroundColor[2],
                sceneData.backgroundColor[3]
            )
        );
        if(!sceneData.backgroundImagePath.empty()){
            Texture background(sceneData.backgroundImagePath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
            std::cout << "Made a texture object for background image" << std::endl;
            newScene->setBackground(background, "tex", GL_TEXTURE0);
        }
        newScene->setBackgroundImage(sceneData.isBackgroundImage);
        std::cout << "Finished creating all needed data" << std::endl;

        std::shared_ptr<std::vector<GLfloat>> vertices = newScene->getVertices();
        std::cout << "Retrieved vertex vector pointer to be used for elments appending" << std::endl;
        for(auto& button: sceneData.sceneMembers){
            std::cout << "current button data:" << std::endl;
            std::cout << "Button name: " << button.name << std::endl;
            std::cout << "Button shape: " << button.shape << std::endl;
            StructAppearance currApp = button.appearance;
            std::cout << "Retrieved the current button appearance in UI configuration loader" << std::endl;
            Texture texture(currApp.textureImagePath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
            std::cout << "Created texture in UI configuration loader" << std::endl;
            std::shared_ptr<Appearance2D> appearancePtr = std::make_shared<Appearance2D>(
                glm::vec2(currApp.posX, currApp.posY),
                glm::vec2(currApp.width, currApp.height),
                glm::vec4(currApp.color[0], currApp.color[1], currApp.color[2], currApp.color[3]),
                glm::vec2(currApp.texturePosX, currApp.texturePosY),
                texture,
                currApp.renderType
            );
            if (!appearancePtr) {
                std::cerr << "Failed to create Button object in UI configuration loader" << std::endl;
                exit(EXIT_FAILURE); // Skip processing if Button creation fails
            }

            std::cout << "Created appearance from data retrieved from json file in UI configuration loader" << std::endl;

            std::shared_ptr<Button> newButton = std::make_shared<Button>(vertices, newScene->currentIndex(), button.name, appearancePtr, button.shape);
            std::cout << "Created a shared button pointer in UI configuration loader" << std::endl;
            if(newButton == nullptr) std::cerr << "Error making button pointer in UI configuration loader" << std::endl;
            newScene->addElement(button.name, newButton);
            if(!button.events.empty()){
                for(auto& event : button.events){
                    newScene->addEventListener(event.event, button.name, actionMap[event.action]);
                }
            }
            std::cout << "added all events related to current button in UI configuration loader" << std::endl;
        }

        newScene->createVBO();
        newScene->createVAO(sceneData.posSize, sceneData.colorSize, sceneData.texSize, GL_FLOAT);
        sceneManager->addScene(sceneData.name, newScene);
        std::cout << "Added current scene to scene manager in UI configuration loader" << std::endl;
    }

}
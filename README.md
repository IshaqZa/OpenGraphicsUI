# OpenUI

## Overview:
- **Description**: **OpenUI** is a simple light weight UI library made for OpenGL, GLFW and glad environment, designed to readuce the workload on a developer
- **Features**: The features in this project range from a scene system that allows the developer a simpler way of switching between menus, to dynamic configuration using .json files
- **Technologies used**:
    - **Programming Language**: C++
    - **Graphics Library**: OpenGL
    - **Other supporting Libraries**: GLFW, glad, GLM, Nlohmann::Json for modern c++, stb_image, FreeType
## Getting Started
### Installation
1. Open the zip file and extract all the contents
2. Click on Sci Hunt.exe and the game will launch

### Compiling the project
- The program can be compiled by running CMake in the root folder, and then make in ./build/build directory
### Configuration
- The UI can be set by modifying `./resources/ui/ui.json`, the file has the following format:
```json
{
  "scenes": [
    {
        "name": "Scene Name",
        "sceneMembers":[
            {
                "name": "UI element name",
                "events": [
                    {
                        "event": "event type",
                        "action": "action name"
                    }
                ],
                "appearance": {
                    "posX": (Float),
                    "posY": (Float),
                    "width": (Float),
                    "height": (Float),
                    "color": (Array of 4 floats indicating Red, Green, Blue and Alpha),
                    "texturePosX": (Float),
                    "texturePosY": (Float),
                    "textureImagePath": "..\\path\\to\\file.png",
                    "renderType": (0 or 1, 0: RGBA_TYPE, 1: IMAGE_TYPE)
                },
                "shape": (Enum of "rectangle", "circle", "triangle")
            }, // more objects can be added to the scene members array as needed
        ],
        "vertexShaderPath": "..\\path\\to\\vertshader.vert",
        "fragmentShaderPath": "..\\path\\to\\fragshader.frag",
        "backgroundColor": (Array of 4 floats indicating Red, Green, Blue and Alpha),
        "posSize": (int, indicating the vertices needed to specify position),
        "colorSize": (int, indicating the vertices needed to specify color),
        "texSize": (int, indicating the vertices needed to specify texture)   
    }, // more scenes can be added to the scenes array by making more objects as needed
  ]
}
```

## Code Documentation
### Code Structure:
- There are several directories in the project each serving a specific purpose, them being:
    - `src/`: contains implementation .cpp files 
        - `external/`: contains implementations for external libraries(glad.c and stb_image.cpp)
        - `graphics/`: contains implementations for the different aspects of the project
            - `Actions.cpp`: Contains implementations for all the funcitons attached to the different ui elements
            - `EBO.cpp`: Implmentation for EBO objects, makes it easier to make new EBOs and bind them
            - `EventHandler.cpp`: Main file to enable event driven api-like functionality, mainly for the 2D aspect of the game
            - `Scene.cpp`: The basic building unit for the game, splits into 2D and 3D scenes
            - `SceneManager.cpp`: A class that helps to manage scenes(example: Scene switching and keeping track of current active scene, can handle 2D and 3D scenes)
            - `shader.cpp`: Implementation for loading and activating shaders
            - `Shape.cpp`: Defines the different shapes the UI elements can come and and accordingly filles the needed vertex data
            - `texture.cpp`: Implementation for loading and using textures
            - `ui.cpp`: Defines the different 2D UI elements that can be displayed in a scene
            - `UIManager.cpp`: Responsible for loading ui.json data and creating the relevant scene and ui elements' objects
            - `VAO.cpp`: Implementation for the VAO
            - `VBO.cpp`: Implementation for the VBO
        - `main.cpp`: Where everything is wrapped together
    - `build/`:
        - `Dr. Memory`: This is a debugging tool to check for any memory related issues
        - `launch.bat & Sci Hunt.exe`: the .bat file launches the .exe file and saves the log.txt file
        - `log.txt`: A file that displays the logs of what happens in the game, useful for debugging
    - `Include/`:
        - `glad/, GLFW/, glm/, Json/, KHR/, stb/`: contains header files for all the external libraries needed for the project
        - `Buffer/, EventHandler/, Scene/, shader/, ui/, UIManager/`: Contains header files for the different .cpp files in the `src/grpahics/` directory
    
    - `resources/`:
        - `icon`:
            - `resource.o, resource.rc & scihunt.ico`: Resource script and its compiled object file, used to load `scihunt.ico` as an icon for `SciHunt.exe`
            - `Shaders/`: Contains `default.vert` and `default.frag` which are shaders written in GLSL(Graphics Library Shader Language)
            - `textures`: contains .png files that are used for the different ui elements displayed in the menus
            - `ui`: contains `ui.json` which ui configuration data
            

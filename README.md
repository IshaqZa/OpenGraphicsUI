# Sci Hunt

## Overview:
- **Description**: Sci Hunt is a game built upon a dynamic and expandable yet minimalistic game engine, and serves to demonstrate the core concepts of making a 3D game from scratch
- **Features**: The features in this project range from a scene system that allows the developer a simpler way of switching between menus and game levels, to dynamic configuration using .json files
- **Technologies used**:
    - **Programming Language**: C++
    - **Graphics Library**: OpenGL
    - **Other supporting Libraries**: GLFW, glad, GLM, Nlohmann::Json for modern c++, stb_image
## Getting Started
### Installation
1. Open the zip file and extract all the contents
2. Click on Sci Hunt.exe and the game will launch

### Compiling the project
- The program can be run using gcc/g++ using the following command:
    `g++ -std=c++17 -I./include ./src/external/glad.c ./src/main.cpp ./src/graphics/*.cpp ./src/external/stb_image.cpp ./resources/icon/resources.o ./libglfw3.a -o ./build/"Sci Hunt.exe" -g -lgdi32`
### Configuration
- The 2D part of the engine can be modified in `./resources/ui/ui.json`, the file has the following format:
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
            - `Shape.cpp`: 
# OpenGraphicsUI

## Overview:
- **Description**: **OpenUI** is a simple light weight UI library made for OpenGL, GLFW and glad environment, designed to readuce the workload on a developer
- **Features**: The project provides a foundation for a developer to be able to create their own custom UI with minimal effort
- **Technologies used**:
    - **Programming Language**: C++
    - **Graphics Library**: OpenGL
    - **Other supporting Libraries**: GLFW, glad, GLM, stb_image
## Getting Started

### Compiling the project (tested using MSYS2 and MinGW on windows)
- The project can be compiled by navigating to the build directory/folder, running `cmake ../` and then running make
- The cmake file can be used as a reference for how the project is structured in case of other methods of compilation
- The project can currently only be compiled for windows

## Code Documentation
### Code Structure:

![UML](https://github.com/user-attachments/assets/d758236a-f038-4b40-a3a3-26fac27ecb20)

### Working with the library:
- The library needs to be added to the project using it, with the include file
- Any element that will be displayed, such as a label, button, slider, etc..., needs to be extended from the MenuElement class to provide the basic funcitonality needed to create such elements
- Any context screen, such as menus, game context, etc..., needs to be extended from the base Scene class
- A sample game known as "Blackhole" is used as a showcase for this project ([github link](https://github.com/IshaqZa/showcase))

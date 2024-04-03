# Senior Project: Cheater
### introduction
This project is an implementation of a game that will be called **Cheater**, which follows the hacking adventure of a school kid that failed most of his classes and wants to alter all his grades by hacking the school database. You as the player will be controlling the avatar of this kid's digital presence. This avatar will be shooting, hacking and slashing his way through the security systems that have been set by the school against intruders.

### Project Setup, development environment and resources
The following resources have been used to set up and aid in the development of the project:
- **Integrated Development Environment(IDE)**: Visual Studio Code
- **Building platform(+compiler)**: MSYS2* with the gcc compiler
- **Version Control**: Github and git
- **API**: OpenGL(Open Graphics Library)
- **Dependecies**:
    - GLFW: Utility Library for OpenGL
    - GLAD: "Function loader" which reduces the amount of code that has to be written and helps with cross-compatibility

*MSYS2: is a software distribution platform developed for Microsoft Windows and offers the Unix development environment for Windows OS users

### OpenGL, GLFW and glad general code flow
There is a general flow for most OpenGL projects that use GLFW and glad, which looks something like this:
1. #### Initialisations:  
    1. GLFW intitalisation, context specification and termination:
        1. GLFW must be intialised (`glfwInit()`) at the beggining of the program and must be terminated at the end (`glfwTerminate()`)
        2. GLFW must be given information about the OpenGL version (major and minor) which in the context of this project is 3.3 (`glfwWindowHint(GLFW_CONTEXT_VERSION_(MAJOR/MINOR), 3)`)
        3. Through the same `glfwWindowHint()` function, the OpenGL profile being used must be specified, which in this case is **Core** (`glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE)`)
    2. Window initilisation:
        1. A `GLFWwindow` object can be created using `glfwCreateWindow(WIDTH, HEIGHT, "title", screen_for_fullscreen, NULL)`, this function will return the handler of the window. The function `getPrimaryMonitor()` can be used to make the program in full screen on the main monitor(parsed in the third parameter)
        2. Error checking is preferable and that can be done by checking if the window handler is `NULL`
        3. GLFW must be informed that the window that's just been created must be used(`glfwMakeContextCurrent(window_handler)`)
    3. Glad initialisation:
        1. glad can be simply intialised with `gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)` where we load the OpenGL function pointers. An `if` statement can be used to check for errors while initialising glad.(the function will return 0 on a success)
        2. using glad, the viewport* can now be initialised via `glViewport(x, y, WIDTH, HEIGHT)`  
        (A Viewport is basically the "rendering window")
    4. Framebuffer size callback:
        1. This will make sure that the viewport will be resized with the window resize
        2. This can be done via declaring the `framebuffer_size_callback(GLFWwindow* window, int width, int height)`, this will be called everytime the framebuffer size is changed.
        3. Inside the function add `glViewport(0, 0, width, height)` to apply the updates
        4. Call `glfwSetFramebufferSizeCallback(window, framebuffer_size_callback)` to pass the function pointer for the `framebuffer_size_callback()` function
    5. Loop until end of program:
        1. A loop must be made to run until an "end of program" condition is met
        2. This can be done using `while(!glfwWindowShouldClose(window))`, this will check each loop iteration whether glfw should be closing or not
        3. Inside the loop, `glfwSwapBuffers(window)` is added to apply the double buffer concept*
        (Double Buffer is just the idea that half the buffer is used to render while the other half is used to display to the screen)
        4. Add `glfwPollEvents()` to go through the event pipeline in glfw and OpenGL
        5. Exit condition can be made using a "process_input()" function. It should look something like this:
        ``` 
        void processInput(GLFWwindow *window)  
        {  
           if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  
           glfwSetWindowShouldClose(window, true);  
        }
        ```
        where it checks for the user pressing the "ESC" button on their keyboard to exit the program and calls `glfwSetWindowShouldClose(window, true)` to acheive the true condition in the while loop
    6. Finally we can set a color for the back ground via `glClearColor(float R, float G, float B, float alpha);` and then in the while loop add `glClear(GL_COLOR_BUFFER_BIT)`
2. #### Basic Geometry and shaders:
    1. Geometry Data
        1. In the case of this program, `std::vector<T>` will be used for storing the vertex data
        2. The VBO(Vertex Buffer Object) is were the data from the vector will be stored onto the memory. This is done by creating `GLuint VBO` and then `glGenBuffers(1, &VBO)`, this gives us an ID for the VBO to use.
        3. In the case of this program, a GL_ARRAY_BUFFER will be used. `glBindBuffer(GL_ARRAY_BUFFER, VBO)` this specifies that the VBO with the ID provided should be used.
        4. Now it is time to copy the data from `std::vector<T>` into our VBO. This is done by `glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW)`(We use GL_STATIC_DRAW only as a placeholder for now)
        5. Shaders are needed for the rendering of graphics, there are two types of shaders, vertex and fragment shaders
        6. A vertex shader is needed to process and output geometry while a fragment shader is needed for color output and shading
        7. This is the most basic vertex shader:
        ```
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        } 
        ```
        8. This is the most basic fragment shader:
        ```
        #version 330 core
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
        ``` 
        9. In order to load the vertex shader above, we need to first create it in the context of OpenGL via `GLuint vertexShader` and then `vertexShader = glCreateShader(GL_VERTEX_SHADER)`, after that the vertex shader source needs to be loaded into the vertexShader with the ID we just created via `glShaderSource(vertexShader, 1, &vertexShaderSource, NULL)` and then to compile it `glCompileShader(vertexShader)`
        >Note: Error checking can be done via
        >```
        >int  success;
        >char infoLog[512];
        >glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        >if(!success)
        >{
        >    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        >    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        >}
        >```
        10. Same thing with the fragment shader: `GLuint fragmentShader`, `fragmentShader = glCreateShader(GL_FRAGMENT_SHADER)`, `glSourceShader(fragmentShader, 1, &fragmentShaderSource, NULL)` then `glCompileShader(fragmentShader)`
        11. Finally to connect both to make the entire shader program. `GLuint shaderProgram`, `shaderProgram = glCreateProgram()`, `glAttachShader(shaderProgram, vertexShader)`, `glAttachShader(shaderProgram, fragmentShader)`
        and `glLinkProgram(shaderProgram)`. `glUseProgram(shaderProgram)` Tells OpenGL that it is time to use the shader program that has just been created
        >Note: vertex and fragment shaders are no longer useful so it can be deleted using `glDeleteShader(vertexShader)` and `glDeleteShader(fragmentShader)`

    

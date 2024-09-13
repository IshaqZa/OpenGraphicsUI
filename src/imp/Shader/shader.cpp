#include "shader/shader.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile){
    
    GLenum error;

    vertexPath = vertexFile;
    fragmentPath = fragmentFile;

    std::string vertexCode;
    std::string fragmentCode;
    try {
        vertexCode = get_file_contents(vertexFile);
        fragmentCode = get_file_contents(fragmentFile);
    } catch(int error){

        std::cout << "Error number:" << error << std::endl;
        exit(EXIT_FAILURE);

    }
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLint success;

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    if(error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error creating vertex shader: " << error << std::endl;
		exit(EXIT_FAILURE);
	}
    
    glShaderSource(vertexShader, 1, &vertexSource, NULL);

    if(error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error setting vertex shader source: " << error << std::endl;
		exit(EXIT_FAILURE);
	}

    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "Error: Vertex shader failed to compile\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if(error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error creating fragment shader: " << error << std::endl;
		exit(EXIT_FAILURE);
	}

    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

    if(error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error setting fragment shader source: " << error << std::endl;
		exit(EXIT_FAILURE);
	}

    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "Error: Fragment shader failed to compile\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();

    if(error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error creating shader program: " << error << std::endl;
		exit(EXIT_FAILURE);
	}

    glAttachShader(ID, vertexShader);

    if(error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error attaching vertex shader to shader program: " << error << std::endl;
		exit(EXIT_FAILURE);
	}

    glAttachShader(ID, fragmentShader);

    if(error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error attaching fragment shader to shader program: " << error << std::endl;
		exit(EXIT_FAILURE);
	}

    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate(){

    glUseProgram(ID);

    if(GLenum error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error activating shader: " << error << std::endl;
		exit(EXIT_FAILURE);
	}


}

void Shader::Delete(){

    glDeleteProgram(ID);

    if(GLenum error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error deleting shader: " << error << std::endl;
		exit(EXIT_FAILURE);
	}


}
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
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "Error: Vertex shader failed to compile\n" << infoLog << std::endl;
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "Error: Fragment shader failed to compile\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }
    glDeleteShader(fragmentShader);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }
}

void Shader::Activate(){

    glUseProgram(ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

}

void Shader::Delete(){

    glDeleteProgram(ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

}
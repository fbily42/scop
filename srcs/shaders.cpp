#include "shaders.hpp"

std::string ReadFile(const char* filePath) {
    std::ifstream file(filePath, std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error(std::string("Failed to open file: ") + filePath);
    }

    std::stringstream sstr;
    sstr << file.rdbuf();
    file.close();
    return sstr.str();
}

GLuint CompileShader(GLenum shaderType, const std::string& source) {
    GLuint shaderID = glCreateShader(shaderType);
    const char* sourceCStr = source.c_str();
    glShaderSource(shaderID, 1, &sourceCStr, nullptr);
    glCompileShader(shaderID);

    GLint result = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> errorMessage(infoLogLength);
        glGetShaderInfoLog(shaderID, infoLogLength, nullptr, errorMessage.data());
        std::string errorStr(errorMessage.begin(), errorMessage.end());
        glDeleteShader(shaderID);
        throw std::runtime_error("Shader compilation error: " + errorStr);
    }

    return shaderID;
}

GLuint LinkProgram(GLuint vertexShaderID, GLuint fragmentShaderID) {
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    GLint result = GL_FALSE;
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> errorMessage(infoLogLength);
        glGetProgramInfoLog(programID, infoLogLength, nullptr, errorMessage.data());
        std::string errorStr(errorMessage.begin(), errorMessage.end());
        glDeleteProgram(programID);
        throw std::runtime_error("Program linking error: " + errorStr);
    }

    return programID;
}

GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath) {
    std::string vertexShaderCode = ReadFile(vertexFilePath);
    std::string fragmentShaderCode = ReadFile(fragmentFilePath);

    GLuint vertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
    GLuint fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    GLuint programID = LinkProgram(vertexShaderID, fragmentShaderID);

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}


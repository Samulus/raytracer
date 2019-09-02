//
// shader.cpp
// Author: Samuel Vargas
// Date: 08/09/2019
//

#include "shader.h"
#include <iostream>
#include <cassert>

Shader::Shader(const char* vertexSource, const char* fragmentSource) : uniformLocations(std::map<const std::string, GLint>()){
    auto vertexID = createShader(GL_VERTEX_SHADER, vertexSource);
    auto fragmentID = createShader(GL_FRAGMENT_SHADER, fragmentSource);
    mID = Shader::linkProgram(vertexID, fragmentID);
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
    assert(mID >= 0 && "Unable to link shader programs");
}

Shader::~Shader() = default;

GLint Shader::getProgramID() const {
    return mID;
}

bool Shader::rememberUniformLocation(const std::string& uniformName) {
    GLint loc = glGetUniformLocation(mID, uniformName.c_str());
    if (loc < 0) {
        return false;
    }

    uniformLocations[uniformName] = loc;
    return true;
}

GLint Shader::getUniformLocation(const std::string& name) const {
    return uniformLocations.count(name) ? uniformLocations.at(name): -1;
}

GLint Shader::linkProgram(GLint vertexID, GLint fragmentID) {
    auto programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);

    GLint ok = GL_FALSE;
    glGetProgramiv(programID, GL_LINK_STATUS, &ok);
    if (ok == GL_FALSE) {
        GLchar error[8192] = {0};
        glGetProgramInfoLog(programID, 8192, nullptr, error);
        throw std::runtime_error(std::string(error));
    }

    return programID;
}

GLint Shader::createShader(GLenum type, const char* glslProgramSource) {
    assert(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);
    auto shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &glslProgramSource, nullptr);
    glCompileShader(shaderID);

    GLint ok = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &ok);
    if (ok == GL_FALSE) {
        GLchar error[8192] = {0};
        glGetShaderInfoLog(shaderID, 8192, nullptr, error);
        throw std::runtime_error(std::string(error));
    }

    return shaderID;
}


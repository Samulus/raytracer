//
// shader.cpp
// Author: Samuel Vargas
// Date: 08/09/2019
//

#pragma once
#include <GL/glew.h>
#include <string>
#include <set>
#include <map>

class Shader {
private:
    std::map<const std::string, GLint> uniformLocations;
    GLint mID;
public:
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();
    [[ nodiscard ]] GLint getProgramID() const;
    bool rememberUniformLocation(const std::string& uniformName);
    [[ nodiscard ]] GLint getUniformLocation(const std::string& uniformName) const;
private:
    static GLint linkProgram(GLint vertexID, GLint fragmentID);
    static GLint createShader(GLenum type, const char* glslProgramSource);
};
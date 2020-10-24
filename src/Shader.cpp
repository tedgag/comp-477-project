//
// Created by Édouard Gagné on 2020-10-08.
//

#include "Shader.h"

#include <utility>
#include <fstream>

using namespace glm;
using namespace std;

Shader::Shader(const string& vertex_shader_path, const string& fragment_shader_path) {
    programID = compileAndLinkShaders(vertex_shader_path, fragment_shader_path);

}
Shader::Shader() = default;

GLuint Shader::compileAndLinkShaders(const string& vertex_shader_path, const string& fragment_shader_path) {
    // Getting vertex shaders code
    string VertexShaderCode = getShaderCode(vertex_shader_path);
    // Getting fragment shaders code
    string FragmentShaderCode = getShaderCode(fragment_shader_path);
    // Compile ColorVertex Shader
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(vShader, 1, &VertexSourcePointer, nullptr);
    glCompileShader(vShader);
    // Check ColorVertex Shader
    checkCompileErrors(vShader, "SHADER");

    // Compile Fragment Shader
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(fShader, 1, &FragmentSourcePointer, nullptr);
    glCompileShader(fShader);

    // Check Fragment Shader
    checkCompileErrors(fShader, "SHADER");

    // Link the programID
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vShader);
    glAttachShader(programID, fShader);
    glLinkProgram(programID);

    // Check the programID
    checkCompileErrors(fShader, "programID");

    // Delete shaders
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return programID;

}
/* Use the shader program at this shader object ID */
void Shader::use() const {
    glUseProgram(programID);
}
void Shader::setMat4(const string &name, const mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setVec3(const string &name, const vec3 &value) const {
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
}
void Shader::setInt(const string &name, int value) const {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}
void Shader::setFloat(const string &name, float value) const {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}
void Shader::setBool(const string &name, bool value) const {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}
/* Check a shaders or programID for compile error */
void Shader::checkCompileErrors(GLuint id, const string &type) {
    GLint Result = GL_FALSE;
    int InfoLogLength;
    if (type == "SHADER") {
        glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ) {
            vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(id, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }
    } else if (type == "programID") {
        glGetProgramiv(id, GL_LINK_STATUS, &Result);
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ) {
            vector<char> programIDErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(id, InfoLogLength, nullptr, &programIDErrorMessage[0]);
            printf("%s\n", &programIDErrorMessage[0]);
        }

    }
}

string Shader::getShaderCode(const string& shader_path) {
    string ShaderCode;
    ifstream ShaderStream(shader_path, ios::in);

    if(ShaderStream.is_open()){
        string Line;
        while(getline(ShaderStream, Line))
            ShaderCode += "\n" + Line;
        ShaderStream.close();
    }
    return ShaderCode;
}



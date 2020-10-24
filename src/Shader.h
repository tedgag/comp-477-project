//
// Created by Édouard Gagné on 2020-10-08.
//

#ifndef COMP477PROJECT_SHADER_H
#define COMP477PROJECT_SHADER_H
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

class Shader {
    public:
        Shader();
        Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
        void use() const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setBool(const std::string &name, bool value) const;
    private:
        GLuint programID;
        static GLuint compileAndLinkShaders(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
        static void checkCompileErrors(GLuint shader, const std::string &type);
        static std::string getShaderCode(const std::string& shader_path);
};


#endif //COMP477PROJECT_SHADER_H

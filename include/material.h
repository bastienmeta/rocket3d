//
//  material.h
//  template
//
//  Created by bwailly on 14/06/2020.
//

#ifndef material_h
#define material_h

#include <string>
#include <glm/glm.hpp>

#include "shader.h"

class Material{
public:
    Shader* shader;
    glm::vec3 diff_color;
    float shininess;
    
    Material(){}
    
    Material(const char* vs, const char* fs, glm::vec3 diff_color, float shininess)
    :shader(new Shader(vs, fs)), diff_color(diff_color), shininess(shininess)
    {}
    
    Material(Shader* shader, glm::vec3 diff_color, float shininess)
    :shader(shader), diff_color(diff_color), shininess(shininess)
    {}
    
    GLuint get_shader_id(){
        return shader->ID;
    }
};

#endif /* material_h */

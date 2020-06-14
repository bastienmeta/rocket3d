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

#include "../include/shader.h"

class Material{
public:
    Shader shader;
    
    glm::vec3 diff_color;
    float shininess;
    
    Material(){}
    Material(const char* vs, const char* fs, glm::vec3 diff_color, float shininess)
    :shader(Shader(vs, fs)), diff_color(diff_color), shininess(shininess)
    {}
};

#endif /* material_h */

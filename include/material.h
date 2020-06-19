#ifndef material_h
#define material_h

#include <string>
#include <memory>
#include <glm/glm.hpp>

#include "shader.h"

class Material{
public:
    Material(){}
    Material(std::shared_ptr<Shader> shader):shader(shader){}
    virtual ~Material(){}
    
    GLuint get_shader_id(){
        return shader->ID;
    }
    
    virtual void set_uniforms() = 0;
    
protected:
    std::shared_ptr<Shader> shader;
};

#endif /* material_h */

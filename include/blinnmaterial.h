#ifndef blinn_material_h
#define blinn_material_h

#include "material.h"
#include "shadermanager.h"

class BlinnMaterial : public Material{
public:
    BlinnMaterial();
    BlinnMaterial(ShaderManager& shaders, glm::vec4 emis, glm::vec4 diff, glm::vec4 spec, float shininess);
    virtual ~BlinnMaterial(){}
    
    void set_uniforms();
    
private:
    glm::vec4 emissive;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float shininess;
};

#endif

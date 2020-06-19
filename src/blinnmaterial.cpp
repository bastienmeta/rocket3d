#include "../include/blinnmaterial.h"
#include <glm/gtc/type_ptr.hpp>

BlinnMaterial::BlinnMaterial(){}

BlinnMaterial::BlinnMaterial(ShaderManager& shaders, glm::vec4 emis, glm::vec4 diff, glm::vec4 spec, float shin)
:Material(shaders.get("advanced_blinn")), emissive(emis), diffuse(diff), specular(spec), shininess(shin)
{}

void BlinnMaterial::set_uniforms(){
    glUniform4fv(glGetUniformLocation(shader->ID, "material.emissive"), 1, value_ptr(emissive));
    glUniform4fv(glGetUniformLocation(shader->ID, "material.diffuse"), 1, value_ptr(diffuse));
    glUniform4fv(glGetUniformLocation(shader->ID, "material.specular"), 1, value_ptr(specular));
    glUniform1fv(glGetUniformLocation(shader->ID, "material.shininess"), 1, &(shininess));
}

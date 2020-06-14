#ifndef __MESH_H__
#define __MESH_H__

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

#include <iostream>

#include "material.h"

class Mesh{
public:
    Material* material;
    bool loaded;

    Mesh(std::string path, Material* mat);

    bool readOFF(std::string path);
    GLuint get_shader_id(){ return material->get_shader_id(); }
    
    void translate(glm::vec3 vec);
    void rotate(glm::vec3 axis, float angle);
    void scale_xyz(glm::vec3 scale);
    void scale(float factor);
    
    glm::mat4& get_model(){ return model; };
    
    void draw();
    
private:
    std::vector<glm::vec3> V;
    std::vector<glm::vec3> Nv;
    std::vector<glm::vec3> Nf;
    std::vector<unsigned int> F;

    unsigned int nvertices, nfaces, nedges;

    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint nbo;

    glm::mat4 model;
};

#endif

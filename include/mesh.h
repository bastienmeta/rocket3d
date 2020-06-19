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
    Mesh(std::string path);

    bool readOFF(std::string path);
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
    
    bool loaded;
};

#endif

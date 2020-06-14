//
//  scene.h
//  template
//
//  Created by bwailly on 14/06/2020.
//

#ifndef scene_h
#define scene_h

#include <vector>
#include <glm/glm.hpp>

#include "mesh.h"
#include "material.h"

class Scene{
public:
    Scene();
    
    void render();
    
private:    
    glm::vec3 camera_position;
    glm::vec3 camera_target;
    glm::vec3 camera_up;
    
    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 VP;
    
    std::vector<Mesh*> objects;
};

#endif /* scene_h */

//
//  scene.h
//  template
//
//  Created by bwailly on 14/06/2020.
//

#ifndef scene_h
#define scene_h

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "spaceobject.h"
#include "shadermanager.h"

class Scene{
public:
    Scene();
    
    void physics_step(double dt);
    void render();
    
private:    
    glm::vec3 camera_position;
    glm::vec3 camera_target;
    glm::vec3 camera_up;
    
    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 VP;
    
    ShaderManager shader_manager;
    std::vector<std::shared_ptr<SpaceObject>> objects;
};

#endif /* scene_h */

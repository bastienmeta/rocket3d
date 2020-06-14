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

#include "../include/mesh.h"
#include "../include/material.h"

class Scene{
public:
    Scene(){
        glEnable(GL_DEPTH_TEST);
        glClearColor(.0, .0, .0, .0);

        Material mat( "../../shaders/vs.glsl", "../../shaders/fs.glsl", glm::vec3(0.4, 0.3, 0.1), 2.0);
        
        objects.push_back( Mesh("../../meshes/tchouri.off", mat) );
        
        // lights
        light_directionnal = glm::normalize(glm::vec3(3, 8, 10));
        light_point = glm::vec3(10, 5, 20);

        // camera
        camera_position = glm::vec3(2.0, 4.0, 0.0);
        camera_target = glm::vec3(0.0, 0.0, 0.0);
        camera_up = glm::vec3(0.0, 1.0, 0.0);
        
        // matrices
        proj = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0);
        view = glm::lookAt(camera_position, camera_target, camera_up);
        MVP = proj * view;
    }
    
    void render(){
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        for(auto obj: objects){
            glUseProgram(obj.material.shader.ID);
            
            // get shader pointers
            GLuint MatrixID = glGetUniformLocation(obj.material.shader.ID, "MVP");
            GLuint ViewID = glGetUniformLocation(obj.material.shader.ID, "V");
            GLuint ProjID = glGetUniformLocation(obj.material.shader.ID, "P");
            GLuint CamposID = glGetUniformLocation(obj.material.shader.ID, "eye_world");
            GLuint DirLightID = glGetUniformLocation(obj.material.shader.ID, "dirlight_world");
            GLuint PointLightID = glGetUniformLocation(obj.material.shader.ID, "pointlight_world");
            
            GLuint MeshDiffID = glGetUniformLocation(obj.material.shader.ID, "mesh_diffuse");
            GLuint ShininessID = glGetUniformLocation(obj.material.shader.ID, "shininess");
            
            // send info to gpu
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
            glUniformMatrix4fv(ProjID, 1, GL_FALSE, glm::value_ptr(proj));
            glUniformMatrix4fv(ViewID, 1, GL_FALSE, glm::value_ptr(view));
            glUniform3fv(CamposID, 1, glm::value_ptr(camera_position));
            glUniform3fv(DirLightID, 1, glm::value_ptr(light_directionnal));
            glUniform3fv(PointLightID, 1, glm::value_ptr(light_point));
            
            glUniform3fv(MeshDiffID, 1, value_ptr(obj.material.diff_color));
            glUniform1fv(ShininessID, 1, &(obj.material.shininess));
            
            // draw item
            obj.draw();
        }
        glUseProgram(0);

    }
    
private:
    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 MVP;
    
    glm::vec3 light_directionnal;
    glm::vec3 light_point;
    
    glm::vec3 camera_position;
    glm::vec3 camera_target;
    glm::vec3 camera_up;
    
    std::vector<Mesh> objects;
};

#endif /* scene_h */

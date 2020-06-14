#define GLM_FORCE_SWIZZLE
#include <glm/gtc/type_ptr.hpp>

#include "../include/scene.h"

Scene::Scene()
:camera_position( glm::vec3(4.0, 2.0, 4.0) ),
camera_target( glm::vec3(0.0, 0.0, 0.0) ),
camera_up( glm::vec3(0.0, 1.0, 0.0) ),
proj( glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0) ),
view( glm::lookAt(camera_position, camera_target, camera_up) ),
VP( proj * view )
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(.0, .0, .0, .0);

    Shader* phong = new Shader("../../shaders/vs.glsl", "../../shaders/fs.glsl");
    
    Material* tchouri_mat = new Material(phong , glm::vec3(0.4, 0.3, 0.1), 10.0);
    Mesh* tchouri = new Mesh("../../meshes/tchouri.off", tchouri_mat);
    objects.push_back( tchouri );

    Material* light_mat = new Material(phong, glm::vec3(1.0, 1.0, 1.0), 0.0);
    Mesh* light = new Mesh("../../meshes/sphere.off", light_mat);
    light->scale(0.9);
    light->translate(glm::vec3(0.0, 10.0, 0.0));
    objects.push_back( light );
}

void Scene::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    for(auto obj: objects){
        GLuint shader_id = obj->get_shader_id();
        obj->rotate(glm::vec3(0.0,1.0,0.0), 0.01);
        glm::mat4 MVP = VP * obj->get_model();
        
        glUseProgram(shader_id);
        
        // get shader pointers
        GLuint MatrixID = glGetUniformLocation(shader_id, "MVP");
        GLuint MID = glGetUniformLocation(shader_id, "M");
        GLuint CamposID = glGetUniformLocation(shader_id, "eye_world");
        GLuint PointLightID = glGetUniformLocation(shader_id, "pointlight_world");
        
        GLuint MeshDiffID = glGetUniformLocation(shader_id, "mesh_diffuse");
        GLuint ShininessID = glGetUniformLocation(shader_id, "mesh_shininess");
        
        // send info to gpu
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(MID, 1, GL_FALSE, glm::value_ptr(obj->get_model()));
        glUniform3fv(CamposID, 1, glm::value_ptr(camera_position));
        glUniform3fv(PointLightID, 1, glm::value_ptr(glm::vec3(0.0, 10.0, 0.0)));
        
        glUniform3fv(MeshDiffID, 1, value_ptr(obj->material->diff_color));
        glUniform1fv(ShininessID, 1, &(obj->material->shininess));
        
        // draw item
        obj->draw();
    }
    glUseProgram(0);
}

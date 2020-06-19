#define GLM_FORCE_SWIZZLE
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <memory>

#include "../include/scene.h"
#include "../include/blinnmaterial.h"
#include "../include/mechanics.h"

Scene::Scene()
:camera_position( glm::vec3(0.0, 0.0, 50.0) ),
camera_target( glm::vec3(0.0, 0.0, 0.0) ),
camera_up( glm::vec3(0.0, 1.0, 0.0) ),
proj( glm::frustum(-5.0, 5.0, -5.0, 5.0, 20.0, 1000.0) ),
view( glm::lookAt(camera_position, camera_target, camera_up) ),
VP( proj * view )
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(.0, .0, .0, .0);

    // Materials
    std::shared_ptr<Material> eerie_mat = std::make_shared<BlinnMaterial>(shader_manager,
                                                                          glm::vec4(0.1, 0.1, 0.1, 1.0),
                                                                          glm::vec4(0.5, 0.6, 0.6, 1.0),
                                                                          glm::vec4(0.7, 0.6, 0.2, 1.0),
                                                                          50.0);
    
    std::shared_ptr<Material> light_mat = std::make_shared<BlinnMaterial>(shader_manager,
                                                                          glm::vec4(1.0, 1.0, 1.0, 1.0),
                                                                          glm::vec4(0.0, 0.0, 0.0, 0.0),
                                                                          glm::vec4(0.0, 0.0, 0.0, 0.0),
                                                                          1.0);

    std::shared_ptr<Material> weird_mat = std::make_shared<BlinnMaterial>(shader_manager,
                                                                          glm::vec4(0.5, 0.4, 0.1, 1.0),
                                                                          glm::vec4(0.8, 0.8, 0.8, 1.0),
                                                                          glm::vec4(0.4, 0.0, 0.0, 1.0),
                                                                          1.0);
    // Meshes
    std::shared_ptr<Mesh> tchouri_mesh = std::make_shared<Mesh>("../../meshes/tchouri.off");
    std::shared_ptr<Mesh> sphere_mesh = std::make_shared<Mesh>("../../meshes/sphere.off");
    
    std::shared_ptr<SpaceObject> sun = std::make_shared<SpaceObject>(sphere_mesh, light_mat, 1000.0, 0.5);
    
    std::shared_ptr<SpaceObject> tchouri = std::make_shared<SpaceObject>(tchouri_mesh, eerie_mat, 0.02, 0.7);
    tchouri->set_position(glm::vec3(9.0, 3.0, 0.0));
    tchouri->set_velocity(glm::vec3(0.3, -0.9, 0.0));
    tchouri->set_rotation(glm::vec3(0.0, 0.0, 1.0), -4e-9);
    
    std::shared_ptr<SpaceObject> eerie_planet = std::make_shared<SpaceObject>(sphere_mesh, weird_mat, 0.01, 1.0);
    eerie_planet->set_position(glm::vec3(2.0, 6.0, 0.0));
    eerie_planet->set_velocity(glm::vec3(0.6, -0.2, 0.0));
    
    objects.push_back(sun);
    objects.push_back(tchouri);
    objects.push_back(eerie_planet);
}

void Scene::physics_step(double dt){
    for(auto obj: objects){
        glm::vec3 accel(0.0);
        for(auto other: objects){
            if(obj != other)
                accel += Mechanics::Newton::compute_acceleration(obj, other);
        }
        obj->apply_rotation(dt);
        obj->apply_acceleration(accel, dt);
    }
}

void Scene::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glm::vec3 light_pos = objects[0]->get_position();
    glm::vec4 light_color(1.0, 1.0, 1.0, 1.0);
    float light_att_const = 1.0;
    float light_att_linear = 0.0;
    float light_att_quad = 0.01;
    
    for(auto obj: objects){
        GLuint shader_id = obj->get_shader_id();
        glm::mat4 MVP = VP * obj->get_model();
        glUseProgram(shader_id);
        obj->set_uniforms();
        
        // scene info
        glUniformMatrix4fv(glGetUniformLocation(shader_id, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(glGetUniformLocation(shader_id, "M"), 1, GL_FALSE, glm::value_ptr(obj->get_model()));
        glUniform3fv(glGetUniformLocation(shader_id, "campos"), 1, glm::value_ptr(camera_position));
        
        // light info
        glUniform3fv(glGetUniformLocation(shader_id, "point_light.position"), 1, glm::value_ptr(light_pos));
        glUniform4fv(glGetUniformLocation(shader_id, "point_light.color"), 1, glm::value_ptr(light_color));
        glUniform1fv(glGetUniformLocation(shader_id, "point_light.constant"), 1, &(light_att_const));
        glUniform1fv(glGetUniformLocation(shader_id, "point_light.linear"), 1, &(light_att_linear));
        glUniform1fv(glGetUniformLocation(shader_id, "point_light.quadratic"), 1, &(light_att_quad));
        
        // draw item
        obj->draw();
    }
    glUseProgram(0);
}

#undef GLM_FORCE_SWIZZLE

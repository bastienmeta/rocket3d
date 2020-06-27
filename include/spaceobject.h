
#ifndef spaceobject_h
#define spaceobject_h

#include <glm/glm.hpp>
#include <string>
#include <memory>

#include "mesh.h"
#include "material.h"

class SpaceObject{
public:
    SpaceObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat, double mass=1.0, double scale=1.0);
    ~SpaceObject();
    
    // setters = for init !
    void set_position(glm::vec3 position);
    void set_velocity(glm::vec3 velocity);
    void set_rotation(glm::vec3 axis, double speed);
    
    // mechanics
    glm::vec3& get_position();
    double get_mass();
    double get_radius();
    // add a force on this object
    void register_acceleration(glm::vec3& a, double dt, float speed);
    void register_rotation(double a, double dt, float speed);
    // apply all forces on this object for this step
    void apply_acceleration(float speed, double dt);
    void apply_rotation(float speed, double dt);
    
    // graphical
    GLuint get_shader_id();
    void set_uniforms();
    glm::mat4& get_model();
    void draw();
    
protected:
    // graphical
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    
    // mechanics
    double mass;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 rotation_axis;
    double rotation_speed;
    double radius;
        
    // transforms
    void translate(glm::vec3& vec);
    void rotate(glm::vec3& axis, float angle);
    void scale_xyz(glm::vec3& scale);
    void scale(float factor);
    
    glm::mat4 T, R, S;
    glm::mat4 model;
};

#endif


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
    void register_acceleration(glm::vec3& a);
    void register_rotation(double a);
    // apply all forces on this object for this step
    void apply_acceleration(double dt);
    void apply_rotation(double dt);
    
    // graphical
    GLuint get_shader_id();
    void set_uniforms();
    glm::mat4& get_model();
    void draw();
    
    // collisions
    virtual bool collides(std::shared_ptr<SpaceObject> other);
    virtual void resolve_collision(std::shared_ptr<SpaceObject> other);
    
protected:
    // graphical
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    
    // mechanics
    double mass;
    double radius;

    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 new_acceleration;
    
    glm::vec3 rotation_axis;
    double rotation_speed;
    double rotation_acc;
        
    // transforms
    void translate(glm::vec3& vec);
    void rotate(glm::vec3& axis, float angle);
    void scale_xyz(glm::vec3& scale);
    void scale(float factor);
    
    glm::mat4 T, R, S;
    glm::mat4 model;
};

#endif

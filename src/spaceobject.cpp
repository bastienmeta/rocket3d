#include "../include/spaceobject.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

SpaceObject::SpaceObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat, double mass, double scale)
:mesh(mesh), material(mat), mass(mass), rotation_axis(glm::vec3(0.0, 1.0, 0.0)), rotation_speed(0.0),
T(glm::mat4(1.0)), R(glm::mat4(1.0)), S(glm::mat4(scale)), model(glm::mat4(1.0))
{
    S[3][3] = 1.0;
}

SpaceObject::~SpaceObject(){
}

void SpaceObject::set_position(glm::vec3 pos){
    position = glm::vec3(0.0,0.0,0.0);
    T = glm::mat4(1.0);
    translate(pos);
}

void SpaceObject::set_velocity(glm::vec3 vel){
    velocity = vel;
}

void SpaceObject::set_rotation(glm::vec3 axis, double speed){
    rotation_axis = glm::normalize(axis);
    rotation_speed = speed;
}

glm::vec3& SpaceObject::get_position(){
    return position;
}

double SpaceObject::get_mass(){
    return mass;
}

void SpaceObject::apply_rotation(double dt){
    rotate(rotation_axis, rotation_speed * dt);
}

void SpaceObject::apply_acceleration(glm::vec3 &a, double dt){
    velocity += a * (float)dt;
    translate(velocity);
}

void SpaceObject::set_uniforms(){
    material->set_uniforms();
}

void SpaceObject::translate(glm::vec3& vec){
    position += vec;
    T = glm::translate(T, vec);
}

void SpaceObject::rotate(glm::vec3& axis, float angle){
    R = glm::rotate(R, angle, axis);
}

void SpaceObject::scale(float factor){
    S = glm::scale(S, glm::vec3(factor, factor, factor));
}

void SpaceObject::scale_xyz(glm::vec3& scale){
    S = glm::scale(S, scale);
}

glm::mat4& SpaceObject::get_model(){
    model = T*R*S;
    return model;
}

GLuint SpaceObject::get_shader_id(){
    return material->get_shader_id();
}

void SpaceObject::draw(){
    mesh->draw();
}

#version 330
layout (location = 0) in vec3 pos_model;
layout (location = 1) in vec3 normal_model;

uniform mat4 MVP;
uniform mat4 M;

out vec3 normal_v;
out vec3 fragpos;
out vec3 vertpos;

void main(){
    vec4 f_pos = MVP * vec4(pos_model, 1.0);
    fragpos = f_pos.xyz;
    
    vertpos = (M * vec4(pos_model, 1.0)).xyz;
    normal_v = (M * vec4(normalize(normal_model), 0.0)).xyz;
    
    gl_Position = f_pos;
}


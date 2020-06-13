#version 330
layout (location = 0) in vec3 pos_model;
layout (location = 1) in vec3 normal_model;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 P;

out vec3 vNormal;
out vec3 fragpos;
out vec3 pos;

void main(){

	gl_Position =  MVP * vec4(pos_model, 1.0);

	vec4 ppos = vec4(pos_model, 1.0);
	fragpos=(MVP * ppos).xyz;
	vNormal=normalize(normal_model);
	pos=ppos.xyz;
}


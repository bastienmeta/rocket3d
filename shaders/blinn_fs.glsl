#version 330

uniform vec3 mat_diffuse;
uniform float mat_shininess;

uniform vec3 pointlight_world;
uniform vec3 eye_world;

in vec3 normal_v;
in vec3 fragpos;
in vec3 vertpos;

out vec4 FragColor;

vec3 normals(vec3 pos) {
  vec3 fdx = dFdx(pos);
  vec3 fdy = dFdy(pos);
  return normalize(cross(fdx, fdy));
}

void main(){
    float amb_factor = 0.01;
    float diff_factor = 1.0;
    float spec_factor = 1.0;
    
    vec3 amb_color = vec3(1.0, 1.0, 1.0);
    vec3 spec_color = vec3(1.0, 1.0, 1.0);
    
    vec3 eyedir = normalize(eye_world - vertpos);
    vec3 lightdir = normalize(pointlight_world - vertpos);
    vec3 normal_f = normals(fragpos); // unused
    vec3 normal = normalize(normal_v);

    // ambient
    vec3 ambient = amb_color * amb_factor;

    // diffuse
	float diff = max(dot(normal, lightdir), 0.0);
    vec3 diffuse = diff * mesh_diffuse * diff_factor;
    
    // specular
    vec3 R = normalize(lightdir + eyedir);
    float spec = pow(max(dot(normal, R), 0.0), mesh_shininess);
    vec3 specular = spec * spec_color * spec_factor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}

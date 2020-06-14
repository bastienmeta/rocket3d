#version 330

uniform vec3 dirlight_world;
uniform vec3 pointlight_world;
uniform vec3 eye_world;

uniform vec3 mesh_diffuse;
uniform float shininess;

in vec3 color;
in vec3 vNormal;
in vec3 fragpos;
in vec3 pos;

out vec4 FragColor;

vec3 normals(vec3 pos) {
  vec3 fdx = dFdx(pos);
  vec3 fdy = dFdy(pos);
  return normalize(cross(fdx, fdy));
}

void main(){
    float spec_factor = 0.7;
    float diff_factor = 0.7;
    float amb_factor = 0.01;
    
    vec3 amb_color = vec3(1.0, 1.0, 1.0);
    vec3 spec_color = vec3(1.0, 1.0, 1.0);
    
	//vec3 dirlight = normalize(dirlight_world);
	vec3 normal_f = normals(pos);
	vec3 normal_v = normalize(vNormal);
	vec3 viewdir = normalize(eye_world - fragpos);
	vec3 plight_dir = normalize(pointlight_world - pos);

	float diff = max(dot(normal_v, plight_dir), 0.0);

	vec3 R = reflect(-plight_dir, normal_v);
	float spec = pow(max(0.0, dot(viewdir, R)), shininess);

    vec3 ambient = amb_color * amb_factor;
	vec3 diffuse = diff * mesh_diffuse * diff_factor;
    vec3 specular = spec * spec_color * spec_factor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}

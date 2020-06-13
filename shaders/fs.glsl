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
	vec3 dirlight = normalize(dirlight_world);
	vec3 normal_f = normals(pos);
	vec3 normal_v = normalize(vNormal);
	vec3 viewdir = normalize(eye_world - pos);
	vec3 plight_dir = normalize(pointlight_world - pos);

	float amb = 0.1;
	vec3 ambient = amb * vec3(1.0, 1.0, 1.0);

	float diff = max(dot(normal_f, plight_dir), 0.0);

	vec3 R = reflect(-plight_dir, normal_v);
	float spec = pow(max(0.0, dot(viewdir, R)), shininess);

	vec3 diffuse = diff * mesh_diffuse;	
	vec3 specular = spec * vec3(1.0, 1.0, 1.0);

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}
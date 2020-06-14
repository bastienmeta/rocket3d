#version 330

uniform vec3 mesh_diffuse;
uniform float mesh_shininess;

in vec3 normal_v;
in vec3 fragpos;
in vec3 vertpos;
in vec3 lightdir;
in vec3 eyedir;

out vec4 FragColor;

vec3 normals(vec3 pos) {
  vec3 fdx = dFdx(pos);
  vec3 fdy = dFdy(pos);
  return normalize(cross(fdx, fdy));
}

void main(){
    float amb_factor = 0.01;
    float diff_factor = 0.6;
    float spec_factor = 0.6;
    
    vec3 amb_color = vec3(1.0, 1.0, 1.0);
    vec3 spec_color = vec3(1.0, 1.0, 1.0);
    
	// vec3 normal_f = normals(fragpos);

	float diff = max(dot(normal_v, -lightdir), 0.0);

	vec3 R = reflect(-lightdir, normal_v);
	float spec = pow(max(0.0, dot(eyedir, R)), mesh_shininess);

    vec3 ambient = amb_color * amb_factor;
	vec3 diffuse = diff * mesh_diffuse * diff_factor;
    vec3 specular = spec * spec_color * spec_factor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}

#version 330

struct DirectionnalLight{
    bool used;
    vec3 direction;
    vec4 color;
};

struct PointLight{
    vec3 position;
    vec4 color;
    
    float constant;
    float linear;
    float quadratic;
};

struct Material{
    vec4 emissive;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform Material material;
// uniform DirectionnalLight dir_light;
uniform PointLight point_light;
uniform vec3 campos;

in vec3 normal_v;
in vec3 fragpos;
in vec3 vertpos;

out vec4 FragColor;

vec3 normals(vec3 pos) {
  vec3 fdx = dFdx(pos);
  vec3 fdy = dFdy(pos);
  return normalize(cross(fdx, fdy));
}

vec4 point_light_contribution(PointLight light, Material mat, vec3 normal, vec3 camdir){
    vec3 lightdir = normalize(light.position - vertpos);
    
    float diff = max(dot(normal, lightdir), 0.0);
    vec4 diffuse = diff * mat.diffuse * light.color;
    
    vec3 R = normalize(lightdir + camdir);
    float spec = pow(max(dot(normal, R), 0.0), mat.shininess);
    vec4 specular = spec * mat.specular * light.color;
    
    float distance = length(light.position - vertpos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                   light.quadratic * distance * distance);
                   
    return attenuation * (diffuse + specular);
}

void main(){
    vec3 camdir = normalize(campos - vertpos);
    vec3 normal_f = normals(fragpos); // unused
    vec3 normal = normalize(normal_v);

    vec4 color = material.emissive;
    color += point_light_contribution(point_light, material, normal, camdir);

	FragColor = color;
}

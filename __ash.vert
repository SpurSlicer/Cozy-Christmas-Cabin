#version 120

//in vec3 pos;
//in vec2 tex_coord;
//in vec3 norm;

varying vec2 tex_coord;
varying vec2 ash_tex_coord;
varying vec2 basalt_tex_coord;
varying vec2 alpha_tex_coord;
// varying float light_color;

uniform float u_time;

void calculatePhong() {
    vec3 position = vec3(gl_ModelViewMatrix * gl_Vertex);
    vec3 normal = normalize(gl_Normal);
    vec3 light_pos = vec3(gl_LightSource[0].position);
    vec3 light_vector = normalize(light_pos - position);
    vec3 reflected_light_vector = reflect(-light_vector, normal);
    vec3 view_vector = normalize(-position);
    // vec3 view_vector = vec3(0.0, 0.0, 0.0);
    float diffuse_intensity = max(dot(light_vector, normal), 0.0);
    float shininess_intensity = 0.0;
    if (diffuse_intensity > 0.0) {
        shininess_intensity = pow(max(dot(reflected_light_vector, view_vector), 0.0), gl_FrontMaterial.shininess);
    } else {
        shininess_intensity = 0.0;
    }
    gl_FrontColor = gl_FrontLightProduct[0].ambient
                  + diffuse_intensity * gl_FrontLightProduct[0].diffuse
                  + gl_FrontLightProduct[0].specular + 0.05;
}

void main() {
   calculatePhong();
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
   tex_coord = vec2(gl_MultiTexCoord0);
   ash_tex_coord = vec2(gl_MultiTexCoord0);
   basalt_tex_coord = vec2(gl_MultiTexCoord1);
   alpha_tex_coord = vec2(gl_MultiTexCoord2);
   // alpha_tex_coord.y -= (u_time * u_scroll_speed.z);
}
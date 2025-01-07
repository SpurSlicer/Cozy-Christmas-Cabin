#version 120

//BASE RETRIEVED FROM: https://rastertek.com/gl4linuxtut33.html

varying vec2 tex_coord;
varying vec2 smoke_tex_coord;
varying vec2 alpha_tex_coord;
// varying vec4 light_color;

uniform float u_time;
uniform float u_scroll_speed = 1.3;
uniform vec2 u_scale = vec2(2.0, 1.0);


// void calculatePhong() {
//     vec3 position = vec3(gl_ModelViewMatrix * gl_Vertex);
//     vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
//     vec3 light_pos = vec3(gl_LightSource[0].position);
//     vec3 light_vector = normalize(light_pos - position);
//     vec3 reflected_light_vector = reflect(-light_vector, normal);
//     vec3 view_vector = normalize(-position);
//     float diffuse_intensity = max(dot(light_vector, reflected_light_vector), 0.0);
//     float shininess_intensity = 0.0;
//     if (diffuse_intensity > 0.0) {
//         shininess_intensity = pow(max(dot(reflected_light_vector, view_vector), 0.0), gl_FrontMaterial.shininess);
//     } else {
//         shininess_intensity = 0.0;
//     }
//     light_color = gl_FrontLightProduct[0].ambient
//                   + diffuse_intensity * gl_FrontLightProduct[0].diffuse 
//                   + shininess_intensity * gl_FrontLightProduct[0].specular;
// }


void main() {
    gl_Position = ftransform();
    tex_coord = vec2(gl_MultiTexCoord0);
    smoke_tex_coord = vec2(gl_MultiTexCoord0 * u_scale.x);
    smoke_tex_coord.y -= (u_time * u_scroll_speed);   
    alpha_tex_coord = vec2(gl_MultiTexCoord1 * u_scale.y);
    // calculatePhong();
   // alpha_tex_coord.y -= (u_time * u_scroll_speed.z);
}
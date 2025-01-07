//  Identity vertex shader
#version 120

uniform vec3 desired_color;

// varying vec4 v_color;
varying vec2 v_texCoord;
uniform float u_flag;

void calculatePhong() {
    vec3 position = vec3(gl_ModelViewMatrix * gl_Vertex);
    vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
    vec3 light_pos = vec3(gl_LightSource[0].position);
    vec3 light_vector = normalize(light_pos - position);
    vec3 reflected_light_vector = reflect(-light_vector, normal);
    vec3 view_vector = normalize(-position);
    float diffuse_intensity = max(dot(light_vector, reflected_light_vector), 0.0);
    float shininess_intensity = 0.0;
    if (diffuse_intensity > 0.0) {
        shininess_intensity = pow(max(dot(reflected_light_vector, view_vector), 0.0), gl_FrontMaterial.shininess);
    } else {
        shininess_intensity = 0.0;
    }
    gl_FrontColor = gl_FrontLightProduct[0].ambient
                  + diffuse_intensity * gl_FrontLightProduct[0].diffuse 
                  * gl_FrontLightProduct[0].specular;
}

void main()
{
    if (u_flag == 1.0) calculatePhong();
    gl_Position = ftransform();
    // v_color = gl_Color;
    v_texCoord = vec2(gl_MultiTexCoord0);
}

// void main()
// {
//     vec3 position = vec3(gl_ModelViewMatrix * gl_Vertex);
//     vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
//     vec3 light_pos = vec3(gl_LightSource[0].position);
//     vec3 light_vector = normalize(light_pos - position);
//     vec3 reflected_light_vector = reflect(-light_vector, normal);
//     vec3 view_vector = normalize(-position);
//     float diffuse_intensity = max(dot(light_vector, normal), 0.0);
//     float shininess_intensity = 0.0;
//     if (diffuse_intensity > 0.0) {
//         shininess_intensity = pow(max(dot(reflected_light_vector, view_vector), 0.0), gl_FrontMaterial.shininess);
//     } else {
//         shininess_intensity = 0.0;
//     }
//     gl_FrontColor = gl_FrontLightProduct[0].ambient
//                   + diffuse_intensity * gl_FrontLightProduct[0].diffuse
//                   + shininess_intensity * gl_FrontLightProduct[0].specular;      v_texCoord = vec2(gl_MultiTexCoord0);
//     gl_Position = ftransform();
// }
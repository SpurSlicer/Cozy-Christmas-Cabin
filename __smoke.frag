#version 120

// BASE RETRIEVED FROM: https://rastertek.com/gl4linuxtut33.html

varying vec2 tex_coord;
varying vec2 smoke_tex_coord;
varying vec2 alpha_tex_coord;

//out vec4 color_result;

uniform sampler2D smoke_tex;
uniform sampler2D alpha_tex;

const vec2 distort_1 = vec2(0.2, 0.5);
const vec2 distort_2 = vec2(0.1, 0.2);

const float distort_scale = 0.2;
const float distort_bias = 0.2;

void main() {
    vec4 noise_1 = (texture2D(smoke_tex, smoke_tex_coord) - 0.5) * 2.0;
    vec4 noise_2 = (texture2D(alpha_tex, alpha_tex_coord) - 0.5) * 2.0;  

    noise_1.xy *= distort_1.xy;
    noise_2.xy *= distort_2.xy;

    vec4 noise_sum = noise_1 + noise_2;

    float perturb = (tex_coord.y * distort_scale) + distort_bias;

    vec2 noise_coords;
    noise_coords.x = (noise_sum.x * perturb) + tex_coord.x;
    noise_coords.y = 1.0 - ((noise_sum.y * perturb) + (1.0 - tex_coord.y));
    
    vec4 smoke = texture2D(smoke_tex, noise_coords);
    vec4 alpha = texture2D(alpha_tex, noise_coords);
    smoke.a = alpha.r;
    gl_FragColor = smoke * vec4(0.3, 0.3, 0.3, 1.0); 
}
#version 120

// BASE RETRIEVED FROM: https://rastertek.com/gl4linuxtut33.html

varying vec2 tex_coord;
varying vec2 noise_tex_coord;
varying vec2 fire_tex_coord;
varying vec2 alpha_tex_coord;

uniform sampler2D noise_tex;
uniform sampler2D fire_tex;
uniform sampler2D alpha_tex;

uniform vec2 distort_1 = vec2(0.2, 0.5);
uniform vec2 distort_2 = vec2(0.1, 0.2);
uniform vec2 distort_3 = vec2(1.0, 0.1);
uniform float distort_scale = 0.2;
uniform float distort_bias = 0.2;

void main() {
    vec4 noise_1 = ((texture2D(noise_tex, noise_tex_coord)) - 0.5) * 2.0; //- 0.5) * 2.0;
    vec4 noise_2 = ((texture2D(noise_tex, fire_tex_coord)) - 0.5) * 2.0; //- 0.5) * 2.0;
    vec4 noise_3 = ((texture2D(noise_tex, alpha_tex_coord)) - 0.5) * 2.0; //- 0.5) * 2.0;  
    noise_1.xy *= distort_1.xy;
    noise_2.xy *= distort_2.xy;
    noise_3.xy *= distort_3.xy;

    vec4 noise_sum = noise_1 + noise_2 + noise_3;

    float perturb = (tex_coord.y * distort_scale) + distort_bias;

    vec2 noise_coords = vec2(mix(noise_1, noise_2, noise_3));
    noise_coords.x = (noise_sum.x * perturb) + tex_coord.x;
    noise_coords.y = 1.1 - ((noise_sum.y * perturb) + (1.0 - tex_coord.y));

    vec4 fire_color = texture2D(fire_tex, noise_coords);
    vec4 alpha_color = texture2D(alpha_tex, noise_coords);
    
    fire_color.a = alpha_color.r;
    gl_FragColor = fire_color; 
}
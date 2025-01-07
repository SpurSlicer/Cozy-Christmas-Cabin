#version 120

varying vec2 tex_coord;
varying vec2 ash_tex_coord;
varying vec2 basalt_tex_coord;
varying vec2 alpha_tex_coord;
// varying float light_color;

uniform sampler2D ash_tex;
uniform sampler2D basalt_tex;
uniform sampler2D alpha_tex;



void main() {
    vec4 ash = texture2D(ash_tex, tex_coord);
    vec4 basalt = texture2D(basalt_tex, tex_coord);
    vec4 alpha = texture2D(alpha_tex, tex_coord); 
    gl_FragColor = (ash*alpha.r + basalt*(1-alpha.r)) * gl_Color; 
}
#version 120
// BASE RETRIEVED FROM: https://rastertek.com/gl4linuxtut33.html

varying vec2 tex_coord;
varying vec2 noise_tex_coord;
varying vec2 fire_tex_coord;
varying vec2 alpha_tex_coord;

uniform float u_time;
uniform vec3 u_scroll_speed = vec3(1.3, 2.1, 2.3);
uniform vec3 u_scale = vec3(1.0, 2.0, 0.0);

void main() {
   gl_Position = ftransform();
   tex_coord = vec2(gl_MultiTexCoord0);
   noise_tex_coord = vec2(gl_MultiTexCoord0 * u_scale.x);
   noise_tex_coord.y -= (u_time * u_scroll_speed.x);   
   noise_tex_coord.x -= sin(u_time);
   fire_tex_coord = vec2(gl_MultiTexCoord1 * u_scale.y);
   fire_tex_coord.y -= (u_time * u_scroll_speed.y);   
   fire_tex_coord.x += sin(u_time);
   alpha_tex_coord = vec2(gl_MultiTexCoord2 * u_scale.z);
   // alpha_tex_coord.y -= (u_time * u_scroll_speed.z);
}
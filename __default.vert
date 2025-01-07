#version 120

varying vec2 tex_coord;

uniform float u_time;

void main() {
   gl_Position = ftransform();
   tex_coord = vec2(gl_MultiTexCoord0);
}
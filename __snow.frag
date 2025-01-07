#version 120

uniform vec3 desired_color;

// varying vec4 v_color;
varying vec2 v_texCoord;
uniform sampler2D tex0;

uniform vec4 v_min;
uniform float u_time;
uniform float u_flag;

void main()
{
    vec4 current_color = texture2D(tex0, v_texCoord);
    //vec4 current_color = texture2D(tex0, v_texCoord) * v_color;
    if (v_min.w == 0.0) { 
        if (all(lessThan(current_color.rgb, v_min.rgb))) discard; 
    } else if (v_min.w == -1.0) {
        if (all(equal(current_color.rgb, v_min.rgb))) discard;
    } else { 
        if (all(greaterThan(current_color.rgb, v_min.rgb))) discard; 
    }
    // current_color.r += cos(u_time);
    if (u_flag == 1.0) gl_FragColor = current_color * gl_Color;
    else gl_FragColor = current_color;
}
#version 120 
// 120 = OpenGL 2.1

// vertex shader, attributs en entree
attribute vec2 a_Position;
attribute vec3 a_Color;

uniform float u_Time;

varying vec4 v_Color;

void main(void)
{
    v_Color = vec4(a_Color, 1.0);

    vec2 offset = vec2(sin(u_Time), 0.0);

    gl_Position = vec4(a_Position + offset
                        , 0.0, 1.0);
}
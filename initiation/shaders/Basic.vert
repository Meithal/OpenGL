#version 120

attribute vec3 a_position;
//attribute vec3 a_color;
attribute vec3 a_normal;
varying vec3 v_normal;


//varying vec4 v_color;

uniform float u_time;

void main(void) {

    gl_Position =  vec4(a_position, 1.0);
    v_normal =  a_normal;

    return;
    // | cos@ -sin@ 0 1 |
    // | sin@  cos@ 0 0 |
    // | 0      0   1 0 |
    // | 0      0   0 1 |
    mat4 transMat = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        /*sin(u_time / 1000.)*/1, 0, 0, 1
    );

    gl_Position = transMat * vec4( a_position, 1.0);
    //v_color = vec4(a_color, 1.0);
}

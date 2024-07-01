attribute vec2 a_position;
attribute vec3 a_color;

varying vec4 v_color;

uniform float u_time;

void main(void) {

    // | cos@ -sin@ 0 1 |
    // | sin@  cos@ 0 0 |
    // | 0      0   1 0 |
    // | 0      0   0 1 |
    mat4 transMat = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        sin(u_time / 1000.), 0, 0, 1
    );

    gl_Position = transMat * vec4( a_position, 0.0, 1.0);
    v_color = vec4(a_color, 1.0);
}

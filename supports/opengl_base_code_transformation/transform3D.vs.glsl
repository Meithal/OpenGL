#version 120 
// 120 = OpenGL 2.1

// vertex shader, attributs en entree
attribute vec2 a_Position;
attribute vec3 a_Color;

uniform float u_Time;

varying vec4 v_Color;

void main(void)
{
    // | cos@ -sin@ 0 0 |
    // | sin@  cos@ 0 0 |
    // | 0      0   1 0 |
    // | 0      0   0 1 |
    mat4 rotationMatrix = mat4(
        cos(u_Time), sin(u_Time), 0.0, 0.0, // 1ere colonne
        -sin(u_Time), cos(u_Time), 0.0, 0.0, // 2eme colonne
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    vec2 offset = vec2(sin(u_Time), 0.0);

    mat4 translationMatrix = mat4(
        1.0, 0.0, 0.0, 0.0, // 1ere colonne
        0.0, 1.0, 0.0, 0.0,  // 2eme colonne
        0.0, 0.0, 1.0, 0.0,
        offset.x, offset.y, 0.0, 1.0   // 4eme colonne (translation homogene)
    );

    v_Color = vec4(a_Color, 1.0);

    mat4 worldMatrix = translationMatrix * rotationMatrix;

    gl_Position = worldMatrix * vec4(a_Position, 0.0, 1.0);


    //gl_Position = vec4(a_Position * rotationMatrix
    //                     + offset, 0.0, 1.0);
}
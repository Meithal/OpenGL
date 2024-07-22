#version 120 
// 120 = OpenGL 2.1

// vertex shader, attributs en entree
attribute vec2 a_Position;
attribute vec3 a_Color;

uniform float u_Time;

// utilisez en C++
// int LOCATION = glGetUniformLocation(program, "nom");
// glUniformMatrix4fv(LOCATION, nombreDeMatrice, false, adresse);
uniform mat4 u_RotationMatrix;
uniform mat4 u_TranslationMatrix;

varying vec4 v_Color;

void main(void)
{
    v_Color = vec4(a_Color, 1.0);

    mat4 worldMatrix = u_TranslationMatrix * u_RotationMatrix;

    gl_Position = worldMatrix * vec4(a_Position, 0.0, 1.0);
}
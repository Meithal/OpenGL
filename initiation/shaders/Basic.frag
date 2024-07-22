#version 120
//varying vec4 v_color;

varying vec3 v_normal;


void main(void) {

    vec3 lightDir = normalize(vec3(0.0, 0.0, 1.0));
    float diff = max(dot(normalize(v_normal), lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    //gl_FragColor = vec4(diffuse, 1.0);

    gl_FragColor = vec4(v_normal * 0.5 + 0.5, 1.0); // Map normals to colors

    //gl_FragColor = vec4(, 1.0);
}


#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "common/GLShader.h"

// a compiler avec la ligne de commande:
// sous Windows
//  g++ -o transform2D.exe main_esgi3.cpp common/GLShader.cpp -lopengl32 -lglfw3 -lglew32
// sous Linux
// g++ -o transform2D.exe main_esgi3.cpp common/GLShader.cpp -lGL -lglfw -lGLEW

struct vec2 { float x, y; };
struct vec3 { float x, y, z; };
struct vec4 { float x, y, z, w; };
struct Vertex {
    vec2 position;
    vec3 color;
};

GLShader g_basicProgram;

void Initialize()
{
    g_basicProgram.LoadVertexShader("transform3D.vs.glsl");
    g_basicProgram.LoadFragmentShader("simple.fs.glsl");
    g_basicProgram.Create();
}

void Deinitialize()
{
    g_basicProgram.Destroy();
}

void Render()
{
    const Vertex triangle[] = {
        Vertex{vec2{+0.0f, +0.5f},vec3{1.0f, 0.0f, 0.0f}}, // sommet 0
        Vertex{vec2{-0.5f, -0.5f},vec3{0.0f, 1.0f, 0.0f}}, // sommet 1
        Vertex{vec2{+0.5f, -0.5f},vec3{0.0f, 0.0f, 1.0f}}  // sommet 2
    };
    glClearColor(1.f, 1.f, 0.0f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    // program est stockee dans notre classe GLShader
    int program = g_basicProgram.GetProgram();
    glUseProgram(program);

    // attributes

    int POSITION = glGetAttribLocation(program, "a_Position");
    glVertexAttribPointer(POSITION, 2, GL_FLOAT, false, 
                            sizeof(Vertex), &triangle->position.x);
    glEnableVertexAttribArray(POSITION);
    int COLOR = glGetAttribLocation(program, "a_Color");
    glVertexAttribPointer(COLOR, 3, GL_FLOAT, false,
                            sizeof(Vertex), &triangle->color.x);
    glEnableVertexAttribArray(COLOR);

    // uniforms

    float time = glfwGetTime();
    int UTIME = glGetUniformLocation(program, "u_Time");
    
    glUniform1f(UTIME, time);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUniform1f(UTIME, time*2.f);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum error = glewInit();

    Initialize();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    Deinitialize();

    glfwTerminate();
    return 0;
}
#include <cstdio>
#include <cmath>

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "common/GLShader.hpp"

int swidth = 960;
int sheight = 540;


GLShader g_BasicShader;

bool Initialise()
{
    if(!g_BasicShader.LoadVertexShader("shaders/Basic.vert"))
        return false;
    if(!g_BasicShader.LoadFragmentShader("shaders/Basic.frag"))
        return false;
    g_BasicShader.Create();
// cette fonction est spécifique à Windows et permet d’activer (1) ou non (0)
// la synchronization vertical. Elle necessite l’include wglew.h
#ifdef WIN32
    wglSwapIntervalEXT(1);
#endif
    return true;
}

void Terminate() {
    g_BasicShader.Destroy();
}

void RenderTri(int x, int y,  int w, int h)
{
    glViewport(x, y, w, h);
    glScissor(x, y, w, h);
    glClearColor(1.f, 1.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    int basicProgram = g_BasicShader.GetProgram();
    glUseProgram(basicProgram);

    glPushMatrix();
    //glLoadIdentity();
    float secs = (float)glutGet(GLUT_ELAPSED_TIME) ;
    //glRotatef(millis * 30, 0, 0, 1);
    int timeunifloc = glGetUniformLocation(basicProgram, "u_time");
    glUniform1f(timeunifloc, secs);

//    glLoadMatrixf((float[]){
//        1, 0, 0, sinf(secs / 100),
//        0, 1, 0, 0,
//        0, 0, 1, 0,
//        0,0, 0, 1
//        });

    float vertice[] = {
            0.0f, 0.5f, 1, 0, 0,
            -0.5f, -0.5f, 0, 1, 0,
            0.5f, -0.5f, 0, 0, 1
    };

    const int POSITION = glGetAttribLocation(basicProgram, "a_position");

    glEnableVertexAttribArray(POSITION);
    glVertexAttribPointer(
            POSITION,
            2, GL_FLOAT,
            GL_FALSE,
            5 * sizeof vertice[0],
    vertice
    );

    int loc_col = glGetAttribLocation(basicProgram, "a_color");

    glEnableVertexAttribArray(loc_col);
    glVertexAttribPointer(
            loc_col,
            3, GL_FLOAT,
            GL_FALSE,
            5 * sizeof vertice[0],
    vertice + 2
    );

    /*glBegin(GL_TRIANGLES);
        glColor3ub(255, 0, 0); // Rouge
        glVertex2f(0.0f, 0.5f);
        glColor3ub(0, 255, 0); // Vert
        glVertex2f(-0.5f, -0.5f);
        glColor3ub(0, 0, 255); // Bleu
        glVertex2f(0.5f, -0.5f);
    glEnd();*/

    glDrawArrays(GL_TRIANGLES, 0, 3);

    //glPopMatrix();
    glUseProgram(0);
}

void RenderFan(int x, int y,  int w, int h)
{
    float millis = (float)glutGet(GLUT_ELAPSED_TIME);

    glViewport(x, y, w, h);
    glScissor(x, y, w, h);
    glClearColor(1.f, .5f, 0.f, 1.f);
    glPushMatrix();

    glLoadIdentity();
    gluPerspective(90.0, 4.0/3.0, 1.0, 100.0);
    gluLookAt(0, 5.0, 5.0,   // Camera position (eye)
              0.0, 0.0, -20.0,   // Look-at point (center)
              0.0, 1.0, 1);  // Up vector



    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
        glColor3ub(255, 0, 0); // Rouge
        glVertex3f(0.0f, 0.5f, /*sin(millis / 1000) **/ -5);
        glColor3ub(0, 255, 0); // Vert
        glVertex3f(-0.5f, -0.5f,  -5);
        glColor3ub(0, 0, 255); // Bleu
        glVertex3f(0.5f, -0.5f, -5);
        glColor3ub(0,255 * sin(millis / 1000), 255 * sin(millis / 1000)); // Bleu
        glVertex3f(1.f, 0.5f,  -5);
        glColor3ub(255,255, 0); // Jaune
        glVertex3f(1.f, 0.5f,  -5);
    glEnd();

    glPopMatrix();
}

void RenderLine(int x, int y,  int w, int h)
{
    glViewport(x, y, w, h);
    glScissor(x, y, w, h);
    glClearColor(1.f, 0.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
        glColor3ub(255, 0, 0); // Rouge
        glVertex2f(0.0f, 0.5f);
        glColor3ub(0, 255, 0); // Vert
        glVertex2f(-0.5f, -0.5f);
        glColor3ub(0, 0, 255); // Bleu
        glVertex2f(0.5f, -0.5f);
        glColor3ub(0, 255, 255); // Bleu
        glVertex2f(1.f, 0.5f);
    glEnd();
}

void RenderTriStrip(int x, int y,  int w, int h)
{
    glViewport(x, y, w, h);
    glScissor(x, y, w, h);
    glClearColor(0.f, 1.f, 1.f, 1.f);
    glPushMatrix();
    gluOrtho2D(0, 400, 0, 400);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_STRIP);
        glColor3ub(255, 0, 0); // Rouge
        glVertex2f(0.0f * 400 + 200, 0.5f * 400 + 200);
        glColor3ub(0, 255, 0); // Vert
        glVertex2f(-0.5f * 400 + 200, -0.5f * 400 + 200);
        glColor3ub(0, 0, 255); // Bleu
        glVertex2f(0.5f * 400 + 200, -0.5f * 400 + 200);
        glColor3ub(0, 255, 255); // Bleu
        glVertex2f(1.f * 400 + 200, 0.5f*400 + 200);
    glEnd();
    glPopMatrix();
}

// la ‘callback’ executee par glutDisplayFunc()
// coordonnes commencent en bas a gauche
void Display(/*int x, int y,  int w, int h*/)
{
    RenderTri(0, sheight / 2, swidth / 2, sheight / 2);
    RenderFan(swidth / 2, sheight / 2, swidth / 2, sheight / 2);
    RenderLine(0, 0, swidth / 2, sheight / 2);
    RenderTriStrip(swidth / 2, 0, swidth / 2, sheight / 2);
    //glFlush();

    glutSwapBuffers(); 
    glutPostRedisplay(); // force reaffichage
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);


    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(swidth,sheight);
    glutCreateWindow("Triangle");

    glutDisplayFunc(Display);
    // glutDisplayFunc(DisplayTopRight);
    // glutDisplayFunc(DisplayBottomLeft);
    // glutDisplayFunc(DisplayBottomRight);
    //glTranslatef(0.3f, 0, 0);
    //glScalef(1.5f, 1.5f, 1.5f);
    //glLoadIdentity();
    //glMatrixMode(GL_MODELVIEW);
    //glRotatef(90.f, 0.f, 0.f, 1.f);

    GLint dim[2]; // Tableau pour stocker les dimensions maximales du viewport

    // Récupérer les dimensions maximales du viewport
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, dim);
    // GLint mvp;
    // glGetInteger(GL_MAX_VIEWPORTS, &mvp);

    printf("%d %d test\n", dim[0], dim[1]);
    glEnable(GL_CULL_FACE);
    glEnable(GL_SCISSOR_TEST);

    if(!Initialise())
        return 1;


    glutMainLoop();

    Terminate();
return 0; }
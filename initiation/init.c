#include <stdio.h>

#include <OpenGL/gl.h>
#include <GLUT/glut.h>


int swidth = 960;
int sheight = 540;

void RenderTri(int x, int y,  int w, int h)
{
    glViewport(x, y, w, h);
    glScissor(x, y, w, h);
    glClearColor(1.f, 1.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        glColor3ub(255, 0, 0); // Rouge
        glVertex2f(0.0f, 0.5f);
        glColor3ub(0, 255, 0); // Vert
        glVertex2f(-0.5f, -0.5f);
        glColor3ub(0, 0, 255); // Bleu
        glVertex2f(0.5f, -0.5f);
    glEnd();
}

void RenderFan(int x, int y,  int w, int h)
{
    glViewport(x, y, w, h);
    glScissor(x, y, w, h);
    glClearColor(1.f, .5f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
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
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_STRIP);
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

    GLint dim[2]; // Tableau pour stocker les dimensions maximales du viewport

    // Récupérer les dimensions maximales du viewport
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, dim);
    // GLint mvp;
    // glGetInteger(GL_MAX_VIEWPORTS, &mvp);

    printf("%d %d test\n", dim[0], dim[1]);
    glEnable(GL_CULL_FACE);
    glEnable(GL_SCISSOR_TEST);


    glutMainLoop();
return 0; }
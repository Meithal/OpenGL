//
// Created by ivo on 22/07/2024.
//


#include <cstdio>
#include <cmath>

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "../initiation/common/GLShader.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tinyobjloader/tiny_obj_loader.h"

#include <vector>
#include <string>

#include <iostream>

bool loadOBJ(const std::string& path, std::vector<float>& vertices, std::vector<float>& normals, std::vector<float>& texcoords) {
    //tinyobj::attrib_t attrib;
    //std::vector<tinyobj::shape_t> shapes;
    //std::vector<tinyobj::material_t> materials;
    std::string warn, err;


    std::string inputfile = "assets/monkey.obj";
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./assets"; // Path to material files
    reader_config.triangulate = true;


    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(inputfile, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        return false;
    }
    //tinyobj::ObjReader::ParseFromFile("assets/monkey.obj", )
    /*if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
        std::cerr << "Failed to load OBJ file: " << err << std::endl;
        return false;
    }*/

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            if (!attrib.normals.empty()) {
                normals.push_back(attrib.normals[3 * index.normal_index + 0]);
                normals.push_back(attrib.normals[3 * index.normal_index + 1]);
                normals.push_back(attrib.normals[3 * index.normal_index + 2]);
            }

            if (!attrib.texcoords.empty()) {
                texcoords.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                texcoords.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            }
        }
    }
    return true;
}



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
    gluPerspective(90.0, 4.0/3.0, 0.1, 100.0);
    gluLookAt(1, 0.0, -4.0,   // Camera position (eye)
              0.0, 0.0, -5.0,   // Look-at point (center)
              0.0, 1, 0);  // Up vector



    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 0, 0); // Rouge
    glVertex3f(0.0f, 0.5f, /*sin(millis / 1000) **/ -5);

    glColor3ub(0, 255, 0); // Vert
    glVertex3f(-0.5f, -0.5f,  -5);

    glColor3ub(0, 0, 255); // Bleu
    glVertex3f(0.5f, -0.5f, -5);

    glColor3ub(255  * sin((millis +333)/ 1000),255 * sin((millis + 666) / 1000), 255 * sin(millis / 1000)); // Bleu
    glVertex3f(1.f, 0.5f,  -5);

    glColor3ub(0,255, 255); // Jaune
    glVertex3f(1.f, 0.2f,  1.5);

    glEnd();

    glPopMatrix();
}

// #3
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

// #4
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

std::vector<GLfloat> vertices;
std::vector<GLfloat> normals;
std::vector<GLfloat> textures;
std::string err;

static float blanc[] = { 1.0F,1.0F,1.0F,1.0F };

void RenderObjOgl1(int x, int y,  int w, int h)
{
    GLfloat l_pos0[] = { 1.0,1.0,1.0,0.0 };
    GLfloat l_ambient0[] = { 1.0,1.0,1.0,0.5 };
    GLfloat shinines[] = { 50.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glClearColor(1.f, 0.f, 1.f, 1.f);

    glViewport(x, y, w, h);
    glScissor(x, y, w, h);
    glEnable(GL_SCISSOR_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, static_cast<double>(w) / static_cast<double>(h), 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 0.0, -4.0,  // Camera position (eye)
              0.0, 0.0, -5.0,  // Look-at point (center)
              0.0, 1.0, 0.0);  // Up vector

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, l_pos0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, l_ambient0);
    //glMaterialfv(GL_FRONT,GL_SPECULAR,blanc);
    //glMaterialfv(GL_FRONT,GL_SHININESS,shinines);

    glBegin(GL_TRIANGLES);
    for(int i = 0; i < vertices.size(); i+=3) {
        glVertex3f(vertices[i], vertices[i+1], vertices[i+2]);
    }

    glEnd();

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

// obj 3 glGetAttribLocation
void RenderObjAttrib(int x, int y,  int w, int h)
{
    glViewport(x, y, w, h);
    glScissor(x, y, w, h);
    glLoadIdentity();
    gluPerspective(90.0, 4.0/3.0, 0.1, 100.0);
    gluLookAt(1, 0.0, -4.0,   // Camera position (eye)
              0.0, 0.0, -5.0,   // Look-at point (center)
              0.0, 1, 0);  // Up vector

    glClearColor(1.f, 1.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int basicProgram = g_BasicShader.GetProgram();
    glUseProgram(basicProgram);

    const int POSITION = glGetAttribLocation(basicProgram, "a_position");

    //glEnableClientState(GL_VERTEX_ARRAY);
    glEnableVertexAttribArray(POSITION);
    glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat), vertices.data());

    //glEnableClientState(GL_NORMAL_ARRAY);

    const int NORMAL = glGetAttribLocation(basicProgram, "a_normal");
    glEnableVertexAttribArray(NORMAL);

    glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat), normals.data());

    //glVertexAttribPointer(GL_FLOAT, 0, normals.data());

    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3.);

    //glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_NORMAL_ARRAY);
    glUseProgram(0);

}

// la ‘callback’ executee par glutDisplayFunc()
// coordonnes commencent en bas a gauche
void Display(/*int x, int y,  int w, int h*/)
{
    /*RenderTri(0, sheight / 2, swidth / 2, sheight / 2);
    RenderFan(swidth / 2, sheight / 2, swidth / 2, sheight / 2);
    RenderLine(0, 0, swidth / 2, sheight / 2);
    RenderTriStrip(swidth / 2, 0, swidth / 2, sheight / 2);*/
    //glFlush();

    RenderObjOgl1(0, sheight / 2, swidth / 2, sheight / 2);
    RenderObjAttrib(0, 0, swidth / 2, sheight / 2);

    glutSwapBuffers();
    glutPostRedisplay(); // force reaffichage
}

/*std::vector<tinyobj::shape_t> shapes;
std::vector<tinyobj::material_t> materials;
std::string err;
*/




int main(int argc, char** argv)
{
    glutInit(&argc, argv);


    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);
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
    glEnable(GL_DEPTH_TEST);  // Enable depth testing

    if(!Initialise())
        return 1;

    if(!loadOBJ("assets/monkey.obj", vertices, normals, textures))
        goto end;

    glutMainLoop();

    end:
    Terminate();
    return 0;

}
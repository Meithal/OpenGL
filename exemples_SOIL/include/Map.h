#ifndef MAP_H
#define MAP_H

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <GLUT/glut.h>
#include <SOIL/SOIL.h>

#include "Camera.h"

class Map
{
    public:
        Map();
        // Stockage des r�f�rences aux textures
        GLuint ListeTextures[20];
        GLuint Skybox[6];
        void LoadTextures(void);
        void DrawGround(void);
        void DrawSkybox(Camera *cam);
    protected:
    private:
};

#endif // MAP_H

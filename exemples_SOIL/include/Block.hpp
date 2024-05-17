#ifndef BLOCK_H
#define BLOCK_H

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <GLUT/glut.h>
#include <SOIL/SOIL.h>

#define ANCHOR_FROM_ORIGIN 0
#define ANCHOR_FROM_CENTER 1

#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define TOP 4
#define BOT 5
#define ALL 6
#define SPHERE 7

#define TEXTURE_SCALE 1.0f

extern int angle;

class Block
{
    public:
        Block();
        Block(float x, float y, float z);
        void Draw();
        void SetTexture(int face, GLuint texture);

        float posx;
        float posy;
        float posz;

        float x;
        float y;
        float z;
    protected:

    private:
        GLuint textures[8];
        char anchor[3];
};

#endif // BLOCK_H

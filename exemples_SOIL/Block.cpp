#include <vector>

#include "Block.hpp"
#include "Quaternion.hpp"
#include "Transform.hpp"

int angle = 0;

Block::Block()
{
    posx = 0.0f;
    posy = 0.0f;
    posz = 0.0f;

    x = 1.0f;
    y = 1.0f;
    z = 1.0f;

    for (int i = 0; i < 6; i++)
    {
        textures[i] = 0;
    }
    for (int j = 0; j < 3; j ++)
    {
        anchor[j] = 0;
    }
}

Block::Block(float x, float y, float z, bool _is_mat)
{
    posx = 0.0f;
    posy = 0.0f;
    posz = 0.0f;
    mat_rot =  _is_mat;

    this->x = x;
    this->y = y;
    this->z = z;

    for (int i = 0; i < 6; i++)
    {
        textures[i] = 0;
    }

    for (int j = 0; j < 3; j ++)
    {
        anchor[j] = 0;
    }
}

void Block::Draw()
{
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();

    if (anchor[0]) glTranslatef(-x/2, 0.0f, 0.0f);
    if (anchor[1]) glTranslatef(0.0f, -y/2, 0.0f);
    if (anchor[2]) glTranslatef(0.0f, 0.0f, -z/2);

    // Calculate the center of the cube
    Vec3 center = {x / 2.0f, y / 2.0f, z / 2.0f};

    // Define the eight vertices of the cube
    std::vector<Vec3> verts = {
            {0.0f, 0.0f, 0.0f},
            {0.0f, y, 0.0f},
            {x, y, 0.0f},
            {x, 0.0f, 0.0f},
            {0.0f, 0.0f, z},
            {0.0f, y, z},
            {x, y, z},
            {x, 0.0f, z}
    };

    if(!mat_rot) {
        for (Vec3 &p: verts) {
            Vec3 translated = p - center;
            Vec3 i{translated.i, translated.j, translated.k};
            Vec3 rotated = rot(
                    i, q{sin((double) angle / 30) * 30, 1, 0, 0},
                    q{(double) angle / 10, 0, 1, 0}
            );
            Vec3 translated2 = rotated + center * 3;
            Vec3 rotated2 = rot(
                    translated2, q{(double) angle, 0, 1, 0}
                    //,q{(double)angle/2, 0, 0, 1}
            );
            p = rotated2 - center * 2;
        }
    } else {
        for (Vec3 &p: verts) {

            auto qa = QuatA(1, p.i, p.j, p.k);

            auto rotated = qa.euler(p.i, p.j, p.k);
            auto res = rotated.toEuler();

            p.i = res.x;
            p.j = res.y;
            p.k = res.z;
        }
    }



    /// LE CUBE
    /** FRONT **/

    glBindTexture(GL_TEXTURE_2D, textures[FRONT]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(verts[0].i, verts[0].j, verts[0].k);
        glTexCoord2f(0.0f, y/TEXTURE_SCALE);
        glVertex3f(verts[1].i, verts[1].j, verts[1].k);
        glTexCoord2f(x/TEXTURE_SCALE, y/TEXTURE_SCALE);
        glVertex3f(verts[2].i, verts[2].j, verts[2].k);
        glTexCoord2f(x/TEXTURE_SCALE, 0.0f);
        glVertex3f(verts[3].i, verts[3].j, verts[3].k);
    glEnd();

    /** BACK **/

    glBindTexture(GL_TEXTURE_2D, textures[BACK]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(verts[4].i, verts[4].j, verts[4].k);
        glTexCoord2f(0.0f, y/TEXTURE_SCALE);
        glVertex3f(verts[5].i, verts[5].j, verts[5].k);
        glTexCoord2f(x/TEXTURE_SCALE, y/TEXTURE_SCALE);
        glVertex3f(verts[6].i, verts[6].j, verts[6].k);
        glTexCoord2f(x/TEXTURE_SCALE, 0.0f);
        glVertex3f(verts[7].i, verts[7].j, verts[7].k);
    glEnd();

    /** TOP **/

    glBindTexture(GL_TEXTURE_2D, textures[TOP]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(verts[1].i, verts[1].j, verts[1].k);
        glTexCoord2f(0.0f, y/TEXTURE_SCALE);
        glVertex3f(verts[5].i, verts[5].j, verts[5].k);
        glTexCoord2f(x/TEXTURE_SCALE, y/TEXTURE_SCALE);
        glVertex3f(verts[6].i, verts[6].j, verts[6].k);
        glTexCoord2f(x/TEXTURE_SCALE, 0.0f);
        glVertex3f(verts[2].i, verts[2].j, verts[2].k);
    glEnd();

    /** BOT **/

    glBindTexture(GL_TEXTURE_2D, textures[BOT]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(verts[0].i, verts[0].j, verts[0].k);
        glTexCoord2f(0.0f, z/TEXTURE_SCALE);
        glVertex3f(verts[4].i, verts[4].j, verts[4].k);
        glTexCoord2f(x/TEXTURE_SCALE, z/TEXTURE_SCALE);
        glVertex3f(verts[7].i, verts[7].j, verts[7].k);
        glTexCoord2f(x/TEXTURE_SCALE, 0.0f);
        glVertex3f(verts[3].i, verts[3].j, verts[3].k);
    glEnd();

    /** LEFT **/

    glBindTexture(GL_TEXTURE_2D, textures[LEFT]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(verts[0].i, verts[0].j, verts[0].k);
        glTexCoord2f(0.0f, z/TEXTURE_SCALE);
        glVertex3f(verts[4].i, verts[4].j, verts[4].k);
        glTexCoord2f(y/TEXTURE_SCALE, z/TEXTURE_SCALE);
        glVertex3f(verts[5].i, verts[5].j, verts[5].k);
        glTexCoord2f(y/TEXTURE_SCALE, 0.0f);
        glVertex3f(verts[1].i, verts[1].j, verts[1].k);
    glEnd();

    /** RIGHT **/

    glBindTexture(GL_TEXTURE_2D, textures[RIGHT]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        
        glVertex3f(verts[3].i, verts[3].j, verts[3].k);
        glTexCoord2f(0.0f, z/TEXTURE_SCALE);
        glVertex3f(verts[7].i, verts[7].j, verts[7].k);
        glTexCoord2f(y/TEXTURE_SCALE, z/TEXTURE_SCALE);
        glVertex3f(verts[6].i, verts[6].j, verts[6].k);
        glTexCoord2f(y/TEXTURE_SCALE, 0.0f);
        glVertex3f(verts[2].i, verts[2].j, verts[2].k);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glPopMatrix();

}

void Block::SetTexture(int face, GLuint texture)
{
    textures[face] = texture;
}

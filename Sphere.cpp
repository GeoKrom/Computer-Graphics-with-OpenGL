#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderHandler.h"
#include "Sphere.h"

Sphere::Sphere() {}

const int na = 72;        // vertex grid size
const int nb = 36;
const int na3 = na * 3;     // line in grid size
const int nn = nb * na3;    // whole grid size
const float PI = acos(-1);
GLfloat sphere_pos[nn]; // vertex
GLfloat sphere_nor[nn]; // normal
GLfloat sphere_col[nn] ;   // color
GLuint  sphere_ix[na * (nb - 1) * 6];    // indices
GLuint sphere_vbo[4] = { -1,-1,-1,-1 };
GLuint sphere_vao[4] = { -1,-1,-1,-1 };

void Sphere::makeSphere(float aktina, float pk, float ad, float me)
{
    // generate the sphere data
    GLfloat x,y,z,a, b, da, db;
    int ia, ib, ix, iy;
    da = 2.0 * PI / GLfloat(na);
    db = PI / GLfloat(nb - 1);
    // [Generate sphere point data]
    // spherical angles a,b covering whole sphere surface
    for (ix = 0, b = -0.5 * PI, ib = 0; ib < nb; ib++, b += db)
        for (a = 0.0, ia = 0; ia < na; ia++, a += da, ix += 3)
        {
            // unit sphere
            x = cos(b) * cos(a) + me; //ad - aristera deksia
            y = cos(b) * sin(a) + pk; //pk - panw katw
            z = sin(b) + ad; //me - mesa eksw
            sphere_pos[ix + 0] = x * aktina;
            sphere_pos[ix + 1] = y * aktina;
            sphere_pos[ix + 2] = z * aktina;
            sphere_nor[ix + 0] = x ;
            sphere_nor[ix + 1] = y ;
            sphere_nor[ix + 2] = z ;
        }
    // [Generate GL_TRIANGLE indices]
    for (ix = 0, iy = 0, ib = 1; ib < nb; ib++)
    {
        for (ia = 1; ia < na; ia++, iy++)
        {
            // first half of QUAD
            sphere_ix[ix] = iy;      ix++;
            sphere_ix[ix] = iy + 1;    ix++;
            sphere_ix[ix] = iy + na;   ix++;
            // second half of QUAD
            sphere_ix[ix] = iy + na;   ix++;
            sphere_ix[ix] = iy + 1;    ix++;
            sphere_ix[ix] = iy + na + 1; ix++;
        }
        // first half of QUAD
        sphere_ix[ix] = iy;       ix++;
        sphere_ix[ix] = iy + 1 - na;  ix++;
        sphere_ix[ix] = iy + na;    ix++;
        // second half of QUAD
        sphere_ix[ix] = iy + na;    ix++;
        sphere_ix[ix] = iy - na + 1;  ix++;
        sphere_ix[ix] = iy + 1;     ix++;
        iy++;
    }
    
    // [VAO/VBO stuff]
    GLuint i;
    glGenVertexArrays(4, sphere_vao);
    glGenBuffers(4, sphere_vbo);
    glBindVertexArray(sphere_vao[0]);
    i = 0; // vertex
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_pos), sphere_pos, GL_STATIC_DRAW);
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
    i = 1; // indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_vbo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere_ix), sphere_ix, GL_STATIC_DRAW);
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, 4, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
    i = 2; // normal
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_nor), sphere_nor, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    i=3; // color
    glBindBuffer(GL_ARRAY_BUFFER,sphere_vbo[i]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(sphere_col),sphere_col,GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(i,1,GL_FLOAT,GL_FALSE,0,0);
 
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glBindVertexArray(sphere_vao[0]);

    glDrawElements(GL_TRIANGLES, sizeof(sphere_ix) / sizeof(GLuint), GL_UNSIGNED_INT, 0);    // indices (choose just one line not both !!!)
    
}

//---------------------------------------------------------------------------
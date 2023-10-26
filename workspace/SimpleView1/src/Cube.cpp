#include "Cube.hpp"
#include <iostream>

Cube::Cube()
{
	// set set cordinate values for all vertices
    // other faces
    r = 1.0;
    g = 0.0;
    b = 0.0;

    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = -1;
    vertex[1][0] = -1; vertex[1][1] = 1;  vertex[1][2] = -1;
    vertex[2][0] = 1;  vertex[2][1] = 1;  vertex[2][2] = -1;
    vertex[3][0] = 1;  vertex[3][1] = -1; vertex[3][2] = -1;
    vertex[4][0] = -1; vertex[4][1] = -1; vertex[4][2] = 1;
    vertex[5][0] = -1; vertex[5][1] = 1;  vertex[5][2] = 1;
    vertex[6][0] = 1;  vertex[6][1] = 1;  vertex[6][2] = 1;
    vertex[7][0] = 1;  vertex[7][1] = -1; vertex[7][2] = 1;

    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
    face[1][0] = 7; face[1][1] = 6; face[1][2] = 5; face[1][3] = 4;
    face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;
    face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;
    face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;
    face[5][0] = 0; face[5][1] = 3; face[5][2] = 7; face[5][3] = 4;
}

void Cube::drawFace(int i)
{
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertex[face[~i][0]]);
	glVertex3fv(vertex[face[i][1]]);
	glVertex3fv(vertex[face[i][2]]);
	glVertex3fv(vertex[face[i][3]]);
	glEnd();
}

void Cube::draw()
{
    glPushMatrix();
    this->ctmMultiply();
 	glColor3f(r, g, b);
 	for (int i = 0; i < 6; i++) {
 		this->drawFace(i);

 	}
    glPopMatrix();
}


Pyramid::Pyramid()
{
	// set set cordinate values for all vertices
    // other faces
    r = 1.0;
    g = 1.0;
    b = 0.0;

    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = -1;
    vertex[1][0] = -1; vertex[1][1] = 1;  vertex[1][2] = -1;
    vertex[2][0] = 1;  vertex[2][1] = 1;  vertex[2][2] = -1;
    vertex[3][0] = 1;  vertex[3][1] = -1; vertex[3][2] = -1;
    vertex[4][0] = 0; vertex[4][1] = 0; vertex[4][2] = 1;

    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
    face[1][0] = 0; face[1][1] = 1; face[1][2] = 4; face[1][3] = 4;
    face[2][0] = 1; face[2][1] = 2; face[2][2] = 4; face[2][3] = 4;
    face[3][0] = 2; face[3][1] = 3; face[3][2] = 4; face[3][3] = 4;
    face[4][0] = 3; face[4][1] = 0; face[4][2] = 4; face[4][3] = 4;
}

void Pyramid::drawFace(int i)
{
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertex[face[i][0]]);
	glVertex3fv(vertex[face[i][1]]);
	glVertex3fv(vertex[face[i][2]]);

	GLfloat value = *vertex[face[i][2]];

	if (value != 4) {
		glVertex3fv(vertex[face[i][3]]);
	}

	glEnd();
}

void Pyramid::draw()
{
    glPushMatrix();
    this->ctmMultiply();
 	glColor3f(r, g, b);
 	for (int i = 0; i < 5; i++) {
 		this->drawFace(i);

 	}
    glPopMatrix();
}


House::House()
{
	// set set cordinate values for all vertices
    // other faces
    r = 1.0;
    g = 0.0;
    b = 0.0;

    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = -1; // Index 0 (bottom)
    vertex[1][0] = -1; vertex[1][1] = -1; vertex[1][2] =  0; // 1

    vertex[2][0] = -1; vertex[2][1] =  1; vertex[2][2] = -1; // Index 2 (bottom)
    vertex[3][0] = -1; vertex[3][1] =  1; vertex[3][2] =  0; // 3

	vertex[4][0] =  1; vertex[4][1] = -1; vertex[4][2] = -1; // Index 4 (bottom)
	vertex[5][0] =  1; vertex[5][1] = -1; vertex[5][2] =  0; // 5

	vertex[6][0] =  1; vertex[6][1] =  1; vertex[6][2] = -1; // Index 6 (bottom)
	vertex[7][0] =  1; vertex[7][1] =  1; vertex[7][2] =  0; // 7

	vertex[8][0] =  0; vertex[8][1] =  0; vertex[8][2] =  1; // Index 8 (Top of triangle)

    face[0][0] = 2; face[0][1] = 3; face[0][2] = 0; face[0][3] = 1;
    face[1][0] = 0; face[1][1] = 4; face[1][2] = 1; face[1][3] = 5;
    face[2][0] = 4; face[2][1] = 5; face[2][2] = 6; face[2][3] = 7;
    face[3][0] = 7; face[3][1] = 6; face[3][2] = 3; face[3][3] = 2;
    face[4][0] = 3; face[4][1] = 7; face[4][2] = 8; face[4][3] = 8;
    face[5][0] = 3; face[5][1] = 1; face[5][2] = 8; face[5][3] = 8;
    face[6][0] = 1; face[6][1] = 5; face[6][2] = 8; face[6][3] = 8;
    face[7][0] = 5; face[7][1] = 7; face[7][2] = 8; face[7][3] = 8;

}

void House::drawFace(int i)
{
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertex[face[i][0]]);
	glVertex3fv(vertex[face[i][1]]);
	glVertex3fv(vertex[face[i][2]]);

	GLfloat value = *vertex[face[i][2]];
	if (value != 8) {glVertex3fv(vertex[face[i][3]]);}

	glEnd();
}

void House::draw()
{
    glPushMatrix();
    this->ctmMultiply();
 	glColor3f(r, g, b);
 	for (int i = 0; i < 8; i++) {

 		if (i == 4) {
 			g = 1.0;
 			glColor3f(r, g, b);
 		}
 		this->drawFace(i);

 	}
    glPopMatrix();
}


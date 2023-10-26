/*
 * Description: SimpleView reference design
 * Author: HBF
 * Version: 2022-10-03
 */
#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

class Cube: public Shape {
protected:
	GLfloat vertex[8][3];  /* 2D array to store cube vertices */
	GLint face[6][4];      /* 2D array to store faces */
	GLfloat r, g, b;       /* color cube */
public:
	Cube();
	void draw();
	void drawFace(int);
};

class Pyramid: public Shape {
protected:
	GLfloat vertex[5][3];  /* 2D array to store triangle vertices */
	GLint face[5][4];      /* 2D array to store faces */
	GLfloat r, g, b;       /* color triangle */
public:
	Pyramid();
	void draw();
	void drawFace(int);
};

class House: public Shape {
protected:
	GLfloat vertex[9][3];  /* 2D array to store cube vertices */
	GLint face[8][4];      /* 2D array to store faces */
	GLfloat r, g, b;       /* color cube */
public:
	House();
	void draw();
	void drawFace(int);
};

#endif

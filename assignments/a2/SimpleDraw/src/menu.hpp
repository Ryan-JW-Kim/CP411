# include <GL/glut.h>
#include <iostream>


#ifndef MENU_HPP
#define MENU_HPP

extern bool drawMode, editMode, rectMode, dragMode;
extern GLint strokeWidth;
extern GLfloat strokeRed, strokeGreen, strokeBlue, red, green, blue;

void editSubMenu(GLint editOption);
void drawSubMenu(GLint drawOption);
void styleSubMenu(GLint styleOption);
void fileSubMenu(GLint fileOption);
void strokeColorSubMenu(GLint colorOption);
void strokeWidthSubMenu(GLint widthOption);
void fillColorSubMenu(GLint colorOption);

#endif
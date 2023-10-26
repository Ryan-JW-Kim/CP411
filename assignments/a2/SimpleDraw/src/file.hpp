# include <GL/glut.h>
# include "object.hpp"

#ifndef FILE_HPP
#define FILE_HPP

extern GLsizei winHeight;
extern GLsizei winWidth;
void fileOpen();
void fileSave();
int exportBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight);
int exportSVG(const char *filename, node* head, int winWidth, int winHeight);
int importSVG(const char *filename);

#endif
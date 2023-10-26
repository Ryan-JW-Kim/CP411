/*
 * Description: Example from textbook chapter 20, GUI menu
 * Compile: g++ opengl_menu.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe
*/

#include <GL/glut.h>
#include <iostream>
#include "menu.hpp"
#include "edit.hpp"
#include "object.hpp"
#include "file.hpp"
#include "object.hpp"

DoubleLinkedList* listPtr = new DoubleLinkedList;
GLsizei winWidth = 800, winHeight = 600;      // Initial Display-window size.
GLenum renderingMode = GL_SMOOTH;             // Initial fill method.

node* tempNode;
node* draggingNode;
// Initialize default modes
bool drawMode = true;
bool editMode = false;
bool dragMode = false;
bool rectMode = true;

float lerpFactor = 0.9;
GLint prevMouseX;
GLint prevMouseY;
GLint strokeWidth = 0;
GLfloat strokeRed = 1.0;
GLfloat strokeGreen  = 0.0;
GLfloat strokeBlue = 0.0;
GLfloat red = 1.0;
GLfloat green = 0.0;
GLfloat blue = 0.0;

void init (void)
{
   glClearColor (1.0, 1.0, 1.0, 1.0);  // Set display-window color to gray.
   glMatrixMode (GL_PROJECTION);
   gluOrtho2D (0.0, 300.0, 0.0, 300.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (listPtr->head != NULL) { listPtr->drawShapes(); }
	if (tempNode != NULL) { listPtr->drawNode(tempNode); }
	glFlush();
}

void mousePtPlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (action == GLUT_DOWN) {
			if (drawMode) {
				tempNode = new node;
				tempNode->x1 = xMouse;
				tempNode->y1 = winHeight - yMouse;
				tempNode->red = red;
				tempNode->green = green;
				tempNode->blue = blue;
				tempNode->strokeWidth = strokeWidth;
				tempNode->strokeRed = strokeRed;
				tempNode->strokeGreen = strokeGreen;
				tempNode->strokeBlue = strokeBlue;

				if (rectMode) {
					tempNode->x2 = tempNode->x1;
					tempNode->y2 = tempNode->y1;
					tempNode->isRectangle = true;
					
				} else {
					tempNode->isRectangle = false;
					tempNode->radius = 0.0;
				}
			} else { 
				Node* current;
				current = listPtr->tail;
				int relativeY = winHeight - yMouse;
				bool found = false;
				while (current != NULL) {
					if (current->isRectangle) {
						int minX; int maxX; int maxY; int minY;
						if (current->x1 < current->x2) { minX = current->x1; maxX = current->x2; } 
						else { minX = current->x2; maxX = current->x1; }
						if (current->y1 < current->y2) { minY = current->y1; maxY = current->y2; }
						else { minY = current->y2; maxY = current->y1; }

						if (xMouse >= minX && xMouse <= maxX && relativeY >= minY && relativeY <= maxY) {
							listPtr->selectedNode = current;
							found = true;
							break;
						}
					} else {
						int deltaX = xMouse - current->x1;
						int deltaY = relativeY - current->y1;
						if (sqrt(pow(deltaX, 2) + pow(deltaY, 2)) <= current->radius) {
							listPtr->selectedNode = current;
							found = true;
							break;
						}
						
					}
					current = current->next;
				}

				if (!found){
					std::cout << "No node selected" << std::endl;
					listPtr->selectedNode = NULL;
				} else if (dragMode) {
					listPtr->drawSelection = false;
					draggingNode = current;
					prevMouseX = xMouse;
					prevMouseY = yMouse;
				} else if (editMode){
					listPtr->drawSelection = true;
				}

			} // EDIT SELECT LOGIC
		} else if (action == GLUT_UP) {
			if (drawMode) {
				if (tempNode == NULL) { return; }
				
				Node* insertNode = new Node;
				insertNode->isRectangle = tempNode->isRectangle;
				insertNode->red = tempNode->red;
				insertNode->green = tempNode->green;
				insertNode->blue = tempNode->blue;
				insertNode->x1 = tempNode->x1;
				insertNode->y1 = tempNode->y1;
				insertNode->strokeWidth = tempNode->strokeWidth;
				insertNode->strokeRed = tempNode->strokeRed;
				insertNode->strokeGreen = tempNode->strokeGreen;
				insertNode->strokeBlue = tempNode->strokeBlue;

				if (tempNode->isRectangle) {
					insertNode->x2 = xMouse;	
					insertNode->y2 = winHeight - yMouse;
				} else {
					insertNode->radius = tempNode->radius;
				} 

				insert(listPtr, insertNode);
				tempNode = NULL;
				
			} else if (dragMode && draggingNode != NULL) {
				draggingNode = NULL;
				prevMouseX = -1;
				prevMouseY = -1;
			}
		}
	}
	glFlush();
}

void mouseMotion(int xMouse, int yMouse) 
{
	if (tempNode != NULL && !dragMode) {
		int relativeY = winHeight - yMouse;
		if (tempNode->isRectangle) {
			tempNode->x2 = xMouse;
			tempNode->y2 = relativeY;
		} else {
			int deltaX = xMouse - tempNode->x1;
			int deltaY = relativeY - tempNode->y1;
			tempNode->radius = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
		}
	} else if (dragMode && draggingNode != NULL) {
		int movementX = xMouse - prevMouseX;
		int movementY = (winHeight - yMouse) - (winHeight - prevMouseY);
		
		draggingNode->x1 += movementX;
		draggingNode->y1 += movementY;
		if (draggingNode->isRectangle) {
			draggingNode->x2 += movementX;
			draggingNode->y2 += movementY;
		}

		prevMouseX = xMouse;
		prevMouseY = yMouse;

	}
	display();
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
/*  Reset viewport and projection parameters  */
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity( );
	gluOrtho2D(0.0, newWidth, 0.0, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
	display();
}

void mainMenu(GLint menuOption)
{
    switch(menuOption) {
        case 1: // New            
            glClear(GL_COLOR_BUFFER_BIT);
			glFlush();
			tempNode = NULL;
			listPtr->head = NULL;
			listPtr->tail = NULL;
			break;

        case 6: // Quit
            glutDestroyWindow(glutGetWindow());
			break;
   }
	glutPostRedisplay( );
}

int main(int argc, char **argv) {

	// Initalize menu variables
	GLint drawsubMenu;        
	GLint stylesubMenu;      
	GLint editsubMenu;           
	GLint filesubMenu;            
	GLint strokeColorsubMenu;           
	GLint strokeWidthsubMenu;
	GLint fillColorsubMenu;           

	// GLUT setup
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Ryan Kim");
	init();
	glutDisplayFunc(display);
	
	glutMouseFunc(mousePtPlot);
	glutMotionFunc(mouseMotion);

	// Menu's initializations
	drawsubMenu = glutCreateMenu(drawSubMenu);
	glutAddMenuEntry("Rectangle", 1);
	glutAddMenuEntry("Circle", 2);

	fillColorsubMenu = glutCreateMenu(fillColorSubMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	glutAddMenuEntry("White", 5);
	
	strokeColorsubMenu = glutCreateMenu(strokeColorSubMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	glutAddMenuEntry("White", 5);
	
	strokeWidthsubMenu = glutCreateMenu(strokeWidthSubMenu);
	glutAddMenuEntry("1", 1);
	glutAddMenuEntry("2", 2);
	glutAddMenuEntry("3", 3);
	glutAddMenuEntry("4", 4);
	glutAddMenuEntry("5", 5);
	
	stylesubMenu = glutCreateMenu(styleSubMenu);
	glutAddSubMenu("Fill Color", fillColorsubMenu);
	glutAddSubMenu("Stroke Color", strokeColorsubMenu);
	glutAddSubMenu("Stroke Width", strokeWidthsubMenu);
	
	editsubMenu = glutCreateMenu(editSubMenu);
	glutAddMenuEntry("Select", 1);
	glutAddMenuEntry("Delete", 2);
	glutAddMenuEntry("Move front", 3);
	glutAddMenuEntry("Move back", 4);
	glutAddMenuEntry("Move around", 5);
	filesubMenu = glutCreateMenu(fileSubMenu);
	glutAddMenuEntry("Save SVG", 1);
	glutAddMenuEntry("Open SVG", 2);
	glutAddMenuEntry("Export bitmap", 3);   
	glutCreateMenu(mainMenu);
	glutAddMenuEntry("New", 1);
	glutAddSubMenu("Draw", drawsubMenu);
	glutAddSubMenu("Style", stylesubMenu);
	glutAddSubMenu("Edit", editsubMenu); 
	glutAddSubMenu("File", filesubMenu);
	glutAddMenuEntry("Quit", 2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutReshapeFunc(reshapeFcn);
	glutMainLoop( );
}

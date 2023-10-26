# include <GL/glut.h>
# include <iostream>
# include <cmath>

#define MAX 100

#ifndef OBJECT_HPP
#define OBJECT_HPP

typedef struct node {
	int x1, y1, x2, y2;
	bool isRectangle;
	GLint radius;
	GLfloat red;
	GLfloat blue;
	GLfloat green;
	GLint strokeWidth;
	GLfloat strokeRed;
	GLfloat strokeBlue;
	GLfloat strokeGreen;
	node* prev;
	node* next;
}Node;

class DoubleLinkedList {
	public:
		Node* head;
		Node* tail;
		Node* selectedNode;
		bool drawSelection;
		DoubleLinkedList();
		void highlightNode();
		void midPoint(Node* node);
		void destroy();
		void drawShapes();
		void drawNode(Node* node);
};

extern DoubleLinkedList* listPtr;

#endif
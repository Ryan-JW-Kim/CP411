#include "object.hpp"
#include "edit.hpp"
#include <cmath>
#include <iostream>


// Constructor for DoubleLinkedList object taking in no parameters (init to empty list)
DoubleLinkedList::DoubleLinkedList(): head(NULL), tail(NULL) {}

void DoubleLinkedList::midPoint(Node* node) {
    GLint xc = node->x1;
    GLint yc = node->y1;
    GLint r = node->radius;
    GLint pk,xk,yk;
    pk=1-r;
    xk=0;
    yk=r;
    
    glVertex2i(xc+xk,yc+yk);
    glVertex2i(xc+yk,yc+xk);
    glVertex2i(xc-yk,yc+xk);
    glVertex2i(xc-xk,yc+yk);
    glVertex2i(xc-xk,yc-yk);
    glVertex2i(xc-yk,yc-xk);
    glVertex2i(xc+yk,yc-xk);
    glVertex2i(xc+xk,yc-yk);
    
    while(xk<=yk) {
        if(pk<0) {
            xk=xk+1;
            pk=pk+(2*xk)+1;
        } else {
            xk=xk+1;
            yk=yk-1;
            pk=pk+(2*xk)+1-(2*yk);
        }
        
        glVertex2i(xc+xk,yc+yk);
        glVertex2i(xc+yk,yc+xk);
        glVertex2i(xc-yk,yc+xk);
        glVertex2i(xc-xk,yc+yk);
        glVertex2i(xc-xk,yc-yk);
        glVertex2i(xc-yk,yc-xk);
        glVertex2i(xc+yk,yc-xk);        
        glVertex2i(xc+xk,yc-yk);

    }
}

void DoubleLinkedList::drawNode(Node* node) {
    int i;
    
    if (node->isRectangle) {
    
        glColor3f(node->red, node->green, node->blue);
        glBegin(GL_QUADS);
            glVertex2f(node->x1, node->y1);
            glVertex2f(node->x2, node->y1);
            glVertex2f(node->x2, node->y2);
            glVertex2f(node->x1, node->y2);
        glEnd();

        if (node-> strokeWidth > 0){
            glColor3f(node->strokeRed, node->strokeGreen, node->strokeBlue);
            glLineWidth(node->strokeWidth);
            glBegin(GL_POLYGON);        
                glVertex2f(node->x1, node->y1);
                glVertex2f(node->x2, node->y1);
                glVertex2f(node->x2, node->y2);
                glVertex2f(node->x1, node->y2);
            glEnd();
        }

    } else {
        glColor3f(node->red, node->green, node->blue);
        glBegin(GL_QUADS);
        DoubleLinkedList::midPoint(node);
        glEnd();

        if (node-> strokeWidth > 0){
            glColor3f(node->strokeRed, node->strokeGreen, node->strokeBlue);
            glLineWidth(node->strokeWidth*5);
            glBegin(GL_LINE_LOOP);
            DoubleLinkedList::midPoint(node);
            glEnd();
        }
    }
}

void DoubleLinkedList::highlightNode() {
    
    if (!drawSelection) {return;}

    Node* node = DoubleLinkedList::selectedNode;
    GLint selectWidth = 3;
    GLint selectRed = 0.7;
    GLint selectGreen = 0.9;
    GLint selectBlue = 0;
    
    if (node != NULL) {
        if (node->isRectangle) {
            glColor3f(selectRed, selectGreen, selectBlue);
            glLineWidth(selectWidth);
            glBegin(GL_LINE_LOOP);        
                glVertex2f(node->x1, node->y1);
                glVertex2f(node->x2, node->y1);
                glVertex2f(node->x2, node->y2);
                glVertex2f(node->x1, node->y2);
            glEnd();
        } else {
            int i;
            glColor3f(selectRed, selectGreen, selectBlue);
            glLineWidth(selectWidth);
            glBegin(GL_LINE_LOOP);        
            DoubleLinkedList::midPoint(node);
            glEnd();
            }
        glEnd();
        }

}

void DoubleLinkedList::drawShapes() {
    Node *current;
    current = head;

    int count = 1;
    // Draw from head to tail
    while (current != NULL) {
        DoubleLinkedList::drawNode(current);
        count++;
        current = current -> prev;
    }

    if (DoubleLinkedList::selectedNode != NULL) {
        DoubleLinkedList::highlightNode();
    }
}

void DoubleLinkedList::destroy() {
    
    Node* head = this->head;
    while (this->head != NULL) {
        std::cout << head->x1 << std::endl;
        remove(this, head);
    }
}


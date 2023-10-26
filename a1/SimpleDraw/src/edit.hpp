# include <GL/glut.h>
# include <iostream>
# include <cmath>
# include "object.hpp"

#ifndef EDIT_HPP
#define EDIT_HPP

Node* remove(DoubleLinkedList* list, Node* node);
void insert(DoubleLinkedList* list, Node* node);
void insertFront(DoubleLinkedList* list, Node* node);

#endif
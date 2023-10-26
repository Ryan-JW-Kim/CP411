#include "object.hpp"
#include "edit.hpp"

void insert(DoubleLinkedList* list, Node* node) {
    if (list->tail == NULL && list->head == NULL) { // Empty list
        list->head = node;
        list->tail  = node;
        list->head -> prev = NULL;
        list->tail -> next = NULL;
    } else {
        list->tail -> prev = node;
        node -> next = list->tail;
        node -> prev = NULL;
        list->tail = node;
    }
}

void insertFront(DoubleLinkedList* list, Node* node) {
    if (list->tail == NULL && list->head == NULL) { // Empty list
        list->head = node;
        list->tail  = node;
        list->head -> prev = NULL;
        list->tail -> next = NULL;
    } else {
        node -> prev = list->head;
        list->head -> next = node;
        list->head = node;
    }
}

Node* remove(DoubleLinkedList* list, Node* node) {

    if (node == list->head) {
        list->head = node->prev;
        list->head->next = NULL;
        node->prev = NULL;
    } else if (node == list->tail) {
        list->tail = node->next;
        node -> next = NULL;
        list->tail -> prev = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = NULL;
        node->next = NULL;
    }
    return node;
}

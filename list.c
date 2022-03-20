#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {

    List* lista;
    lista = (List*)malloc(sizeof(List));

    lista->head = NULL;
    lista->current = NULL;
    lista->tail = NULL;

     return lista;
}

void * firstList(List * list) {

    if (!list->head){
        return NULL;
    }
    list->current = list->head;

    return list->head->data;
}

void * nextList(List * list) {

    if (list->current != NULL){
        if (list->current->next != NULL){
            if (list->current->data != NULL){

                list->current = list->current->next;
                return list->current->data;
            }
        }
    }

    return NULL;
}

void * lastList(List * list) {

    if (!list->tail){
        return NULL;
    }
    list->current = list->tail;

    return list->tail->data;

}

void * prevList(List * list) {

    if (list->current != NULL){
        if (list->current->prev != NULL){
            if (list->current->data != NULL){

                list->current = list->current->prev;
                return list->current->data;
            }
        }
    }
    return NULL;
}

void pushFront(List * list, void * data) {

    Node* a = createNode(data);

    if (list->head != NULL){
        
        list->current = list->head;
        list->head = a;
        list->head->next = list->current;
        list->current->prev = list->head;
    }

    if ( list->head == NULL) {

        list->head = a;
        list->tail = list->head;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {

    Node* b = createNode(data);

    if (list->current->next != NULL ){

        list->current->next->prev = b;
        list->current->next = b->next;
    }

    list->current->next = b;
    b->prev = list->current;

    if (b->next == NULL) list->tail = b;
    
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {

    if ( list->current != NULL ){
        list->current->prev->next = list->current->next;
    }
    else list->head = list->current->next;

    if (list->current->next != NULL){
        list->current->next->prev = list->current->prev;
    }


    return list->current->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
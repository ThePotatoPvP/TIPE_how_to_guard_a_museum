#include <stdarg.h>
#include "structures.h"


Node* new_Node(void* element){
    Node* node = malloc(sizeof(Node));
    node->value = element;
    return node;
}

LinkedList* new_LinkedList(){
    return malloc(sizeof(LinkedList));
}

void apply_indexed_LinkedList(LinkedList* list, void (*to_apply)(void* element, int idx)){
    int i = 0;
    for(Node* element = list->head; element != NULL || element != list->head; element = element->next){
        to_apply(element->value, i++);
    }
}

void apply_LinkedList(LinkedList* list, void (*to_apply)(void* element)){
    for(Node* element = list->head; element != NULL || element != list->head; element = element->next){
        to_apply(element->value);
    }
}

bool add_LinkedList(LinkedList* list, void* element, int idx){

    if(idx < 0 || idx > list->size)
        return false;

    if(idx == 0){
        Node* all;
        Node* new_element = new_Node(element);;

        if(is_empty_LinkedList(list)){
            all = NULL;
            list->tail = new_element;
        } else {
            all = list->head->next;
        }

        list->head = new_element;
        list->head->next = all;
        list->size++;
        return true;
    }

    if (idx == list->size){
        list->tail->next = new_Node(element);
        list->tail = list->tail->next;
        list->size++;
        return true;
    }

    Node* tmp = list->head;

    // never NULL as idx < list->size
    while(--idx){
        tmp = tmp->next;
    }

    Node* after = tmp->next;
    tmp->next = new_Node(element);
    tmp->next->next = after;
    list->size++;
    return true;
}

Node* remove_Node_LinkedList(LinkedList* list, int idx){
    Node* tmp = list->head;

    if(idx < 0 || idx > list->size - 1){
        return NULL;
    }

    if(idx == 0){
        Node* to_return = list->head;
        list->head = list->head->next;
        return to_return;
    }

    while(--idx){
        tmp = tmp->next;
    }
    Node* to_return = tmp->next;
    tmp->next = tmp->next->next;
    return to_return;
}

Node* pop_Node_LinkedList(LinkedList* list){
    return remove_Node_LinkedList(list, list->size - 1);
}

void* remove_LinkedList(LinkedList* list, int idx){
    Node* node = remove_Node_LinkedList(list, idx);
    void* data = node->value;
    free(node);
    return data;
}

void* pop_LinkedList(LinkedList* list){
    return remove_LinkedList(list, list->size - 1);
}

void concat_LinkedList(LinkedList* dst, LinkedList to_add){
    dst->tail->next = to_add.head;
    dst->tail = to_add.tail;
    dst->size += to_add.size;
}

void print_LinkedList(LinkedList* list, void (*print_element)(void* element)){
    printf("[");

    if(is_empty_LinkedList(list)){
        printf("]");
        return;
    }

    for(Node* element = list->head;; element = element->next){
        if(element->next == NULL || element->next == list->head){
            print_element(element->value);
            printf("]");
            return;
        } else{
            print_element(element->value);
            printf(", ");
        }
    }
}

bool is_empty_LinkedList(LinkedList* list){
    return list->size == 0;
}
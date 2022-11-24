#include <stdlib.h>
#include "structures.h"

Node* new_Node(void* element){
    Node* node = malloc(sizeof(Node));
    node->value = element;
    return node;
}

void free_Node(Node* node){
    Node* current = node;
    Node* after;
    while(current != NULL || current != node){
        after = current->next;
        free(current->value);
        free(current);
        current = after;
    }
}

void invalid_index_Error_LinkedList(LinkedList* list, int i){
    fprintf(stderr, "Error: Index out of range for i=%d and length=%d", i, list->size);
    exit(1500);
}

LinkedList* new_LinkedList(){
    return malloc(sizeof(LinkedList));
}

void free_LinkedList(LinkedList* list){
    free_Node(list->head);

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

void append_LinkedList(LinkedList* list, void* element){
    add_LinkedList(list, element, list->size);
}

void add_LinkedList(LinkedList* list, void* element, int idx){

    if(idx < 0 || idx > list->size)
        invalid_index_Error_LinkedList(list, idx);

    if(idx == 0){
        Node* new_element = new_Node(element);;

        if(is_empty_LinkedList(list)){
            list->tail = new_element;
        }

        new_element->next = list->head;
        list->head = new_element;
        list->size++;
        return;
    }

    if (idx == list->size){
        list->tail->next = new_Node(element);
        list->tail = list->tail->next;
        list->size++;
        return;
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
}

Node* remove_Node_LinkedList(LinkedList* list, int idx){
    Node* tmp = list->head;

    if(!is_valid_idx_LinkedList(list, idx)){
        invalid_index_Error_LinkedList(list, idx);
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

bool is_valid_idx_LinkedList(LinkedList* list, int i){
    return i >= 0 && i < list->size;
}

Node* get_Node_LinkedList(LinkedList* list, int idx){

    if(!is_valid_idx_LinkedList(list, idx))
        invalid_index_Error_LinkedList(list, idx);

    int i =0;
    for(Node* element = list->head; element != NULL || element->next != list->head; element = element->next){
        if(idx == i++)
            return element;
    }
}

void* get_LinkedList(LinkedList* list, int idx){
    return get_Node_LinkedList(list, idx)->value;
}

Node* sorted_merge__(Node* a, Node* b, int (*compare)(void* element1, void* element2)){
    Node* result = NULL;
    if(a == NULL)
        return b;
    if(b == NULL)
        return a;

    if(compare(a->value, b->value) == -1){
        result = a;
        result->next = sorted_merge__(a->next, b, compare);
    } else{
        result = b;
        result->next = sorted_merge__(a, b->next, compare);
    }
    return result;
}

Node* get_mid__(Node* node){
    if(node == NULL)
        return node;

    Node* slow = node;
    Node* fast = node;

    while (fast->next != NULL && fast->next->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* merge_sort__(Node* node, int (*compare)(void* element1, void* element2)){
    if(node == NULL || node->next == NULL)
        return node;

    Node* mid = get_mid__(node);
    Node* midNext = mid->next;

    mid->next = NULL;
    Node* left = merge_sort__(node, compare);
    Node* right = merge_sort__(midNext, compare);

    Node* sorted = sorted_merge__(left, right, compare);

    return sorted;
}

void sort_LinkedList(LinkedList* list, int (*compare)(void* element1, void* element2)){
    list->head = merge_sort__(list->head, compare);
}

void* to_array_LinkedList(LinkedList* list){
    void** arr = malloc(sizeof (void*) * list->size);
    int i = 0;
    for(Node* node = list->head; node != NULL; node = node->next){
        arr[i++] = node->value;
    }
    return arr;
}
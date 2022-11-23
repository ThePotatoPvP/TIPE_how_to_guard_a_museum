#ifndef STRUCTURES
#define STRUCTURES

#include <malloc.h>
#include <stdbool.h>

typedef struct Node{
    void* value;
    struct Node* next;
} Node;

typedef struct LinkedList{
    Node* head;
    Node* tail;
    int size;
} LinkedList;

Node* new_Node(void*);

void free_Node(Node* node);

LinkedList* new_LinkedList();

void free_LinkedList(LinkedList* list);

/**
 * Apply the function to_apply to each element of the list.
 * @param list a Linked list
 * @param to_apply a function
 */
void apply_LinkedList(LinkedList* list, void (*to_apply)(void* element));

/**
 * Same as apply_LinkedList but with an indexed function.
 */
void apply_indexed_LinkedList(LinkedList* list, void (*to_apply_idx)(void* element, int idx));

/**
 * Add an element to the linked list at the given index.<p>
 * <b>idx € [0;list_size]</b>
 *
 * @param list a linked list
 * @param element the element to add
 * @param idx an index
 */
void add_LinkedList(LinkedList* list, void* element, int idx);

/**
 * Append an element at the end of the list.
 *
 * @param list the modified list
 * @param element an element
 */
void append_LinkedList(LinkedList* list, void* element){
    add_LinkedList(list, element, list->size);
}

/**
 * Prints the linked list using the given print function.
 *
 * @param list a linked list
 * @param the function that prints an element
 */
void print_LinkedList(LinkedList* list, void (*print_element)(void* element));

/**
 * Returns true if the list is empty and false otherwise.
 *
 * @param list a linked list;
 * @return true if the list is empty
 */
bool is_empty_LinkedList(LinkedList* list);

/**
 * Deletes a node from the linked list and returns the deleted node.<p>
 *
 * @param list a linked list
 * @param idx the index
 * @return the deleted Node
 */
Node* remove_Node_LinkedList(LinkedList* list, int idx);

/**
 * Remove the last node of the linked list and returns it.
 * See, remove_Node_LinkedList.
 *
 * @param list the modified linked list
 * @return the deleted Node
 */
Node* pop_Node_LinkedList(LinkedList* list);

/**
 * Deletes a node from the linked list, free it and returns the void* element.
 *
 * @param list a linked list
 * @param idx the index
 * @return the deleted element
 */
void* remove_LinkedList(LinkedList* list, int idx);

/**
 * Concatenate two list together.
 * The appended list will be dst.
 *
 * @param dst the appended list
 * @param to_add the list of elements to add to dst
 */
void concat_LinkedList(LinkedList* dst, LinkedList to_add);

/**
 * Remove the last element of the list.
 *
 * @param list the modified list
 */
void* pop_LinkedList(LinkedList* list);

/**
 * Sort the linked list in place using the given compare function.
 * The compare function works as follow:
 * (a,b) -> -1 if a < b
 *       ->  1 if a > b
 *       ->  0 if a = b
 * @param list a linked list
 * @param compare the compare function
 */
void sort_LinkedList(LinkedList* list, int (*compare)(void* element1, void* element2));

/**
 * Returns true if the given idx is a valid one.
 */
bool is_valid_idx_LinkedList(LinkedList* list, int i);

/**
 * Returns the Node at given index.
 *
 * @param list a linked list
 * @param idx an index
 * @return the wanted Node
 */
Node* get_Node_LinkedList(LinkedList* list, int idx);

/**
 * Returns the element at the given index.
 * If the idx is invalid returns NULL.
 *
 * @param list
 * @param idx
 * @return the 'idx-th' element of the list
 */
void* get_LinkedList(LinkedList* list, int idx);

/**
 * Throws an error.
 */
void invalid_index_Error_LinkedList(LinkedList* list, int i);

void* to_array_LinkedList(LinkedList* list);

#endif
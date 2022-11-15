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

LinkedList* new_LinkedList();

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
 * @return true if the element was added and false otherwise
 */
bool add_LinkedList(LinkedList* list, void* element, int idx);

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
 * <i>This should be used to ensure the deletion of an element as NULL might be
 * a list entry but not a Node.
 * </i>
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
 * Use with care as the deletion of an element is not ensured,
 * see remove_Node_LinkedList.
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

#endif
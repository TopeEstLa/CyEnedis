#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * This structure represent a node of a list containing the value of the node and a pointer to the next node.
 * @param data the value of the node.
 * @param next a pointer to the next node.
 */
typedef struct list_node {
    void* data;
    struct list_node* next;
} ListNode;

/**
 * This structure represent a list containing the head of the list and the size of the list.
 * @param head a pointer to the first node of the list.
 * @param size the size of the list.
 */
typedef struct listTest {
    ListNode* head;
    int size;
} List;

/**
 * Create a new list.
 * @return the new list.
 */
List* createList();

/**
 * Free the list.
 * @param list the list to free.
 */
void freeList(List* list);

/**
 * Append a new node to the end of the list.
 * @param list the list to append to.
 * @param data the value of the new node.
 * @return index of the new node or -1 if the node was not added.
 */
int append(List* list, void* data);

/**
 * Add a node to the beginning of the list.
 * @param list the list to add to
 * @param data data of the node
 * @return true if the node was added, false otherwise.
 */
bool prepend(List* list, void* data);

/**
 * Add a node to the list at a specific index.
 * @param list the list to add to
 * @param data data of the node
 * @param index index to add the node
 * @return true if the node was added, false otherwise.
 */
bool addAt(List* list, void* data, int index);

/**
 * Remove the last node of the list.
 * @param list the list to remove from.
 * @return true if the node was removed, false otherwise.
 */
bool removeLast(List* list);

/**
 * Remove the first node of the list.
 * @param list the list to remove from.
 * @return true if the node was removed, false otherwise.
 */
bool removeFirst(List* list);

/**
 * Remove the node at a specific index.
 * @param list the list to remove from.
 * @param index the index of the node to remove.
 * @return true if the node was removed, false otherwise.
 */
bool removeAt(List* list, int index);

/**
 * Get the value of the last node of the list.
 * @param list the list.
 * @param index the index of the node to get.
 * @return the value contained in the node.
 */
void* get(List* list, int index);

/**
 * Reverse the list.
 * @param list the list to reverse.
 * @return a new list that is the reverse of the original list.
 */
List* reverseList(List* list);


/**
 * Print the list.
 * @param list the list to print.
 */
void printList(List* list);


#endif //LIST_H

/**
 * Singly linked list implementation.
 *
 * @author: Koshin Mohamed
 * @class: CS 5008
 * @term: Fall 2025
 */

#include <stdlib.h>
#include <stdbool.h>


#include "movie.h"
#include "linked_list.h"


/** 
 * Creates a new linked list node.
*/
node * __ll__new_node(Movie *movie) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->movie = movie;
    new_node->next = NULL;
    return new_node;
}

/**
 * Creates a new linked list.
 * 
 * @return a pointer to the new linked list
 */
LinkedList *new_linked_list() {
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/**
 * Frees the memory associated with a linked list.
 * 
 * Frees just the linked list and nodes, the movies
 * stored are not freed. 
 * @param list the linked list to free
 */
void free_linked_list(LinkedList *list) {
    node *curr = list->head;
    node *next;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

/**
 * Frees the memory, including memory allocated
 * to movies stored in the link list. 
 * 
 * @param list the linked list to free
*/
void clear_and_free_linked_list(LinkedList *list) {
    node *curr = list->head;
    node *next;
    while (curr != NULL) {
        next = curr->next;
        free_movie(curr->movie);
        free(curr);
        curr = next;
    }
    free(list);
}

/**
 * Adds a movie to the front of a linked list.
 * 
 * Don't forget to update the tail pointer if the list is empty,
 * as when there is a single node, head and tail should both point
 * towards it.
 * 
 * @param list the linked list to add to
 * @param movie the movie to add
 */
void ll_add_front(LinkedList *list, Movie *movie) {
     if (list == NULL || movie == NULL) return;

    // make a new node
    node *new_node = __ll__new_node(movie);

    // point the new node to the current head
    new_node->next = list->head;

    // update head to the new node
    list->head = new_node;

    // if list was empty, tail also points here
    if (list->tail == NULL){
        list->tail = new_node;
    }

    // update the size
    list->size++;
}

/**
 * Adds a movie to the back of a linked list.
 *
 * Don't forget to update the head pointer if the list is empty,
 * as when there is a single node, head and tail should both point
 * towards it.
 *
 * @param list the linked list to add to
 * @param movie the movie to add
 */
void ll_add_back(LinkedList *list, Movie *movie) {
    if (list == NULL || movie == NULL) return;

    // make a new movie node
    node *new_node = __ll__new_node(movie);

    // if list is empty, then heads and tails are the same
    if (list->head == NULL){
        list->head = new_node;
        list->tail = new_node;
    } else{
        // connect new node after tail
        list->tail->next = new_node;
        list->tail = new_node;
    }
    
    list->size++;   
}


/**
 * Inserts a movie into a linked list at a given index.
 * 
 * if n == 0, safe to call ll_add_front, if n == list->size, safe to call ll_add_back
 * 
 * if n is out of bounds, do nothing (return early)
 * 
 * @param list the linked list to insert into
 * @param movie the movie to insert
 * @param n the index to insert at
 */
void ll_insert(LinkedList *list, Movie *movie, int n) {
  if (list == NULL || movie == NULL) return;
    if (n < 0 || n > list->size) return;

    node *new_node = __ll__new_node(movie);

    // inserting at the front
    if (n == 0){
        new_node->next = list->head;
        list->head = new_node;
        if (list->tail == NULL) {
            list->tail = new_node;
        }
    }
    // inserting at the back
    else if (n == list->size){
        if (list->tail == NULL) {
            list->head = new_node;
            list->tail = new_node;
        } else{
            list->tail->next = new_node;
            list->tail = new_node;
        }
    }
    // inserting in the middle
    else{
        node *prev = list->head;
        for (int i = 0; i < n - 1; i++) {
            prev = prev->next;
        }
        new_node->next = prev->next;
        prev->next = new_node;
    }

    list->size++;

}


/**
 * Removes the first movie from a linked list.
 * 
 * Don't forget if there is only one item in the list, and it is removed,
 * to update the tail pointer.
 * 
 * @param list the linked list to remove from
 * @return the movie that was removed
 */
Movie * ll_remove_front(LinkedList *list) {
    Movie *movie = NULL;
     if (list == NULL || list->head == NULL){
        return NULL;
    }
   // keep track of the first node so we can free it
    node *temp = list->head;
    movie = temp->movie;

    // move head to the next node
    list->head = temp->next;

    // if list becomes empty, tail should also be NULL
    if (list->head == NULL){
        list->tail = NULL;
    }
    free(temp);
    list->size--;
    return movie;
}

/**
 * Removes the last movie from a linked list.
 * 
 * Don't forget if there is only one item in the list, and it is removed,
 * to update the head pointer.
 * 
 * @param list the linked list to remove from
 * @return the movie that was removed
 */
Movie * ll_remove_back(LinkedList *list) {
    Movie* movie = NULL;
    if (list == NULL || list->head == NULL){
        return NULL;
    }
    // if there’s only one node in the list
    if(list->head == list->tail){
        movie = list->head->movie;
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    } else{
        // loop until the node right before the tail
        node *curr = list->head;
        while (curr->next != list->tail) {
            curr = curr->next;
        }
        // store the movie from the tail before freeing it
        movie = list->tail->movie;
        free(list->tail);
        // update the tail to the previous node
        curr->next = NULL;
        list->tail = curr;
    }
    list->size--;
    return movie;
}

/**
 * Removes a movie from a linked list at a given index.
 * 
 * if n == 0, safe to call ll_remove_front, if n == list->size - 1, safe to call ll_remove_back
 * 
 * if n is out of bounds, return NULL
 * 
 * @param list the linked list to remove from
 * @param n the index to remove at
 * @return the movie that was removed
 */
Movie * ll_remove(LinkedList *list, int n) {
    Movie * movie = NULL;
 if (list == NULL || n < 0 || n >= list->size){
        return NULL;
    }
    // remove from front
    if (n == 0){
        return ll_remove_front(list);
    }
    // remove from back
    if (n == list->size - 1){
        return ll_remove_back(list);
    }
    node *curr = list->head;
    node *prev = NULL;

    // move until the node before the one we’re deleting
    for (int i = 0; i < n; i++){
        prev = curr;
        curr = curr->next;
    }
    // save the movie, unlink and free the node
    movie = curr->movie;
    prev->next = curr->next;
    free(curr);
    list->size--;    
    return movie;
}

/**
 * Gets a movie from a linked list at a given index.
 * 
 * if n is out of bounds, return NULL
 * 
 * @param list the linked list to get from
 * @param n the index to get at
 * @return the movie at the given index
 */
Movie* ll_get(LinkedList *list, int n) {
    node *curr = list->head;
    if (n < 0 || n >= list->size) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        curr = curr->next;
    }
    return curr->movie;
}

/**
 * Checks if a linked list contains a given movie.
 * 
 * Rare if a linked list contains a movie more than once, but
 * if so, just immediately return true.
 * 
 * @param list the linked list to check
 * @param movie the movie to check for
 * @return true if the linked list contains the movie, false otherwise
 */
bool ll_contains(LinkedList *list, Movie *movie) {
    node *curr = list->head;
    while (curr != NULL) {
        if (curr->movie == movie) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

/**
 * Checks if a linked list is empty.
 * 
 * @param list the linked list to check
 * @return true if the linked list is empty, false otherwise
 */
bool ll_is_empty(LinkedList *list) {
    return list->size == 0;
}

/**
 * Converts a linked list to a string representation.
 * 
 * @param list the linked list to convert
 * @return a string representation of the linked list
 */
char* ll_to_str(LinkedList *list) {
    
char *str = (char *)malloc(sizeof(char) * ((MAX_MOVIE_STR_LEN + 5) * list->size + 3));
    if (list->size == 0) {
        strcpy(str, "[]");
        return str; // early exit
    }
    // implied else
    strcpy(str, "[");
    node *curr = list->head;
    while (curr != list->tail) {
        char *movie_str = movie_to_str(curr->movie);
        strcat(str, movie_str);
        strcat(str, ", ");
        free(movie_str);
        curr = curr->next;
    }
    // now add the tail
    char *movie_str = movie_to_str(curr->movie);
    strcat(str, movie_str);
    free(movie_str);
    strcat(str, "]");

    return str;
}


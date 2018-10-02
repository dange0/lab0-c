/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
   Create empty queue.
   Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == 0)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Empty queue handling */
    if (q == NULL)
        return;

    list_ele_t *ptr, *del;
    ptr = q->head;

    /* Free list & value */
    while (ptr != NULL) {
        del = ptr;
        ptr = ptr->next;
        free(del->value);
        free(del);
    }

    /* Free queue structure */
    free(q);
}

/*
   Attempt to insert element at head of queue.
   Return true if successful.
   Return false if q is NULL or could not allocate space.
   Argument s points to the string to be stored.
   The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* Empty queue handling */
    if (q == NULL)
        return false;


    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;

    /* strings copy with malloc */
    newh->value = malloc(strlen(s) + 1);
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);

    /* update the head ptr */
    newh->next = q->head;
    q->head = newh;

    /* The first */
    if (newh->next == NULL) {
        q->tail = newh;
    }

    /* counter for q_size */
    q->size++;
    return true;
}
/*
   Attempt to insert element at tail of queue.
   Return true if successful.
   Return false if q is NULL or could not allocate space.
   Argument s points to the string to be stored.
   The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* Empty queue handling */
    if (q == NULL)
        return false;

    /* malloc and initial */
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
        return false;
    newt->next = NULL;

    /* strings copy with malloc */
    newt->value = malloc(strlen(s) + 1);
    if (newt->value == NULL) {
        free(newt);
        return false;
    }
    strcpy(newt->value, s);

    /* update the tail */
    if (q->tail != NULL)
        q->tail->next = newt;
    q->tail = newt;

    /* The first */
    if (q->head == NULL)
        q->head = newt;
    /* counter for q_size */
    q->size++;
    return true;
}

/*
   Attempt to remove element from head of queue.
   Return true if successful.
   Return false if queue is NULL or empty.
   If sp is non-NULL and an element is removed, copy the removed string to *sp
   (up to a maximum of bufsize-1 characters, plus a null terminator.)
   The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* Empty queue handling */
    if (q == NULL)
        return false;

    /*Return false if queue is NULL or empty.*/
    if (q->head == NULL)
        return false;

    /* move the head */
    list_ele_t *del;
    del = q->head;
    q->head = q->head->next;

    /*  If sp is non-NULL and an element is removed, copy the removed string to
     *sp
     (up to a maximum of bufsize-1 characters, plus a null terminator.)*/
    if (sp != NULL) {
        memset(sp, '\0', bufsize);
        strncpy(sp, del->value, bufsize - 1);
    }


    /* free */
    free(del->value);
    free(del);

    /* counter for q_size */
    q->size--;
    return true;
}

/*
   Return number of elements in queue.
   Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Empty queue handling */
    if (q == NULL)
        return 0;

    return q->size;
}
/*
   Reverse elements in queue
   No effect if q is NULL or empty
   This function should not allocate or free any list elements
   (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
   It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /*No effect if q is NULL or empty*/
    if (q == NULL)
        return;
    if (q->size <= 1)
        return;


    list_ele_t *ptr_pre, *ptr_now, *ptr_next;

    /* move to the first windows */
    ptr_pre = q->head;
    ptr_now = ptr_pre->next;
    ptr_next = ptr_now->next;

    /* reverse the pointer next and shift the windows */
    while (ptr_next != NULL) {
        ptr_now->next = ptr_pre;
        ptr_pre = ptr_now;
        ptr_now = ptr_next;
        ptr_next = ptr_next->next;
    }

    /* The last */
    ptr_now->next = ptr_pre;

    /* modify the head and tail */
    q->head->next = NULL;
    q->tail = q->head;
    q->head = ptr_now;
}

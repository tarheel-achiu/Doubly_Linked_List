/* Doubly Linked List implementation */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct dllist
{
    int number;
    struct dllist* prev;
    struct dllist* next;
}
        dllnode;

/*
The operations needed to work with linked lists
    1. Create a linked list when it doesn't already exist.
    2. Search though a list to find an element.
    3. Insert a new node into the list.
    4. Delete a single element from a linked list.
    5. Delete an entire linked list.
*/

// initialize functions
dllnode *create(int value);
bool find(dllnode *head, int value);
dllnode *insert(dllnode *head, int value);
void delete(dllnode *target);
void destroy(dllnode* head);

dllnode *head_node1; // global variable - pointer to head node.

int main(void)
{
    // create the head which is just a pointer to a linked list that does not yet exist
    head_node1 = NULL;

    // create a dll
    head_node1 = create(2);

    // insert elements into the dll
    head_node1 = insert(head_node1, 1);
    head_node1 = insert(head_node1, 3);
    head_node1 = insert(head_node1, 5);
    head_node1 = insert(head_node1, 7);

    // use linear search function
    bool isFound = find(head_node1, 7);
    printf("%s", isFound ? "true" : "false");
}

// defining function for creating a doubly-linked list
dllnode *create(int value)
{
    // dynamically allocate space for a new dllnode
    dllnode *newNode = malloc(sizeof(dllnode));
    // check to make sure we didn't run out of memory
    if (newNode == NULL)
    {
        fprintf(stderr, "out of memory\n");
        return NULL;
    }
    // initialize the node's value field
    newNode->number = value;
    // initialize the node's prev field
    newNode->prev = NULL;
    // initialize the node's next field
    newNode->next = NULL;
    // return a pointer to the newly created dllnode
    return newNode;
}

// defining a function to search though a linked list to find an element
bool find(dllnode *head, int value)
{
    // create a traversal pointer pointing to the list's head
    dllnode *trav_ptr = head;

    // execute until you reach the end of the list where trav_ptr == NULL
    while (trav_ptr->next != NULL)
    {
        if (trav_ptr->number == value)
        {
            return true;
        }
            // if not, set the tranversal pointer to the next pointer in the list and go back to prev step
        else
        {
            trav_ptr = trav_ptr->next;
        }
    }
    // if you've reached the end of list, report failure
    return false;
}

// defining a function to insert a node into the linked list
dllnode *insert(dllnode *head, int value)
{
    // dynamically allocate space for a new dllnode
    dllnode *newNode = malloc(sizeof(dllnode));
    // check to make sure we didn't run out of memory
    if (newNode == NULL)
    {
        fprintf(stderr, "out of memory\n");
        return NULL;
    }
    // populate and insert the node at the beginning of the linked list
    newNode->number = value;
    newNode->next = head;
    newNode->prev = NULL;
    // fix the prev pointer of the old head of the linked list
    head->prev = newNode;
    // return a pointer to the new head of the linked list
    head = newNode;
    return head;
}

// deleting a node from a linked list
void delete(dllnode *target)
{
    // three scenarios, deleting head, middle, or last element

    // if first element
    if (target->prev == NULL)
    {
        // fix the prev pointer of the next element
        target->next->prev = NULL;
        // set head to point to new first element
        head_node1 = target->next;
        // free target
        free(target);
    }
        // if last element
    else if (target->next == NULL)
    {
        // fix the next pointer of the previous element
        target->prev->next = NULL;
        // free target
        free(target);
    }
        // if middle element
    else
    {
        // fix the pointers of the surrounding nodes to "skip over" target
        target->prev->next = target->next;
        target->next->prev = target->prev;
        // free target
        free(target);
    }
}

// delete an entire linked list
void destroy(dllnode* head)
{
    // if you have reached a null pointer, stop
    while (head != NULL)
    {
        // delete the rest of the list
        destroy(head->next);
    }
    // free the current node
    free(head);
}
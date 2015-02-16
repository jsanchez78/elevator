/*
 * Mugdha Deepak Gawde
 * Course Name  : Operating Systems
 * Lab Number   : 5
 * Lab		: Elevator Simulation
 * ABOUT:
 *	Linked list related function declaration is in this file 
 */

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

/*
 *  Function to add person node in a global listto the person doubly linked list
 *  gv 		: global variables pointer
 *  id_no 	: id_no to be assigned to each person
 *  new_node	: node to be added in the linked list
 */
void add_person(globalVariable *gv, int id_no, struct node *new_node);

/*
 *  General function to add node to the given doubly linked list
 *  start	: start of the linked list
 *  new_node	: node to be added in the linked list starting with start
 *  Return the starting node of the list
 */
struct node * add_node(struct node *new_node, struct node *start);

/*
 *  General function to delete node from the given doubly linked list
 *  start	: start of the linked list
 *  del		: node to be deleted from linked list starting with start
 *  Return the starting node of the list
 */
struct node * del_node(struct node *del, struct node *start);

/*
 * This function is used to pick up the person from the global list and add to
 * the temporary list
 * ev 		: elevator pointer of the specific elevator
 * start_node 	: starting of the temporary list
 *  Return the starting node of the list
 */
struct node *pickup_person(struct elevator *ev, struct node *start_node, int
	get_gv);
	
/*
 * This function is used to drop the person from the temporary list and free the
 * node
 * ev 		: elevator pointer of the specific elevator
 * start_node 	: starting of the temporary list
 *  Return the starting node of the list
 */
struct node *drop_person(struct elevator *ev, struct node *start_node);

/*
 * Prints the specified list and print the specific elevator Id, used for the
 * testing purpose
 * name 	: name of the list
 * id		: id of the elevator
 * list		: start of the list
 */
void print_list(char *name, int id, struct node *list);

/*
 * Print the elevator arrived message 
 * ev 		: Pointer of the elevator
 */
void print_arrives(struct elevator *ev);

/*
 * Frees the doubly linked list
 * start 	: starting address of the list
 */
void free_memory(struct node *start);
#endif

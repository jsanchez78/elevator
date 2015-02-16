/*
 * Mugdha Deepak Gawde
 * Course Name  : Operating Systems
 * Lab Number   : 5
 * Lab          : Elevator Simulation
 * ABOUT:
 * 	Function implementation for linked list to add, delete nodes, adding nodes
 * 	in global list and temporary list etc,
 */

#include <stdlib.h>
#include <sys/timeb.h>
#include <stdio.h>
#include "personT.h"
#include "linkedList.h"
#include "elevator.h"
#include "findT.h"

/*
 * Function to add person node in a global listto the person doubly linked list
 * gv          : global variables pointer
 * id_no       : id_no to be assigned to each person
 * new_node    : node to be added in the linked list
 */ 
void add_person(globalVariable *gv, int id_no, struct node *new_node)
{
        struct node *temp;

        new_node->per.id = id_no;
	/* Check whether the random numbers assigned to from and to floor 
	 * are different or not
	 */
        do
        {
                new_node->per.from_floor = rand()%(gv->num_of_floors)+1;
                new_node->per.to_floor = rand()%(gv->num_of_floors)+1;
        }while(new_node->per.to_floor == new_node->per.from_floor);

	/*
	 * Assign direction according to the to and from floors initialisation
	 */
        if(new_node->per.to_floor > new_node->per.from_floor)
		new_node->per.direction = UPWARD_DIR;
	else
		new_node->per.direction = DOWNWARD_DIR;

        new_node->next = NULL;
        new_node->prev = NULL;

        gv->num_of_people_started++;
	
	/* add the initialised node in the list */
	if(gv->ppl_start == NULL)
		gv->ppl_start = new_node;
        else
		gv->ppl_start = add_node(new_node, gv->ppl_start);
}


/*
 *  General function to add node to the given doubly linked list
 *  start       : start of the linked list
 *  new_node    : node to be added in the linked list starting with start
 *  Return the starting node of the list
 */

struct node * add_node(struct node *new_node, struct node *start)
{
	int i=0;
	struct node *temp  = NULL;
	if(start == NULL)
                start = new_node;
        else
        {
                temp= start;
                while(temp->next!=NULL)
		{
                        temp = temp->next;
			i++;
		}
                temp->next = new_node;
                new_node->prev = temp;
        }
	return(start);
}

/*
 *  General function to delete node from the given doubly linked list
 *  start       : start of the linked list
 *  del         : node to be deleted from linked list starting with start
 *  Return the starting node of the list
 */

struct node * del_node(struct node *del, struct node *start)
{
	struct node *temp = del;
	if(temp->prev !=NULL)
	{
		temp = temp->prev;
		temp->next = del->next;
	}
	if(temp->next != NULL)
	{
		temp = temp->next;
		temp->prev = del->prev;
	}
	if(del == start)
		start = start->next;

	del->next = NULL;
	del->prev = NULL;
	
	return(start);
}

/*
 * If anyone wants to go  in the direction that the elevator is going
 * add them to the temorary list
 * the temporary list
 * ev           : elevator pointer of the specific elevator
 * start_node   : starting of the temporary list
 *  Return the starting node of the list
 */
struct node *pickup_person(struct elevator *ev, struct node *start_node, int get_gv)
{
        struct node *ret=NULL, *del_nod=NULL;
        struct node *temp = ev->gv->ppl_start;
	int i=0;
	
	if(start_node == NULL)
		ev->direction = -1;
	
	/*
	 *Loop to decide the direction of the elevator
	 */	
	temp = start_node;
        while(temp!=NULL)
        {
                if(temp->per.from_floor == ev->current_floor &&
                        ev->current_floor == ev->to)
                {
                        ev->direction = temp->per.direction;
                        ev->to = temp->per.to_floor;
                        i++;
                        break;
                }
                temp = temp->next;
        }

	/*
	 * Check the global linked list if anyone is waiting 
	 */
	temp = ev->gv->ppl_start;
	while(temp!=NULL && get_gv==1)
	{
		if(temp->per.from_floor == ev->current_floor)
		{
			if(ev->direction == -1)
				ev->direction = temp->per.direction;
			ret = temp;
			temp = temp->next;
			if(ret->per.direction == ev->direction)
			{
			if((ev->direction == UPWARD_DIR &&
			   ev->to >= ret->per.to_floor &&
			   ret->per.direction == UPWARD_DIR)||
			   (ev->direction == DOWNWARD_DIR &&
			   ev->to <= ret->per.to_floor &&
			   ret->per.direction == DOWNWARD_DIR) ||
			   ev->to == -1) 
				  
			{
				// delete node from global list
		 		ev->gv->ppl_start = del_node(ret, ev->gv->ppl_start);

				//add deleted node in the temp list
				start_node = add_node(ret, start_node); 
	
				ev->num_person_started++;
				if(ev->to==-1)
					ev->to = ret->per.to_floor;
				i++;
			}
			}
		}
		else
			temp=temp->next;
	}

	/*
	 * If noone is on floor serve the first person in the global list
	 */
	if(start_node==NULL && get_gv==1)
	{
		del_nod = ev->gv->ppl_start;
		ev->gv->ppl_start = del_node(del_nod,ev->gv->ppl_start);
		start_node = add_node(del_nod, start_node);
		if(del_nod->per.from_floor != ev->current_floor)
			ev->to = del_nod->per.from_floor;
		else
			ev->to = del_nod->per.to_floor;

		if(ev->to > ev->current_floor)
		ev->direction = UPWARD_DIR;
		else
		ev->direction = DOWNWARD_DIR;
					
		if(ev->arrives_at != ev->current_floor)
		{
			ev->arrives_at = ev->current_floor;
			print_arrives(ev);
		}
		ev->num_person_started++;
	}
	i=0;

	/*
	 * Check the number of people joining the elevator
	 */
	temp = start_node;
	while(temp!=NULL)
	{
		if(temp->per.from_floor == ev->current_floor &&
			 ev->direction == temp->per.direction)
			i++;
		temp = temp->next;
	}
	
	 
	 /* 
	  * Print the output
	 */
	if(i>0)
	{
		int to=1, from=1;
		ev->arrives_at = ev->current_floor;
		print_arrives(ev);
		find_time(ev->gv->start_time, PRINT);
		printf("Elevator %d picks up ", ev->id);
		temp = start_node;
		while(temp!=NULL)
		{
			if(temp->per.from_floor == ev->current_floor && 
					temp->per.direction == ev->direction)
			{
				temp->per.picked_up = 1;
				printf("person %d, ", temp->per.id);
				if((ev->direction == UPWARD_DIR &&
				   ev->to < temp->per.to_floor) ||
	   			  (ev->direction == DOWNWARD_DIR &&
				   ev->to > temp->per.to_floor) ||
				   (ev->to == -1))
					ev->to = temp->per.to_floor;
			}
			temp = temp->next;
		}
	}
	
        return(start_node);
}

/*
 * This function is used to drop the person from the temporary list and free the
 * node
 * ev           : elevator pointer of the specific elevator
 * start_node   : starting of the temporary list
 *  Return the starting node of the list
 */
struct node * drop_person(struct elevator *ev, struct node *start_node)
{
	struct node *temp = start_node, *ret;
	int i = 0;
	
	/*
	 * Check if there is any person to drop at the current floor
	 */
	while(temp!=NULL)
	{
		if(temp->per.to_floor == ev->current_floor 
			&& temp->per.picked_up == 1)
			//&& temp->per.direction == ev->direction)
		{	
			i++;
			ev->num_person_finished++;
			ev->gv->num_of_people_finished++;
		}
		temp=temp->next;
	}
	/*
	 * If there is someone drop that person and free the node
	 * Print the output
	 */
	if(i>0)
	{
		if(ev->current_floor!=ev->arrives_at)
		{
			ev->arrives_at = ev->current_floor ;
			print_arrives(ev);
		}
		temp = start_node;
		find_time(ev->gv->start_time, PRINT);
		printf("Elevator %d drops ", ev->id);
		while(temp!=NULL)
	        {
	                if(temp->per.to_floor == ev->current_floor   
			&& temp->per.picked_up == 1)
			//&& temp->per.direction == ev->direction)
	                {
				ret = temp;
				temp = temp->next;
				printf("Person %d, ", ret->per.id);
				start_node = del_node(ret, start_node);
				free(ret);
	                }
			else
	                	temp=temp->next;
		}
	}
	return(start_node);
}

/*
 * Prints the specified list and print the specific elevator Id, used for the
 * testing purpose
 * name         : name of the list
 * id           : id of the elevator
 * list         : start of the list
 */
void print_list(char *name, int id, struct node *list)
{
	struct node *lis = list;
	printf("\n%s", name);
	while(lis != NULL)	
	{
		printf("\n%s elevator%d person%d to_Floor%d from_Floor%d", 
			name, 
			id,lis->per.id, lis->per.to_floor, lis->per.from_floor);
		lis = lis ->next;
	}
}

/*
 * Print if there elevator reaches the floor where some one wants to get in or 
 * get out of the elevator
 * ev           : Pointer of the elevator
 */
void print_arrives(struct elevator *ev)
{
	find_time(ev->gv->start_time, PRINT);
	printf("Elevator %d arrives at floor %d", ev->id, 
		ev->arrives_at);
}

/*
 * Frees the doubly linked list
 * start        : starting address of the list
 */
void free_memory(struct node *start)
{
	struct node *temp = start;
	while(start != NULL)
	{
		temp = start;
		start = temp->next;
		temp->next = NULL;
		free(temp);
	}
}

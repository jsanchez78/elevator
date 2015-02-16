/*
 * Mugdha Deepak Gawde
 * Course Name  : Operating Systems
 * Lab Number   : 5
 * Lab          : Elevator Simulation
 * ABOUT:
 *   Thread functions implementation for elevator thread
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/timeb.h>
#include "findT.h"
#include "elevatorT.h"
#include "linkedList.h"

/*
 * Elevator threads
 * This thread is run by each elevator
 */
void *elevator_t(void *data)
{
	struct elevator *ev = (struct elevator *)data;
        globalVariable *gv = ev->gv;
	struct node *del_nod=NULL, *temp_list=NULL, *temp=NULL;
	int i=0;
	double start_tm;
	int sim_tm;
	
	start_tm = gv->start_time;
	sim_tm = gv->simulation_time;
	
	/* start the loop */
	do
	{
		if(find_time(start_tm, NO_PRINT)<(double)sim_tm)
		{
			if(temp_list != NULL && gv->ppl_start == NULL)
			{
				/* Pick up person */
				temp_list = pickup_person(ev, temp_list, 0);
			}
			else 
			{
				/* if going to use the global list acquire the lock */
				pthread_mutex_lock(gv->lock);
				while(gv->ppl_start == NULL && gv->STOP == 0)
				pthread_cond_wait(gv->cond, gv->lock);
				if(gv->STOP == 1)
				{
					free_memory(temp_list);
                	        	pthread_mutex_unlock(gv->lock);
                        		pthread_exit(NULL);
				}
				/* Pick up person */
				temp_list = pickup_person(ev, temp_list, 1);
                	       	pthread_mutex_unlock(gv->lock);
			}
			
			/* Drop the person if he is destined for current floor */
			temp_list = drop_person(ev, temp_list);

			/* Print elevator has started moving */
			if(ev->to != i && ev->to!=ev->current_floor && temp_list!=NULL)
			{
				find_time(ev->gv->start_time, PRINT);
	        		printf("Elevator %d starts moving from %d to %d",
 		       			ev->id, ev->current_floor, ev->to);
				i=ev->to;
			}

			/* sleep if elevator is not idle */
			if(temp_list != NULL)
			{
				sleep(gv->elevator_speed);
				ev->direction==1 ? ev->current_floor++ : ev->current_floor--;
			}
		}
		else
		{
			free_memory(temp_list);
			pthread_mutex_unlock(gv->lock);
			pthread_exit(NULL);
		}
	}while(1);
}

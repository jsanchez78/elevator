/*
 * Mugdha Deepak Gawde
 * Course Name  : Operating Systems
 * Lab Number   : 5
 * Lab          : Elevator Simulation
 * ABOUT:
 *   Thread functions implementation of thread for person waiting for lift
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/timeb.h>
#include <time.h>
#include "findT.h"
#include "personT.h"
#include "linkedList.h"

/*
 * Thread implementation for initialising people waiting for lift
 * data		: thread data
 */
void *person_t(void *data)
{
	globalVariable *gv = data;
	struct node *new_node= NULL;
	int id_no = 0;
	double start_tm;
        int arrival_tm, sim_tm;
	int speed = gv->elevator_speed;
        start_tm = gv->start_time;
        arrival_tm = gv->arrival_time;
        sim_tm = gv->simulation_time;

	do
	{	
		pthread_mutex_lock(gv->lock);
		if(find_time(start_tm, NO_PRINT)<(double)sim_tm)
                {	
		        new_node = (struct node *)malloc(sizeof(struct node));

        		if(new_node == NULL)
				exit(0);
			
			add_person(gv, id_no, new_node);
			id_no++;
			gv->num_person++;
			find_time(start_tm, PRINT);	
			printf("Person %d arrives on floor %d , waiting to go to floor %d", 
				new_node->per.id, 
				new_node->per.from_floor, new_node->per.to_floor);

			pthread_cond_broadcast(gv->cond); 
			pthread_mutex_unlock(gv->lock);

			sleep(arrival_tm);
		}
		else
		{
			gv->STOP = 1;
			pthread_cond_broadcast(gv->cond); 
			pthread_mutex_unlock(gv->lock);
			free_memory(gv->ppl_start);
                        pthread_exit(NULL);
		}
	}while(1);
}

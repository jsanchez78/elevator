/*
 * Elevator Simulation
 * Name : Mugdha Gawde 
 * ABOUT:
 *   This file has the main fucntion which will eventually start the elevator 
 *   and person thread
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/timeb.h>
#include <pthread.h>
#include "personT.h"
#include "elevatorT.h"
#include "findT.h"

//This is the main function which in turn will call reaining functions.
int main(int argc, char *argv[])
{

	int i, thread_return;
	pthread_t pid;
	struct timeb t;
	long seed;
	globalVariable *gv;
	pthread_t p_t;
	int p_id=0;
	int thread_ret;
	double start_tm;
	
	/*
	 * Create and initialise global variable
	 */
        gv = (globalVariable *)malloc(sizeof(globalVariable));
	if(gv == NULL)
	{
		printf("\nMemory allocation problem");
		exit(0);
	}

	init_global(argc, argv, gv);
	start_tm = gv->start_time;

	/* Init the pseudo random code */
	srand(gv->random_seed);

	/*
	 * Create the person thread
	 */
	thread_ret = pthread_create(&p_t, NULL, (void *)&person_t, gv);
	if(thread_ret)
	{
		printf("\nERROR: Cannot create thread");
		exit(0);
	}

	/*
	 * Create Elevator thread
	 */
	pthread_t e_t[gv->num_of_elevators];
	struct elevator *ev[gv->num_of_elevators];
        for(i=0; i< gv->num_of_elevators; i++)
        {
		ev[i] = (struct elevator *)malloc(sizeof(struct elevator));
		if(ev[i] == NULL)
		{
			printf("\nMemory allocation problem");
			exit(0);
		}	
		ev[i]->gv = gv;
		ev[i]->id = i;
		/*
		 * Keep elevators on 1st and last floor alternatively
		 */	
		if(i%2 ==1 )
			ev[i]->current_floor = ev[i]->arrives_at = 1;
		else
			ev[i]->current_floor 	= ev[i]->arrives_at 
						= gv->num_of_floors;
		ev[i]->direction = -1;
		ev[i]->idle = 0;
		ev[i]->num_person_started = 0;	
		ev[i]->num_person_finished = 0;	
		ev[i]->to = -1;
                thread_ret = pthread_create(&e_t[i], NULL, (void *)&elevator_t, ev[i]);
		if(thread_ret)
        	{
                	printf("\nERROR: Cannot create thread");
        	        exit(0);
	        }
        }

	/*
	 * Wait for threads to exit
	 */
	pthread_join(p_t, 0);
        for(i=0; i< gv->num_of_elevators; i++)
		pthread_join(e_t[i], 0);
	

	/*
	 * Free up the mutezes
	 */
	pthread_mutex_destroy(gv->lock);     	/* Free up the_mutex */
	pthread_cond_destroy(gv->cond);         /* Free up consumer condition variable */
		
	/*
	 * Print the final result
	 */
	printf("\nSimulation result:");
	printf(" %d people have started, %d people have finished during %0.4f seconds.\n",
		gv->num_of_people_started, gv->num_of_people_finished,
		find_time(start_tm, NO_PRINT));
	free(gv);
}

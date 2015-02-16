/*
 * Mugdha Deepak Gawde
 * Course Name  : Operating Systems
 * Lab Number   : 5
 * Lab          : Elevator Simulation
 * ABOUT:
 * 	This file contains a function to initialise the global variable
 * 	using the command line arguements
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/timeb.h>
#include <pthread.h>
#include "elevator.h"
#include "init_global.h"

/* 
 * Initialise input variable and check whether the value is valid or not using
 * compare variable 
 * arg_index	: arguement in the argv
 * compare	: arguement should be greater than the compare variable
 * argv		: arguments
 * mesg		: message to print
 */
int check_input(int arg_index,int compare, char *argv[], char *mesg)
{
	int var;
        if((var = atoi(argv[arg_index])) <= compare)
        {
                printf("\nError : <%s> must be greater than or equal to %d\n", 
			mesg, (compare+1));
                exit(0);
        }
	return(var);

}

/* 
 * Initialise global variable with command line arguements 
 * argc 	: Number of arguements
 * argv		: arguements
 * gv		: global variable
 */
void init_global(int argc, char *argv[], globalVariable *gv)
{
        struct timeb t;
	if(argc==7)
        {
                gv->num_of_elevators = check_input(1, 0, argv, "num_0f_elevators");
                gv->num_of_floors = check_input(2, 1, argv, "num_of_floors"); 
                gv->arrival_time = check_input(3, 0, argv, "arrival_time");
                gv->elevator_speed = check_input(4, 0, argv, "elevator_speed");
                gv->simulation_time = check_input(5, 0, argv, "simulation_time");
		gv->random_seed = check_input(6, -1, argv, "random_seed");
        }
        else
        {
                printf("\nError :: Invalid command. Format :: \n");
                printf("%s <num_0f_elevators> <num_of_floors> <arrival_time>", argv[0]);
		printf(" <elevator_speed> <simulation_time> <random_seed>\n");
                exit(0);
        }
	

	gv->num_of_people_started = 0;
	gv->num_of_people_finished = 0;
	gv->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	gv->cond = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
	if(gv->lock == NULL || gv->cond == NULL)
	{
		printf("\nMemory allocation problem!!");
		exit(0);
	}
	gv->num_person = 0;
	gv->STOP= 0;
	
	/* Initia;is locks */
        pthread_mutex_init(gv->lock, NULL);
        pthread_cond_init(gv->cond, NULL);     
	ftime(&t);
        gv->start_time = (double)t.time + (double)t.millitm/1000;
}

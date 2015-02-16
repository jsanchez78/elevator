/*
 * Mugdha Deepak Gawde
 * Course Name  : Operating Systems
 * Lab Number   : 5
 * Lab          : Elevator Simulation
 * ABOUT:
 *     This header file contains the data structures for global usage, elevator
 *     use and person thread use. 
 */

#ifndef _ELEVATOR_H_ 
#define _ELEVATOR_H_ 

#include <pthread.h> 

/*
 * Macros used for indicating the direction person wants to move or the 
 * elevator is moving
 */
#define UPWARD_DIR 	1
#define DOWNWARD_DIR 	0

/*
 * data structure of the person as defined in assignment
 */
struct person 
{
  	int id; 			// Unique id of the person
	int picked_up;
	int from_floor, to_floor; 	// Person's travel information
	int direction;			// Direction to travel
};

/*
 * using doubly linked list to define the person
 */
struct node
{
	struct person per;		// Person information
	struct node *prev;		// Prev pointer
	struct node *next;		// next pointer
};
/*
 * global variables decleration in the header file
 */
typedef struct 
{ 
	int num_of_elevators;		// Number of elevators
	int num_of_floors;		// Number of floors
	int arrival_time;		// Arrival time of the person
	int elevator_speed;		// Speed of the elevator
	int simulation_time;		// Total simulation time
	int random_seed;		// To generate pseudo random numbers
	int num_of_people_started; 	// No of ppl get into the elevator
	int num_of_people_finished; 	// No of ppl finished the travelling
        pthread_cond_t *cond;		// Condition variable
	pthread_mutex_t *lock;		// Locks
	struct node *ppl_start;		// Start of the person linked list
	double start_time;		// Start time of the code
	int num_person;			// Total number of people
	int STOP;			// STOP variable to stop the functions
}globalVariable;

/*
 * elevator structure which declare few variables
 */
struct elevator 
{
	int id;				// ID of the elevator
	int current_floor;		// Current floor
	int direction;			// Direction of traverse
	globalVariable *gv;		// Global variable pointer
	int num_person_started;		// No of ppl get into the elevator
	int num_person_finished;	// No of ppl finished the travel in the elevator 
	int arrives_at;			// used for output messages
	int to;				// used to print starts moving from mesg
	int idle;			// used to print idle state of the elevator
};
#endif

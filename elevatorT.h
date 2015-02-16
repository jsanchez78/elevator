/*
 * Mugdha Deepak Gawde
 * Course Name  : Operating Systems
 * Lab Number   : 5
 * Lab          : Elevator Simulation
 * ABOUT:
 *      Elevator thread function declaration is here in this header file
 */


#ifndef _ELEVATORT_H_
#define _ELEVATORT_H_

#include "elevator.h"


/*
 * Elevator threads
 * This thread is run by each elevator
 * data		: Pointer to the elevator structure
 */
void *elevator_t(void *data);

#endif

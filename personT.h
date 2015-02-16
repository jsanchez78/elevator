/*
 * Elevator Simulation
 * Name : Mugdha Gawde
 * ABOUT:
 *   Thread functions declaration of thread for person waiting for lift
 */

#ifndef _PERSONT_H_
#define _PERSONT_H_
 
#include "elevator.h"



/*
 * Thread implementation for initialising people waiting for lift
 */
void *person_t(void *data);

#endif

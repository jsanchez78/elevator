/*
 * Mugdha Deepak Gawde
 * Course Name  : Operating Systems
 * Lab Number   : 5
 * Lab          : Elevator Simulation
 * ABOUT:
 *      This file contains the function declaration to print and return the time 
 *      difference between start time and current time
 */

#ifndef _FINDT_H_
#define _FINDT_H_

#define PRINT 		1  // To specify whether to print mesg or not
#define NO_PRINT 	0  // No print
/*
 * Find the difference of start and the current time
 * start_time   : Starting time when the code has started
 * pri	        : Specifies whether to print message or not
 */
double find_time(double start_time, int pri);

#endif

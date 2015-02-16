/*
 * Mugdha Deepak Gawde
 * Course Name  : Operating Systems
 * Lab Number   : 5
 * Lab          : Elevator Simulation
 * ABOUT:
 * 	This file contains the function to print and return the time difference
 * 	between start time and current time
 */

#include <sys/timeb.h>
#include <stdio.h>
/*
 * Find the difference of start and the current time
 * start_time	: Starting time when the code has started
 * print	: Specifies whether to print message or not
 */
double find_time(double start_time, int print)
{
        struct timeb t;
        double time;

        ftime(&t);
        time = (double)t.time + ((double)t.millitm / 1000);
	time -= start_time;
	if(print)
		printf("\n[%0.4f] ", time);
        return(time);
}


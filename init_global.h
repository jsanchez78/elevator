/*
 * Mugdha Deepak Gawde
 * Course Name  : Operating Systems
 * Lab Number   : 5
 * Lab          : Elevator Simulation
 * ABOUT:
 *      This file contains a function declaration to initialise the global variable
 *      using the command line arguements
 */

#ifndef _INIT_GLOBAL_H_
#define _INIT_GLOBAL_H_

#include "elevator.h"

/*
 * Initialise input variable and check whether the value is valid or not using
 * compare variable
 * arg_index    : arguement in the argv
 * compare      : arguement should be greater than the compare variable
 * argv         : arguments
 * mesg         : message to print
 */
int check_input(int arg_index,int compare, char *argv[], char *mesg);

/*
 * Initialise global variable with command line arguements
 * argc         : Number of arguements
 * argv         : arguements
 * gv           : global variable
 */
void init_global(int argc, char *argv[], globalVariable *gv);

#endif

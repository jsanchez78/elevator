Mugdha Deepak Gawde
Course Name  : Operating Systems
Lab Number   : 5
Lab          : Elevator Simulation
-------------------------------------------------------------------------------


Indtroduction
-------------
This is the  advanced development of the elevator. In this code elevator picks 
up multiple people. Minimum number of floors for this code are fixed to 2.
1. First, person thread gets initialised it starts adding people in a global
   linked list at certain "arrival time"
2. Each elevator thread then works in following way::
	a. Each elevator is kept on first, and last floor alternately for
	   better functioning
	b. Elevator then checks whether there are people in its own list
		i) If so and if there are no people in the global list, it
		   starts its work without applying locks and without 
		   accessing the global list
		ii)If there is no person it threads own list then it waits 
		   for global list to have atleast one person in it
	c. The destination and direction of the linked list is set, and any 
	   other person who wants to go in the same direction and leave the
	   elevator before or on the same floor as that of the elevators
	   destination.
	d. Then the own list of the elevator is checked to print the person id
	   who will enter in the elevator, and set the flag for each person
	   who has entered the elevator
	e. The the function to drop the people to certain floor is called then
           Depending on the direction of each person and the flag telling that
	   ther person has entered the elevator the person node is removed
	   from the elevator.
3.When the simulation time gets over both elevator and person thread stops
working, and memory will be freed.	   

	

Following files are included in the code
1. elevator
	This file is the executable for the code

2. elevator.h
	This file contains the structure defination for all the global variables
	and thread specific variables

3. elevator_t.c
	This file contains thread function implementation for elevator thread

4. elevatorT.h
	This contains the thread function declaration

5. findT.c
	This contains the function to find the relative time

6. findT.h
	This contains the function declaration to find the relative time

7. init_global.c
	Function defination to initialise the global variable

8. init_global.h
	Function declaration  to initialise the global variable

9. linkedList.c
	This file includes function definations for function related to linked 
	list

10. linkedList.h
	This file includes function declarations for function related to linked
	list

11. main.c
	This file has the main fucntion which will eventually start the elevator
 	and person thread

12. person_t.c
	Thread functions implementation of thread for person waiting for 
	elevator

13. personT.h
	Thread functions declaration of thread for person waiting for lift

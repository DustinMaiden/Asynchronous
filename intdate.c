////////////////////////////////////////////////////////
// Main File:		intdate.c
// Semester:		CS 354 Fall 2016 Section 2
// 
// Author:		Dustin Maiden
// Email:		dmaiden@wisc.edu
// CS Login		maiden
///////////////////////////////////////////////////////


//Directives
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <string.h>

// GLOBALS // 
// seconds  => how long between timestamp displays
// controls => how many cntrl + c it will take to exit
int seconds = 3;
int controls = 5;


/* Prints current timestamp on SIGALRM interrupt  
 * This will get called every 3 seconds	
 *
 */
void time_Handler()
{
	//time data type for calendar time
	time_t cur_Time;
	time(&cur_Time);
		
	//print time using ctime to convert to string
	printf("current time is %s", ctime(&cur_Time));
	
	//arm alarm
	alarm(seconds);
}

/* Takes 5 interrupts to break the loop
 * SIGINT is in form of control + c
 *
 */
void interrupt_Handler()
{
	//decrement number of controls remaining
	controls--;	
	
	//handles # of controls and continues or exits
	if(controls > 0)
	{
	 printf("\nControl-c caught. %d more before progam is ended.\n",controls);
	}
	else if(controls == 0)
	{ 
	  printf("\nFinal Control-c caught. Exiting.\n");
	  exit(1);
	}
	else
	{
	 printf("Error");
	 exit(1);
	}
}

/* Prints the time in correct format using sigaction -> SIGALRM
 * Requires 5 interrupts to exit infinite while loop
 *
 */
int main()
{
	//structures for sigaction
	struct sigaction action;
	struct sigaction interrupt_action;
	
	memset(&action, '\0', sizeof(action));
	memset(&interrupt_action, '\0', sizeof(interrupt_action));

	// Prompt
	printf("Date will be printed every 3 seconds\n");
	printf("Enter ^C 5 times to end the program:\n");
	
	// Set alarm
	alarm(seconds);
	
	// set handler and activate sigaction
	action.sa_handler = time_Handler;
	if(sigaction(SIGALRM, &action, NULL) < 0)
	{
		perror("ERROR");
		return 1;
	}
	
	// set interrrupt handler and activate sigaction	
	interrupt_action.sa_handler = interrupt_Handler;
	if(sigaction(SIGINT, &interrupt_action, NULL) < 0)
	{
		perror("ERROR");
		return 1;
	}

	// infinite loop as suggested
	while(1)
	{
	}

	return 0;
}


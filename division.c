////////////////////////////////////////////////////////////////////////////////
// Main File:		division.c
// Semester:		CS 354 Fall 2016 Section 2
//
// Author:		Dustin Maiden
// Email:		dmaiden@wisc.edu
// CS Login		maiden
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// Global variable count
int count = 0; 

/* handler for when the user attempts dividing by 0
 * will exit the progam and print out number of operations
 *
 */
void division_Handler()
{  
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed: %d\n", count);
    printf("The program will be stopped.\n");
    exit(0);
}

/* handler for interrupt string Control + C
 * will exit the program and print out number of operations
 *
 */
void interrupt_Handler()
{   
    printf("\nTotal number of operations successfully completed: %d\n", count); 
    printf("The program will be halted.\n");
    exit(0);
}

/* driver program will infinitely request 2 integers
 * the only way to exit is to attempt a 0-divide
 * or to use the interrupt string control + c
 *
 */
int main() 
{

    // Sigaction for division handling (0-divide)
    struct sigaction divide;
    divide.sa_handler = division_Handler;
    if(sigaction(SIGFPE, &divide, NULL) !=0)
    {
	printf("ERROR");
    }   

    // Sigaction for interrupt handling (control + c)
    struct sigaction interrupt;
    interrupt.sa_handler = interrupt_Handler;
    if(sigaction(SIGINT, &interrupt, NULL) != 0)
    {
	printf("ERROR");
    }
 
    //loop
    while (1) 
    {
	//integers or chars for division
        int integer1;
	int integer2;
        char input[100]; //100 bytes as referenced in assignment sheet

        printf("Enter first integer: ");
        //use fgets and atoi as referenced in assignment sheet
	if (fgets(input, 100, stdin) != NULL) 
   		integer1 = atoi(input);          
        
	printf("Enter second integer: ");
        //use fgets and atoi as referenced in assignment sheet
	if (fgets(input, 100, stdin) != NULL) 
		integer2 = atoi(input);
        
        
	printf("%d / %d is %d with a remainder of %d\n", integer1, integer2, integer1 / integer2, integer1 % integer2);
         
	count++; //number of operations
    }
    
    return 0;
}



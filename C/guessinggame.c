#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000

int main(void) {
	   //Declaring variables
	   int lowerbound = 0, upperbound = MAX, user_guess = -1, valid_num;
	   
	   //Set the random number
	   valid_num = rand()%(MAX+1);

	   //Runs while user does not guess the right number
	   while(user_guess != valid_num) {
			 //Guessing info and input getting
			 printf("My number is between %d and %d\n", lowerbound, upperbound);
			 printf("Please enter your guess: ");
			 scanf("%d", &user_guess);

			 //Responses
			 if(user_guess > valid_num) {
				    //Tests for too big resonse
				    if(user_guess < upperbound) {
						  //Sees if upperbound should be updated
						  upperbound = user_guess;
				    }
				    printf("Too big!\n");
			 } else if(user_guess < valid_num) {
				    //Tests for too low response
				    if(user_guess > lowerbound) {
						  //Sees if lowerbound should be updated
						  lowerbound = user_guess;
				    }
				    printf("Too low!\n");
			 } else {
				    break;
			 }
	   }
	   printf("Congrats! You win!\n");
	   return 0;
}

void __attribute__ ((__constructor__)) 
	   set_seed() {
			 //Sets seed to a "random" value using time
			 srand(time(NULL));
}

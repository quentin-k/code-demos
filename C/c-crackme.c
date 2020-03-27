#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#define MAX 21

//global variables
int lc, g1=0, g2=0;

unsigned long long reverse(unsigned long long var) {
	   /*
	    * Reverse a given number
	    * */

	   //Value of the reversed number
	   unsigned long long reversed_val = 0;
	   
	   while(var != 0) {
			 /* The reversing loop
			  * */
			 reversed_val *= 10;
			 int tmp = var % 10;
			 if(tmp == 0 && reversed_val == 0) {
				    //Makes sure that a number that tries beat the
				    //system by appending extra zeros is unable to
				    reversed_val += (rand()%8)+1;
			 }

			 g2 += tmp;
			 reversed_val += tmp;
			 var /= 10;
	   }

	   //Gets last 3 numbers and "un-reverses" them
	   //for use in g1
	   int tmp = reversed_val % 1000;
	   for(int i = 0; i < 3; i++) {
			 g1 = (g1 * 10) + (tmp % 10);
			 tmp /= 10;
	   }

	   //Should set g2 to 30 if a valid number is entered
	   g2 = g2 - (g2/11);

	   //Gives the reveresed number
	   return reversed_val;
}

int validate(unsigned long long var) {
	   /*
	    * Validate the given number
	    * */

	   //a & b are decrypted at runtime regardless of 
	   //the given key, app is prepared for getting g1
	   //appended to it
	   int a = 115422447, b = 160043528, app = g2*1000;
	   
	   for(int i = 0; i < rand()%1000; i++) {
			 /* Decrypts a
			  * */
			 srand(rand());
			 a ^= rand();
	   } for(int i = 0; i < rand()%1000; i++) {
			 /* Decrypts b
			  * */
			 srand(rand());
			 b ^= rand();
	   }

	   //Appends g1 to app
	   app += g1;
	   
	   // logic for determing if a valid number is given
	   if(var % app == var % a && //makes sure that app == a
			 var % app == 0 && // makes sure that var is cleanly divisible by a
			 var / a == b) { // makes sure that the division yields the correct value
				    return 1;
	   } else {
			 return 0;
	   }
}

void msg_lose() {
	   /* Displays the losing message
	    * */

	   //This is an encrypted string that gets decrypted when called
	   //its intention is to keep you from using strings to help identify
	   //functions
	   int lose[10] = {145649822,2051073159,1951101528,783742405,1413613942,1044967195,1379773739,1093391462,996294164,1806741961};
	   srand(lc);
	   for(int i = 0; i < 10; i++) {
			 //Decrypts and displays the message
			 srand(rand());
			 printf("%c", lose[i]^rand());
	   }
}

void msg_win() {
	   /* Displays the winning message
	    * */

	   //The message encrypted to make it harder to find the function with strings
	   int win[9] = {1602870440,840693458,200264073,665851524,1404163032,1833610925,1123472814,1986617512,1918443610};
	   
	   for(int i = 0; i < 9; i++) {
			 /* Decryption of the winning message
			  * */
			 srand(rand());
			 int tmp = win[i]^rand();
			 if((tmp >= 32 && tmp <= 126) || tmp == 10) { 
				    //makes sure no funky values have slipped in
				    printf("%c", tmp);
			 } else {
				    //punishes the user if they have the wrong key from doing an illegal action
				    msg_lose();
				    break;
			 }
	   }
}

int main(void) {
	   /*
	    * The main function
	    * */
	   
	   //user_num, fun fact: I had to make this an unsigned double long
	   //to allow it to contain a 20 digit number.
	   unsigned long long user_num = 0;

	   //gets and contains the user string
	   char char_var[MAX];
	   fgets(char_var, MAX, stdin);

	   for(int i = 0; i < MAX; i++) {
			 /* Turns the string to an unsigned double long
			  * */
			 if(char_var[i] >= 48 && char_var[i] <= 57) {
				    user_num*=10;
				    user_num += char_var[i]-48;
			 } else {
				    break;
			 }
	   }

	   //Reverses the user_num
	   user_num = reverse(user_num);
	   
	   //Checks which statement to give the user on their input
	   if(validate(user_num)) {
			 msg_win();
	   } else {
			 msg_lose();
	   }
	   return 0;
}

void __attribute__ ((__constructor__)) set_initial_seed() {
	   /*
	    * Sets the user seed, this runs before main
	    * which can leed to some fun disassembling times
	    * */
	   int a=0;
	   srand(a);
	   for(int i = 0; i < 1000; i++) {
			 a+=i+rand();
			 a ^=rand();
			 lc = a^i;
			 if(i%11 == 7) {
				    srand(a);
			 }
	   }
	   srand(a);
}

void __attribute__ ((__constructor__)) welcome_msg() {
	   /*
	    * Prints the welcome message, this runs after set_initial_seed()
	    * but still before main
	    * */
	   int msglen = 26;
	   int msg[26] = {769248948,1998748032,362118477,1304970565,790374794,1720477564,1260604870,774924176,1290213382,229059766,704414215,1438655513,248066626,767505112,1604827693,1648810831,222031863,104255061,1858400878,1827134483,1458485066,11306953,1195079467,3728507,2075191027,95405132};
	   for(int i = 0; i < msglen; i++) {
			 printf("%c", msg[i]^rand());
	   }
}

void __attribute__ ((__constructor__)) detect_debugger() {
	   /*
	    * Detects if there is a debugger,
	    * I had a fun time placing this function,
	    * I wanted to have the output seem normal
	    * but give incorrect results, I ripped this 
	    * off the internet from a linux anti-debugging tutorial.
	    * (This is the last function run before main)
	    * */
	   if(ptrace(PTRACE_TRACEME, 0, 1, 0) < 0) {
			 for(int i = 0; i < rand()%1001; i++) {
				    srand(rand());
			 }
	   }
}

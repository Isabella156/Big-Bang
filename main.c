/************************************************************************
University of Leeds
School of Computing
COMP1711/XJCO1711- Procedural Programming
Coursework 3
File: main.c

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name: Liu Yunzhu
Student ID: 201388894
Email: sc192yl@leeds.ac.uk
Date Work Commenced: 11/27/2020
*************************************************************************/


// ********************************************************************************************************************
// DO NOT CHANGE ANYTHING IN THE FOLLOWING SECTION. IF YOU CHANGE ANYTHING, YOUR CODE WILL FAIL THE AUTOGRADER TESTS.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "uni.h"



// Use the following format strings in your printf statements so that your program output will be identical to mine
//-----------------------------------------------------------------------------------------------------------------
/*

"star %i\n"
"name: %s\n"
"coords: (%.3f,%.3f)\n"
"Pair %i:\n"
"distance: %f\n"
"**************************\n"
"The Big Bang has occurred!\n"
"Sorry, unable to bang!\n"
"Sorry no pairs were found!\nWish you a better luck in the next universe\n"
"The closest pair of stars are no. %i and %i\n"
"They are %.3f light years apart\n"
"Would you like to name this pair (y/n)?"
"Enter your full name:"
"Enter your spouse full name:"
"Congratulations a pair of stars has been named after you and your spouse\n"
"Thanks, you have saved the universe!\n"
"Congratulations, your saved universe was restored!\n"
"No such command!\n"

*/


// END OF CODE SECTION THAT SHOULD NOT BE CHANGED
// ************************************************



// -------------------------------------------------------------------------------------------------
// NOW, IMPLEMENT THE FOLLOWING FUNCTIONS BY WRITING THE CORRECT CODE IN THE BODIES OF THE FUNCTIONS
// please, don't change the functions' names, return types, or parameters. If you change any of these the grader will crash
// initially, some of these functions contain 'return 0'. Before implementing a function you should delete this statement



// Print the details of a star
void printStar (Star* s)
{

}

// Display a list of all stars in the universe
void listStars ()
{
	int i;
	for(i=0;i<numStars;i++){
		printf("star %i\n",i);
		printf("coords: (%.3f,%.3f)\n",stars[i]->x,stars[i]->y);
	}

}

// List all named pairs
void listPairs ()
{
// "star %i\n"
// "name: %s\n"
// "coords: (%.3f,%.3f)\n"
// "Pair %i:\n"
// "distance: %f\n"
// "**************************\n"
	int i;
	for(i=0;i<MaxPair;i++){
		if(pairs[i]->h->named==1){
			printf("Pair %i:\n",i);
			printf("distance: %f\n",pairs[i]->d);
			printf("star %i\n",pairs[i]->h->id);
			printf("name: %s\n",pairs[i]->h->named);
			printf("coords: (%.3f,%.3f)\n",pairs[i]->h->x,pairs[i]->h->y);
			printf("star %i\n",pairs[i]->w->id);
			printf("name: %s\n",pairs[i]->w->named);
			printf("coords: (%.3f,%.3f)\n",pairs[i]->w->x,pairs[i]->w->y);
			printf("**************************\n");
		}
	}

}

// Draw the entire universe
void drawUniverse ()
{
	int i;
	// clear buffer
	clearBuffer;
	// plot stars
	for(i=0;i<numStars;i++){
		plot(stars[i]->x,stars[i]->y,'.');
	}
	// show buffer
	showBuffer;
}

// Tag a named pair of stars by writing a string comprising the names of the couple that own the pair
// underneath this pair in the frame buffer (see assignment brief)
// The names of the 2 owners should be concatenated into one string with an & sign in between.
// The name of the h star should be first followed by the name of the w star (by the way, h stands for husband and w stands for wife).
// For example, if the the h star name is "Mr Bean" and the w star name is "Irma Gobb", the string will be "Mr Bean & Irma Gobb"
// with exactly one space before and after the &.
// The string should be positioned one row below the h star's row, with the middle of the string aligned with the h star's column
// Calling this function will NOT cause the frame buffer to be redisplayed on the screen, if you need to show the frame buffer, you must
// call showBuffer (but NOT inside this function)

void tagPair (Pair* p)
{

}
char clearCommand(char string[])
{
	int i=0;
	while(string[i]!='\0'){
		string[i]='\0';
		i++;
	}
	return string;
}
char clearCommand(char string[]);
// DON'T CHANGE THE FOLLOWING 3 LINES
#ifndef TEST
int  main (int argc, char* argv[])
{
	// ENTER THE CODE OF YOUR main FUNCTION BELOW
	char command[100];
	char first_name1[30];
	char sur_name1[30];
	char first_name2[30];
	char sur_name2[30];
	int pair_number=0;
	char full_name[30];
	char link_name[60];

	while(1){
		// enter big bang
		printf(">>>");
		scanf("%s %i",command,&numStars);
		if(command=="bang"&&numStars<MaxStar&&numStars>0){
			bigBang(numStars);
			clearCommand;
		}
		if(command=="list"){
			listStars;
			clearCommand;
		}
		
	}
	scanf("%s %i",command,&numStars);

	if(!strcmp("bang",command)){
		// big bang function
		printf("The Big Bang has occurred!\n");
	}
	
	scanf("%s",command);
	if(!strcmp("list",command)){
		// list function
		listStars;
	}
	scanf("%s",command);
	if(!strcmp("draw",command)){
		// draw function
	}
	scanf("%s",command);
	if(!strcmp("name",command)){
		Pair *pair1 = closestPair;
		printf("The closest pair of stars are no. %i and %i\n",pair1->h->id,pair1->w->id);
		pair1->d=pointDistance(pair1->h->x,pair1->h->y,pair1->w->x,pair1->w->y);
		printf("They are %.3f light years apart\n",pair1->d);
		printf("Would you like to name this pair (y/n)?");
		scanf("%s",command);
		if(command=='y'){
			printf("Enter your full name:");
			scanf("%s %s",first_name1,sur_name1);
			printf("Enter your spouse full name:");
			scanf("%s %s",first_name2,sur_name2);
			nameStar(pair1->h,first_name1,sur_name1);
			nameStar(pair1->w,first_name2,sur_name2);
			pairs[pair_number]=pair1;
			plot(pair1->h->x,pair1->h->y,'*');
			plot(pair1->w->x,pair1->w->y,'*');
			printf("Congratulations a pair of stars has been named after you and your spouse\n");
		}
		scanf("%s",command);
		if(!strcmp("pairs",command)){
			listPairs;
		}
		scanf("%s",command);
		if(!strcmp("draw",command)){
			drawUniverse;
		}
		scanf("%s",command);
		if(!strcmp("show",command)){
			printf("Enter your full name:");
			scanf("%s",full_name);
			Pair* pair2=findPairByName(full_name);
			
		}
	}

// DON'T CHANGE THE FOLLOWING 2 LINES
}
#endif
// DON'T WRITE ANYTHING BELOW THIS LINE
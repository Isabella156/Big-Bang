/************************************************************************
University of Leeds
School of Computing
COMP1711/XJCO1711- Procedural Programming
Coursework 3
File: logic.c

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
// However, please read through this section and look at the declarations of arrays and global vars that you will be using in your program


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "uni.h"


int SerNum=0;			// a counter to create unique star numbers (identifiers)
int numStars = 0;		// the actual number of stars in the universe (not the same as the maximum)
int numPairs = 0;		// the number of pairs that have been named

Star *stars[MaxStar];		// the array of stars (an array of pointers to stars)
Pair *pairs[MaxPair];		// the array of named pairs (an array of pointers to pairs)

// END OF CODE SECTION THAT SHOULD NOT BE CHANGED
// ************************************************

// --------------------------------------------------------------------------------------------------
// NOW IT IS YOUR TURN, YOU CAN DEFINE ANY OTHER GLOBAL VARIABLES YOU MAY NEED IN YOUR CODE BELOW THIS LINE
int numStar1, numPair1;



// END OF SECTION FOR DECLARRING ADDITIONAL GLOBAL VARIABLES
// ----------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// NOW, IMPLEMENT THE FOLLOWING FUNCTIONS BY WRITING THE CORRECT CODE IN THE BODIES OF THE FUNCTIONS
// please, don't change the functions' names, return types, or parameters. If you change any of these the grader will crash
// Initially, some of these functions contain 'return 0' or 'return -99'. Before implementing a function you should delete this statement
// None of the functions should cause memory leaks

Star* findStarByXY  (double x , double y, double tolerance)
{
	int found = 0;
	int i,j;

	for(i=0;i<numStars;i++){
		if(fabs(stars[i]->x-x)<tolerance&&fabs(stars[i]->y-y<tolerance)){
			found = 1;
			break;
		}
	}

	if(found){
		return  stars[i];
	}else{
		return 0;
	}
}

int bigBang (int n_stars)
{
	if(n_stars>=1&&n_stars<=1891){
		
		// declaration
		int i,j;
		Star first_star[MaxStar];
		double tolerance = 0.00000001;
		int coincide=0;

		// initialize the stars
		for(i=0;i<MaxStar;i++){
			stars[i] = (Star *) malloc (sizeof (Star));
		}

		// initialize the pairs
		Pair first_pair[MaxPair];
		for(i=0;i<MaxPair;i++){
			pairs[i] = (Pair *) malloc (sizeof (Pair));
		}

		// array to store x coordinates and y coordinates
		double xcoordinates[n_stars],ycoordinates[n_stars];

		// create the stars
		for(i=0;i<n_stars;i++){

			// create identifier
			stars[i]->id=i;

			// create coordinates
			stars[i]->x=rand()%MaxX+1;
			stars[i]->y=rand()%MaxY+1;

			xcoordinates[0]=stars[0]->x;
			ycoordinates[0]=stars[0]->y;

			// check if the coordinates are coincident
			for(j=0;j<i;j++){

				// determine the coincidence
				if(fabs(stars[i]->x-xcoordinates[j])<tolerance&&fabs(stars[i]->y-ycoordinates[j])<tolerance){
					coincide=1;
				}

				// handle the coincidence
				if(coincide){
					stars[i]->x=rand()%MaxX+1;
					stars[i]->y=rand()%MaxY+1;
					coincide=0;
					j=-1;
				}else{
					xcoordinates[i]=stars[i]->x;
					ycoordinates[i]=stars[i]->y;
				}	
			}
			stars[i]->named=0;
			
		}

		// initialize the other variables
		numStars=n_stars;
		numPairs=0;

		return 1;
	}else{
		return 0;
	}
}

double pointDistance (double x1, double y1, double x2, double y2)
{
	double distance=sqrt( (pow((x1-x2),2)) + (pow((y1-y2),2)) );
	return distance;
}


Pair* closestPair ()
{
	int i,j;
	double minDistance=70.0;
	double currentDistance;
	Pair *closestPair = (Pair *) malloc (sizeof (Pair));

	for(i=0;i<numStars;i++){
		if(stars[i]->named==0){
			for(j=i+1;j<numStars;j++){
				if(stars[j]->named==0){
					currentDistance=pointDistance(stars[i]->x,stars[i]->y, stars[j]->x, stars[j]->y);
					if(currentDistance<minDistance){
						minDistance=currentDistance;
						closestPair->h=stars[i];
						closestPair->w=stars[j];
						closestPair->d=minDistance;
						numPairs++;
					}
				}
			}
		}
	}

	if(minDistance==70.0){
		return 0;
	}else{
		return closestPair;
	}

}


int nameStar (Star *s, char* first_name, char* sur_name)
{
	int i,j;
	
	// invalid parameter
	if(s==0||first_name==0||sur_name==0){
		return 0;
	}else{

	// first name
	for(i=0;first_name[i]!='\0';i++){
		s->name[i]=first_name[i];
	}
	s->name[i]=' ';
	// surname
	for(j=0;sur_name[j]!='\0';j++){
		s->name[i+j+1]=sur_name[j];
	}
	s->name[i+j+1]='\0';
	// change name flag
	s->named=1;

	// long name
	if(i+j+1>30){
		return 0;
	}else{
		return 1;
	}

	

}
}

Pair* findPairByName (char* name)
{
	int i,find=0;
	// compare the name of husband and wife and the name
	for(i=0;i<numPairs;i++){
		if( (!strcmp(pairs[i]->h->name,name)) || (!strcmp(pairs[i]->w->name,name)) ){
			find=1;
			break;
		}
	}
	if(find==1){
		return pairs[i];
	}else{
		return 0;
	}
	
}

int saveUniverse ()
{
	FILE *outputFile;
	outputFile = fopen("universe.bin","wb");
	if(outputFile == NULL){
		return 0;
	}else{
		fwrite(stars,sizeof(Star),numStars,outputFile);
		fwrite(pairs,sizeof(Pair),numPairs,outputFile);
		numStar1=numStars;
		numPair1=numPairs;
		fclose(outputFile);
		return 1;
	}

}

int loadUniverse ()
{
	FILE *inputFile;
	inputFile=fopen("universe.bin","rb");
	if(inputFile==NULL){
		return 0;
	}else{
		numStars=numStar1;
		numPairs=numPair1;
		fread(stars,sizeof(Star),numStar1,inputFile);
		fread(pairs,sizeof(Pair),numPair1,inputFile);
		fclose(inputFile);
		return 1;
	}

}

// IF YOU NEED ADDITIONAL FUNCTIONS YOU CAN DEFINE THEM BELOW
// WITH THEIR PROTOTYPES DEFINED IN THE GLOBAL VARS SECTION OF THIS FILE
//----------------------------------------------------------------------
void clearCommand(char string[])
{
	int i=0;
	while(string[i]!='\0'){
		string[i]='\0';
		i++;
	}
}

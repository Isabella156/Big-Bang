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
#define MaxRow  31		// The number of rows in the frame buffer
#define MaxCol 61		// The number of columns in the frame buffer

#define MaxStar 1891	// The maximum number of stars in a 'completely filled' universe
#define MaxPair 945		// The maximum number of star pairs that can be named in a universe

#define MaxX 60			// The length of the universe in light years
#define MaxY 30			// The width of the universe in light years

// A structure to store data about a star
typedef struct
{
	int id;					// A unique number (identifier) for this star. Identifiers start at 0.
	double x;				// The star's x coordinate in the universe, [0-60] light years
	double y;				// The star's y coordinate in the universe, [0-30] light years
	char name[30];			// The name of this star, maximum 30 chars including the \0 at the end
	int named;				// A flag that is set to true (1) if the star has a name, initially 0 for all stars
} Star;

// A structure to store data about a pair of named stars
typedef struct
{
	Star* h;					// A pointer to the first star in this pair
	Star* w;					// A pointer to the second star in this pair
	double d;					// The distance between the two stars of this pair
} Pair;

extern Star *stars[MaxStar];		// the array of stars
extern Pair *pairs[MaxPair];		// the array of named pairs
extern int numStars;				// number of stars in the universe
extern int numPairs;				// number of named star pairs
char fbr[MaxRow][MaxCol];
int numStar1, numPair1;

void clearBuffer ()
{
	for(int i=0;i<MaxRow;i++){
		for(int j=0;j<MaxCol;j++){
			fbr[i][j]=' ';
		}
	}		
}

void plot (int row, int col, char c)
{
	if(row<MaxRow&&row>=0&&col<MaxCol&&col>=0){
		fbr[row][col]=c;
	}
}

char peek (int row, int col)
{
	if(row<MaxRow&&row>=0&&col<MaxCol&&col>=0){
		return fbr[row][col];
	}else{
		return 0;
	}
}

void writeAt (int row, int col, char str[])
{
	int i=0;
	if(row<MaxRow&&row>=0&&col<MaxCol&&col>=0){
		while(str[i]!='\0'&&col<MaxCol){
			fbr[row][col]=str[i];
			col++;
			i++;
		}
	}
}

void showBuffer ()
{
	for(int i=0;i<MaxRow;i++){
		for(int j=0;j<MaxCol;j++){
			printf("%c",fbr[i][j]);
		}
		printf("\n");
	}
}

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


// prototypes of the functions that you will implementing
// the functions themselves are in the graph.c, logic.c, and main.c files

// graphics functions
void clearBuffer ();
void plot (int row, int col, char c);
char peek (int row, int col);
void writeAt (int row, int col, char* text);
void showBuffer ();
// program logic functions
Star* findStarByXY(double x, double y, double tolerance);
int bigBang (int n_stars);
double pointDistance (double x1, double y1, double x2, double y2);
Pair* closestPair ();
int nameStar (Star *s, char* first_name, char* sur_name);
Pair* findPairByName (char* name);
int saveUniverse ();
int loadUniverse();
// interface functions
void printStar (Star*);
void listStars ();
void listPairs ();
void drawUniverse ();
void tagPair (Pair* p);

// DON'T CHANGE THE FOLLOWING 3 LINES
// #ifndef TEST
// int  main (int argc, char* argv[])
int main()
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
// #endif
// DON'T WRITE ANYTHING BELOW THIS LINE
#include <stdio.h>

// define
#define MaxRow  31
#define MaxCol 61

#define MaxStar 1891
#define MaxPair 945

#define MaxX 60
#define MaxY 30

// *****************************global variables*****************************

// A structure to store data about a star
typedef struct
{
	int id;
	double x;
	double y;
	char name[30];
	int named;
} Star;
// A structure to store data about a pair of named stars
typedef struct
{
	Star* h;					// A pointer to the first star in this pair
	Star* w;					// A pointer to the second star in this pair
	double d;					// The distance between the two stars of this pair
} Pair;

Star *stars[MaxStar];		// the array of stars
Pair *pairs[MaxPair];		// the array of named pairs
int numStars;				// number of stars in the universe
int numPairs;				// number of named star pairs
Star *stars[MaxStar];

// *****************************Function*************************
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
char clearCommand(char string[]);
// function to clear command
char clearCommand(char string[])
{
	int i=0;
	while(string[i]!='\0'){
		string[i]='\0';
		i++;
	}
	return string;
}
// function to display list of stars
void listStars ()
{
	int i;
	for(i=0;i<numStars;i++){
		printf("star %i\n",i);
		printf("coords: (%.3f,%.3f)\n",stars[i]->x,stars[i]->y);
	}

}
int main()
{
	char command[10];
	while(1){
		// enter big bang
		printf(">>>");
		scanf("%s %i",command,&numStars);
		if(command=="bang"&&numStars<MaxStar&&numStars>0){
			bigBang(numStars);
			clearCommand;
		}
		printf(">>>");
		scanf("%s",command);
		if(command=="list"){
			listStars;
			clearCommand;
		}
		
		
	}
	return 0;

}
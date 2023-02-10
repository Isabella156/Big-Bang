#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MaxRow  31        // The number of rows in the frame buffer
#define MaxCol 61        // The number of columns in the frame buffer

#define MaxStar 1891    // The maximum number of stars in a 'completely filled' universe
#define MaxPair 945        // The maximum number of star pairs that can be named in a universe

#define MaxX 60            // The length of the universe in light years
#define MaxY 30

double pointDistance (double x1, double y1, double x2, double y2)
{
    double distance = sqrt(pow(x1-x2, 2)+pow(y1-y2, 2));

    return distance;
}

int main ()
{
    typedef struct
    {
        int id;                    // A unique number (identifier) for this star. Identifiers start at 0.
        double x;                // The star's x coordinate in the universe, [0-60] light years
        double y;                // The star's y coordinate in the universe, [0-30] light years
        char name[30];            // The name of this star, maximum 30 chars including the \0 at the end
        int named;                // A flag that is set to true (1) if the star has a name, initially 0 for all stars
    } Star;

    Star *stars[MaxStar];        // the array of stars (an array of pointers to stars)
    int SerNum = 0;
    int n_stars = 4;
    double tolerance = 0.00000001;
    int result = 0;
    double x = 0, y = 0;
    Star initial[MaxStar];
    



    typedef struct
    {
        Star* h;                    // A pointer to the first star in this pair
        Star* w;                    // A pointer to the second star in this pair
        double d;                    // The distance between the two stars of this pair
    } Pair;

    int numStars = 2;
    int numPairs = 0;
    Pair *pairs[MaxPair];

	// big bang
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
	}

	// closest pair
	double minDistance=70.0;
	double currentDistance;
	numStars=2;
	Pair *closestPair = (Pair *) malloc (sizeof (Pair));
	int i,j;
	for(i=0;i<numStars;i++){
		if(stars[i]->name==0){
			for(j=i+1;j<numStars;j++){
				if(stars[j]->name==0){
					currentDistance=pointDistance(stars[i]->x,stars[i]->y, stars[j]->x, stars[j]->y);
					if(currentDistance<minDistance){
						minDistance=currentDistance;
						closestPair->h=stars[i];
						closestPair->w=stars[j];
						closestPair->d=minDistance;
					}
				}
			}
		}
	}

	if(minDistance==70.0){
		return 0;
	}else{
		return 1;
	}

}

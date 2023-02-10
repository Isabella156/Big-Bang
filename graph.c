/************************************************************************
University of Leeds
School of Computing
COMP1711/XJCO1711- Procedural Programming
Coursework 3
File: graph.c

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



#include <stdlib.h>
#include <stdio.h>
#include "uni.h"

char fbr[MaxRow][MaxCol];	// the frame buffer

// END OF CODE SECTION THAT SHOULD NOT BE CHANGED
// ************************************************


// -------------------------------------------------------------------------------------------------
// NOW, IMPLEMENT THE FOLLOWING FUNCTIONS BY WRITING THE CORRECT CODE IN THE BODIES OF THE FUNCTIONS
// please, don't change the functions' names, return types, or parameters. If you change any of these the grader will crash


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
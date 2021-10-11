//Senior Design Fall 2021
//Written By Madison Pisone
//main file for housing the User Interface for a Robotic Arm for Drawing 2D Geometric Shapes

#include <stdio.h>
#include <stdlib.h>
#include "shape.h"
#include "shape.c"
#include "validate.c"


int main(void){
  int shape, ifSquare, goAgain = 1, options =4;
  float mainVals[10];


  printf("\nRobotic Arm for Drawing 2D Geometric Shapes\n");

  while(goAgain == 1){
    printf("Welcome! What shape would you like to draw?\n");
    printf("1. Triangle\n2. Rectangle\n3. Square\n4. Circle\n");
    scanf("%d", &shape);
    //printf("choice = %d", shape);
    //error check for user input
    while(shape < 0 || shape > options){
      printf("\nPlease enter a t value between 1 and %d: ", options);
      scanf("%d", &shape);
    }

    //mainVals = toDraw();

    if(shape == 1){
      //triangle
      triangleDeclare();

    }else if(shape ==2){
      //rectangle
      ifSquare = 0;
      rectangleDeclare(ifSquare);

    }else if(shape == 3){
      //square
      ifSquare = 1;
      rectangleDeclare(ifSquare);
    }else{
      //circle
      circleDeclare();
    }
    int temp;
    printf("\nWoud you like to draw another shape? Enter 1 for YES or 0 for NO.\n");
    scanf("%d", &temp);
    while(temp != 1 && temp != 0){
      printf("Please enter either 1 or 0: ");
      scanf("%d", &temp);
    }
    if(temp == 1){
      goAgain = 1;
    }else{
      goAgain = 0;
    }

  }

}

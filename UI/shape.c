//Senior Design Fall 2021
//Written By Madison Pisone
//Shape Framework File
//Need to use mathmatical equations to verify valid inputs

#include <stdio.h>
#include <stdlib.h>
#include "shape.h"


//Global Variables
float vals[20];
int choice, validity;

void triangleDeclare(){
  //TRIANGLE
  //Declare side lengths
  //Side 1 = vals[0]
  //Side 2 = vals[1]
  printf("Side Length A: ");
  scanf("%f", &vals[0]);
  while(vals[0] >= 8.5|| vals[0] < 0){
    //The side length must be less than 8.5 inches.
    printf("\nPlease enter a new value.");
    scanf("%f", &vals[0]);
  }
  printf("Side Length B: ");
  scanf("%f", &vals[1]);
  while(vals[1] >= 8.5|| vals[1] < 0){
    //The side length must be less than 8.5 inches.
    printf("\nPlease enter a new value.\n");
    scanf("%f", &vals[1]);
  }
  rotate();

  //Starting Coordinates
  printf("X starting point: ");
  scanf("%f", &vals[3]);
  printf("Y starting point: ");
  scanf("%f", &vals[4]);


  validate(1, vals);
}

//For defining a rectanlge OR square
void rectangleDeclare(int ifSquare){

  if(ifSquare == 0){
    //RECTANGLE
    //Declare side lengths
    //Side 1 = vals[0]
    //Side 2 = vals[1]
    printf("Side Length A: ");
    scanf("%f", &vals[0]);
    while(vals[0] >= 8.5|| vals[0] < 0){
      //The side length must be less than 8.5 inches.
      printf("\nPlease enter a new value.");
      scanf("%f", &vals[0]);
    }

    //Rotation Degree = vals[2]
    printf("Side Length B: ");
    scanf("%f", &vals[1]);
    while(vals[1] >= 8.5|| vals[1] < 0){
      //The side length must be less than 8.5 inches.
      printf("\nPlease enter a new value.\n");
      scanf("%f", &vals[1]);
    }

    rotate();

    //Starting Coordinates
    printf("X starting point: ");
    scanf("%f", &vals[3]);
    printf("Y starting point: ");
    scanf("%f", &vals[4]);

    validate(2, vals);
  }else{
    //SQUARE
    //Declare side length
    //Sides = vals[0]
    printf("Side Length: ");
    scanf("%f", &vals[0]);
    while(vals[0] >= 8.5|| vals[0] < 0){
      //The side length must be less than 8.5 inches.
      printf("\nPlease enter a new value.");
      scanf("%f", &vals[0]);
    }

    rotate();

    //Starting Coordinates
    printf("X starting point: ");
    scanf("%f", &vals[3]);
    printf("Y starting point: ");
    scanf("%f", &vals[4]);

    validate(3, vals);
  }

}

void ellipseDeclare(){
  //ELLIPSE
  //Declare Radius lengths
  //X radius = vals[0]
  //Y radius = vals[1]
  printf("X Radius: ");
  scanf("%f", &vals[0]);
  while(vals[0] >= 8.5|| vals[0] < 0){
    //The side length must be less than 8.5 inches.
    printf("\nPlease enter a new value.");
    scanf("%f", &vals[0]);
  }
  printf("Y Radius: ");
  scanf("%f", &vals[1]);
  while(vals[1] >= 8.5|| vals[1] < 0){
    //The side length must be less than 8.5 inches.
    printf("\nPlease enter a new value.\n");
    scanf("%f", &vals[1]);
  }

  rotate();

  //Starting Coordinates
  printf("X starting point: ");
  scanf("%f", &vals[3]);
  printf("Y starting point: ");
  scanf("%f", &vals[4]);

  validate(4, vals);
}

void rotate(){
  //Rotation Degree = vals[2]
  printf("Rotation?: 0,45,90,135,180,225,270,315 \n");
  scanf("%f", &vals[2]);
  while(vals[2] != 0 && vals[2] != 45 && vals[2] != 90 && vals[2] != 135 && vals[2] != 180 && vals[2] != 225 && vals[2] != 270 && vals[2] != 315){
    printf("Please enter a valid input.\n");
    scanf("%f", &vals[2]);
  }
}

void validate(int whichShape, float vals[]){
  if(whichShape == 1){
    //TRIANGLE
    
    if(vals[0] > vals[1]){
      //Side A > Side B

    }
  }
}

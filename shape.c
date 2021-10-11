//Senior Design Fall 2021
//Written By Madison Pisone
//Shape Framework File
//Need to use mathmatical equations to verify valid inputs

#include <stdio.h>
#include <stdlib.h>
#include "shape.h"


//Have user decide how they want to define their triangle
//return their choice (int)
//1 = 3 Side Lengths
//2 = SAS: Side Angle Side
//3 = ASA: Angle Side Angle
void triangleDeclare(){
  int choice, validity;
  //array for holding triangle values
  float vals[5];
  printf("\nHow would you like to define your triangle?\n");
  printf("1. Two Side Lengths\n2. Right Angle Triangle; Side + Angle.\n");
  scanf("%d",&choice);
  while(choice < 1 || choice > 2){
    printf("Please enter a valid input: ");
    scanf("%d",&choice);
  }

  //printf("\nchoice = %d", choice);

  //get user inputs

  if(choice == 1){

    //3 Side Lengths
    printf("\n2 Side Lengths\n");
    printf("Length of side C (in inches): ");
    scanf("%f", &vals[0]);
    while(vals[0] >= 8.5|| vals[0] < 0){
      printf("\nThe side length must be less than 8.5 inches. Please enter a new value.");
      scanf("%f", &vals[0]);
    }
    //printf("%.2f", vals[0]);
    printf("Length of side B(in inches): ");
    scanf("%f", &vals[1]);
    while(vals[1] >= 8.5|| vals[1] < 0){
      printf("\nThe side length must be less than 8.5 inches. Please enter a new value.\n");
      scanf("%f", &vals[1]);
    }

    //find length of side c
    validity = validate(1, vals);

  }else{
    //SAS
    printf("\nRight Triangle by Side Angle\n");
    printf("\nLength of side C (in inches): ");
    scanf("%f", &vals[0]);
    while(vals[0] >= 8.5 || vals[0] < 0){
      printf("The side length must be less than 8.5 inches and larger than 0. Please enter a new value.\n");
      scanf("%f", &vals[0]);
    }
    printf("Degree of the angle(in degrees): ");
    scanf("%f", &vals[1]);
    while(vals[1] >= 90|| vals[1] < 0){
      printf("The angle must be smaller that 90 Degrees and larger than 0. Please enter a new value for the anlge(in Degrees).\n");
      scanf("%f", &vals[1]);
    }

    //TODO: Call to validate triangle inputs
    //find length of side C
    validity = validate(2, vals);

  }


  //return choice;
}

//For defining a rectanlge OR square
void rectangleDeclare(int ifSquare){
  float vals[5];
  int choice, validity, rotate;
  //is a rectangle
  if(ifSquare == 0){
    printf("\nLength of side 1(in inches): ");
    scanf("%f", &vals[0]);
    while(vals[0] >= 8.5|| vals[0] < 0){
      printf("The side length must be less than 8.5 inches and larger than 0. Please enter a new value.\n");
      scanf("%f", &vals[0]);
    }
    printf("Length of side 2(in inches): ");
    scanf("%f", &vals[1]);
    while(vals[1] >= 8.5|| vals[1] < 0){
      printf("The side length must be less than 8.5 inches and larger than 0. Please enter a new value.\n");
      scanf("%f", &vals[1]);
    }
    printf("Would you like to rotate your rectangle? Enter 1 for YES or 0 for NO. \n");
    scanf("%d", &rotate);
    while(rotate != 1 && rotate != 0){
      printf("Please enter a valid input.\n");
      scanf("%d", &rotate);
    }


    if(rotate == 1){
      printf("How many degrees to the right would you like to rotate your rectangle? \n");
      scanf("%f", &vals[2]);
      while(vals[2] < 1 || vals[2] > 359){
        printf("Please enter a degree rotation between 1 degree and 359 degrees.\n");
        scanf("%f", &vals[2]);
      }
      //indicate rotation is TRUE
      vals[3] = 1;
    }
    validity = validate(3, vals);


  }else{
    //is a square; ifSquare = 1;
    printf("\nSide length(in inches): ");
    scanf("%f", &vals[0]);
    while(vals[0] >= 8.5 || vals[0] < 0){
      printf("The side length must be greater than 0 and less than 8.5. Please enter a valid input: ");
      scanf("%f", &vals[0]);
    }

    printf("Would you like to rotate your square? Enter 1 for YES or 0 for NO. \n");
    scanf("%d", &rotate);
    while(rotate != 1 && rotate != 0){
      printf("Please enter a valid input.\n");
      scanf("%d", &rotate);
    }


    if(rotate == 1){
      printf("How many degrees to the right would you like to rotate your square? \n");
      scanf("%f", &vals[1]);
      while(vals[1] < 1 || vals[1] > 359){
        printf("Please enter a degree rotation between 1 degree and 359 degrees.\n");
        scanf("%f", &vals[1]);
      }
      //indicate rotation is TRUE
      vals[2] = 1;
    }
    validity = validate(4, vals);

  }

  //ask for rotation
  //printf("Would you like to rotate the shape? Enter 1 for YES, 0 for NO.")
}

void circleDeclare(){
  //float radius;
  float vals[5];
  int validity;
  printf("What is the radius of your circle (in inches): ");
  scanf("%f", &vals[0]);
  while(vals[0] >= 8.5 || vals[0] < 0){
    printf("The side length must be greater than 0 and less than 8.5. Please enter a valid input: ");
    scanf("%f", &vals[0]);
  }
  validity = validate(5, vals);
}

void trapezoidDeclare(){

}

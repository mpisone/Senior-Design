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
  int choice, valid;
  //array for holding triangle values
  float vals[5];
  printf("\nHow would you like to define your triangle?\n");
  printf("1. Three Side Lengths\n2. SAS: Side Angle Side. Two sides and the included angle.\n3. ASA: Angle Side Angle. Two angles and the included side.\n");
  scanf("%d",&choice);

  printf("\nchoice = %d", choice);

  //get user inputs

  if(choice ==1){
    //3 Side Lengths
    printf("\n3 Side Lengths\n");
    printf("\nLength of side A(in inches): ");
    scanf("%f", &vals[0]);
    printf("\nLength of side B(in inches): ");
    scanf("%f", &vals[1]);
    printf("\nLength of side C(in inches): ");
    scanf("%f", &vals[2]);
    //TODO: Call to validate triangle inputs
    valid = validate(1, vals);

  }else if(choice ==2){
    //SAS
    printf("\nSide Angle Side\n");
    printf("\nLength of side A(in inches): ");
    scanf("%f", &vals[0]);
    printf("\nDegree of the included angle(in inches): ");
    scanf("%f", &vals[1]);
    printf("\nLength of side B(in inches): ");
    scanf("%f", &vals[2]);
    //TODO: Call to validate triangle inputs

  }else{
    //ASA
    printf("\nAngle Side Angle\n");
    printf("\nDegree of Angle 1 ");
    scanf("%f", &vals[0]);
    printf("\nLength of included side A: ");
    scanf("%f", &vals[1]);
    printf("\nDegree of Angle 2: ");
    scanf("%f", &vals[2]);
    //TODO: Call to validate triangle inputs

  }


  //return choice;
}

//For defining a rectanlge OR square
void rectangleDeclare(int ifSquare){
  float sideOne, sideTwo;
  //is a rectangle
  if(ifSquare == 0){
    printf("\nLength of side 1(in inches):\n");
    scanf("%f", &sideOne);
    printf("\nLength of side 2(in inches):\n");
    scanf("%f", &sideTwo);

  }else{
    //is a square; ifSquare = 1;
    printf("\nSide length(in inches):\n");
    scanf("%f", &sideOne);

  }

  //ask for rotation
}

void trapezoidDeclare(){

}

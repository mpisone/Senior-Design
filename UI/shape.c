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
  float vals[20];
  int rotate;
  printf("\nDefine your triangle?\n");
  printf("1. 2 Sides\n2. Side + Angle.\n");
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
    printf("Length of side C: ");
    scanf("%f", &vals[0]);
    while(vals[0] >= 8.5|| vals[0] < 0){
      //The side length must be less than 8.5 inches.
      printf("\nPlease enter a new value.");
      scanf("%f", &vals[0]);
    }
    //printf("%.2f", vals[0]);
    printf("Length of side B: ");
    scanf("%f", &vals[1]);
    while(vals[1] >= 8.5|| vals[1] < 0){
      //The side length must be less than 8.5 inches.
      printf("\nPlease enter a new value.\n");
      scanf("%f", &vals[1]);
    }
    printf("Rotate? Enter 1 for YES or 0 for NO. \n");
    scanf("%d", &rotate);
    while(rotate != 1 && rotate != 0){
      printf("Please enter a valid input.\n");
      scanf("%d", &rotate);
    }


    if(rotate == 1){
      printf("Rotation: 45,90,135,180,225,270,315 \n");
      scanf("%f", &vals[4]);
      while(vals[4] != 45 && vals[4] != 90 && vals[4] != 135 && vals[4] != 180 && vals[4] != 225 && vals[4] != 270 && vals[4] != 315){
        printf("Please enter a valid input.\n");
        scanf("%f", &vals[4]);
      }
      //indicate rotation is TRUE
      vals[5] = 1;
    }

    //find length of side c
    validity = validate(1, vals);

  }else{
    //SAS
    printf("\nRight Triangle by Side Angle\n");
    printf("\nLength of side C: ");
    scanf("%f", &vals[0]);
    while(vals[0] >= 8.5 || vals[0] < 0){
      //The side length must be less than 8.5 inches and larger than 0.
      printf(" Please enter a new value.\n");
      scanf("%f", &vals[0]);
    }
    printf("Degree of the angle(in degrees): ");
    scanf("%f", &vals[1]);
    while(vals[1] >= 90|| vals[1] < 0){
      //The angle must be smaller that 90 Degrees and larger than 0.
      printf("Please enter a new value.\n");
      scanf("%f", &vals[1]);
    }
    printf("Rotate? Enter 1 for YES or 0 for NO. \n");
    scanf("%d", &rotate);
    while(rotate != 1 && rotate != 0){
      printf("Please enter a valid input.\n");
      scanf("%d", &rotate);
    }


    if(rotate == 1){
      printf("Rotation: 45,90,135,180,225,270,315 \n");
      scanf("%f", &vals[4]);
      while(vals[4] != 45 && vals[4] != 90 && vals[4] != 135 && vals[4] != 180 && vals[4] != 225 && vals[4] != 270 && vals[4] != 315){
        printf("Please enter a valid input.\n");
        scanf("%f", &vals[4]);
      }
      //indicate rotation is TRUE
      vals[5] = 1;
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
    printf("\nLength of side 1: ");
    scanf("%f", &vals[0]);
    while(vals[0] >= 8.5|| vals[0] < 0){
      //The side length must be less than 8.5 inches and larger than 0.
      printf("Please enter a new value.\n");
      scanf("%f", &vals[0]);
    }
    printf("Length of side 2: ");
    scanf("%f", &vals[1]);
    while(vals[1] >= 8.5|| vals[1] < 0){
      //The side length must be less than 8.5 inches and larger than 0.
      printf("Please enter a new value.\n");
      scanf("%f", &vals[1]);
    }
    printf("Rotate? Enter 1 for YES or 0 for NO. \n");
    scanf("%d", &rotate);
    while(rotate != 1 && rotate != 0){
      printf("Please enter a valid input.\n");
      scanf("%d", &rotate);
    }


    if(rotate == 1){
      printf("Rotation: 45,90,135,180,225,270,315 \n");
      scanf("%f", &vals[2]);
      while(vals[2] != 45 && vals[2] != 90 && vals[2] != 135 && vals[2] != 180 && vals[2] != 225 && vals[2] != 270 && vals[2] != 315){
        printf("Please enter a valid input.\n");
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
      //The side length must be greater than 0 and less than 8.5.
      printf("Please enter a valid input: ");
      scanf("%f", &vals[0]);
    }

    printf("Would you like to rotate your square? Enter 1 for YES or 0 for NO. \n");
    scanf("%d", &rotate);
    while(rotate != 1 && rotate != 0){
      printf("Please enter a valid input.\n");
      scanf("%d", &rotate);
    }

    printf("X starting point: ");
    scanf("%f", &vals[3]);

    printf("Y starting point: ");
    scanf("%f", &vals[4]);


    if(rotate == 1){
      printf("Rotation: 45,90,135,180,225,270,315 \n");
      scanf("%f", &vals[2]);
      while(vals[2] != 45 && vals[2] != 90 && vals[2] != 135 && vals[2] != 180 && vals[2] != 225 && vals[2] != 270 && vals[2] != 315){
        printf("Please enter a valid input.\n");
        scanf("%f", &vals[2]);
      }
      //indicate rotation is TRUE
      vals[2] = 1;
    }
    validity = validate(4, vals);

  }

  //ask for rotation
  //printf("Would you like to rotate the shape? Enter 1 for YES, 0 for NO.")
}

void ellipseDeclare(){
  //float radius;
  float vals[5];
  int validity;
  printf("What is the radius y: ");
  scanf("%f", &vals[0]);
  while(vals[0] >= 8.5 || vals[0] < 0){
    //The side length must be greater than 0 and less than 8.5.
    printf("Please enter a valid input: ");
    scanf("%f", &vals[0]);
  }

  printf("What is the radius x: ");
  scanf("%f", &vals[1]);
  while(vals[1] >= 8.5 || vals[1] < 0){
    //The side length must be greater than 0 and less than 8.5.
    printf("Please enter a valid input: ");
    scanf("%f", &vals[1]);
  }

  printf("X starting point: ");
  scanf("%f", &vals[2]);

  printf("Y starting point: ");
  scanf("%f", &vals[3]);



  validity = validate(5, vals);
}

void trapezoidDeclare(){

}

//Senior Design Fall 2021
//Written By Madison Pisone
//Shape Framework File
//Need to use mathmatical equations to verify valid inputs

#include <stdio.h>
#include <stdlib.h>
//#include "shape.h"
#include <math.h>

//shape.c
void triangleDeclare(void);
//use same method for rectangle +  square
void rectangleDeclare(int ifSquare);
void ellipseDeclare(void);

//validate.c
void validate(int whichShape, float vals[]);
//void Confirmation(int whichShape, float vals[]);

void rotate(void);
void center(void);
void HandW(void);

//Global Variables
float vals[20];
int choice, validity;

void triangleDeclare(){
  //TRIANGLE
  //find center points
  center();
  //Declare side lengths
  HandW();
  rotate();
  validate(1, vals);
}

//For defining a rectanlge OR square
void rectangleDeclare(int ifSquare){

  if(ifSquare == 0){
    //RECTANGLE
    //find center points
    center();
    //Declare side lengths
    HandW();
    rotate();
    validate(2, vals);
  }else{
    //SQUARE
    //find center points
    center();
    //Declare side length
    //Sides = vals[0]
    printf("Side Length: ");
    scanf("%f", &vals[0]);
    while(vals[0] >= 8.5|| vals[0] < 0){
      //The side length must be less than 8.5 inches.
      printf("\nPlease enter a new value.");
      scanf("%f", &vals[0]);
    }
    vals[1] = vals[0];
    rotate();
    validate(3, vals);
  }

}

void ellipseDeclare(){
  //ELLIPSE
  center();
  //Declare Radius lengths
  HandW();
  rotate();
  validate(4, vals);
}

void HandW(){
  //Height = Y radius = vals[0]
  //Width = X radius = vals[1]
  printf("Height: ");
  scanf("%f", &vals[0]);
  while(vals[0] >= 8.5|| vals[0] < 0){
    //The side length must be less than 8.5 inches.
    printf("\nPlease enter a new value.");
    scanf("%f", &vals[0]);
  }
  printf("Width: ");
  scanf("%f", &vals[1]);
  while(vals[1] >= 8.5|| vals[1] < 0){
    //The side length must be less than 8.5 inches.
    printf("\nPlease enter a new value.\n");
    scanf("%f", &vals[1]);
  }
}

void center(){
  //Starting Coordinates
  printf("\nCX: ");
  scanf("%f", &vals[3]);
  printf("CY: ");
  scanf("%f", &vals[4]);
}

void rotate(){
  //Rotation Degree = vals[2]
  printf("Rotation Deg: ");
  scanf("%f", &vals[2]);
  while(vals[2] < 0 || vals[2] > 360){
    printf("Please enter a valid input.\n");
    scanf("%f", &vals[2]);
  }
}

void validate(int whichShape, float vals[]){
  float h = vals[0],w = vals[1], a = vals[2], cx = vals[3], cy = vals[4];

  if(whichShape == 1){
    //TRIANGLE
    //Find initial triangle before Rotation
    float A1x = cx;
    float A1y = cy + (cy/2.0);

    float B1x = cx - (cx/2.0);
    float B1y = cy - (cy/2.0);

    float C1x = cx + (cx/2.0);
    float C1y = cy - (cy/2.0);

    //convert degree to radians
    a = a * (M_PI/180.0);
    //Find points after rotation
    float A2x = cos(a)*(A1x-cx)-sin(a)*(A1y-cy)+cx;
    float A2y = sin(a)*(A1x-cx)+cos(a)*(A1y-cy)+cy;

    float B2x = cos(a)*(B1x-cx)-sin(a)*(B1y-cy)+cx;
    float B2y = sin(a)*(B1x-cx)+cos(a)*(B1y-cy)+cy;

    float C2x = cos(a)*(C1x-cx)-sin(a)*(C1y-cy)+cx;
    float C2y = sin(a)*(C1x-cx)+cos(a)*(C1y-cy)+cy;




    printf("a1x = %f\na1y = %f\nb1x = %f\nb1y = %f\nc1x = %f\nc1y = %f\ndeg = %f\nrad = %f", A1x,A1y,B1x,B1y,C1x,C1y,vals[2],a);
    printf("\n\na2x = %f\na2y = %f\nb2x = %f\nb2y = %f\nc2x = %f\nc2y = %f", A2x,A2y,B2x,B2y,C2x,C2y);

  }else if(whichShape == 2 || whichShape == 3){
    //Rectangle + Square
    //float h = vals[0],w = vals[1], a = vals[2], cx = vals[3], cy = vals[4];

    //convert angle to radians for c
    a = a * (M_PI/180.0);

    //top right vertex
    float tRx = cx + ((w/2.0)*cos(a))-((h/2.0)*sin(a));
    float tRy = cy + ((w/2.0)*sin(a))+((h/2.0)*cos(a));

    //top left vertex
    float tLx = cx - ((w/2.0)*cos(a))-((h/2.0)*sin(a));
    float tLy = cy - ((w/2.0)*sin(a))+((h/2.0)*cos(a));

    //bottom left vertex
    float bLx = cx - ((w/2.0)*cos(a))+((h/2.0)*sin(a));
    float bLy = cy - ((w/2.0)*sin(a))-((h/2.0)*cos(a));

    //bottom right vertex
    float bRx = cx + ((w/2.0)*cos(a))+((h/2.0)*sin(a));
    float bRy = cy + ((w/2.0)*sin(a))-((h/2.0)*cos(a));


    vals[5] = tRx;
    vals[6] = tRy;
    vals[7] = tLx;
    vals[8] = tLy;
    vals[9] = bLx;
    vals[10] = bLy;
    vals[11] = bRx;
    vals[12] = bRy;

    printf("tRx = %f\ntRy = %f\ntLx = %f\ntLy = %f\nbLx = %f\nbLy = %f\nbRx = %f\nbRy = %f\n", tRx, tRy, tLx, tLy, bLx, bLy, bRx, bRy);
  }
}

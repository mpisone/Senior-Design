//Senior Design Fall 2021
//Written By Madison Pisone
//Shape Framework File
/*

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#define M_PI 3.14

//Shape verification methods
void triangleDeclare(void);
void rectangleDeclare(int ifSquare);
void ellipseDeclare(void);
void validate(int whichShape, float vals[]);
void rotate(void);
void center(void);
void HandW(void);

//Global Variables
float vals[20];
int choice, validity;


void HandW(void){
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

void center(void){
  //Starting Coordinates
  printf("\nCX: ");
  scanf("%f", &vals[3]);
  printf("CY: ");
  scanf("%f", &vals[4]);
}

void rotate(void){
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

    //convert to radians
    a = a * (M_PI/180);

    //point a before Rotation
    float a1 = cx;
    float a2 = cy + (h/2);

    float Ax = cos(a)*cx - sin(a)*cy;
    float Ay = (h/2)+cos(a)*cx + sin(a)*cy;

    float Bx = cx + cos(a)*(-h/2) - sin(a)*(-w/2);
    float By = cy + cos(a)*(-h/2) + sin(a)*(-w/2);

    float Cx = cx + cos(a)*(-h/2) - sin(a)*(w/2);
    float Cy = cy + cos(a)*(-h/2) + sin(a)*(w/2);

    printf("ax = %f\nay = %f\nbx = %f\nby = %f\ncx = %f\ncy = %f", Ax,Ay,Bx,By,Cx,Cy);

  }else if(whichShape == 2 || whichShape == 3){
    //Rectangle + Square
    //float h = vals[0],w = vals[1], a = vals[2], cx = vals[3], cy = vals[4];

    //convert angle to radians for c
    a = a * (M_PI/180);

    //top right vertex
    float tRx = cx + ((w/2)*cos(a))-((h/2)*cos(a));
    float tRy = cy + ((w/2)*cos(a))+((h/2)*cos(a));

    //top left vertex
    float tLx = cx - ((w/2)*cos(a))-((h/2)*cos(a));
    float tLy = cy - ((w/2)*cos(a))+((h/2)*cos(a));

    //bottom left vertex
    float bLx = cx - ((w/2)*cos(a))+((h/2)*cos(a));
    float bLy = cy - ((w/2)*cos(a))-((h/2)*cos(a));

    //bottom right vertex
    float bRx = cx + ((w/2)*cos(a))+((h/2)*cos(a));
    float bRy = cy + ((w/2)*cos(a))-((h/2)*cos(a));

    vals[0] = tRx;
    vals[1] = tRy;
    vals[2] = tLx;
    vals[3] = tLy;
    vals[4] = bLx;
    vals[5] = bLy;
    vals[6] = bRx;
    vals[7] = bRy;
    printf("tRx = %f\ntRy = %f\ntLx = %f\ntLy = %f\nbLx = %f\nbLy = %f\nbRx = %f\nbRy = %f\n", tRx, tRy, tLx, tLy, bLx, bLy, bRx, bRy);
  }
}

void triangleDeclare(void){
  //TRIANGLE
  //find center points
  center();
  //Declare side lengths
  HandW();
  rotate();
  validate(1, vals);
}

//For defining a rectangle OR square
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

void ellipseDeclare(void){
  //ELLIPSE
  center();
  //Declare Radius lengths
  HandW();
  rotate();
  validate(4, vals);
}
*/
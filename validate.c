//Senior Design Fall 2021
//Written By Madison Pisone
//File for validating all shape inputs to make sure it is a legal shape.

#include <stdio.h>
#include <stdlib.h>
#include "shape.h"
#include <math.h>

//return 1 for valid Shape
//return 0 for invalid shape
int validate(int whichShape, float vals[]){
  int valid;

  if(whichShape == 1){
    //Triangle 2 sides
    //a^2 + b^2 = c^2
    float a = vals[0];
    float b = vals[1];
    float c;
    c = pow(a,2)+pow(b,2);
    vals[2] = sqrt(c);

    //Heron's formula
    float p = a+b+c; //perimeter
    float area = sqrt(p*(p-a)*(p-b)*(p-c));
    float height = 2*(area*a);
    printf("\nCongratulations, the robot will draw your triangle of dimensions:\nSide A = %.2f inches, Side B = %.2f inches, and side C = %.2f inches\n", vals[0], vals[1], vals[2]);
    valid = 1;
    return valid;
  }else if(whichShape ==2){
    //Triangle by SAS
    float c = vals[0];
    float degrees = vals[1];
    float radians = degrees * M_PI/ 180.0;
    //side a
    vals[2] = c * sin(radians);
    //side b
    vals[3] = c*cos(radians);
    printf("\nCongratulations, the robot will draw your triangle of dimensions:\nSide A = %.2f inches, Side B = %.2f inches, and side C = %.2f inches\n", vals[2], vals[3], vals[0]);
    return 1;

  }else if(whichShape == 3){
    //RECTANGLE
    //side length 1 = vals[0]
    //side length 2 = vals[1]
    printf("\nCongratulations, the robot will draw your reactangle of dimensions:\nSide 1 = %.2f inches, Side 2 = %.2f inches. ", vals[0], vals[1]);
    if(vals[3] == 1){
      printf("And a degree rotation of %.2f degrees\n", vals[2]);
    }
    return 1;
  }else if(whichShape == 4){
    //SQUARE
    //side length = vals[0]
    printf("\nCongratulations, the robot will draw your square of dimensions:\nSide 1 = %.2f inches, Side 2 = %.2f inches. ", vals[0], vals[0]);
    if(vals[2] == 1){
      printf("And a degree rotation of %.2f degrees\n", vals[1]);
    }
    return 1;
  }else{
    //CIRCLE
    //radius = vals[0]
    printf("\nCongratulations, the robot will draw you circle of radius %.2f inches. \n", vals[0]);
    return 1;
  }


  return valid;
}
/*
float toDraw(){
  float x, y;
  float vals[10];
  //vals[4] = x
  //vals[5] = y
  printf("Where on the paper would you like to draw your shape?\nX-coordinate: ");
  scanf("%f", &vals[4]);
  while(vals[4] < 2 || vals[4] > 7){
    printf("Please enter a value between 2 and 7.\n");
    scanf("%f", &vals[4]);
  }
  printf("Y-coordinate: ");
  scanf("%f", &vals[5]);
  while(vals[5] < 2 || vals[5] > 7){
    printf("Please enter a value between 2 and 7.\n");
    scanf("%f", &vals[5]);
  }
  return vals[];
}
*/
/*
void printTriangle(float height){
  char printLine[200];
  for(int i=1; i<=height; i++){
    printLine[i] = "";
    for(int j = height - i; j>0; j--){
      printLine[j] += " ";
    }
    for(int j=i*2-1; j>0; j--){
      printLine[j] += "x";
    }
    printf("%s", printLine);
  }
}
*/

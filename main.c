//Senior Design Fall 2021
//Written By Madison Pisone
//main file for housing the User Interface for a Robotic Arm for Drawing 2D Geometric Shapes

#include <stdio.h>
#include <stdlib.h>
#include "shape.h"
#include "shape.c"
#include "validate.c"


int main(void){
  int shape, options = 4, ifSquare;

  printf("\nRobotic Arm for Drawing 2D Geometric Shapes\n");
  printf("Welcome! What shape would you like to draw?\n");
  printf("1. Triangle\n2. Rectangle\n3. Square\n4. Trapezoid\n5. Ellipse\n");
  scanf("%d", &shape);


  //error check for user input
  while(shape < 0 && shape > options){
    printf("Please enter a t value between 1 and 4: ");
    scanf("%d", &shape);
  }

  if(shape == 1){
    //triangle
    triangleDeclare();

  }else if(shape ==2){
    //rectangle
    ifSquare = 0;
    rectangleDeclare(ifSquare);

  }else if(shape ==3){
    //square
    ifSquare = 1;
    rectangleDeclare(ifSquare);

  }else if(shape ==4){
    //trapezoid
    trapezoidDeclare();
  }else{
    //ellipse

  }

}

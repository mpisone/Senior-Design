//Senior Design Fall 2021
//Written By Madison Pisone

#include <stdio.h>
#include <stdlib.h>
#include "shape.h"
#include "triangle.c"


int main(void){
  int shape, options = 4;


  printf("\nRobotic Arm for Drawing 2D geometric shapes\n");
  printf("Welcome! What shape would you like to draw?\n");
  printf("1. Triangle\n2. Rectangle\n3. Trapezoid\n4. Ellipse\n");
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

  }else if(shape ==3){
    //square

  }else{
    //ellipse

  }

}

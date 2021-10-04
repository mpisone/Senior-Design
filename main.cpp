//Senior Design Fall 2021
//Written By Madison Pisone

#include <stdio.h>
#include <stdlib.h>

void main(){
  int shape, options = 4;


  printf("Robotic Arm for Drawing 2D geometric shapes\n")
  printf("Welcome! What shape would you like to draw?\n");
  printf("1. Triangle\n2. Rectangle\n3. Trapezoid4. Ellipse\n");
  scanf("%d", &shape);

  //error check for user input
  while(shape == NULL || shape < 0 && shape > options){
    printf("Please enter a t value between 1 and 4: ");
    scanf("%f", &shape);
  }


  if(shape == 1){
    //triangle

  }else if(shape ==2){
    //rectangle

  }else if(shape ==3){
    //square

  }else{
    //ellipse

  }

  switch(shape)
  {
    //triangle
    case 1:

      break;

    //rectangle
    case 2:
      break;

    //trapezoid
    case 3:
      break;

    //ellipse
    case 4:
      break;
  }
}

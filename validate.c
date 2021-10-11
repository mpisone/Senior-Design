//Senior Design Fall 2021
//Written By Madison Pisone
//File for validating all shape inputs to make sure it is a legal shape.

#include <stdio.h>
#include <stdlib.h>
#include "shape.h"

//return 1 for valid Shape
//return 0 for invalid shape
int validate(int whichShape, float vals[]){
  int valid;

  if(whichShape == 1){
    //Triangle 3 sides
    //a^2 + b^2 = c^2
  }
  valid = 1;
  printf("the validity is %d", valid);
  return valid;


}

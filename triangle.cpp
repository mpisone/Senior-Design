//Senior Design Fall 2021
//Written By Madison Pisone
//Triangle Framework File

#include <stdio.h>
#include <stdlib.h>

//Have user decide how they want to define their triangle
//return their choice (int)
//1 = 3 Side Lengths
//2 = SAS: Side Angle Side
//3 = ASA: Angle Side Angle
int triangleDeclare(){
  int choice;

  printf("How would you like to define your triangle?\n");
  printf("1. 3 Side Lengths\n\
  2. SAS: Side Angle Side. Two sides and the included angle.\n\
  3. ASA: Angle Side Angle. Two angles and the included side.\n");
  scanf("%d",&choice);

  return choice;
}

//Senior Design Fall 2021
//Written By Madison Pisone
//File for declaring functions needed throughout the project

#ifndef SHAPE_H
#define SHAPE_H

#include <stdio.h>
#include <stdlib.h>

void triangleDeclare(void);
//use same method for rectangle +  square
void rectangleDeclare(int ifSquare);
void trapezoidDeclare(void);
int validate(int whichShape, float vals[]);


#endif

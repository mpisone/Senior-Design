//Senior Design Fall 2021
//Written By Madison Pisone
//File for declaring functions needed throughout the project

#ifndef SHAPE_H
#define SHAPE_H

#include <stdio.h>
#include <stdlib.h>

//shape.c
void triangleDeclare(void);
//use same method for rectangle +  square
void rectangleDeclare(int ifSquare);
void ellipseDeclare(void);

//validate.c
void validate(int whichShape, float vals[]);
void Confirmation(int whichShape, float vals[]);

void rotate(void);
void center(void);
void HandW(void);


#endif

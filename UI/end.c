//Senior Design Fall 2021
//Written By Madison Pisone
//File for validating all shape inputs to make sure it is a legal shape.

#include <stdio.h>
#include <stdlib.h>
#include "shape.h"
#include <math.h>
//#include <graphics.h>

//return 1 for valid Shape
//return 0 for invalid shape
//assuming starting point of 1,1
void Confirmation(int whichShape, float vals[]){
  float points[100];
  #define PI 3.142857

  if(whichShape == 1){
    //Triangle 2 sides
    //a^2 + b^2 = c^2
    float a = vals[0];
    float b = vals[1];
    float c;
    c = pow(a,2)+pow(b,2);
    vals[5] = sqrt(c);

    //Heron's formula
    float p = a+b+c; //perimeter
    float area = sqrt(p*(p-a)*(p-b)*(p-c));
    float height = 2*(area*a);

    printf("\nCongratulations, the robot will draw your triangle of dimensions:\nSide A = %.2f inches, Side B = %.2f inches, and side C = %.2f inches\n", vals[0], vals[1], vals[5]);
    printf("And a degree rotation of %.2f degrees\n", vals[2]);

  }else if(whichShape == 2){
    //RECTANGLE
    //side length 1 = vals[0]
    //side length 2 = vals[1]
    //rotation degree = vals[3]
    printf("\nCongratulations, the robot will draw your reactangle of dimensions:\nSide A = %.2f inches, Side B = %.2f inches. ", vals[0], vals[1]);
    printf("And a degree rotation of %.2f degrees\n", vals[2]);
  }else if(whichShape == 3){
    //SQUARE
    //side length = vals[0]
    //rotation degree = vals[3]
    printf("\nCongratulations, the robot will draw your square of dimensions:\nSide A = %.2f inches, Side B = %.2f inches. ", vals[0], vals[0]);
    printf("And a degree rotation of %.2f degrees\n", vals[2]);

  }else{
    //ELLIPSE
    //radius = vals[0]
    /*
    step = 2*PI/20;
    //step = 15;
    //radius
    r = vals[0];
    //starting x, center
    h = vals[1];
    //starting y, center
    k = vals[2];

    printf("\nPoints to draw: \n");
    for(theta = 0; theta < 2*PI; theta+=step){
      x = h + r*cos(theta);
      y = k - 0.5*r*cos(theta);
      printf("(%.2f, %.2f)\n", x, y);
    }
    */

    //float theta, h, k, step, x, y, r;
    //amount added to theta each time


    float dx, dy, d1, d2, x, y, rx, ry, xc, yc;
    ry = vals[0];
    rx = vals[1];
    xc = vals[3];
    yc = vals[4];
    x = 0;
    y = ry;


    // Initial decision parameter of region 1
    d1 = (ry * ry)
         - (rx * rx * ry)
         + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // For region 1
    while (dx < dy) {

        // Print points based on 4-way symmetry
        printf("(%.2f, %.2f)\n", x + xc, y + yc);
        printf("(%.2f, %.2f)\n", -x + xc, y + yc);
        printf("(%.2f, %.2f)\n", x + xc, -y + yc);
        printf("(%.2f, %.2f)\n", -x + xc, -y + yc);

        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0) {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5)))
         + ((rx * rx) * ((y - 1) * (y - 1)))
         - (rx * rx * ry * ry);

    // Plotting points of region 2
    while (y >= 0) {

        // printing points based on 4-way symmetry
        printf("(%.2f, %.2f)\n", x + xc, y + yc);
        printf("(%.2f, %.2f)\n", -x + xc, y + yc);
        printf("(%.2f, %.2f)\n", x + xc, -y + yc);
        printf("(%.2f, %.2f)\n", -x + xc, -y + yc);

        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0) {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }


    printf("\nCongratulations, the robot will draw you ellipse of y radius %.2f inches and x radius %.2f\n", vals[0], vals[1]);
    printf("And a degree rotation of %.2f degrees\n", vals[2]);
  }
}

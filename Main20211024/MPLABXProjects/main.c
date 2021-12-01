/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ256GA702
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
/** These 3 lines are from 1st try at LCD with Dan
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/interrupt_manager.h"
*/
#include <xc.h>
#include "shape.c"
#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SDA _RB14 //changed this for my Pic 24
#define SCL _RB13 //changed this for my Pic 24
#define SDA_DIR _TRISB14 //changed this for my Pic 24
#define SCL_DIR _TRISB13 //changed this for my Pic 24
#define Set_SDA_Low		SDA_DIR = 0
#define Set_SDA_High	SDA_DIR = 1
#define Set_SCL_Low		SCL_DIR = 0
#define Set_SCL_High	SCL_DIR = 1
#define LCDRST _RB12


//#define _XTAL_FREQ 64000000
#define FCY 8000000UL
#include <libpic30.h>

int update_direction1(_Bool direction);
int pulse_ntimes1(int n);
int update_direction2(_Bool direction);
int pulse_ntimes2(int n);
int pulse_simultaneous_ntimes(int n);

void delay_cycles(int cycles);
void init_I2C();
void init_LCD();
void I2C_out(unsigned char);
void I2C_Start();
void I2C_Stop();
void clear_LCD();
void move_cursor(unsigned char, unsigned char);
void reset_cursor();
void Show(unsigned char *);


//Shape verification methods
void triangleDeclare(void);
void rectangleDeclare(int ifSquare);
void ellipseDeclare(void);
void validate(int whichShape, double vals[]);
void rotate(void);
void center(void);
void HandW(void);

//Global Variables
#define M_PI 3.14
double vals[20];
int choice, validity;
int i2c_delay;
int counter;
unsigned char buffer[20];
// Define parameters for motor control
int headingVectorInt[2], ind, ind2, ind3, tempValA, tempValB, tempVal, tempValMin, tempValMax, numDP, a, b;
int ratGCD, tempN, tempD;
double delayX, delayY, startX, startY, endX, endY, headingVector[2], Nx, Ny, pitch, stepSize; //delay in ms and start/end in inches
double headingFrac, factor, ratInt, ratDec, Val, roundVal, countX, countY;
_Bool directionX, directionY, clockwise, counter_clockwise; //0 for CW?, 1 for CCW?

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
void validate(int whichShape, double vals[]){
  double h = vals[0],w = vals[1], a = vals[2], cx = vals[3], cy = vals[4];

  if(whichShape == 1){
    //TRIANGLE

    //convert to radians
    a = a * (M_PI/180);

    //point a before Rotation
    double a1 = cx;
    double a2 = cy + (h/2);

    double Ax = cos(a)*cx - sin(a)*cy;
    double Ay = (h/2)+cos(a)*cx + sin(a)*cy;

    double Bx = cx + cos(a)*(-h/2) - sin(a)*(-w/2);
    double By = cy + cos(a)*(-h/2) + sin(a)*(-w/2);

    double Cx = cx + cos(a)*(-h/2) - sin(a)*(w/2);
    double Cy = cy + cos(a)*(-h/2) + sin(a)*(w/2);

    printf("ax = %f\nay = %f\nbx = %f\nby = %f\ncx = %f\ncy = %f", Ax,Ay,Bx,By,Cx,Cy);

  }else if(whichShape == 2 || whichShape == 3){
    //Rectangle + Square
    //float h = vals[0],w = vals[1], a = vals[2], cx = vals[3], cy = vals[4];

    //convert angle to radians for c
    a = a * (M_PI/180);

    //top right vertex
    double tRx = cx + ((w/2)*cos(a))-((h/2)*cos(a));
    double tRy = cy + ((w/2)*cos(a))+((h/2)*cos(a));

    //top left vertex
    double tLx = cx - ((w/2)*cos(a))-((h/2)*cos(a));
    double tLy = cy - ((w/2)*cos(a))+((h/2)*cos(a));

    //bottom left vertex
    double bLx = cx - ((w/2)*cos(a))+((h/2)*cos(a));
    double bLy = cy - ((w/2)*cos(a))-((h/2)*cos(a));

    //bottom right vertex
    double bRx = cx + ((w/2)*cos(a))+((h/2)*cos(a));
    double bRy = cy + ((w/2)*cos(a))-((h/2)*cos(a));

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

int update_direction1(_Bool direction)
{
    _RB7 = direction;
    __delay_ms(5);
    return 0;
}

int pulse_ntimes1(int n)
{
    while (n > 0)
    {
        _RB6 = 1;
        __delay_ms(1);
        _RB6 = 0;
        __delay_ms(1);
        n = n-1;
    }
    return 0;
}
int update_direction2(_Bool direction)
{
    _RB11 = direction;
    __delay_ms(5);
    return 0;
}

int pulse_ntimes2(int n)
{
    while (n > 0)
    {
        _RB10 = 1;
        __delay_ms(1);
        _RB10 = 0;
        __delay_ms(1);
        n = n-1;
    }
    return 0;
}

int pulse_simultaneous_ntimes(int n)
{
    while (n > 0)
    {
        _RB10 = 1;
        _RB6 = 1;
        __delay_ms(1);
        _RB10 = 0;
        _RB6 = 0;
        __delay_ms(1);
        n = n-1;
    }
    return 0;
}

//the function below will move the cursor to a desired location.
//line input is zero-referenced (i.e. line = 0 -> top line, line = 1 -> bottom line)
//x is the x-position of the cursor.
void move_cursor(unsigned char line,unsigned char x)
{

    unsigned char out = 0x00;
    if (line == 1)
    {
        out = 0x40 + 0x80 + x;

    }
    else
    {
        out = 0x00 + 0x80 + x;
    }

    I2C_Start();
    I2C_out(0x78);//Slave=0x78
    I2C_out(0x00);//Comsend = 0x00
    I2C_out(out);//Comsend = 0x01
    I2C_Stop();

}

void clear_LCD()
{
    I2C_Start();
    I2C_out(0x78);//Slave=0x78
    I2C_out(0x00);//Comsend = 0x00
    I2C_out(0x01);//Comsend = 0x01
    I2C_Stop();
}


void reset_cursor()
{
    I2C_Start();
    I2C_out(0x78);//Slave=0x78
    I2C_out(0x00);//Comsend = 0x00
    I2C_out(0x02);//Comsend = 0x02
    I2C_Stop();
}

void init_I2C()
{

    LCDRST = 0; //reset the LCD module.
    delay_cycles(20000);
    LCDRST = 1; //pull LCD module out of reset

    SDA = 0;
    SCL = 0;
    Set_SDA_Low; //macro to pull down I2C data line. Set to output.
    Set_SCL_Low; //macro to pull down I2C clock line. Set to output.
}

void init_LCD()
{
    I2C_Start();
    I2C_out(0x78);//Slave=0x78
    I2C_out(0x00);//Comsend = 0x00
    I2C_out(0x38);
    delay_cycles(1000);
    I2C_out(0x39);
    delay_cycles(1000);
    I2C_out(0x14);
    I2C_out(0x78);
    I2C_out(0x5E);
    I2C_out(0x6D);
    I2C_out(0x0C);
    I2C_out(0x01);
    I2C_out(0x06);
    delay_cycles(1000);
    I2C_Stop();
    delay_cycles(10000);

}

void delay_cycles(int cycles)
{
    while(cycles > 0)
    {
        //cycles = cycles;
        cycles = cycles - 1;

    }

    return;

}

void I2C_out(unsigned char Byte) //I2C Output
{
	unsigned char i;		// Variable to be used in for loop

	for(i=0;i<8;i++)		// Repeat for every bit
	{
		Set_SCL_Low;		// Make SCL pin low

		delay_cycles(i2c_delay/2);	// Data pin should change it's value,
									// when it is confirm that SCL is low

		if((Byte<<i)&0x80)  // Place data bit value on SDA pin
			Set_SDA_High;	// If bit is high, make SDA high
		else				// Data is transferred MSB first
			Set_SDA_Low;	// If bit is low, make SDA low

		delay_cycles(i2c_delay/2);	// Toggle SCL pin
		Set_SCL_High;				// So that slave can
		delay_cycles(i2c_delay);	// latch data bit
    }

	// Get ACK from slave
	Set_SCL_Low;
    Set_SDA_High;
    delay_cycles(i2c_delay);
    Set_SCL_High;
    delay_cycles(i2c_delay);
}

/****************************************************
* I2C Start *
*****************************************************/
void I2C_Start(void)
{
	SDA = 0;	// Write zero in output register
	SCL = 0;	// of SDA and SCL pin

	Set_SCL_High;				// Make SCL pin high
	Set_SDA_High;				// Make SDA pin High
	delay_cycles(i2c_delay);	// Half bit delay
	Set_SDA_Low;				// Make SDA Low
	delay_cycles(i2c_delay);	// Half bit delay
}
/*****************************************************/
/****************************************************
* I2C Stop *
*****************************************************/
void I2C_Stop(void)
{
	Set_SCL_Low;				// Make SCL pin low

	delay_cycles(i2c_delay/2);	// Data pin should change it's value,
								// when it is confirm that SCL is low
	Set_SDA_Low;				// Make SDA pin low

	delay_cycles(i2c_delay/2);	// 1/4 bit delay
	Set_SCL_High;				// Make SCL pin high
	delay_cycles(i2c_delay/2);	// 1/4 bit delay
	Set_SDA_High;				// Make SDA high
	delay_cycles(i2c_delay/2);	// 1/4 bit delay
    delay_cycles(20);
    Set_SDA_Low;
    Set_SCL_Low;
}
/*****************************************************/
/****************************************************
* Send string of ASCII data to LCD *
*****************************************************/
void Show(unsigned char *text)
{
    int n,d;
    d=0x00;
    I2C_Start();
    I2C_out(0x78); //Slave=0x78
    I2C_out(0x40);//Datasend=0x40
    for(n=0;n<20;n++)
    {
        I2C_out(*text);
        ++text;
    }
    I2C_Stop();
}

void controlLoop(double startX, double startY, double endX, double endY){
    //********* Open Loop Control *********


		//General Parameters
		pitch = 1/1.25;
		Nx = 2*M_PI*pitch;
		Ny = 2*M_PI*pitch;
		stepSize = 1.8*M_PI/180;
		clockwise = 1;
		counter_clockwise = 0;


		// Desired heading
		headingVector[0] = endX - startX;
		headingVector[1] = endY - startY;


		// Motor Direction
		// X Motor
		if (headingVector[0] > 0)
		{
			directionX = clockwise;
		}
		else if (headingVector[0] < 0)
		{
			directionX = counter_clockwise;
		}
		else //headingVector[1] == 0
		{
			directionX = clockwise;
		}

		// Y Motor
		if (headingVector[1] > 0)
		{
			directionY = clockwise;
		}
		else if (headingVector[1] < 0)
		{
			directionY = counter_clockwise;
		}
		else //headingVector[2] == 0
		{
			directionY = clockwise;
		}


		//_RB7 = directionX;
        _RB7 = 1;
        __delay_ms(5);
		//_RB11 = directionY;
        _RB11 = 1;
        __delay_ms(5);


        // Motor step count
		countX = headingVector[0]*25.4*Nx/stepSize;
		countY = headingVector[1]*25.4*Ny/stepSize;


        // Motor Speed
		// calculate relative number of steps for x vs y

		// convert heading in inches to be whole numbers (1/4 inch is smallest interval of shape placement)
		// absolute value since direction is already set
		//headingVectorInt = 4*abs(headingVector);
        
        numDP = 2;
        headingFrac = abs(round(countX/countY * pow(10,numDP-1)/ pow(10,numDP-1)));
        factor = pow(10,numDP*2);
        ratInt = floor(headingFrac);
        ratDec = headingFrac - ratInt;
        ratGCD = gcd((int) ratDec*factor, (int) factor);
        tempN = ratDec*factor/ratGCD;
        tempD = factor/ratGCD;
        headingVectorInt[0] = ratInt*tempD + tempN;
        headingVectorInt[1] = tempD;
        
        

		// cycle for the total number of steps necessary
        tempValA = countX/headingVectorInt[0];
        tempValB = countY/headingVectorInt[1];
        if (tempValA > tempValB)
        {
            tempVal = tempValA;
        }
        else
        {
            tempVal = tempValB;
        }
        
        if (headingVectorInt[0] >= headingVectorInt[1])
        {
            tempValMin = headingVectorInt[1];
            tempValMax = headingVectorInt[0];
        }
        else
        {
            tempValMin = headingVectorInt[0];
            tempValMax = headingVectorInt[1];
        }

		for (ind = 1; ind < tempVal; ind = ind + 1)
		{
			// cycle thru several steps of only X motor
			for (ind2 = 1; ind2 < tempValMin; ind2 = ind2 + 1)
			{
				_RB6 = 1;
                _RB10 = 1;
				__delay_ms(1);
				_RB6 = 0;
                _RB10 = 0;
				__delay_ms(1);
			}

			// cycle thru several steps of only Y motor
			for (ind3 = 1; ind3 < tempValMax; ind3 = ind3 + 1)
			{
                
                if (headingVectorInt[0] >= headingVectorInt[1])
                {
                    _RB6 = 1;
                    __delay_ms(1);
                    _RB6 = 0;
                    __delay_ms(1);                    
                }
                else if (headingVectorInt[0] < headingVectorInt[1])
                {
                    _RB10 = 1;
                    __delay_ms(1);
                    _RB10 = 0;
                    __delay_ms(1); 
                }
               
			}

		}

}
/*
                         Main application
 */

int gcd (int a, int b)
{
    /*
     Function Citation:
     
     https://www.geeksforgeeks.org/convert-given-decimal-number-into-an-irreducible-fraction/
     */
    
    int gcf = 1;
    int i;
    for (i = 1; (i <= a) && (i <= b); i=i+1)
    {
        if (a % i == 0 && b % i == 0)
        {
            gcf = i;
        }
    }
    return gcf;
    
}



double round (double Val)
{
    if (Val - (double) floor(Val) >= 0.5)
    {
        double roundVal = ceil(Val);
    }
    else if (Val - (double) floor(Val) < 0.5)
    {
        double roundVal = floor(Val);
    }
    
    return roundVal;
}


int main(void)
{
    int shape, ifSquare, goAgain = 1, options =4;
    // initialize the device
    SYSTEM_Initialize();

    i2c_delay = 2; //delay for i2c timing. Tweak as needed. Should be divisible by 2.
    buffer[20] = ""; //initialize buffer for writing out numbers.
    counter = 1;

    init_I2C(); //configure ports for I2C.

    delay_cycles(20000);
    init_LCD(); //startup code from NHD datasheet
    delay_cycles(20000);



    _RB6 = 0;
    _RB7 = 0;
    _RB10 = 0;
    _RB11 = 0;
    _RB15 = 0;
    while (1)
    {

        _RB15 = 1;
        __delay_ms(10);
        _RB15 = 0;
        __delay_ms(10);

        //***** Motor control *****
        update_direction1(0);
        pulse_ntimes1(50); //16 full revs
        __delay_ms(5);
        update_direction2(0);
        pulse_ntimes2(50);
        //update_direction2(1);
        //pulse_ntimes2(50);
        //update_direction1(0);
        //pulse_ntimes1(50);
        //update_direction2(0);
        //pulse_ntimes2(50);

        __delay_ms(5);
        //update_direction2(1);
        pulse_simultaneous_ntimes(50);
        //*************************************


        //***** LCD Control in main *****
         //clear_LCD();
        delay_cycles(5);
        reset_cursor(); //put cursor back to 0,0
        delay_cycles(5);
        ultoa(buffer, counter, 10);//convert int to unsigned char.
        //have to set -no-legacy-libc in XC16 global properties to get this function

        if(_RA0 == 0)
        {
        Show("RA0 Pressed             ");
        }

        else
        {
         Show("Please Press Button            ");
        }
        //move_cursor(0, 7); //move cursor to 0,7.
        //Show(buffer); //display current count
        //delay_cycles(500);
        //move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
        //Show("Team 5, Checkoff 2            ");
        move_cursor(1, 8);
        Show(buffer);
        //Show(buffer); //display current count
        delay_cycles(5);
        counter = counter +1;
        __delay_ms(5);

        //Get User inputs
        while(goAgain == 1){
          printf("Welcome! What shape would you like to draw?\n");
          printf("1. Triangle\n2. Rectangle\n3. Square\n4. Ellipse\n");

          delay_cycles(5);
          reset_cursor(); //put cursor back to 0,0
          delay_cycles(5);
          ultoa(buffer, counter, 10);//convert int to unsigned char.
          Show("What shape to draw?");
          move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
          Show("1.Triangle 2.Rectangle 3.Square");
          //Buttons
          //RA0 = top,
          //RA1 = left,
          //RB2 = enter,
          //RB3 = bottom,
          //RA2 = right

          if(shape == 1 || RA1 == 0){
            //triangle
            triangleDeclare();

          }else if(shape ==2 || RB2 == 0){
            //rectangle
            ifSquare = 0;
            rectangleDeclare(ifSquare);

          }else if(shape == 3 || || RA2 == 0){
            //square
            ifSquare = 1;
            rectangleDeclare(ifSquare);

          }else if(shape == 4 || || RB3 == 0){
            //ellipse
            ellipseDeclare();
          }else{
            clear_LCD();
            reset_cursor(); //put cursor back to 0,0
            Show("No selection made");

          }
        }

        controlLoop(0.0, 0.0, 3.4, 4.5);


    }

    return 1;
}





/**
 End of File
*/

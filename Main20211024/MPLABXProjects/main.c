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
void validate(int whichShape);
void rotate(void);
void center(void);
void HandW(void);
double countVal(int lCount, int hCount);
double countDeg(int minDeg, int maxDeg);

//Global Variables
#define M_PI 3.14
double vals[20];
int choice, validity;
int i2c_delay;
int counter;
unsigned char buffer[20];
// Define parameters for motor control
int headingVectorInt[2], ind, ind2, ind3, tempValA, tempValB, tempVal, tempValMin, tempValMax, numDP;
int tempN, tempD;
double delayX, delayY, startX, startY, endX, endY, headingVector[2], Nx, Ny, pitch, stepSize; //delay in ms and start/end in inches
double headingFrac, factor, ratInt, ratDec, Val, roundVal, countX, countY, tempValRound;
double a,b, ratGCD, tempA, tempB;
_Bool directionX, directionY, clockwise, counter_clockwise; //0 for CW?, 1 for CCW?

/******************************************************************
 ***********************  FUNCTIONS *******************************
 *****************************************************************/

double countDeg(int minDeg, int maxDeg){
    int temp;
  move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
  //start at 5 so user can increase or decrease
  Show("         0         ");
  temp = 0;
  while (1){

    if(temp < minDeg){
      move_cursor(0, 0);
      temp=temp+45;
      Show("  Cannot Go Lower  ");
    }else if(temp > maxDeg){
      move_cursor(0, 0);
      temp=temp-45;
      Show(" Cannot Go Higher  ");
    }else if(!BT_GetValue()){
      temp=temp+45;
      __delay_ms(500); //5 seconds
    }else if(!BB_GetValue()){
      temp=temp-45;
      __delay_ms(500); //5 seconds
    }else if(!BC_GetValue()){
      return(temp);
    }else if(temp == 0){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         0         ");
    }else if(temp == 45){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         45        ");
    }else if(temp == 90){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         90        ");
    }else if(temp == 135){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("        135        ");
    }else if(temp == 180){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("        180        ");
    }else if(temp == 225){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("        225        ");
    }else if(temp == 270){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("        270        ");
    }else if(temp == 315){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("        315        ");
    }
  }
}
double countVal(int lCount, int hCount){
  int temp;
  //lCount = lowest value allowed
  //hCount = highest value allowed
  // use button to increment or decrement parameter value
  move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
  //start at 5 so user can increase or decrease
  Show("         5         ");
  temp = 5;
  while (1){

    if(temp < lCount){
      move_cursor(0, 0);
      temp++;
      Show("  Cannot Go Lower  ");
    }else if(temp > hCount){
      move_cursor(0, 0);
      temp--;
      Show(" Cannot Go Higher  ");
    }else if(!BT_GetValue()){
      temp++;
      __delay_ms(500); //15 seconds

    }else if(!BB_GetValue()){
      temp--;
      __delay_ms(500); //15 seconds

    }else if(!BC_GetValue()){
      return(temp);
    }else if(temp == 1){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         1         ");
    }else if(temp == 2){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         2         ");
    }else if(temp == 3){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         3         ");
    }else if(temp == 4){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         4         ");
    }else if(temp == 5){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         5         ");
    }else if(temp == 6){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         6         ");
    }else if(temp == 7){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         7         ");
    }else if(temp == 8){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         8         ");
    }else if(temp == 9){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         9         ");
    }else if(temp == 10){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         10        ");
    }else if(temp == 11){
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("         11        ");
    }
  }
}

void HandW(void){
  //HEIGHT = Y radius = vals[0]
  clear_LCD();
  delay_cycles(5);
  reset_cursor(); //put cursor back to 0,0
  delay_cycles(5);
  Show("Pick Height Value  ");
  vals[0] = countVal(1,8);

  __delay_ms(400);

  //WIDTH = X radius = vals[1]
  clear_LCD();
  delay_cycles(5);
  reset_cursor(); //put cursor back to 0,0
  delay_cycles(5);
  Show("Pick Width Value   ");
  vals[1] = countVal(1,8);

}
void center(void){
  //Starting Coordinates
  //CENTER X = vals[3]
  clear_LCD();
  delay_cycles(5);
  reset_cursor(); //put cursor back to 0,0
  delay_cycles(5);
  Show("Pick Center X      ");
  vals[3] = countVal(4,6);

  __delay_ms(400);

  //CENTER Y = vals[4]
  clear_LCD();
  delay_cycles(5);
  reset_cursor(); //put cursor back to 0,0
  delay_cycles(5);
  Show("Pick Center Y      ");
  vals[4] = countVal(4,6);

}
void rotate(void){
  //Rotation Degree = vals[2]
  //CENTER Y = vals[4]
  clear_LCD();
  delay_cycles(5);
  reset_cursor(); //put cursor back to 0,0
  delay_cycles(5);
  Show("Pick Rotation Deg  ");
  vals[2] = countDeg(0,360);

  printf("Rotation Deg: ");
  scanf("%f", &vals[2]);
  while(vals[2] < 0 || vals[2] > 360){
    printf("Please enter a valid input.\n");
    scanf("%f", &vals[2]);
  }
}
void validate(int whichShape){
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

    vals[5] = tRx;
    vals[6] = tRy;
    vals[7] = tLx;
    vals[8] = tLy;
    vals[9] = bLx;
    vals[10] = bLy;
    vals[11] = bRx;
    vals[12] = bRy;
    controlLoop(vals[5], vals[6], vals[7], vals[8]);
    controlLoop(vals[7], vals[8], vals[9], vals[10]);
    controlLoop(vals[9], vals[10], vals[11], vals[12]);
    controlLoop(vals[11], vals[12], vals[5], vals[6]);

    //printf("tRx = %f\ntRy = %f\ntLx = %f\ntLy = %f\nbLx = %f\nbLy = %f\nbRx = %f\nbRy = %f\n", tRx, tRy, tLx, tLy, bLx, bLy, bRx, bRy);
  }
}
void triangleDeclare(void){
  //TRIANGLE
  //find center points
  center();
  //Declare side lengths
  HandW();
  rotate();
  validate(1);
}
//For defining a rectangle OR square
void rectangleDeclare(int ifSquare){

  if(ifSquare == 0){
    //RECTANGLE
    //find center points
    center();
    __delay_ms(200);
    //Declare side lengths
    HandW();
    __delay_ms(200);
    rotate();
    __delay_ms(200);
    validate(2);
  }else{
    //SQUARE
    //find center points
    center();
    __delay_ms(200);
    //Declare side length
    //Sides = vals[0]
    clear_LCD();
    delay_cycles(5);
    reset_cursor(); //put cursor back to 0,0
    delay_cycles(5);
    Show("Pick Side Length   ");
    vals[0] = countVal(1,8);
    vals[1] = vals[0];
    __delay_ms(200);
    rotate();
    __delay_ms(200);
    validate(3);
  }

}
void ellipseDeclare(void){
  //ELLIPSE
  center();
  //Declare Radius lengths
  HandW();
  rotate();
  validate(4);
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


		_RB7 = directionX;
        //_RB7 = 1;
        __delay_ms(5);
		_RB11 = directionY;
        //_RB11 = 1;
        __delay_ms(5);


        // Motor step count
		countX = headingVector[0]*25.4*Nx/stepSize;
		countY = headingVector[1]*25.4*Ny/stepSize;

        if (countX < 0)
        {
            countX = -1.0*countX;
        }
        if (countY < 0)
        {
            countY = -1.0*countY;
        }


        // Motor Speed
		// calculate relative number of steps for x vs y

		// convert heading in inches to be whole numbers (1/4 inch is smallest interval of shape placement)
		// absolute value since direction is already set
		//headingVectorInt = 4*abs(headingVector);

        numDP = 3;
        headingFrac = round(countX/countY * pow(10,numDP-1))/ pow(10,numDP-1);
        factor = pow(10,numDP);
        ratInt = (double) floor(headingFrac);
        ratDec = headingFrac - ratInt;
        tempA = (ratDec*factor);
        tempB = factor;
        ratGCD = (double) gcd( (int) tempA, (int) tempB);
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
        if ((int)a % i == 0 && (int)b % i == 0)
        {
            gcf = i;
        }
    }
    return gcf;

}
double round (double Val)
{
    //tempValRound = Val - (double) floor(Val);
    //roundVal = ceil(Val);
    if (Val - (double) floor(Val) >= 0.5)
    {
        roundVal = ceil(Val);
    }
    else if (Val - (double) floor(Val) < 0.5)
    {
        roundVal = floor(Val);
    }

    return roundVal;
}


/******************************************************************
 ***********************  MAIN ************************************
 *****************************************************************/
int main(void)
{
    int shape, ifSquare;
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

    //Get User inputs
      /*
      delay_cycles(5);
      reset_cursor(); //put cursor back to 0,0
      delay_cycles(5);
      //ultoa(buffer, counter, 10);//convert int to unsigned char.
      Show("What shape to draw?");
      __delay_ms(500); //5 seconds

      while(1){
        //move to next screen
        if(!BR_GetValue()){
          break;
        }
      }
      */
      clear_LCD();
      delay_cycles(5);
      reset_cursor(); //put cursor back to 0,0
      delay_cycles(5);
      Show("1.Triangle 2.Rect  ");
      move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
      Show("3.Square 4.Ellipse ");
      __delay_ms(1500); //15 seconds

      //Buttons
      //BT = top,
      //BL = left,
      //BC = center,
      //BB = bottom,
      //BR = right

      while(1){
        if(!BT_GetValue()){
          //triangle
          clear_LCD();
          delay_cycles(5);
          reset_cursor(); //put cursor back to 0,0
          delay_cycles(5);
          Show("Triangle Picked    ");
          __delay_ms(700); //15 seconds

          triangleDeclare();

          break;
        }else if(!BL_GetValue()){
          //rectangle
          clear_LCD();
          delay_cycles(5);
          reset_cursor(); //put cursor back to 0,0
          delay_cycles(5);
          Show("Rectangle Picked   ");
          __delay_ms(700); //15 seconds

          ifSquare = 0;
          rectangleDeclare(ifSquare);

          break;
        }else if(!BC_GetValue()){
          //square

          clear_LCD();
          delay_cycles(5);
          reset_cursor(); //put cursor back to 0,0
          delay_cycles(5);
          Show("Square Picked      ");
          __delay_ms(700); //15 seconds

          ifSquare = 1;
          rectangleDeclare(ifSquare);

          break;
        }else if(!BR_GetValue()){
          //ellipse
          clear_LCD();
          delay_cycles(5);
          reset_cursor(); //put cursor back to 0,0
          delay_cycles(5);
          Show("Ellipse Picked     ");
          __delay_ms(700); //15 seconds

          ellipseDeclare();

          break;
        }
      }
    __delay_ms(700);



    controlLoop(0.0, 0.0, vals[7], vals[8]);
    //goAgain loop
    clear_LCD();
    delay_cycles(5);
    reset_cursor(); //put cursor back to 0,0
    delay_cycles(5);
    Show("Go again?          ");
    while(1){
      if(!BT_GetValue()){
        //top button for yes
        clear_LCD();
        delay_cycles(5);
        reset_cursor(); //put cursor back to 0,0
        delay_cycles(5);
        Show("Go again picked    ");
        __delay_ms(700); //15 seconds
        return(1);
      }else if(!BB_GetValue()){
        //bottom button for no
        clear_LCD();
        delay_cycles(5);
        reset_cursor(); //put cursor back to 0,0
        delay_cycles(5);
        Show("End of program     ");
        __delay_ms(700); //15 seconds

        break;
      }else if(!BL_GetValue() || !BC_GetValue() || !BC_GetValue()){
        return(1);
      }
    }
    exit(0);

}





/**
 End of File
*/

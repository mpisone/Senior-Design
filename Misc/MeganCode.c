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

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <stdio.h>
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

int update_direction_X(_Bool direction);
int pulse_ntimes_X(int n);
int update_direction_Y(_Bool direction);
int pulse_ntimes_Y(int n);
int pulse_simultaneous_ntimes(int n);


// Define parameters for motor control
extern int countX, countY, headingVectorInt[2], ind, indX, indY;
extern double pi, delayX, delayY, startX, startY, endX, endY, headingVector[2], Nx, Ny, pitch, stepSize; //delay in ms and start/end in inches
extern _Bool directionX, directionY, clockwise, counter_clockwise; //0 for CW?, 1 for CCW?

// Include motor synchronization library
// testing to see if this throws any errors
//#include <AccelStepper.h>


/*
                         Main application
 */
int main(void)
{
    // initialize the device
    //SYSTEM_Initialize();

    pi = 3.14;
    _RB6 = 0;
    _RB7 = 0;
    _RB10 = 0;
    _RB11 = 0;
    _RB15 = 0;

    while (1)
    {

		//*************************************
		//********* Open Loop Control *********

		//General Parameters
		pitch = 1/1.25;
		Nx = 2*pi*pitch;
		Ny = 2*pi*pitch;
		stepSize = 1.8*pi/180;
		clockwise = 0;
		counter_clockwise = 1;


		// Desired heading
		startX = 0;
		startY = 0;
		endX = 5;
		endY = 3;
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
		_RB11 = directionY;


		// Motor step count
		countX = headingVector[0]*25.4*Nx/stepSize;
		countY = headingVector[1]*25.4*Ny/stepSize;

		// Motor Speed
		// calculate relative number of steps for x vs y

		// convert heading in inches to be whole numbers (1/4 inch is smallest interval of shape placement)
		// absolute value since direction is already set
		headingVectorInt[0] = 4*abs(headingVector[0]);
		headingVectorInt[1] = 4*abs(headingVector[1]);

		// cycle for the total number of steps necessary
		for (ind = 1; ind < (max(countX/headingVectorInt[0], countY/headingVectorInt[1])); ind = ind + 1)
		{
			// cycle thru several steps of only X motor
			for (indX = 1; indX < headingVectorInt[0]; indX = indX + 1)
			{
				_RB6 = 1;
				__delay_ms(1);
				_RB6 = 0;
				__delay_ms(1);
			}

			// cycle thru several steps of only Y motor
			for (indY = 1; indY < headingVectorInt[1]; indY = indY + 1)
			{
				_RB10 = 1;
				__delay_ms(1);
				_RB10 = 0;
				__delay_ms(1);
			}

		}

    }

    return 1;
}




/**
 End of File
*/

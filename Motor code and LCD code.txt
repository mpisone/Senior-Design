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
int i2c_delay;
int counter;
unsigned char buffer[20];


/*
                         Main application
 */
int main(void)
{
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
        __delay_ms(500);
        _RB15 = 0;
        __delay_ms(500);
        
        //***** Motor control *****
        update_direction1(0);
        pulse_ntimes1(800); //16 full revs
        //update_direction2(1);
        //pulse_ntimes2(50);
        //update_direction1(0);
        //pulse_ntimes1(50);
        //update_direction2(0);
        //pulse_ntimes2(50);
        
        __delay_ms(500);
        update_direction2(1);
        pulse_simultaneous_ntimes(1600);
        //*************************************
        
        
        //***** LCD Control in main *****
         //clear_LCD();
        delay_cycles(500);
        reset_cursor(); //put cursor back to 0,0
        delay_cycles(500);
        ultoa(buffer, counter, 10);//convert int to unsigned char.
        //have to set -no-legacy-libc in XC16 global properties to get this function 
        Show("Robot Arm             ");
        delay_cycles(500);
        //move_cursor(0, 7); //move cursor to 0,7. 
        //Show(buffer); //display current count
        delay_cycles(500);
        move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
        Show("Team 5             ");
        move_cursor(1, 8);
        Show(buffer);
        //Show(buffer); //display current count
        delay_cycles(500);        
        counter = counter +1;
        __delay_ms(1000);
        //**************************************
    
    }
    
    return 1;
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

/**
 End of File
*/


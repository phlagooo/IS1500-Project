/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int playerPosY = 16;
int playerPosX = 16;
int fps = 10;

int pipe1X = 50;
int pipe2X = 75;
int pipe3X = 100;
int pipe4X = 125;
int pipe5X = 150;
int pipe6X = 175;


/* Interrupt Service Routine */
void user_isr( void ) {
  if(IFS(0) & 0x100) { //check timer flag
      clearDisplay();
      borderCollision();
      display_update();
  
      playerPosY++;

      drawRoof();
      drawGround();
      drawPipes();
      drawPlayer(playerPosX, playerPosY);

      
      display_image3(0, icon2);

      handlePipes();

      int buttonCheck = getbtns();
      if((buttonCheck >> 2) & 0x1 == 1) {
        playerPosY -= 4;
 }
    
      volatile int* lights = (volatile int*) 0xbf886110;
      *lights = *lights & 0xFF;
      (*lights)++;
      
    }
    IFSCLR(0) = 0x100; //clear timer flag
 }

/* Lab-specific initialization goes here */
void labinit( void ) {
  volatile int* triselightsP = (volatile int*) 0xbf886100;
  *triselightsP = *triselightsP & 0xFF;
  *triselightsP = 0;

  TRISD &= 0xFE0;

  PR2 = ((80000000/fps)/256);
  T2CONSET = 0x70; // prescaler 1:256
  TMR2 = 0x0;
  T2CONSET = 0x8000;

  IPC(2) = IPC(2)|0x10; 
  IECSET(0) = 0x100; 

  enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork( void ) { //handle inputs here for lower latency (might be negligible tho, 1/60 seconds)
  int buttonCheck = getbtns();
  if(buttonCheck != 0) {
    int switchesCheck = getsw();

    if(buttonCheck & 0x1 == 1) {
    //mytime = (mytime & 0xFF0F) | (switchesCheck << 4);
    }

    if((buttonCheck >> 1) & 0x1 == 1) {
     //mytime = (mytime & 0xF0FF) | (switchesCheck << 8);
    }

    if((buttonCheck >> 2) & 0x1 == 1) {
     //mytime = (mytime & 0xFFF) | (switchesCheck << 12);
     
     

    }
 }
}

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

int numberOfPipes = 6;
//two y cords indicate the gap in the pipe
int pipeGap[6*2] = {5, 20, 13, 28, 5, 25, 3, 18, 17, 30, 9, 24};
int pipeXs[6] = {50, 75, 100, 125, 150, 175};

/* Interrupt Service Routine */
void user_isr( void ) {
  if(IFS(0) & 0x100) { //check timer flag
      clearDisplay();

      playerPosY++;
      roofCollision();
      drawRoof();
      drawGround();
      drawPipes();
      handlePipes();
      drawPlayer(playerPosX, playerPosY);
      
      display_image(0, icon2);
    
      int buttonCheck = getbtns();
      if((buttonCheck >> 2) & 0x1 == 1) {
        playerPosY -= 4;
      }      
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
void labwork( void ) { 
}

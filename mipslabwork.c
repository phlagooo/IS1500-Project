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


int mytime = 0x5957;
//int timeoutcount = 0; //should be no longer necessary as 16bits is enough for timer when set at 1/60 seconds
int prime = 1234567;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void ) {
  if(IFS(0) & 0x100) { //check timer flag

  //timeoutcount++;

    //if(timeoutcount >= 10) { //timer is 100 ms so 10x for 1000ms currently, update 60hz future and handle graphics here
      time2string( textstring, mytime );
      display_string( 3, textstring );
      display_update();
      tick( &mytime );
      display_image(96, icon);
      //timeoutcount = 0;

      volatile int* lights = (volatile int*) 0xbf886110;
      *lights = *lights & 0xFF;
      (*lights)++;
   // }
    IFSCLR(0) = 0x100; //clear timer flag
 }
}

/* Lab-specific initialization goes here */
void labinit( void ) {
  volatile int* triselightsP = (volatile int*) 0xbf886100;
  *triselightsP = *triselightsP & 0xFF;
  *triselightsP = 0;

  TRISD &= 0xFE0;

  PR2 = ((80000000/60)/256);
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
    mytime = (mytime & 0xFF0F) | (switchesCheck << 4);
    }

    if((buttonCheck >> 1) & 0x1 == 1) {
     mytime = (mytime & 0xF0FF) | (switchesCheck << 8);
    }

    if((buttonCheck >> 2) & 0x1 == 1) {
     mytime = (mytime & 0xFFF) | (switchesCheck << 12);
    }
 }
}

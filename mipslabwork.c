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


int randomNumber = 0;
int tmr = 0;

int mytime = 0x5902;
static unsigned int g_seed;
//int timeoutcount = 0;
int prime = 1234567;
int box = 0;
int sifr = 3;
int andr = 1;
int rakn = 0;

//srand(myTime);

int x1 = 96;
int x2 = 96-64;
int y1 = 1;
int y2 = 0;


char textstring[] = "o";
char nada[] = "";

/* Interrupt Service Routine */
void user_isr( void ) {
  if(IFS(0) & 0x100) { //check timer flag

  //timeoutcount++;

   // if(timeoutcount >= 10) { //timer is 100 ms so 10x for 1000ms currently, update 60hz future and handle graphics here
      //time2string( textstring, box );
      display_string( sifr, textstring );
      display_string( sifr-1, nada );
      display_string( sifr+1, nada );
      display_update();
      tick( &mytime );
      display_image(x1, y1, icon);
      
      display_image(x2, y2, icon);

      tmr++;
      x1 = x1-16;
      x2 = x2-16;
      
     // timeoutcount = 0;
      oka(andr);

      if(x1 == -16){
          y1 = (tmr % 3) + 1;
          x1=112;
          
      }
      if(x2 == -16){
          y2 = (tmr % 3) + 1;
          x2=112;
          
      }      
      if(sifr > 4){
        sifr = 0;
      }

      volatile int* lights = (volatile int*) 0xbf886110;
      *lights = *lights & 0xFF;
      (*lights)++;
      
    }
    IFSCLR(0) = 0x100; //clear timer flag
 }
}

void oka(int numr) {
  if (numr == 1){
    sifr++;
  }
  else{
    sifr--;
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
    //mytime = (mytime & 0xFF0F) | (switchesCheck << 4);
    }

    if((buttonCheck >> 1) & 0x1 == 1) {
     //mytime = (mytime & 0xF0FF) | (switchesCheck << 8);
     andr = 1;
    }

    if((buttonCheck >> 2) & 0x1 == 1) {
     //mytime = (mytime & 0xFFF) | (switchesCheck << 12);
     
    andr = 0;

    }
 }
}

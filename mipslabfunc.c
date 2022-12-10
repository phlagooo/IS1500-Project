/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */


/* Declare a helper function which is local to this file */
static void num32asc( char * s, int ); 

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

#define WIDTH (128)
#define HEIGHT (32)
#define PAGES (4)

extern x1;
extern y1;
extern x2;
extern y2;
extern tmr;
extern playerPosY;
extern pipe1X;
extern pipe2X;
extern pipe3X;
extern pipe4X;
extern pipe5X;
extern pipe6X;

/*
Sets the specified pixel to on
*/
void setPixel(int x, int y) {
  uint8_t page;
  int indexSliver;

  if ((y >= 0) && (y < 32) && (x >= 0) && (x < 128))
  {
  
  if (y < 8) {
    page = 0;
  } else if (y < 16) {
    page = 1;
  } else if (y < 24) {
    page = 2;
  } else if (y < 32) {
    page = 3;
  }
  y = y % 8;
  indexSliver = (page*128) + x;

  switch (y) {
  case 0:
    icon2[indexSliver] &= 0b11111110;
    break;

  case 1:
    icon2[indexSliver] &= 0b11111101;
    break;

  case 2:
    icon2[indexSliver] &= 0b11111011;
    break;
    
  case 3:
    icon2[indexSliver] &= 0b11110111;
    break;

  case 4:
    icon2[indexSliver] &= 0b11101111;
    break;

  case 5:
    icon2[indexSliver] &= 0b11011111;
    break;

  case 6:
    icon2[indexSliver] &= 0b10111111;
    break;
    
  case 7:
    icon2[indexSliver] &= 0b01111111;
    break;
  }
}
}

/*
Sets the specified pixel on and also ends game if the pixels collide.
*/
void setPixelCheckCollision(int x, int y) {
  uint8_t page;
  int indexSliver;

  if ((y >= 0) && (y < 32) && (x >= 0) && (x < 128))
  {
  
  if (y < 8) {
    page = 0;
  } else if (y < 16) {
    page = 1;
  } else if (y < 24) {
    page = 2;
  } else if (y < 32) {
    page = 3;
  }
  y = y % 8;
  indexSliver = (page*128) + x;
  uint8_t icon3[512];
  int i;
  for (i = 0; i < 512; i++) {
    icon3[i] = icon2[i];
  }


  switch (y) {
  case 0:
    if ((icon3[indexSliver] &= 0b1) == 0) {
      death();
    } else {
      icon2[indexSliver] &= 0b11111110;
    }
    break;

  case 1:
    if ((icon3[indexSliver] &= 0b10) == 0) {
      death();
    } else {
      icon2[indexSliver] &= 0b11111101;
    }
    break;

  case 2:
    if ((icon3[indexSliver] &= 0b100) == 0) {
      death();
    } else {
      icon2[indexSliver] &= 0b11111011;
    }
    break;
    
  case 3:
    if ((icon3[indexSliver] &= 0b1000) == 0) {
      death();
    } else {
      icon2[indexSliver] &= 0b11110111;
    }
    break;

  case 4:
    if ((icon3[indexSliver] &= 0b10000) == 0) {
      death();
    } else {
      icon2[indexSliver] &= 0b11101111;
    }
    break;

  case 5:
    if ((icon3[indexSliver] &= 0b100000) == 0) {
      death();
    } else {
      icon2[indexSliver] &= 0b11011111;
    }
    break;

  case 6:
    if ((icon3[indexSliver] &= 0b1000000) == 0) {
      death();
    } else {
      icon2[indexSliver] &= 0b10111111;
    }
    break;
    
  case 7:
    if ((icon3[indexSliver] &= 0b10000000) == 0) {
      death();
    } else {
      icon2[indexSliver] &= 0b01111111;
    }
    break;
  }
}
}


/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

void resetPipes() {
  pipe1X = 50;
  pipe2X = 75;
  pipe3X = 100;
  pipe4X = 125;
  pipe5X = 150;
  pipe6X = 175;
}

void movePipe(int pipeNumber) {
  switch (pipeNumber)
  {
  case 1:
    pipe1X = 150;
    break;

  case 2:
    pipe2X = 150;
    break;

  case 3:
    pipe3X = 150;
    break;

  case 4:
    pipe4X = 150;
    break;

  case 5:
    pipe5X = 150;
    break;

  case 6:
    pipe6X = 150;
    break;
  
  default:
    break;
  }
}

void drawPipes() {
  int height1;
  int width1;
  for (height1 = 1; height1 < 5; height1++) {
    for (width1 = pipe1X; width1 < pipe1X + 5; width1++) {
      setPixel(width1, height1);
    }
  }
  for (height1 = 20; height1 < 31; height1++) {
    for (width1 = pipe1X; width1 < pipe1X + 5; width1++) {
      setPixel(width1, height1);
    }
  }

  int height2;
  int width2;
  for (height2 = 1; height2 < 13; height2++) {
    for (width2 = pipe2X; width2 < pipe2X + 5; width2++) {
      setPixel(width2, height2);
    }
  }
  for (height2 = 28; height2 < 31; height2++) {
    for (width2 = pipe2X; width2 < pipe2X + 5; width2++) {
      setPixel(width2, height2);
    }
  }
//pipe 3
  int height3;
  int width3;
  for (height3 = 1; height3 < 5; height3++) {
    for (width3 = pipe3X; width3 < pipe3X + 5; width3++) {
      setPixel(width3, height3);
    }
  }
  for (height3 = 25; height3 < 31; height3++) {
    for (width3 = pipe3X; width3 < pipe3X + 5; width3++) {
      setPixel(width3, height3);
    }
  }
//pipe 4
  int height4;
  int width4;
  for (height4 = 1; height4 < 3; height4++) {
    for (width4 = pipe4X; width4 < pipe4X + 5; width4++) {
      setPixel(width4, height4);
    }
  }
  for (height4 = 18; height4 < 31; height4++) {
    for (width4 = pipe4X; width4 < pipe4X + 5; width4++) {
      setPixel(width4, height4);
    }
  }
  //pipe 4
  int height5;
  int width5;
  for (height5 = 1; height5 < 17; height5++) {
    for (width5 = pipe5X; width5 < pipe5X + 5; width5++) {
      setPixel(width5, height5);
    }
  }
  for (height5 = 30; height5 < 31; height5++) {
    for (width5 = pipe5X; width5 < pipe5X + 5; width5++) {
      setPixel(width5, height5);
    }
  }
//pipe 5
  int height6;
  int width6;
  for (height6 = 1; height6 < 9; height6++) {
    for (width6 = pipe6X; width6 < pipe6X + 5; width6++) {
      setPixel(width6, height6);
    }
  }
  for (height6 = 24; height6 < 31; height6++) {
    for (width6 = pipe6X; width6 < pipe6X + 5; width6++) {
      setPixel(width6, height6);
    }
  }
}

void handlePipes() {
  if (pipe1X < 0) {
        movePipe(1);
      } else {
        pipe1X -= 1;
      }

      if (pipe2X < 0) {
        movePipe(2);
      } else {
        pipe2X -= 1;
      }

      if (pipe3X < 0) {
        movePipe(3);
      } else {
        pipe3X -= 1;
      }

      if (pipe4X < 0) {
        movePipe(4);
      } else {
        pipe4X -= 1;
      }

      if (pipe5X < 0) {
        movePipe(5);
      } else {
        pipe5X -= 1;
      }

      if (pipe6X < 0) {
        movePipe(6);
      } else {
        pipe6X -= 1;
      }
}

void drawRoof() {
  int i;
  for (i = 0; i < WIDTH; i++) {
    setPixel(i, 0);
  }
}

void drawGround() {
  int i;
  for (i = 0; i < WIDTH; i++) {
    setPixel(i, 31);
  }
}

void drawPlayer(int x, int y) {
  setPixelCheckCollision(x+1, y-3);
  setPixelCheckCollision(x-1, y-3);

  setPixelCheckCollision(x+1, y);
  setPixelCheckCollision(x, y);
  setPixelCheckCollision(x-1, y);

  setPixelCheckCollision(x+2, y-1);
  setPixelCheckCollision(x-2, y-1);
}

void clearDisplay() {
  int i;
  for (i = 0; i < 512; i++) {
    icon2[i] = 255;
  }
}

void death() {
  char endText[] = "    Game Over";
  int i;
  int k;
  int line = 2;
  while (1) {
    display_string(line, endText);
    display_update();
    TMR2 = 0x1;
    int buttonCheck = getbtns();
    if((buttonCheck >> 1) & 0x1 == 1) {
      for (i = 0; i < 16; i++){
        textbuffer[line][i] = ' ';
      }
      resetPipes();
      TMR2 = 0x0;
      playerPosY = 16;
      break;
    }
  }
}


void borderCollision() {
  if (playerPosY < 1) {
     playerPosY = 4;
  } 
  if (playerPosY > 30) {
    playerPosY = 16;
    death();
  }
}

void obstacleCollision() {
  
}

/* tick:
   Add 1 to time in memory, at location pointed to by parameter.
   Time is stored as 4 pairs of 2 NBCD-digits.
   1st pair (most significant byte) counts days.
   2nd pair counts hours.
   3rd pair counts minutes.
   4th pair (least significant byte) counts seconds.
   In most labs, only the 3rd and 4th pairs are used. */
void tick( unsigned int * timep )
{
  /* Get current value, store locally */
  register unsigned int t = * timep;
  t += 1; /* Increment local copy */
  
  /* If result was not a valid BCD-coded time, adjust now */

  if( (t & 0x0000000f) >= 0x0000000a ) t += 0x00000006;
  if( (t & 0x000000f0) >= 0x00000060 ) t += 0x000000a0;
  /* Seconds are now OK */

  if( (t & 0x00000f00) >= 0x00000a00 ) t += 0x00000600;
  if( (t & 0x0000f000) >= 0x00006000 ) t += 0x0000a000;
  /* Minutes are now OK */

  if( (t & 0x000f0000) >= 0x000a0000 ) t += 0x00060000;
  if( (t & 0x00ff0000) >= 0x00240000 ) t += 0x00dc0000;
  /* Hours are now OK */

  if( (t & 0x0f000000) >= 0x0a000000 ) t += 0x06000000;
  if( (t & 0xf0000000) >= 0xa0000000 ) t = 0;
  /* Days are now OK */

  * timep = t; /* Store new value */
}

/* display_debug
   A function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/   
void display_debug( volatile int * const addr )
{
  display_string( 1, "Addr" );
  display_string( 2, "Data" );
  num32asc( &textbuffer[1][6], (int) addr );
  num32asc( &textbuffer[2][6], *addr );
  display_update();
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

void display_init(void) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	
	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}



void display_image(int x, int y, const uint8_t *data) {
	int i, j;
  
  for(i = y+1; i < 5; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 16; j++)
			spi_send_recv(~data[i*16 + j]);
	}

	for(i = -1; i < y-1; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 16; j++)
			spi_send_recv(~data[i*16 + j]);
	}
}


void display_image2(int x, const uint8_t *data) {
	int i, j;
	
	//for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

    //vertical column
		spi_send_recv(0x22);
		spi_send_recv(0);
    spi_send_recv(127);
		
	//	spi_send_recv(x & 0xF);
		//spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 128; j++)
			spi_send_recv(~data[j]);
	//}
}


void display_image3(int x, const uint8_t *data) {
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 32*4; j++)
			spi_send_recv(~data[i*32*4 + j]);
	}
}



void display_update(void) {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;
			
			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}

/* Helper function, local to this file.
   Converts a number to hexadecimal ASCII digits. */
static void num32asc( char * s, int n ) 
{
  int i;
  for( i = 28; i >= 0; i -= 4 )
    *s++ = "0123456789ABCDEF"[ (n >> i) & 15 ];
}

/*
 * nextprime
 * 
 * Return the first prime number larger than the integer
 * given as a parameter. The integer must be positive.
 */
#define PRIME_FALSE   0     /* Constant to help readability. */
#define PRIME_TRUE    1     /* Constant to help readability. */
int nextprime( int inval )
{
   register int perhapsprime = 0; /* Holds a tentative prime while we check it. */
   register int testfactor; /* Holds various factors for which we test perhapsprime. */
   register int found;      /* Flag, false until we find a prime. */

   if (inval < 3 )          /* Initial sanity check of parameter. */
   {
     if(inval <= 0) return(1);  /* Return 1 for zero or negative input. */
     if(inval == 1) return(2);  /* Easy special case. */
     if(inval == 2) return(3);  /* Easy special case. */
   }
   else
   {
     /* Testing an even number for primeness is pointless, since
      * all even numbers are divisible by 2. Therefore, we make sure
      * that perhapsprime is larger than the parameter, and odd. */
     perhapsprime = ( inval + 1 ) | 1 ;
   }
   /* While prime not found, loop. */
   for( found = PRIME_FALSE; found != PRIME_TRUE; perhapsprime += 2 )
   {
     /* Check factors from 3 up to perhapsprime/2. */
     for( testfactor = 3; testfactor <= (perhapsprime >> 1) + 1; testfactor += 1 )
     {
       found = PRIME_TRUE;      /* Assume we will find a prime. */
       if( (perhapsprime % testfactor) == 0 ) /* If testfactor divides perhapsprime... */
       {
         found = PRIME_FALSE;   /* ...then, perhapsprime was non-prime. */
         goto check_next_prime; /* Break the inner loop, go test a new perhapsprime. */
       }
     }
     check_next_prime:;         /* This label is used to break the inner loop. */
     if( found == PRIME_TRUE )  /* If the loop ended normally, we found a prime. */
     {
       return( perhapsprime );  /* Return the prime we found. */
     } 
   }
   return( perhapsprime );      /* When the loop ends, perhapsprime is a real prime. */
} 

/*
 * itoa
 * 
 * Simple conversion routine
 * Converts binary to decimal numbers
 * Returns pointer to (static) char array
 * 
 * The integer argument is converted to a string
 * of digits representing the integer in decimal format.
 * The integer is considered signed, and a minus-sign
 * precedes the string of digits if the number is
 * negative.
 * 
 * This routine will return a varying number of digits, from
 * one digit (for integers in the range 0 through 9) and up to
 * 10 digits and a leading minus-sign (for the largest negative
 * 32-bit integers).
 * 
 * If the integer has the special value
 * 100000...0 (that's 31 zeros), the number cannot be
 * negated. We check for this, and treat this as a special case.
 * If the integer has any other value, the sign is saved separately.
 * 
 * If the integer is negative, it is then converted to
 * its positive counterpart. We then use the positive
 * absolute value for conversion.
 * 
 * Conversion produces the least-significant digits first,
 * which is the reverse of the order in which we wish to
 * print the digits. We therefore store all digits in a buffer,
 * in ASCII form.
 * 
 * To avoid a separate step for reversing the contents of the buffer,
 * the buffer is initialized with an end-of-string marker at the
 * very end of the buffer. The digits produced by conversion are then
 * stored right-to-left in the buffer: starting with the position
 * immediately before the end-of-string marker and proceeding towards
 * the beginning of the buffer.
 * 
 * For this to work, the buffer size must of course be big enough
 * to hold the decimal representation of the largest possible integer,
 * and the minus sign, and the trailing end-of-string marker.
 * The value 24 for ITOA_BUFSIZ was selected to allow conversion of
 * 64-bit quantities; however, the size of an int on your current compiler
 * may not allow this straight away.
 */
#define ITOA_BUFSIZ ( 24 )
char * itoaconv( int num )
{
  register int i, sign;
  static char itoa_buffer[ ITOA_BUFSIZ ];
  static const char maxneg[] = "-2147483648";
  
  itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
  sign = num;                           /* Save sign. */
  if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
  {
    for( i = 0; i < sizeof( maxneg ); i += 1 )
    itoa_buffer[ i + 1 ] = maxneg[ i ];
    i = 0;
  }
  else
  {
    if( num < 0 ) num = -num;           /* Make number positive. */
    i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
    do {
      itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
      num = num / 10;                   /* Remove digit from number. */
      i -= 1;                           /* Move index to next empty position. */
    } while( num > 0 );
    if( sign < 0 )
    {
      itoa_buffer[ i ] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return( &itoa_buffer[ i + 1 ] );
}

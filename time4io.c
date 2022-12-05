#include <stdint.h>   
#include <pic32mx.h>  
#include "mipslab.h"

//returns int with stauts of switches in the 4 least signficant bit, SW1 being least significant and SW4 most.
int getsw(void) {
    int status = (PORTD >> 8) & 0xF;
    return status;
}

//returns int with stauts of buttons in the 3 least signficant bit, bt1 being least significant and bt3 most.
int getbtns(void) {
    int status = (PORTD >> 5) & 0x7;
    return status;
}
#include <reg51.h>  // Include the header file for 8051

#define LED  P1 // Define LED pin as P1.0

void delay(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 1275; j++);  // Approximate delay for 1 ms
}

void main() {
	LED =0X00;
    while(1) {
        LED = 0xff;  // Turn ON the LED
        delay(500);  // Delay of 500 ms
        LED = 0x00;  // Turn OFF the LED
        delay(500);  // Delay of 500 ms
    }
}

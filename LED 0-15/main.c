#include <reg51.h>  // Include 8051 register definitions

// HEX codes for digits 0 to 9 (Common Anode display)
unsigned char seg_code[16] = {
    0x0F,  // opposite of 0x00
0x0E,  // opposite of 0x01
0x0D,  // opposite of 0x02
0x0C,  // opposite of 0x03
0x0B,  // opposite of 0x04
0x0A,  // opposite of 0x05
0x09,  // opposite of 0x06
0x08,  // opposite of 0x07
0x07,  // opposite of 0x08
0x06,  // opposite of 0x09
0x05,  // opposite of 0x0A
0x04,  // opposite of 0x0B
0x03,  // opposite of 0x0C
0x02,  // opposite of 0x0D
0x01,  // opposite of 0x0E
0x00   // opposite of 0x0F
	
};

// Simple delay function (~1 sec delay)
void delay() {
    int i, j;
    for (i = 0; i < 200; i++) {
        for (j = 0; j < 1275; j++);  // Calibrated for ~1 second (approx)
    }
}

void main() {
    unsigned char i;
    
    while (1) {
        for (i = 0; i < 16; i++) {
            P2 = seg_code[i];  // Send digit to Port 3 (connected to 7-seg)
            delay();           // Wait for a second
        }
    }
}

#include <reg51.h>  // Include 8051 register definitions

// HEX codes for digits 0 to 9 (Common Anode display)
unsigned char seg_code[10] = {
    0xC0,  // 0
    0xF9,  // 1
    0xA4,  // 2
    0xB0,  // 3
    0x99,  // 4
    0x92,  // 5
    0x82,  // 6
    0xF8,  // 7
    0x80,  // 8
    0x90   // 9
};

// Simple delay function (~1 sec delay)
void delay() {
    int i, j;
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 1275; j++);  // Calibrated for ~1 second (approx)
    }
}

void main() {
    unsigned char i;
    
    while (1) {
        for (i = 0; i < 10; i++) {
            P2 = seg_code[i];  // Send digit to Port 3 (connected to 7-seg)
            delay();           // Wait for a second
        }
    }
}

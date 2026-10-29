#include <reg51.h>

// Define motor control port
#define STEPPER P1  // Stepper motor connected to Port 1

// Define switch pin
sbit switch_pin = P2^7;  // Switch connected to P2.7

// Delay function to control motor speed
void delay(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 1275; j++);  // Approx 1ms delay
}

// Function to rotate motor clockwise using 03H, 06H, 09H, 0CH sequence
void stepper_clockwise(void) {
    STEPPER = 0x03;  // Step 1 (03H)
    delay(1);
    STEPPER = 0x06;  // Step 2 (06H)
    delay(1);
    STEPPER = 0x0C;  // Step 3 (0CH)
    delay(1);
    STEPPER = 0x09;  // Step 4 (09H)
    delay(1);
}

// Function to rotate motor counterclockwise using reverse 0CH, 09H, 06H, 03H sequence
void stepper_counterclockwise(void) {
    STEPPER = 0x09;  // Step 1 (09H)
    delay(1);
    STEPPER = 0x0C;  // Step 2 (0CH)
    delay(1);
    STEPPER = 0x06;  // Step 3 (06H)
    delay(1);
    STEPPER = 0x03;  // Step 4 (03H)
    delay(1);
}

void main(void) {
    while(1) {
        if (switch_pin == 1) {
            // Switch is pressed, rotate stepper motor clockwise
            stepper_clockwise();
        } else {
            // Switch is not pressed, rotate stepper motor counterclockwise
            stepper_counterclockwise();
        }
    }
}

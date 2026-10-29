#include <reg51.h>  // Include 8051 register definitions
sbit RS = P2^0;     // RS pin connected to P2.0
sbit RW = P2^1;     // RW pin connected to P2.1
sbit EN = P2^2;     // Enable pin connected to P2.2

// Function prototypes
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_set_cursor(unsigned char, unsigned char);
void lcd_write_string(unsigned char *);
void delay_ms(unsigned int);
void lcd_send_nibble(unsigned char);
void lcd_enable_pulse(void);

void main(void) {
    lcd_init();  // Initialize the LCD

    // Set cursor to row 1, column 1, and display "Hello"
    lcd_set_cursor(1, 4);
    lcd_write_string("Welcome To");

    // Set cursor to row 2, column 1, and display "8051!"
    lcd_set_cursor(2, 1);
    lcd_write_string("ENTC Department!");

    while(1);  // Infinite loop
}

// LCD initialization function
void lcd_init(void) {
    lcd_cmd(0x02);  // Initialize LCD in 4-bit mode
    lcd_cmd(0x28);  // 2 lines, 5x7 matrix in 4-bit mode
    lcd_cmd(0x0C);  // Display ON, Cursor OFF
    lcd_cmd(0x06);  // Auto-increment cursor
    lcd_cmd(0x01);  // Clear display
    delay_ms(2);
}

// Function to send a command to LCD
void lcd_cmd(unsigned char cmd) {
    RS = 0;  // Command mode
    RW = 0;  // Write operation
    
    // Send higher nibble
    lcd_send_nibble(cmd >> 4);
    
    // Send lower nibble
    lcd_send_nibble(cmd);
    
    delay_ms(2);  // Wait for the command to execute
}

// Function to send data to LCD
void lcd_data(unsigned char dat) {
    RS = 1;  // Data mode
    RW = 0;  // Write operation

    // Send higher nibble
    lcd_send_nibble(dat >> 4);
    
    // Send lower nibble
    lcd_send_nibble(dat);
    
    delay_ms(2);  // Wait for the data to execute
}

// Function to set cursor position
void lcd_set_cursor(unsigned char row, unsigned char column) {
    unsigned char position;
    if(row == 1) {
        position = 0x80 + (column - 1);  // Starting address of row 1
    } else if(row == 2) {
        position = 0xC0 + (column - 1);  // Starting address of row 2
    }
    lcd_cmd(position);  // Set cursor position
}

// Function to write a string to the LCD
void lcd_write_string(unsigned char *str) {
    while(*str) {
        lcd_data(*str++);
    }
}

// Function to send a nibble (half byte) to the LCD using P2.4 to P2.7
void lcd_send_nibble(unsigned char nibble) {
    // Clear upper nibble (D4-D7) and set it to the value of the nibble being sent
    P2 = (P2 & 0x0F) | (nibble << 4);

    lcd_enable_pulse();  // Generate the enable pulse
}

// Function to generate enable pulse
void lcd_enable_pulse(void) {
    EN = 1;  // Set Enable high
    delay_ms(1);  // Short delay
    EN = 0;  // Set Enable low
}

// Simple delay function
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++) {
        for(j = 0; j < 1275; j++);  // 1ms delay for 8051 at 11.0592 MHz
    }
}

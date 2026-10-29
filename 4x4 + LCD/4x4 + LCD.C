#include <reg51.h> // Header file for 8051

// Define LCD control pins
sbit RS = P1^0;  // Register select pin
sbit RW = P1^1;  // Read/Write pin
sbit EN = P1^2;  // Enable pin

// Define rows and columns for 4x4 Keypad
sbit R1 = P3^0;
sbit R2 = P3^1;
sbit R3 = P3^2;
sbit R4 = P3^3;
sbit C1 = P3^4;
sbit C2 = P3^5;
sbit C3 = P3^6;
sbit C4 = P3^7;

// Function prototypes
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *str);
void delay(unsigned int);
char keypad_scan(void);
void lcd_data_display(char key);

void main() {
    char key;
    lcd_init(); // Initialize LCD
    lcd_string("Keypad Testing"); // Display start-up message

    while(1) {
        key = keypad_scan(); // Scan the keypad
        if(key != 0) {
            lcd_cmd(0x01); // Clear LCD
            lcd_data_display(key); // Display pressed key
        }
    }
}

// Initialize LCD in 4-bit mode
void lcd_init() {
    lcd_cmd(0x02);  // Initialize in 4-bit mode
    lcd_cmd(0x28);  // 4-bit, 2 lines, 5x7 matrix
    lcd_cmd(0x0C);  // Display ON, cursor OFF
    lcd_cmd(0x06);  // Increment cursor
    lcd_cmd(0x01);  // Clear display
    lcd_cmd(0x80);  // Move cursor to first line, first position
}

// Function to send commands to the LCD
void lcd_cmd(unsigned char cmd) {
    P2 = (cmd & 0xF0);  // Send higher nibble
    RS = 0;  // Command mode
    RW = 0;  // Write mode
    EN = 1;
    delay(1);
    EN = 0;
    
    P2 = ((cmd << 4) & 0xF0);  // Send lower nibble
    EN = 1;
    delay(1);
    EN = 0;
    delay(2);  // Small delay for command processing
}

// Function to send data to the LCD
void lcd_data(unsigned char data) {
    P2 = (data & 0xF0);  // Send higher nibble
    RS = 1;  // Data mode
    RW = 0;  // Write mode
    EN = 1;
    delay(1);
    EN = 0;

    P2 = ((data << 4) & 0xF0);  // Send lower nibble
    EN = 1;
    delay(1);
    EN = 0;
    delay(2);  // Small delay for data processing
}

// Function to display string on the LCD
void lcd_string(unsigned char *str) {
    while(*str) {
        lcd_data(*str++);
    }
}

// Function to introduce delay
void delay(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 1275; j++);
}

// Keypad scanning function
char keypad_scan() {
    // Set all columns high and rows low
    C1 = C2 = C3 = C4 = 1;
    R1 = R2 = R3 = R4 = 0;

    // Check row 1
    R1 = 0; R2 = R3 = R4 = 1;
    if (C1 == 0) { delay(10); return '1'; }
    if (C2 == 0) { delay(10); return '2'; }
    if (C3 == 0) { delay(10); return '3'; }
    if (C4 == 0) { delay(10); return 'A'; }

    // Check row 2
    R2 = 0; R1 = R3 = R4 = 1;
    if (C1 == 0) { delay(10); return '4'; }
    if (C2 == 0) { delay(10); return '5'; }
    if (C3 == 0) { delay(10); return '6'; }
    if (C4 == 0) { delay(10); return 'B'; }

    // Check row 3
    R3 = 0; R1 = R2 = R4 = 1;
    if (C1 == 0) { delay(10); return '7'; }
    if (C2 == 0) { delay(10); return '8'; }
    if (C3 == 0) { delay(10); return '9'; }
    if (C4 == 0) { delay(10); return 'C'; }

    // Check row 4
    R4 = 0; R1 = R2 = R3 = 1;
    if (C1 == 0) { delay(10); return '*'; }
    if (C2 == 0) { delay(10); return '0'; }
    if (C3 == 0) { delay(10); return '#'; }
    if (C4 == 0) { delay(10); return 'D'; }

    return 0; // No key pressed
}

// Function to display the pressed key on the LCD
void lcd_data_display(char key) {
    lcd_cmd(0x80); // Move cursor to the beginning of the first line
    lcd_data(key); // Display the key
}

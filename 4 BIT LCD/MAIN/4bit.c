/* 4-bit LCD interface for 8051 (Keil C51)
   Uses:
     P2.4 - D4
     P2.5 - D5
     P2.6 - D6
     P2.7 - D7
     P3.2 - RS
     P3.3 - RW
     P3.4 - EN
   IMPORTANT: Do NOT have a macro like "#define lcd_data P2" anywhere.
*/

#include <reg51.h>

sbit LCD_RS = P2 ^ 0;
sbit LCD_RW = P2 ^ 1;
sbit LCD_EN = P2 ^ 2;

void lcd_delay(void);
void pulse_en(void);
void write4bits(unsigned char high_nibble); /* expects data in bits 7..4 */
void lcd_send(unsigned char value, bit is_data);
void lcd_cmd(unsigned char c);
void lcd_put(unsigned char ch);
void lcd_init(void);
void lcd_print(unsigned char *str);

void lcd_delay(void) {
    unsigned int i;
    for (i = 0; i < 3000
	
	; i++); /* crude delay - increase if needed */
}

void pulse_en(void) {
    LCD_EN = 1;
    lcd_delay();
    LCD_EN = 0;
    lcd_delay();
}

/* Place the high nibble (bits7..4) onto P2.7..P2.4 and pulse EN.
   We preserve P2.0..P2.3 in case they are used elsewhere. */
void write4bits(unsigned char high_nibble) {
    unsigned char tmp = P2 & 0x0F;          /* keep lower nibble */
    P2 = tmp | (high_nibble & 0xF0);        /* set upper nibble */
    pulse_en();
}

void lcd_send(unsigned char value, bit is_data) {
    LCD_RS = is_data; /* 1 = data, 0 = command */
    LCD_RW = 0;       /* write */
    write4bits(value & 0xF0);               /* send upper nibble */
    write4bits((value << 4) & 0xF0);        /* send lower nibble (shifted to high nibble) */
}

void lcd_cmd(unsigned char c) {
    lcd_send(c, 0);
}

void lcd_put(unsigned char ch) {
    lcd_send(ch, 1);
}

void lcd_print(unsigned char *str) {
    while (*str) {
        lcd_put(*str++);
    }
}

/* Initialize HD44780 in 4-bit mode (standard sequence) */
void lcd_init(void) {
    /* initial delays to allow module power-up */
    lcd_delay(); lcd_delay(); lcd_delay();

    LCD_RS = 0; LCD_RW = 0; LCD_EN = 0;

    /* The following are single-nibble writes to get into 4-bit mode */
    write4bits(0x30); /* function set (8-bit mode) - 1st */
    lcd_delay();
    write4bits(0x30); /* 2nd */
    lcd_delay();
    write4bits(0x30); /* 3rd */
    lcd_delay();
    write4bits(0x20); /* set to 4-bit mode */
    lcd_delay();

    /* Now send full commands (each will be sent as two nibbles) */
    lcd_cmd(0x28); /* function set: 4-bit, 2 lines, 5x8 dots */
    lcd_cmd(0x0C); /* display ON, cursor OFF, blink OFF */
    lcd_cmd(0x06); /* entry mode: increment, no shift */
    lcd_cmd(0x01); /* clear */
    lcd_delay();
    lcd_cmd(0x80); /* set DDRAM addr = 0 */
}

int main(void) {
    unsigned int j;
    lcd_init();

    while (1) {
        lcd_cmd(0x80);
        lcd_print("Human Detection");
        lcd_cmd(0xC0);
        lcd_print("Light On & OF");
        for (j = 0; j < 30000; j++);

        lcd_cmd(0x01);
        for (j = 0; j < 30000; j++);
				lcd_cmd(0x80);
        lcd_print("   
			16 X 2 LCD  ");
        lcd_cmd(0xC0);
        lcd_print("  By Using 8051  ");
        for (j = 0; j < 30000; j++);

        lcd_cmd(0x01);
        for (j = 0; j < 30000; j++);
        lcd_cmd(0x80);
        lcd_print("   Code By :   ");
        lcd_cmd(0xC0);
        lcd_print("  ELCTROGENIX! ");
        for (j = 0; j < 30000; j++);

        lcd_cmd(0x01);
        for (j = 0; j < 30000; j++);
    }

    return 0;
}

#include <reg52.h>

/* Pinouts:
   PIR  -> P1.0
   RELAY-> P1.1 (active HIGH)
   LCD  -> P2 (4-bit)
     RS P2.0
     RW P2.1
     EN P2.2
     D4 P2.4
     D5 P2.5
     D6 P2.6
     D7 P2.7
*/

sbit PIR    = P1^0;
sbit RELAY  = P1^1;

sbit LCD_RS = P2^0;
sbit LCD_RW = P2^1;
sbit LCD_EN = P2^2;
#define LCD_DATA_PORT P2

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 120; j++); // ~1ms at 11.0592MHz (tweak if needed)
}

/* small pulse */
void lcd_enable_pulse(void) {
    LCD_EN = 1;
    { volatile unsigned char x = 0; x++; } // tiny
    LCD_EN = 0;
}

/* write 4-bit nibble to P2.4-P2.7 */
void lcd_write_nibble(unsigned char nib) {
    LCD_DATA_PORT &= 0x0F;                // clear P2.4-P2.7
    LCD_DATA_PORT |= ( (nib & 0x0F) << 4 );
    lcd_enable_pulse();
}

void lcd_cmd(unsigned char cmd) {
    LCD_RS = 0;
    LCD_RW = 0;
    lcd_write_nibble(cmd >> 4);
    lcd_write_nibble(cmd & 0x0F);
    delay_ms(2);
}

void lcd_data(unsigned char dat) {
    LCD_RS = 1;
    LCD_RW = 0;
    lcd_write_nibble(dat >> 4);
    lcd_write_nibble(dat & 0x0F);
    delay_ms(1);
}

/* convenience print function to match your lcd_print usage */
void lcd_print(char *s) {
    while(*s) lcd_data(*s++);
}

void lcd_init(void) {
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    delay_ms(20);

    /* Init sequence (4-bit) */
    LCD_DATA_PORT &= 0x0F;
    LCD_DATA_PORT |= (0x03 << 4); lcd_enable_pulse(); delay_ms(5);
    LCD_DATA_PORT &= 0x0F;
    LCD_DATA_PORT |= (0x03 << 4); lcd_enable_pulse(); delay_ms(1);
    LCD_DATA_PORT &= 0x0F;
    LCD_DATA_PORT |= (0x03 << 4); lcd_enable_pulse(); delay_ms(1);

    LCD_DATA_PORT &= 0x0F;
    LCD_DATA_PORT |= (0x02 << 4); lcd_enable_pulse(); delay_ms(1);

    lcd_cmd(0x28); // function set: 4-bit, 2 line, 5x8
    lcd_cmd(0x06); // entry mode
    lcd_cmd(0x0C); // display ON, cursor OFF
    lcd_cmd(0x01); // clear
    delay_ms(2);
}

void lcd_goto(unsigned char row, unsigned char col) {
    unsigned char addr;
    if(row == 1) addr = 0x00 + (col - 1);
    else addr = 0x40 + (col - 1);
    lcd_cmd(0x80 | addr);
}

/* small helper: print and pad with spaces to clear old text */
void lcd_print_pad(char *s, unsigned char pad) {
    while(*s) lcd_data(*s++);
    while(pad--) lcd_data(' ');
}

/* a long busy-wait used to mimic your for(j=0;j<30000;j++) delays in splash */
void long_busy(unsigned int loops) {
    volatile unsigned int j;
    for(j = 0; j < loops; j++); // loops ~ delay; tweak loops if needed
}

void main(void) {
    unsigned int expiry_ms = 0;        // countdown in milliseconds
    const unsigned int HOLD_MS = 5000; // 5 seconds
    unsigned char last_pir = 0xFF;
    unsigned char last_relay = 0xFF;
    int seconds_display = -1;

    /* ensure relay OFF initially */
    RELAY = 0;

    lcd_init();

    /* --- Startup splash screens (your provided text) --- */
    lcd_cmd(0x80);
    lcd_print("Human Detection");
    lcd_cmd(0xC0);
    lcd_print("Light ON & OFF");
    long_busy(30000);

    lcd_cmd(0x01);

    lcd_cmd(0x01);
    long_busy(30000);

    lcd_cmd(0x80);
    lcd_print("   Code By :    ");
    lcd_cmd(0xC0);
    lcd_print("  ELCTROGENIX!  ");
    long_busy(30000);

    lcd_cmd(0x01);
    long_busy(30000);

    /* Prepare static labels for status lines */
    lcd_cmd(0x80); lcd_print("PIR: ");
    lcd_cmd(0xC0); lcd_print("Relay: ");

    /* Main loop: poll PIR frequently (every 100ms) so we can reset the 5s timer quickly */
    while(1) {
        /* read PIR input (active HIGH) */
        if(PIR == 0) {
            /* reset countdown to 5s */
            expiry_ms = HOLD_MS;
            if(last_pir != 1) {
                last_pir = 1;
                lcd_cmd(0x80); lcd_goto(1,6); lcd_print_pad("DETECT", 2);
            }
        } else {
            if(last_pir != 0) {
                last_pir = 0;
                lcd_cmd(0x80); lcd_goto(1,6); lcd_print_pad("NO    ", 0);
            }
        }

        /* Manage relay and countdown display */
        if(expiry_ms > 0) {
            /* ensure relay ON */
            if(last_relay != 1) {
                RELAY = 1;
                last_relay = 1;
            }

            /* compute seconds remaining for display */
            {
                int sec = (expiry_ms + 999) / 1000; // rounds up
                if(sec != seconds_display) {
                    seconds_display = sec;
                    /* show "Relay: ON x s" on second line.
                       Position: after "Relay: " which begins at 1st char of line 2 */
                    lcd_cmd(0xC0); lcd_goto(2,8);
                    lcd_print_pad("ON ", 0);
                    /* print seconds as single digit (5..0) - two chars if needed */
                    // convert sec to ASCII
                    if(sec >= 10) {
                        // unlikely here (max 5), but handle generically
                        char buf[3];
                        buf[0] = '0' + (sec / 10);
                        buf[1] = '0' + (sec % 10);
                        buf[2] = '\0';
                        lcd_print(buf);
                    } else {
                        char c = '0' + sec;
                        lcd_data(c);
                        lcd_data('s');
                        lcd_data(' ');
                    }
                }
            }

            /* wait 100 ms and decrement expiry */
            delay_ms(100);
            if(expiry_ms > 100) expiry_ms -= 100;
            else expiry_ms = 0;
        } else {
            /* ensure relay OFF and show OFF on LCD */
            if(last_relay != 0) {
                RELAY = 0;
                last_relay = 0;
                seconds_display = -1;
                lcd_cmd(0xC0); lcd_goto(2,8); lcd_print_pad("OFF   ", 0);
            }
            /* when idle poll slower */
            delay_ms(200);
        }
    } /* while */
}

#include <reg51.h>

void delay_50ms()
{
    TMOD = 0x01;      // Timer0 Mode1 (16-bit)

    TH0 = 0x4C;       // 50ms delay
    TL0 = 0x00;

    TR0 = 1;          // Start timer
    while(TF0 == 0);  // Wait overflow

    TR0 = 0;          // Stop timer
    TF0 = 0;          // Clear flag
}

void delay_half_second()
{
    int i;
    for(i=0;i<10;i++)     // 10 × 50ms = 0.5 sec
        delay_50ms();
}

void delay_1s()
{
    int i;
    for(i=0;i<20;i++)     // 20 × 50ms = 1 sec
        delay_50ms();
}

void delay_seconds(int sec)
{
    int j;
    for(j=0;j<sec;j++)
        delay_1s();
}

void main()
{
    int k;

    while(1)
    {
        // -------- WAY 1 GREEN --------
        P2 = 0xBE;      // G1=1 , R2=1
        delay_seconds(10);

        // -------- WAY 1 YELLOW BLINK (0.5 sec) --------
        for(k=0;k<5;k++)
        {
            P2 = 0xBD;      // Y1 ON
            delay_half_second();

            P2 = 0xBF;      // Y1 OFF
            delay_half_second();
        }

        // -------- WAY 2 GREEN --------
        P2 = 0xEB;      // R1=1 , G2=1
        delay_seconds(10);

        // -------- WAY 2 YELLOW BLINK (0.5 sec) --------
        for(k=0;k<5;k++)
        {
            P2 = 0xDB;      // Y2 ON
            delay_half_second();

            P2 = 0xFB;      // Y2 OFF
            delay_half_second();
        }
    }
}
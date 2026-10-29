#include <reg51.h>

sbit BUZZER = P2^2;   // Active LOW buzzer
sbit BUTTON = P2^0;   // Push button

void delay(unsigned int ms)
{
    unsigned int i,j;
    for(i=0;i<ms;i++)
        for(j=0;j<1275;j++);
}

void emergency_beep()
{
    unsigned int i;

    for(i=0;i<3;i++)   // ~7 seconds total
    {
        // Fast beeps
        BUZZER = 0; delay(10);
        BUZZER = 1; delay(10);

        BUZZER = 0; delay(10);
        BUZZER = 1; delay(10);

        BUZZER = 0; delay(10);
        BUZZER = 1; delay(40);

        // Slow warning beep
        BUZZER = 0; delay(80);
        BUZZER = 1; delay(40);

        // Triple alert burst
        BUZZER = 0; delay(15);
        BUZZER = 1; delay(15);

        BUZZER = 0; delay(15);
        BUZZER = 1; delay(15);

        BUZZER = 0; delay(15);
        BUZZER = 1; delay(60);
    }

    BUZZER = 1; // OFF
}

void main()
{
    BUZZER = 1; // buzzer OFF initially

    while(1)
    {
        if(BUTTON == 0)
        {
            delay(20);

            if(BUTTON == 0)
            {
                emergency_beep();   // play ~7 sec alarm

                while(BUTTON == 0); // wait for release
            }
        }
    }
}
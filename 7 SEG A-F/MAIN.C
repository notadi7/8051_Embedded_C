// Code for 7 Segment Display Interfacing with 8051 Microcontroller (AT89S52)


#include<reg51.h>


void msdelay(unsigned int time)  // Function for creating delay in milliseconds.

{

    unsigned i,j ;

    for(i=0;i<time;i++)    

    for(j=0;j<1275;j++);

}


void main()

{

    unsigned char no_code[]={0xC0,0xFC,0x92,0x98,0xAC,0x89,0x81,0xDC,0x80,0x88}; //Array for hex values (0-9) for common anode 7 segment

    int k;

    while(1)

    {

        for(k=0;k<6;k++)

        {

         P2=no_code[k]; 

         msdelay(300);

        }

    }

}


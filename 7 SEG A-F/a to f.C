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

    unsigned char no_code[]={0X77,0X7F,0X39,0X3F,0X79,0X71}; //Array for hex values (A to F) for common anode 7 segment

    int k;

    while(1)

    {

        for(k=0;k<6;k++)

        {

         P3=no_code[k]; 

         msdelay(300);

        }

    }

}


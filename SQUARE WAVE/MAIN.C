#include<reg51.h>  
void delay(unsigned int);  
sbit p=P1^5;  
void main (void)  
{ 
    while (1)  
    {  
         p=1 ;
         delay(500);  
    p=0;
			delay(500);
		}  
}  
void delay(unsigned int time)  
{  
	unsigned int i , j;
	
	for (i=0;i<time;i++)
	{
		for (j=0;j<1275;j++);
	}
     
}
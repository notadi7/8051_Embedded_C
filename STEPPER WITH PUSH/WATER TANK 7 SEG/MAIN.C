#include<reg51.h>
sbit empty=P2^0;
sbit full =P2^7;
#define display P3

void main ()
{
empty =0xff;
full=0xff;
display=0;

	
	while(1)
		
	{
	if(full==0)
	{
	P3=0x71;
	
	}
	else if (empty==0)
		{
		P3= 0x79;
		
		}
	else
	{
	P3=0x00;
	}
}
}








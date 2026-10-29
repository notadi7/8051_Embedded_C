#include<reg51.h>
#define seg1 P2 
#define seg2 P3 
sbit key0 =P1^0;
sbit key1= P1^1 ;
sbit key2 =P1^2;
sbit key3 =P1^3;
sbit rled= P1^4;
sbit yled =P1^5;
sbit bled =P1^6;
sbit gled =P1^7;
sbit motor =P0^0;  
void main ()
{
key0=0xff;
key1=0xff;
key2=0xff;
key3=0xff;
rled=0x00;
yled=0x00;
bled=0x00;
gled=0x00;
motor=0x00;

if (key0==0)
{
seg1=0x5b;
seg2=0x6d;
rled=1;
bled=0;
yled=0;
gled=0;
motor=1;

}
else if (key1==0)
{
seg1=0x6d;
seg2=0x3f;
rled=0;
bled=0;
yled=1;
gled=0;
motor=1;

}
else if (key2==0)
{
seg1=0x07;
seg2=0x6d;
rled=0;
bled=1;
yled=0;
gled=0;
motor=1;

}
else if (key3==0)
{
seg1=0x67;
seg2=0x67;
rled=0;
bled=0;
yled=0;
gled=1;
motor=0;

}
else
{
seg1=0x3f;
seg2=0x3f;
rled=0;
bled=0;
yled=0;
gled=0;
motor=1;

}







}
	
	
	
	
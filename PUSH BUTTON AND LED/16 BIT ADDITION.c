#include<reg51.h>
void main (void)
{
unsigned char a,b,c;
P1=0x00;
a=0x1234;
b=0x5678;
c=a+b;
P1=c;
}
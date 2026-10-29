#include<reg51.h>
void delay(unsigned int);
void main()
{
unsigned char i;
P1=0X00;
while(1)
{
for(i=0;i<255;i++)
{
P1=i;
delay(10);
}
}
}

void delay (unsigned int time )
{
unsigned int j , k;
	
for(j=0;j<time;j++)
	{
	for(k=0;j<1275;j++);
	
	}

}
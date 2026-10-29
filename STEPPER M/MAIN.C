#include<reg52.h>
#include<stdio.h>

void delay(int);

void main()
{
  do
  {
    P2 = 0x09; //0011
    delay(10);
    P2 = 0x0C; //0110
    delay(10);
    P2 = 0x06; //1100
    delay(10);
    P2 = 0x03; //1001
    delay(10);
  }
while(1);
}

void delay(int k)
{
  int i,j;
  for(i=0;i<k;i++)
  {
    for(j=0;j<100;j++)
    {}
  }
}
#include<reg51.h>
void delay(unsigned int);
void main(void)
  {
       unsigned int x;
       while(1)                                               //repeat forever

  {
                 for(x=0;x<255;x++)
                         {
                                  P1=x;
                                  delay(1);
                         }

                  for(x=255;x>0;x--)
                         {
                                  P1=x;
                                 delay(1);
                         }
          }
}

void delay(unsigned int time)
{
unsigned int i,j;
for(i=0;i<time;i++)
	{
for(j=0;j<1275;j++);
}
	}
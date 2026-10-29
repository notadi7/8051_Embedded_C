#include<reg52.h>
sbit button=P2^0;  //Push button pin declared
sbit led=P2^1;     //Led pin declared

void main()
{

P2=0x01;      //Push button as input and led as output

while(1){     //Control will remain in while loop for ever

if(button==1) //Button status check
led=1;        //If pressed switch on led
else
led=0;        //If noting led off
}

}
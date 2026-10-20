#include<lpc21xx.h>
#include"header.h"
void uart0_init(unsigned int baud)
{
 int pclk,result=0;
 
if(VPBDIV==0)
  pclk=15000000;
else if(VPBDIV==0X01)
pclk=60000000;
else if(VPBDIV==0X02)
pclk=30000000;

result=pclk/(16*baud);

PINSEL0 |=0X0000005;
U0LCR=0X83;
U0DLL=result&0XFF;
U0DLM=(result>>8)&0xff;
U0LCR=0X03;
}

#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
U0THR=data;
while(THRE==0);
}

#define RDR (U0LSR&1)
unsigned char uart0_rx()
{
while(RDR==0);
			  return U0RBR;
}

 void uart0_tx_string(char *ptr)
 {
 while(*ptr!='\0')
 {
  uart0_tx(*ptr);
  ptr++;
 }

 }

void uart0_binary(int num)
{
 int pos;

 for(pos=7;pos>=0;pos--)
 {
  if(num&(1<<pos))
  uart0_tx('1');
  else
  uart0_tx('0');
 }

}

void uart0_integer(int num)
 {
  int a[10],i=0;
  if(num==0)
  {
   uart0_tx('0');
  }
  if(num<0)
  {
   num=-num;
   uart0_tx('-');
  }
 while(num>0)
 {
  a[i]=num%10+48;
  num=num/10;
  i++;
 }
 for(i=i-1;i>=0;i--)
 {
 uart0_tx(a[i]);
 }
 }

void uart0_rx_string(unsigned char *ptr,int len)
 {
 	int i;
	for(i=0;i<len;i++)
	{
		while(RDR==0);
		ptr[i]=U0RBR;
		if(ptr[i]=='\r')
		break;

		}
		ptr[i]=='\0';
}


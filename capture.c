#include <io.h>
#include <alcd.h>
#include <stdio.h>
#include <delay.h>
volatile unsigned int tmp,tmp_old;
float result;
volatile unsigned char flag,buff[16],ovf;
void main(void)
{ lcd_init(16);
  TCCR1B=(1<<ICES1)|(1<<CS11)|(1<<CS10);//timer divided by 64 and rising part appear
  TIMSK1=(1<<ICIE1)|(1<<TOIE1  ) ;//input capture interrupt enable
  #asm("sei")
while (1)
    {  
        if(flag>=2)
        {
           
            result=ovf; 
            result=result*65536;
            if(tmp>tmp_old)
              result+=tmp-tmp_old;
            else
              result+=65536-tmp+tmp_old;
            
            sprintf(buff,"%1.0f   ",result);
            lcd_gotoxy(0,0);
            lcd_puts(buff); 
            tmp=0;
            flag=0;
            ovf=0;
            TCNT1H=0;
            TCNT1L=0;
        }

    }
}
interrupt [TIM1_OVF] void tim1_ovf(void)
{
  ovf++; 

}
                                      
interrupt [TIM1_CAPT] void tim1_cap_ir(void)
{
    tmp_old=tmp;
    tmp=ICR1L;
    tmp|=ICR1H<<8;
    flag++;

}

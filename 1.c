/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Automatic Program Generator
© Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 09.06.2015
Author  : Serj
Company : If You Like This Software,Buy It
Comments: 


Chip type               : ATmega8
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega8.h>
#include <delay.h>
#include "max6675.h"


// Declare your global variables here
#define LED_delay 150    

int byDisplay[4];        // áóôåð äàííûõ, äëÿ âûâîäà íà ýêðàí
int temperatura,ii=0;
int temp=0,temp1=0,temp2=0,tempi=0;
int byCharacter[13] = {0x3F,     //0
                0x06,   //1
 	              0x5B,   //2
	              0x4F,	  //3 
	              0x66,   //4 
	              0x6D,   //5 
	              0x7D,   //6
                0x07,   //7 
                0x7F,   //8
                0x6F,   //9 
                0x00,   //blank   
                0x40,  //-
                0x80    //
                }; 


void ShowDisplayData(void)
{                      
 
  PORTB = byCharacter[byDisplay[0]];
  PORTC.0 = 0;
  delay_us(LED_delay);
  PORTC.0 = 1;    
     
  PORTB = byCharacter[byDisplay[1]];
  PORTC.1 = 0;
  delay_us(LED_delay);
  PORTC.1 = 1;
      
  PORTB = byCharacter[byDisplay[2]] ;
  PORTC.2 = 0;
  delay_us(LED_delay);
  PORTC.2 = 1;
      
  PORTB = byCharacter[byDisplay[3]];
  PORTC.3 = 0;
  delay_us(LED_delay);
  PORTC.3 = 1;
}

/*interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{                
// Reinitialize Timer 0 value
 if (PIND.6) 
    PORTD &= ~(1<<6);
 else
    PORTD |= 1<<6;   
// Place your code here
}    */

interrupt [TIM2_COMP] void timer2_comp_isr(void)
{
// #asm("cli");
 /*if (PIND.6) 
    PORTD &= ~(1<<6);
 else
    PORTD |= 1<<6;  */
 
    if (ii>4)
    {  
    temp2=temp1;
       temp1=temp;  
        temp = ReadMAX6675();
       tempi=(temp+temp1+temp2)/12;   
       ii=0;   
       if(tempi>=temperatura)  
     {
         PORTD &= ~(1<<5); 
         PORTD &= ~(1<<6);
          byDisplay[3] = 10;
     }
     if(tempi<temperatura-3)
     {
         PORTD |= 1<<5;
         PORTD |= 1<<6;
          byDisplay[3] = 12;
     }
    }
    else
    ii++; 
  // ShowDisplayData();     
 //  #asm("sei");
}  

// Timer 1 overflow interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
  
// Reinitialize Timer 1 value
//TCNT1H=0x8F;
//TCNT1L=0xD1;
// Place your code here 
/*if (PIND.3==0)
    {
      
byDisplay[1]=byDisplay[1]+1;
//byDisplay[2]=byDisplay[2];
    }  */     
  ShowDisplayData();
}


void main(void)
{
 byDisplay[0]=0; 
byDisplay[1]=0;
byDisplay[2]=2;
byDisplay[3]=4; 
// Declare your local variables here

// Input/Output Ports initialization
// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=Out Func2=Out Func1=Out Func0=Out 
// State6=T State5=T State4=T State3=0 State2=0 State1=0 State0=0 
PORTC=0x00;
DDRC=0x0F;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=Out Func1=Out Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=0 State1=0 State0=T 
PORTD=0x98;
DDRD=0x66;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=0x05;
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x0A;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x70;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x07;
TCNT2=0xFA;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
MCUCR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x90;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;
#asm("sei");

while (1)
      {
      // Place your code here
           #asm("cli");       
          
    temperatura=byDisplay[2]*100+byDisplay[1]*10;  
    /* temp2=temp1;
       temp1=temp;  
        temp = ReadMAX6675();
       tempi=(temp+temp1+temp2)/12;   */
      /* if (tempi!=0)
        PORTD |= 1<<6;
        else
         PORTD &= ~(1<<6);    */
      
    /* if(tempi>=temperatura)  
     {
         PORTD &= ~(1<<5); 
          byDisplay[3] = 10;
     }
     if(tempi<temperatura-5)
     {
         PORTD |= 1<<5;
          byDisplay[3] = 12;
     }      */
      // Place your code here
     // ShowDisplayData();   
     
      if (PIND.7==0)  
      { 
       
        byDisplay[2]=tempi/100;
        byDisplay[1]=(tempi-byDisplay[2]*100)/10;  
        byDisplay[0]=tempi-byDisplay[2]*100-byDisplay[1]*10;   
         
                 while(!PIND.7)
          {
        ShowDisplayData();
            }  
        
        byDisplay[2]= temperatura/100;    
        byDisplay[1]=( temperatura-byDisplay[2]*100)/10;     
         byDisplay[0] =0;
        //delay_ms(300);  
         ShowDisplayData(); 
        
      }       
     
            
           if (PIND.3==0)
    { 
    
    switch(byDisplay[1])
    {  
        case 0 :
        byDisplay[1]=1; 
        break;
        case 1:
        byDisplay[1]=2;  
         break;
         case 2:
        byDisplay[1]=3; 
         break;
         case 3:
        byDisplay[1]=4; 
         break;
         case 4 :
        byDisplay[1]=5; 
         break;
         case 5 :
        byDisplay[1]=6; 
         break;
         case 6 :
        byDisplay[1]=7;  
         break;
         case 7:
        byDisplay[1]=8; 
         break;
         case 8 :
        byDisplay[1]=9;
         break;
         case 9 :
        byDisplay[1]=0;   
        /*if (  byDisplay[2]==1)
        byDisplay[2]=2;       
        else 
        byDisplay[2]=3;   */
        byDisplay[2]=byDisplay[2]+1;
         break;
//byDisplay[2]=byDisplay[2];
    }
    delay_ms(50);
    }    
    
    
     if (PIND.4==0)
    { 
    
    switch(byDisplay[1])
    {  
        case 0 :
        byDisplay[1]=9;  
       /* if (  byDisplay[2]==3)
        byDisplay[2]=2; */
        byDisplay[2]=byDisplay[2]-1;  
            
       /* else 
        byDisplay[2]=1;  */
        break;
        case 1:
        byDisplay[1]=0;  
         break;
         case 2:
        byDisplay[1]=1; 
         break;
         case 3:
        byDisplay[1]=2; 
         break;
         case 4 :
        byDisplay[1]=3; 
         break;
         case 5 :
        byDisplay[1]=4; 
         break;
         case 6 :
        byDisplay[1]=5;  
         break;
         case 7:
        byDisplay[1]=6; 
         break;
         case 8 :
        byDisplay[1]=7;
         break;
         case 9 :
        byDisplay[1]=8;   
                 break;
        }
    delay_ms(50);
    } 
    
      #asm("sei");

      }
}


/***************************************************************************
 * Title:         MAX6675 K-Typ Temperatur SPI Sensor  
 * Author: 
 *
 * File Name            : "MAX7775.c"
 * Title                : MAX6675 SPI interface
 * Date                 : 2008/02/27
 * Version              : 0.1
 * Target MCU           : Any AVR with SPI
 *
 * DESCRIPTION
 * The MAX6675 is a Temperatur Sensor IC for K-Type Termocouplers. 
 *
 * \author               Stephan Harms: http://www.stepphanharms.de \n
 *                       Support email: avr@stephaharms.de
 *
 * Modified 2008-02-27 
*************************************************************************/


//#include <stdio.h>
#include <mega8.h>
#include <stdlib.h>
//#include <delay.h>
//#include <avr/pgmspace.h>


#include "MAX6675.h"


//volatile unsigned char str1[8];
//volatile unsigned char portout=0;
//volatile unsigned long j=0;  //Счетчик данных ТЕРМО 
//volatile unsigned long k=0;  //Счетчик данных  ФОТО
//volatile unsigned long n=0;  //Для фото
//volatile unsigned long t=0;  //Для термо
//volatile unsigned char T1,T2,FR,NumC,a,TT;
volatile unsigned int C,s,i;



/* interrupt mode not implemented
// Interrupt Routine Master Mode (interrupt controlled)
ISR(SPI_STC_vect)
{
        PtrToStrChar++;                         // Point to next Char in String
        if (*PtrToStrChar != 0)                 // if end not reached
        {
                SPDR  = *PtrToStrChar;          // send Character
        }
        else ClearToSend = 1;                   // if end reached enable transmission of next String
}
*/




/*************************************************************************
Request a Temperatur value read for interrupt driven SPI
Input:    none
Returns:  none
*************************************************************************/
/* interrupt mode not implemented
void MAX6675RequestTemp(void)
{
        if (ClearToSend == 1){                  // if no transmission is in progress
                PtrToStrChar  = TextString;     // Set Pointer to beginning of String
                                                // initiate new transmission by 
                SPDR = *PtrToStrChar;           // sending first Char of new String
                ClearToSend = 0;                // block initiation of new transmissions
        }
}
*/




/*************************************************************************
Read the temperature Value
Input:    none
Returns:  0xFFFF: ERROR
          else:   Temperatur Value * 4 [шC]
*************************************************************************/
/*uint16_t MAX6675ReadTemp(void)
{
  uint16_t tempRead;
  uint8_t valRead;


  // pull SS Line low
  SPI_PORT &= ~(1<<SS_BIT);


  // start SPI data transfer
  SPDR = 0x00;


  // wait for transmision complete
  while(!(SPSR & (1<<SPIF)))
    ; // do nothing
  

  // copy hi byte
  valRead = SPDR;


  
  // start SPI data transfer
  SPDR = 0x00;


  // shift hi-byte
  tempRead = valRead << 5;


  // wait for transmision complete
  while(!(SPSR & (1<<SPIF)))
    ; // do nothing


  // copy hi byte
  valRead = SPDR;
  valRead &= 0b11111000;
  valRead >>= 3;


  tempRead |= valRead;


  // pull SS Line hi
  SPI_PORT |= (1<<SS_BIT);




  return tempRead;
}

 */


/*************************************************************************
 * Initialize the SPI Port to communicate with MAX6675
 * Input:    none
 * Returns:  none
 ************************************************************************/
/*void MAX6675Init(void)
{
  //volatile char IOReg;


  // set /SS, MOSI, SCK as output 
  SPI_DDR  |= (1<<SS_BIT)|(0<<MOSI_BIT)|(1<<SCK_BIT);
  // enable SPI in Master Mode with SCK = CK/128
  SPCR  = (1<<SPE)|(0<<MSTR)|(1<<CPHA)|(1<<SPR0)|(1<<SPR1);
  SPCR=0x5B;
  //IOReg   = SPSR;                     // clear SPIF bit in SPSR
  //IOReg   = SPDR;
}

 */

/*Hide details 

Change log
r6 by stephan.harms on Mar 1, 2009   Diff 
[No log message]Go to: 	 

Project members, sign in to write a code review

Older revisions
 r4 by stephan.harms on Feb 28, 2009   Diff 
 r3 by stephan.harms on Feb 27, 2009   Diff 
All revisions of this file 

File info
Size: 3565 bytes, 127 lines
View raw file
  */
  unsigned int ReadMAX6675()// Чтение АЦП МАХ6675
{
   CSOFF;   
  // delay_ms(100);   
  C=0;                        //Выбор кристалла
   for(s=24;s!=0;s--);          //задержка    C = 0;
   for (i = 0; i < 16; i++ )    // Читаем 16 бит
      {
         C *= 2;                       //Следующий разряд
            SCKON;                     // Такт= 1;
    for(s=24;s!=0;s--);         // задержка
	
          if ( PIND & 0b00000001)  C++;              //Если пришедш. бит =1 пишем в С
            SCKOFF;                    //  Такт= 0;
      }
            SCKOFF;                    //  Такт= 0 Читаем данные      
            if(C & 0x4)    
            {
            CSON;
            return 0;
            }        
		   C=C>>3;
	        CSON;                      // Запускаем преобразование
			 return (C);
}
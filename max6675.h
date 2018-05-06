#ifndef MAX6675_H
#define MAX6675_H




#include <stdint.h>




#define SPI_PORT   PORTD


#define SPI_DDR    DDRD


//#define SS_BIT     PORTD1
//#define MOSI_BIT   PORTD0


//#define SCK_BIT    PORTD2
#define CSON PORTD |= 1<<1
#define CSOFF PORTD &= ~(1<<1)
#define SO          (PIND & 0b00000001) 
#define SCKON       PORTD |= 1<<2 
#define SCKOFF PORTD &= ~(1<<2)


//void MAX6675Init(void);


//uint16_t MAX6675ReadTemp(void);


//void MAX6675RequestTemp(void);
unsigned int ReadMAX6675();


#endif // MAX6675_H
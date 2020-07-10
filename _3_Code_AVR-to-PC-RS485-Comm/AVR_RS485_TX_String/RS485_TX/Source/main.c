/*
RS485 communication from ATmega328p microcontroller to PC Tutorial

Website-> https://www.xanthium.in/atmel-microchip-avr-atmega328p-rs485-communication-with-computer-tutorial-for-beginners

// Program send the string "Hello from ATmega328p" Continuously to PC using a RS485 cable //

  MAX485                               ATmega328p
+----------+               +--------------------+
|        RO|-------------->|PD0/RXD		     PB2|
|A       D1|<--------------|PD1/TXD		     PB3|
|B      ~RE|<--------------|PD2			     PB4|
|        DE|<--------------|PD3			     PB5|
+----------+               |                    |
						   +--------------------+

	   

*/


//+------------------------------------------------------------------------------------------------+
//| Compiler           : AVR GCC (WinAVR)                                                          |
//| Microcontroller    : ATmega328p                                                                |
//| Programmer         : Rahul.Sreedharan                                                          |
//| Date               : 04-July-2020                                                             |
//+------------------------------------------------------------------------------------------------+

//(C) www.xanthium.in 
// Visit to Learn More 


#include <stdint.h>
#include <avr/io.h>

#define F_CPU  11059200
#include <util/delay.h>

// +-----------------------------------------------------------------------+ //
// | ATmega328p Baudrate values for UBRRn for external crystal 11.0592MHz  | //
// +-----------------------------------------------------------------------+ //

#define BAUD_RATE_4800_BPS  143 // 4800bps
#define BAUD_RATE_9600_BPS  71  // 9600bps

#define BAUD_RATE_14400_BPS  47 // 14.4k bps
#define BAUD_RATE_19200_BPS  35 // 19.2k bps
#define BAUD_RATE_28800_BPS  23 // 28.8k bps
#define BAUD_RATE_38400_BPS  17 // 38.4k bps
#define BAUD_RATE_57600_BPS  11 // 57.6k bps
#define BAUD_RATE_76800_BPS   8 // 76.8k bps

#define BAUD_RATE_115200_BPS  5 // 115.2k bps
#define BAUD_RATE_230400_BPS  2 // 230.4k bps


int main()
{
	
	int i = 0;
	unsigned int ubrr = BAUD_RATE_9600_BPS;  //Set Baudrate
	
	unsigned char data[] = "Hello from ATmega328p  "; //String to be transmitted
	
	// RS485 Control Lines
	// PD2 -> ~RE (Active Low signal)
	// PD3 ->  DE
	
	DDRD  |= (1<<PD2) | (1<<PD3); // PD2,PD3 both Outputs
	PORTD |= (1<<PD3);            // PD3->  DE = High; 
	                              // MAX485 Transmit mode
	PORTD |= (1<<PD2);            // PD2-> ~RE = High;
	
	
	
	/* Set Baudrate @ 9600bps */
	UBRR0H = (ubrr>>8);
	UBRR0L = (ubrr);
	
	/*Enable receiver and transmitter */
	UCSR0B = (1<<TXEN0);
	
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = 0x06;
	
	
	while(1) /* Loop the message continuously */
	{
		i = 0;
		while(data[i] != 0) /* print the String  "Hello from ATmega328p" */
		{
			while (!( UCSR0A & (1<<UDRE0))); /* Wait for empty transmit buffer       */
			UDR0 = data[i];					 /* Put data into buffer, sends the data */
			i++;                             /* increment counter                    */
		}
		
		/* Send new line Character */
		/* On the PC side we are using ReadLine() function to Read,
		/* which exits on receiving new line \n Character*/
		while (!( UCSR0A & (1<<UDRE0))); /* Wait for empty transmit buffer       */
		UDR0 = '\n';					 /* Put data into buffer, sends the data */
		
		_delay_ms(1000);
	}
	
	
	while(1);
}


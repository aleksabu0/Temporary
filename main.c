/**
 * @file main.c
 * @brief Implementacija Morzeovog koda
 * @author ABYU
 * @date 02.05.2021.
 * @version 1.0
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include"../timer0/timer0.h"
#include"../pin/pin.h"

///Konstantan niz za reprezentaciju slova u Morzeovom kodu
const PROGMEM uint16_t morse_letters[] = {0x0000, 0x0000, 0x0000, 0x0057,0x0001,
		0x0000,0x0000,0x0055,0x00,0x00,
		0x00,0x015d,0x00,0x00,0x0777,
		0x00,0x00,0x005d,0x00,0x00,
		0x00,0x00,0x01dd,0x00,0x00,
		0x00};

///Konstantan niz za broj bita potreban za reprezentaciju slova u Morzeovom kodu
const PROGMEM uint8_t letter_bit_repr[] = {0, 0, 0, 7, 1, 0, 0, 7, 0, 0, 0, 9, 0, 0,
		11, 0, 0, 7, 0, 0, 0, 0, 9, 0, 0, 0};

///Konstantan niz za redosled slova u poruci
const PROGMEM uint8_t word[] = {7, 4, 11, 11, 14, 22, 14, 17, 11, 3};

//h =8, e = 5, l = 12, o = 15, w = 23, r = 18, d =4

int main()
{
	///Promenljiva za privremeno cuvanje izmenjenog clana niza
	uint16_t temporary;

	///Red slova u nizu morse_letters[]
	uint8_t let_order;

	///Trenutno slovo koje se koristi u poruci
	uint8_t letter;

	timer0InteruptInit();
	pinInit(PORT_B,5,OUTPUT);
	timer0DelayMs(600);

	for(uint8_t i=0;i<10;i++)
	{
		let_order=pgm_read_byte(&word[i]);
		temporary = pgm_read_word(&morse_letters[let_order]);
		for(uint8_t j = 0; j<pgm_read_byte(&letter_bit_repr[let_order]);j++)
		{
			letter = 0x01 & temporary;
			if(letter==0)
			{
				pinSetValue(PORT_B,5,LOW);
			}
			else
			{
				pinSetValue(PORT_B,5,HIGH);
			}
			temporary=(temporary>>1);
			timer0DelayMs(300);
		}
		pinSetValue(PORT_B,5,LOW);
		if(i==4)
		{
			timer0DelayMs(2100);
		}
		else
		{
			timer0DelayMs(900);
		}
	}

   return 0;
}


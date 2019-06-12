﻿
#ifndef _MCU_INIT_H__
#define _MCU_INIT_H__

//////////////////////////////////////////////////////////////////
//include
//////////////////////////////////////////////////////////////////
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#define sbi(PORTX,BitX)  PORTX|= (1<<BitX)   //비트 set   명령 정의
#define cbi(PORTX,BitX)  PORTX&=~(1<<BitX)   //비트 clear 명령 정의
#define NUM1 0b11111001
#define NUM2 0b10100100
#define NUM3 0b10110000
#define OPEN 34
#define CLOSE 80

//////////////////////////////////////////////////////////////////
//Functions
//////////////////////////////////////////////////////////////////
void InitIO();
void InitExtInt();

void InitTimer0();
void InitTimer1();
void InitTimer2();
void InitTimer3();

void InitADC();
int GetADC(char ch);

void InitUart0();
void InitUart1();

void TransUart0(unsigned char data);
void TransUart1(unsigned char data);

void TransNumUart0(int num);
void TransNumUart1(int num);

unsigned char RecvUart0();
unsigned char RecvUart1();

void Init_CLCD();
void CLCD_Command(unsigned char Comm);
void CLCD_Data(unsigned char Data);
void CLCD_Position(unsigned char col, unsigned char row);
void CLCD_String_Data(unsigned char* str);

void ULTRA_SONIC_TRIG();


//////////////////////////////////////////////////////////////////
//enum for external interrupt
//EICRA
enum{

	INT0_LOW_LEVEL = 0x00,
	INT0_RESERVED = 0x01,
	INT0_FALLING = 0x02,
	INT0_RISING = 0x03,
	
	INT1_LOW_LEVEL = 0x00,
	INT1_RESERVED = 0x04,
	INT1_FALLING = 0x08,
	INT1_RISING = 0x0C,
	
	INT2_LOW_LEVEL = 0x00,
	INT2_RESERVED = 0x10,
	INT2_FALLING = 0x20,
	INT2_RISING = 0x30,
	
	INT3_LOW_LEVEL = 0x00,
	INT3_RESERVED = 0x40,
	INT3_FALLING = 0x80,
	INT3_RISING = 0xC0
};

//EICRB
enum{

	INT4_LOW_LEVEL = 0x00,
	INT4_TOGGLE = 0x04,
	INT4_FALLING = 0x08,
	INT4_RISING = 0x0C,
	
	INT5_LOW_LEVEL = 0x00,
	INT5_TOGGLE = 0x04,
	INT5_FALLING = 0x08,
	INT5_RISING = 0x0C,
	
	INT6_LOW_LEVEL = 0x00,
	INT6_TOGGLE = 0x10,
	INT6_FALLING = 0x20,
	INT6_RISING = 0x30,
	
	INT7_LOW_LEVEL = 0x00,
	INT7_TOGGLE = 0x40,
	INT7_FALLING = 0x80,
	INT7_RISING = 0xC0
};

//EIMSK
enum{

	INT0_ENABLE = 0x01,
	INT1_ENABLE = 0x02,
	INT2_ENABLE = 0x04,
	INT3_ENABLE = 0x08,
	INT4_ENABLE = 0x10,
	INT5_ENABLE = 0x20,
	INT6_ENABLE = 0x40,
	INT7_ENABLE = 0x80
};



//////////////////////////////////////////////////////////////////
//enum for timer0
//TCCR0
enum{
	
	TIMER0_WGM_NORMAL = 0x00,
	TIMER0_WGM_PWM = 0x08,
	TIMER0_WGM_CTC = 0x40,
	TIMER0_WGM_FAST_PWM   = 0x48
};
enum{

	TIMER0_COM_NORMAL = 0x00,
	TIMER0_COM_TOGGLE_OC0 = 0x10,
	TIMER0_COM_RESERVED_OC0 = 0x10,
	TIMER0_COM_CLEAR_OC0 = 0x20,
	TIMER0_COM_SET_OC0 = 0x30
};
enum{

	TIMER0_CS_NO_CLOCK_SOURCE = 0,
	TIMER0_CS_PRESCALER_1 = 1,
	TIMER0_CS_PRESCALER_8 = 2,
	TIMER0_CS_PRESCALER_64 = 3,
	TIMER0_CS_PRESCALER_256 = 4,
	TIMER0_CS_PRESCALER_1024 = 5,
	TIMER0_CS_EXTERNAL_CLOCK_T2_1FALLING = 6,
	TIMER0_CS_EXTERNAL_CLOCK_T2_RISING = 7
};

enum{

	TIMER0_COM_INT_ENABLE = 0x02,
	TIMER0_OVF_INT_ENABLE = 0x01
};


//////////////////////////////////////////////////////////////////
//enum for timer2
//TCCR2
enum{
	
	TIMER2_WGM_NORMAL = 0x00,
	TIMER2_WGM_PWM = 0x08,
	TIMER2_WGM_CTC = 0x40,
	TIMER2_WGM_FAST_PWM   = 0x48
};
enum{

	TIMER2_COM_NORMAL = 0x00,
	TIMER2_COM_TOGGLE_OC0 = 0x10,
	TIMER2_COM_RESERVED_OC0 = 0x10,
	TIMER2_COM_CLEAR_OC0 = 0x20,
	TIMER2_COM_SET_OC0 = 0x30
};
enum{

	TIMER2_CS_NO_CLOCK_SOURCE = 0,
	TIMER2_CS_PRESCALER_1 = 1,
	TIMER2_CS_PRESCALER_8 = 2,
	TIMER2_CS_PRESCALER_64 = 3,
	TIMER2_CS_PRESCALER_256 = 4,
	TIMER2_CS_PRESCALER_1024 = 5,
	TIMER2_CS_EXTERNAL_CLOCK_T2_1FALLING = 6,
	TIMER2_CS_EXTERNAL_CLOCK_T2_RISING = 7
};

//////////////////////////////////////////////////////////////////
//enum for timer0
//TIMSK
enum{

	TIMER2_COM_INT_ENABLE = 0x80,
	TIMER2_OVF_INT_ENABLE = 0x40
};

//////////////////////////////////////////////////////////////////
//enum for uart
//UCSRA
enum{

	USART_MULTI_PROCESSOR_MODE = 0x01,
	USART_DOUBLE_SPEED = 0x02,
	USART_PARITY_ERROR = 0x04,
	USART_DATA_OVERRUN = 0x08,
	USART_FRAME_ERROR = 0x10,
	USART_UDR_EMPTY = 0x20,
	USART_TRANS_COMPLETE = 0x40,
	USART_RECV_COMPLETE = 0x80
};

//UCSRB
enum{
	USART_CHAR_SIZE_9BIT_B = 0x04,
	USART_TRANS_ENABLE = 0x08,
	USART_RECV_ENABLE = 0x10,
	USART_UDR_EMPTY_INTERRUPT_ENABLE = 0x20,
	USART_TRANS_INTERRUPT_ENABLE = 0x40,
	USART_RECV_INTERRUPT_ENABLE = 0x80
};

//UCSRC
enum{

	USART_SYNC_MODE   = 0x40,
	USART_PARITY_NONE = 0x00,
	USART_PARITY_EVEN = 0x20,
	USART_PARITY_ODD = 0x30,
	USART_STOP_1BIT   = 0x00,
	USART_STOP_2BIT = 0x08,
	USART_CHAR_SIZE_5BIT = 0x00,
	USART_CHAR_SIZE_6BIT = 0x02,
	USART_CHAR_SIZE_7BIT = 0x04,
	USART_CHAR_SIZE_8BIT = 0x06,
	USART_CHAR_SIZE_9BIT_C = 0x06,
	USART_SYNC_CLOCK_RISING = 0x00,
	USART_SYNC_CLOCK_FALLING = 0x01
};

//UBRRL
enum{

	USART_9600BPS = 103,
	USART_115200BPS = 8
};


//////////////////////////////////////////////////////////////////
//enum for adc
//ADMUX
enum{

	ADC_REF_SELECTION_AREF = 0x00,
	ADC_REF_SELECTION_AVCC = 0x40,
	ADC_REF_SELECTION_INTERNAL = 0xC0,
	ADC_ADJUST_RIGHT = 0x00,
	ADC_ADJUST_LEFT = 0x20
};

enum{

	ADC_MUX_CH0 = 0,
	ADC_MUX_CH1 = 1,
	ADC_MUX_CH2 = 2,
	ADC_MUX_CH3 = 3,
	ADC_MUX_CH4 = 4,
	ADC_MUX_CH5 = 5,
	ADC_MUX_CH6 = 6,
	ADC_MUX_CH7 = 7
};

//ADCSRA
enum{

	ADC_INTERRUPT_ENABLE = 0x08,
	ADC_FREE_RUNNING = 0x20,
	ADC_CONVERTION_START = 0x40,
	ADC_ENABLE = 0x80
};
enum{
	ADC_PRESCALER_2 = 1,
	ADC_PRESCALER_4 = 2,
	ADC_PRESCALER_8 = 3,
	ADC_PRESCALER_16 = 4,
	ADC_PRESCALER_32 = 5,
	ADC_PRESCALER_64 = 6,
	ADC_PRESCALER_128 = 7
};

#endif 
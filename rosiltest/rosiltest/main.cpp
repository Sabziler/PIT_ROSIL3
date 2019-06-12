#include "mcu_init.h"
#include "stdlib.h"

volatile int g_Cnt = 0;
volatile int g_flag = 0;
volatile bool saram = true;
volatile unsigned short g_Time = 0;
volatile unsigned int distance = 0;

ISR(TIMER2_OVF_vect	){		// 약 16ms마다 인터럽트가 걸린다. 
	ULTRA_SONIC_TRIG();
	TransNumUart0(GetADC(5));
	TransUart0('\n');
	TransUart0('\r');
}

ISR(USART0_RX_vect){
	if(RecvUart0() == '1')
		saram = true;
	else
		saram = false;
}

ISR(INT0_vect){
	sbi(PORTF,7);
	OCR1A += 50;
}
ISR(INT1_vect){
	cbi(PORTF, 7);
	PORTA = NUM1;
	sbi(PORTE, 2);					//up
}
ISR(INT2_vect){
	cbi(PORTB, 2);
	PORTA = NUM2;
	cbi(PORTE, 2);					//down
	OCR1C = OPEN;
}
ISR(INT3_vect){
	cbi(PORTB, 3);
	OCR1C = CLOSE;
	PORTA = NUM3;
}

ISR(INT4_vect){
	 if((EICRB&0b00000011) == 0b00000010)//라이징일때
	 {
		 g_Time = TCNT3;
		 distance = g_Time/116;
		 EICRB = 0b00000011;//라이징으로 바꿈
	 }

	 else//폴링일때
	 {
		 TCNT3=0;
		 EICRB = 0b00000010;//폴링으로 바꿈
	 }
}



int main(void)
{
	unsigned char str1[] = "Smart-Elevator";
	InitIO();
	InitExtInt();
	InitUart0();	
	Init_CLCD();
	InitTimer1();
	InitTimer2();
	InitTimer3();
	InitADC();
	_delay_ms(500);
	CLCD_String_Data(str1);
	CLCD_Command(0xc0); // 커서를2번째줄첫번째칸으로이동
	sei();
    while (1){}
	return 0;
}


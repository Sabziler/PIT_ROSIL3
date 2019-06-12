#include "mcu_init.h"

 //////////////////////////////////////////////////////////////////
 //InitIO()
 //Initialize Input & Output of Port
 // Input : None
 // Output : None
 //////////////////////////////////////////////////////////////////
 void InitIO(){

	//////////////// 핀 세팅 //////////////////
	// UART 0번 사용 PE0 ~ 1					//
	// LED = PB0 ~ 3						//
	// 7SEG = PA0 ~ 7						//
	// SWITCH = PD0 ~ 3						//
	// CLCD_DATA = PC0 ~ 7					//
	// RS = PG0, R/W = PG1, E = PG2			//
	// SENSOR = PF0 ~ 7						//
	// MOTOR = PB5							//
	// ELEVATOR LED = PB6					//
	// SERVO = PB7							//
	// MOTOR_DIRECTION = PE2				//
	// ULTRA_SONIC TRIG = PE5				//
	// ULTRA_SONIC ECHO = PE4				//
	// POTENTIOMETER = PF0					//
	// PRESSURE_SENSOR = PF1				//
	//////////////////////////////////////////
	
    //TO DO
    DDRA = 0xff;			// 7SEG PIN 출력                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
	DDRB = 0xff;			// LED 출력
	DDRE = 0b00101110;		// UART0_RX 입력 TX출력 MOTOR_DIRECTION출력, SERVO PWM 출력, TRIG출력, ECHO입력
    PORTB = 0xff;			// 불좀 켜봅시다.
	PORTA = 0xff;			// 7segment 켜봅시다.	
	cbi(PORTE,5);
		
 }



 //////////////////////////////////////////////////////////////////
 //InitExtInt()
 //Initialize External Interrupt
 // Input : None
 // Output : None
 //////////////////////////////////////////////////////////////////
 void InitExtInt(){
    
    //TO DO
    DDRD = 0x00;
    
    EICRA = INT3_FALLING | INT2_FALLING | INT1_FALLING | INT0_FALLING;
    EICRB = INT4_RISING;
    EIMSK = INT4_ENABLE | INT3_ENABLE | INT2_ENABLE | INT1_ENABLE | INT0_ENABLE; 
 }



 //////////////////////////////////////////////////////////////////
 //InitTimer0()
 //Initialize Timer0
 // Input : None
 // Output : None
 //////////////////////////////////////////////////////////////////
 void InitTimer0(){
    
    //TO DO
	TCCR0 = TIMER0_WGM_NORMAL | TIMER0_COM_NORMAL | TIMER0_CS_PRESCALER_1024;
	TCNT0 = 0;
 }



 //////////////////////////////////////////////////////////////////
 //InitTimer1()
 //Initialize Timer1
 // Input : None
 // Output : None
 //////////////////////////////////////////////////////////////////
 void InitTimer1(){
    
    //TO DO
	TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<COM1C1)|(1<<WGM11)|(0<<WGM10);	// 1,2,3번채널 출력 14번 FASTPWM모드
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS12)|(0<<CS11)|(0<<CS10);		// 분주비 1
	ICR1 = 1250;
	OCR1A = 0;					// 모터정지
	OCR1B = 1250;				// LED출력 최대
	OCR1C = CLOSE;
 }



 //////////////////////////////////////////////////////////////////
 //InitTimer2()
 //Initialize Timer2
 // Input : None
 // Output : None
 //////////////////////////////////////////////////////////////////
 void InitTimer2(){
    
    TCCR2 = (1<<CS22)|(1<<CS20);
    TIMSK = (1<<TOIE2);//TIMER2_OVF_INT_ENABLE;
    //TCNT2 = 6; //250계단
}



 //////////////////////////////////////////////////////////////////
 //InitTimer3()
 //Initialize Timer3
 // Input : None
 // Output : None
 //////////////////////////////////////////////////////////////////
 void InitTimer3(){
	 
    //TO DO
	TCCR3A = (1<<COM3A1);
	TCCR3B = (1<<CS31);
	//ICR3 = 1250;
	//OCR3A = CLOSE;
 }



 //////////////////////////////////////////////////////////////////
 //InitADC()
 //InitADC
 // Input : None
 // Output : None
 //////////////////////////////////////////////////////////////////
 void InitADC(){
    
    //TO DO.
    DDRF = 0x80;
    ADMUX = ADC_REF_SELECTION_AVCC;
    ADCSRA = ADC_ADJUST_RIGHT | ADC_ENABLE | ADC_PRESCALER_128;
 }



 //////////////////////////////////////////////////////////////////
 //GetADC()
 //GetADC
 // Input : adc chanel
 // Output : ADC Result
 //////////////////////////////////////////////////////////////////
 int GetADC(char ch){
    
    //TO DO
    ADMUX = 0b01000000 | ch;   //인자로 넣은 채널 선택
    ADCSRA |= ADC_CONVERTION_START;
    while(!(ADCSRA & (1 << ADIF)));
    return ADC;
 }



 //////////////////////////////////////////////////////////////////
 //InitUart0()
 //InitUart0
 // Input : None
 // Output : None
 //////////////////////////////////////////////////////////////////
 void InitUart0(){
    
    //TO DO
	DDRE = 0b00101110;
	
	UCSR0A = 0x00;
	UCSR0B = USART_RECV_ENABLE | USART_TRANS_ENABLE  | USART_RECV_INTERRUPT_ENABLE;
	UCSR0C = USART_CHAR_SIZE_8BIT;
	
	UBRR0L = USART_115200BPS;
 }



 //////////////////////////////////////////////////////////////////
 //InitUart1()
 //InitUart1
 // Input : None
 // Output : None
 //////////////////////////////////////////////////////////////////
 void InitUart1(){
    
    //TO DO
    DDRD = (DDRD & 0xF3) | 0x08;
    
    UCSR1A = 0x00;
    UCSR1B = USART_RECV_ENABLE | USART_TRANS_ENABLE;
    UCSR1C = USART_CHAR_SIZE_8BIT;
    
    UBRR1L = USART_115200BPS;
 }



 //////////////////////////////////////////////////////////////////
 //TransUart0()
 //TransUart0
 // Input : Transmit data
 // Output : None
 //////////////////////////////////////////////////////////////////
 void TransUart0(unsigned char data){
    
    //TO DO
    while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;

 }



 //////////////////////////////////////////////////////////////////
 //TransUart1()
 //TransUart1
 // Input : Transmit data
 // Output : None
 //////////////////////////////////////////////////////////////////
 void TransUart1(unsigned char data){
    
    //TO DO
    while(!(UCSR1A & (1 << UDRE1)));
    UDR1 = data;
 }



 //////////////////////////////////////////////////////////////////
 //RecvUart0()
 //RecvUart0
 // Input : None
 // Output : Recved Data
 //////////////////////////////////////////////////////////////////
 unsigned char RecvUart0(){
    
    //TO DO
    while(!(UCSR0A & (1 << RXC0)));
    return UDR0;
 }



 //////////////////////////////////////////////////////////////////
 //RecvUart1()
 //RecvUart1
 // Input : None
 // Output : Recved Data
 //////////////////////////////////////////////////////////////////
 unsigned char RecvUart1(){
    
    //TO DO
    while(!(UCSR1A & (1 << RXC1)));
    return UDR1;
 }



 //////////////////////////////////////////////////////////////////
 //TransNumUart0()
 //TransNumUart0
 // Input : Number data
 // Output : None
 //////////////////////////////////////////////////////////////////
 void TransNumUart0(int num){
    
    //TO DO
	 if (num < 0)
	 {
		 TransUart0('-');
		 num = -num;
	 }
	TransUart0((num % 100000)/10000 + 48);
	TransUart0((num % 10000)/1000 + 48);
	TransUart0((num % 1000)/100 + 48);
	TransUart0((num % 100)/10 + 48);
	TransUart0((num % 10) + 48);
	//TransUart0(13);
	
 }



 //////////////////////////////////////////////////////////////////
 //TransNumUart1()
 //TransNumUart1
 // Input : Number data
 // Output : None
 //////////////////////////////////////////////////////////////////
 void TransNumUart1(int num){
    
    //TO DO
    TransUart1((num % 100000)/10000 + 48);
    TransUart1((num % 10000)/1000 + 48);
    TransUart1((num % 1000)/100 + 48);
    TransUart1((num % 100)/10 + 48);
	TransUart1((num % 10) + 48);
	TransUart1(13);
 }
 
 
 
  //////////////////////////////////////////////////////////////////
  //Init_CLCD()
  //Init_CLCD
  // Input : None
  // Output : None
  //////////////////////////////////////////////////////////////////
 void Init_CLCD(){
	 DDRC = 0xff;			// CLCD_DATA 출력  
	 DDRG = 0xff;			// CLCD 명령어 출력 
	 CLCD_Command(0x38); // FUNCTION SET
	 CLCD_Command(0x06); // ENTRY MODE
	 CLCD_Command(0x0c); // DISPLAY ON
	 CLCD_Command(0x01); // ALL CLEAR
 }
 
 
 
 //////////////////////////////////////////////////////////////////
 //CLCD_Command()
 //CLCD_Command
 // Input : COMMAND
 // Output : None
 //////////////////////////////////////////////////////////////////
 void CLCD_Command(unsigned char Comm){
	 PORTG = 0x04; // LCD를 명령쓰기모드로설정
	 PORTC = Comm; // 명령어 전송
	 PORTG &= 0xfb; // LCD Disable (E=0)
	 if(Comm == 0x01) // ALL CLEAR 명령만 대기시간이 길다.
		_delay_ms(2);
	 else 
		_delay_us(40);
 }
 
 
 
 //////////////////////////////////////////////////////////////////
 //CLCD_Data()
 //CLCD_Data
 // Input : ASCII DATA
 // Output : None
 //////////////////////////////////////////////////////////////////
 void CLCD_Data(unsigned char Data){
	 PORTG = 0x05; // LCD를 데이터쓰기모드로설정
	 PORTC = Data;  // 데이터 전송
	 PORTG &= 0xfb; // LCD Disable (E=0)
	 _delay_us(50);
	 //for(int i=0; i<10; i++) _delay_ms(10);
 }
 
 
 
 
  //////////////////////////////////////////////////////////////////
  //CLCD_String_Data()
  //CLCD_String_Data
  // Input : unsigned char* data
  // Output : None
  //////////////////////////////////////////////////////////////////
 void CLCD_String_Data(unsigned char* str){
	while(*str !=0){
		CLCD_Data(*str);
		str++;
	}
 }

void CLCD_Position(unsigned char col, unsigned char row){
	CLCD_Command(0x80 | (col + row * 0x40));
}

 //////////////////////////////////////////////////////////////////
 //ULTRA_SONIC_TRIG()
 //ULTRA_SONIC_TRIGGER
 // Input : None
 // Output : None
 ////////////////////////////////////////////////////////////////// 
 void ULTRA_SONIC_TRIG(){
	 sbi(PORTE, 5);		// TRIG핀 SET
	 _delay_us(10);
	 cbi(PORTE, 5);		// TRIG핀 CLEAR
 }
 
 
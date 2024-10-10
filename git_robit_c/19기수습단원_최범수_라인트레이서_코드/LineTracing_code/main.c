#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD_Text.h"

int adc_regular_max[6] = {0,};
int adc_regular_min[6] = {1023,1023,1023,1023,1023,1023};
double adc_regular[6];

int adc_num[6];
int adc_min_setted[6] = {0,};
int adc_max_setted[6] = {0,};
   
char buffer[6][10];
int phase = 0;

unsigned int capture_value = 0;
unsigned int rising_edge = 1;
unsigned int distance;

//IR센서   
void adc_set()
{
   DDRF = 0x00;
   ADMUX = 0x40;
   ADCSRA = 0x87;
   SREG = 0x80;
}
//IR센서 값 읽기
unsigned int read_adc(unsigned int channel)
{
   ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); //ADC 채널 설정
   ADCSRA |= (1 << ADSC); // 변환 시작
   while (ADCSRA & (1 << ADSC));
   return ADC;
}
//정규화 - 최대 최소
void set_max_min(void)
{
   for(int i = 0; i < 6; i++)
   {
      if(adc_num[i] > 0)
      {
        
         if(adc_regular_min[i] > adc_num[i])
         adc_regular_min[i] = adc_num[i];
		  if(adc_regular_max[i] < adc_num[i])
         adc_regular_max[i] = adc_num[i];
      }
   }
}
//
void adc_regular_set(void)
{
   for(int i = 0; i < 6; i++)
   {
      if(adc_max_setted[i] != adc_min_setted[i]) // 분모가 0이 되는 것을 방지
      {
         adc_regular[i] = (double)(adc_num[i] - adc_min_setted[i]) / (adc_max_setted[i] - adc_min_setted[i]);
      }
      else
      {
         adc_regular[i] = 0; // 분모가 0이면 0으로 설정
      }
   }
}
// 스위치 0번 인터럽트
ISR(INT0_vect)
{
   for(int i = 0; i < 6; i++)
   {
      adc_max_setted[i] = adc_regular_max[i];
      adc_min_setted[i] = adc_regular_min[i];
   }
   lcdClear();
}
//LCD 출력
void LCD_Print()
{
   lcdString(0, 0, buffer[0]);  // PF1 (ADC1)
   lcdString(0, 5, buffer[1]);  // PF2 (ADC2)
   lcdString(0, 10, buffer[2]);  // PF3 (ADC3)
   lcdString(1, 0, buffer[3]);  // PF4 (ADC4)
   lcdString(1, 5, buffer[4]);  // PF5 (ADC5)
   lcdString(1, 10, buffer[5]);  // PF6 (ADC6)
}

void motor_set()
{
   DDRB = 0x6F;
   TCCR1A = 0xA2;
   TCCR1B = 0x1A;
   TCCR1C = 0x00;
   
   ICR1 = 399;
   TCNT1 = 0x00;
   
   SREG = 0x80;
}


int main(void)
{
   DDRA = 0xff;
   DDRB = (1 << PB0);
   DDRD = 0x00;
   
   EIMSK = (1 << INT0);
   EICRA = (0 << ISC01) | (0 << ISC00);
   
   adc_set();
   motor_set();
   
   
   lcdInit();
   lcdClear();
   
   int mode = 100;
   int mode2 = 100;
   int cnt_park = 0;
   int nmode = 0;
   int nmode_chg = 1;
   while (1)
   {
      
      lcdClear();
      set_max_min();
      // PF1~PF6 핀에 해당하는 ADC 값을 읽어서 배열에 저장
      for (int i = 0; i < 6; i++)
      {
         unsigned int adc_value = read_adc(i + 1);  // PF1~6
         adc_num[i] = adc_value;
      }
               unsigned int ultra_value = read_adc(0);
     unsigned int front_distance = read_adc(7);
      adc_regular_set();
      
      for(int i = 0; i < 6; i++)
      {
         sprintf(buffer[i], "%.2lf", adc_regular[i]); // 각 채널의 값을 buffer에 저장
      }

      //-----------------------모터 출력--------------------------------//
     //-------------------------------------------phase 0----------------------------------------//
     if(phase == 0)
     {
		 if(nmode_chg == 2)
		 {
			 if(adc_regular[4] > 0.6)
			 {
				 PORTB = (PORTB & 0xF0) | 0x06;
				 OCR1A = ICR1 * 0.7;
				 OCR1B = ICR1 * 0.7;
			 }
			 else if(adc_regular[4] < 0.6 && adc_regular[4] > 0.2)
			 {
				 PORTB = (PORTB & 0xF0) | 0x05;
				 OCR1A = ICR1 * 0.6;
				 OCR1B = ICR1 * 0.7;
				 _delay_ms(300);
				 nmode_chg = 1;
			 }
		 }
		 else if(nmode_chg == 1)
		 {
       if(adc_regular[0] < 0.1 && adc_regular[5] < 0.1)
       {
          if(adc_regular[2] > 0.1 || adc_regular[3] > 0.1 || adc_regular[4] > 0.1)
          {
             phase = 1;
             nmode = 1;
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0.7;
             OCR1B = ICR1 * 0.6;
             _delay_ms(1400);
          }
       }
       else
       {
       if(adc_regular[2] < 0.6 && adc_regular[2] > 0.4 && adc_regular[3] < 0.6 && adc_regular[3] > 0.4)
       {
          PORTB = (PORTB & 0xF0) | 0x05;
          OCR1A = ICR1 * 0.6;
          OCR1B = ICR1 * 0.6;
          _delay_ms(550);
          nmode_chg = 2;
       }
       else if(adc_regular[5] < 0.6)
       {
          PORTB = (PORTB & 0xF0) | 0x05;
          OCR1A = ICR1 * 0;
          OCR1B = ICR1 * 0.9;
       }
       else if(adc_regular[4] < 0.6)
       {
         PORTB = (PORTB & 0xF0) | 0x05;
         OCR1A = ICR1 * 0;
         OCR1B = ICR1 * 0.7; 
       }
       else
       {
          PORTB = (PORTB & 0xF0) | 0x05;
          OCR1A = ICR1 * 0.65;
          OCR1B = ICR1 * 0;
       }
       }
		 }
       LCD_Print();
      /*
        if(adc_regular[0] < 0.1 && adc_regular[5] < 0.1)
        {
         if(adc_regular[2] > 0.1 || adc_regular[3] > 0.1 || adc_regular[4] > 0.1)
         {
            phase = 1;
         nmode = 1;
            PORTB = (PORTB & 0xF0) | 0x05;
            OCR1A = ICR1 * 0.5;
            OCR1B = ICR1 * 0.7;
            _delay_ms(1600);
         }
        }
        else
        {
           if(mode == 15) // 전부 감지 0~5까지(오류 때문에 2,3)
           {
              PORTB = (PORTB & 0xF0) | 0x05;
              OCR1A = ICR1 * 0.80;
              OCR1B = ICR1 * 0.70;
              mode = 100;
           }
           else if(mode == 0)
           {
              if(adc_regular[1] > 0.6 && adc_regular[5] > 0.6)
              {
                 PORTB = (PORTB & 0xF0) | 0x05;
                 OCR1A = ICR1 * 0;
                 OCR1B = ICR1 * 0.85;
              }
              mode = 100;
           }
           else if(mode == 5)
           {
              if(adc_regular[0] > 0.6 && adc_regular[4] > 0.6)
              {
                 PORTB = (PORTB & 0xF0) | 0x05;
                 OCR1A = ICR1 * 0.85;//1
                 OCR1B = ICR1 * 0;
              }
              mode = 100;
           }
           
           else
           {
            if(adc_regular[1] < 0.6 && adc_regular[4] < 0.6)
            {
               if(adc_regular[2] < 0.6 && adc_regular[3] < 0.6)
               {
                   PORTB = (PORTB & 0xF0) | 0x05;
                  OCR1A = ICR1 * 0.9;//85

                  _delay_ms(300);
               }
            }
            else if(adc_regular[0] < 0.6 && adc_regular[1] < 0.6 && adc_regular[2] < 0.6 && adc_regular[3] < 0.6 && adc_regular[4] > 0.6 && adc_regular[5] > 0.6)
            {
               PORTB = (PORTB & 0xF0) | 0x05;
               OCR1A = ICR1 * 0.7;//85
               OCR1B = ICR1 * 0.7;
               _delay_ms(300);
            }
            else if(adc_regular[0] < 0.6)
            {
               PORTB = (PORTB & 0xF0) | 0x05;
               OCR1A = ICR1 * 0;
               OCR1B = ICR1 * 0.80;//85
               mode = 0;
            }
            else if(adc_regular[5] < 0.6)
            {
               PORTB = (PORTB & 0xF0) | 0x05;
               OCR1A = ICR1 * 0.80;//85
               OCR1B = ICR1 * 0;
               mode = 5;
            }
              else if(adc_regular[4] < 0.6)
              {
                 PORTB = (PORTB & 0xF0) | 0x05;
                 OCR1A = ICR1 * 0.80;
                 OCR1B = ICR1 * 0;
                 mode = 5;
              }
              else if(adc_regular[1] < 0.6)
              {
                 PORTB = (PORTB & 0xF0) | 0x05;
                 OCR1A = ICR1 * 0;
                 OCR1B = ICR1 * 0.80;
                 mode = 0;
              }
              //고정
              else if(adc_regular[2] < 0.6)
              {
                 PORTB = (PORTB & 0xF0) | 0x05;
                 OCR1A = ICR1 * 0;
                 OCR1B = ICR1 * 0.60;
                 mode = 0;
              }
              //고정
              else if(adc_regular[3] < 0.6)
              {
                 PORTB = (PORTB & 0xF0) | 0x05;
                 OCR1A = ICR1 * 0.60;
                 OCR1B = ICR1 * 0;
                 mode = 5;
              }
              else
              {
                 PORTB = (PORTB & 0xF0) | 0x0A;
                 OCR1A = ICR1 * 0.75;
                 OCR1B = ICR1 * 0.65;
              }
           }
        }//phase 전환
      */
     }//phase
    
      //-------------------------------------------black phase 0 finished-------------------------------------------------//
      else if(phase == 1)
     {
       //LCD_Print();
       //lcdNumber(0, 0, front_distance);
       //lcdNumber(0, 5, cnt_park);
       //lcdNumber(1, 0, cnt_front_check);
       lcdNumber(1, 0, ultra_value);
       lcdNumber(0, 0, front_distance);
      if(nmode == 1)
      {
         if(adc_regular[0] > 0.1 || adc_regular[2] > 0.1 || adc_regular[3] > 0.1 || adc_regular[4] > 0.1 || adc_regular[5] > 0.1)
         nmode = 2;
         else if(ultra_value > 410 && adc_regular[2] < 0.1 && adc_regular[3] < 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0.6;
             OCR1B = ICR1 * 0.9;
          }
          else if(ultra_value < 390 && ultra_value > 100 && adc_regular[2] < 0.1 && adc_regular[3] < 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0.9;
             OCR1B = ICR1 * 0.6;
          }
      }
          else if(nmode == 2)
        {
           if(cnt_park == 3)
           {
              PORTB = (PORTB & 0xF0) | 0x05;
              OCR1A = ICR1 * 0.75;
              OCR1B = ICR1 * 0.70;
              _delay_ms(2300);
			  PORTB = (PORTB & 0xF0) | 0x05;
			  OCR1A = ICR1 * 0;
			  OCR1B = ICR1 * 0;
			  _delay_ms(200);
              PORTB = (PORTB & 0xF0) | 0x05;
              OCR1A = ICR1 * 0;
              OCR1B = ICR1 * 0;
              _delay_ms(6600);
			  PORTB = (PORTB & 0xF0) | 0x05;
			  OCR1A = ICR1 * 0;
			  OCR1B = ICR1 * 0;
			  _delay_ms(200);
              PORTB = (PORTB & 0xF0) | 0x09;
              OCR1A = ICR1 * 0.90;
              OCR1B = ICR1 * 0.90;
              _delay_ms(1400);
			  PORTB = (PORTB & 0xF0) | 0x05;
			  OCR1A = ICR1 * 0;
			  OCR1B = ICR1 * 0;
			  _delay_ms(200);
              PORTB = (PORTB & 0xF0) | 0x05;
              OCR1A = ICR1 * 0.80;
              OCR1B = ICR1 * 0.80;
              _delay_ms(1500);
			  PORTB = (PORTB & 0xF0) | 0x05;
			  OCR1A = ICR1 * 0;
			  OCR1B = ICR1 * 0;
			  _delay_ms(200);
			  PORTB = (PORTB & 0xF0) | 0x09;
			  OCR1A = ICR1 * 0.80;
			  OCR1B = ICR1 * 0.80;
			  _delay_ms(700);
			  PORTB = (PORTB & 0xF0) | 0x05;
			  OCR1A = ICR1 * 0;
			  OCR1B = ICR1 * 0;
			  _delay_ms(200);
			  if(adc_regular[5] > 0.1)
			  {
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0.60;
				  OCR1B = ICR1 * 0;
				  _delay_ms(200);
			  }
			  
              cnt_park = 100;
              nmode = 3;
           }
           else if(cnt_park == 2)
           {
              if(front_distance < 300)
              {
                 cnt_park = 3;
              }
              else if(front_distance > 350)
              {
                 PORTB = (PORTB & 0xF0) | 0x05;
                 OCR1A = ICR1 * 0;
                 OCR1B = ICR1 * 0;
              }
           }
                else if(front_distance > 350 && adc_regular[0] > 0.1 && adc_regular[5] > 0.1 && cnt_park != 100)
                {
               PORTB = (PORTB & 0xF0) | 0x05;
               OCR1A = ICR1 * 0;
               OCR1B = ICR1 * 0;
			   _delay_ms(200);
               cnt_park = 2;
                }
            else if(front_distance < 300 && front_distance > 100 && adc_regular[0] > 0.1 && adc_regular[5] > 0.1 && cnt_park != 100)
            {
               PORTB = (PORTB & 0xF0) | 0x05;
               OCR1A = ICR1 * 0;
               OCR1B = ICR1 * 0;
            }
            
            else
            {
               if(adc_regular[5] > 0.1)
               {
                  PORTB = (PORTB & 0xF0) | 0x05;
                  OCR1A = ICR1 * 0.85;//85
                  OCR1B = ICR1 * 0;
               }
               else if(adc_regular[0] > 0.1)
               {
                  PORTB = (PORTB & 0xF0) | 0x05;
                  OCR1A = ICR1 * 0;
                  OCR1B = ICR1 * 0.85;//85
               }
               else if(adc_regular[4] > 0.1)
               {
                  PORTB = (PORTB & 0xF0) | 0x05;
                  OCR1A = ICR1 * 0.80;
                  OCR1B = ICR1 * 0;
               }
               else if(adc_regular[1] > 0.1)
               {
                  PORTB = (PORTB & 0xF0) | 0x05;
                  OCR1A = ICR1 * 0;
                  OCR1B = ICR1 * 0.80;
               }
               //고정
               else if(adc_regular[2] > 0.1)
               {
                  PORTB = (PORTB & 0xF0) | 0x05;
                  OCR1A = ICR1 * 0;
                  OCR1B = ICR1 * 0.70;
                  mode2 = 0;
               }
               //고정
               else if(adc_regular[3] > 0.1)
               {
                  PORTB = (PORTB & 0xF0) | 0x05;
                  OCR1A = ICR1 * 0.70;
                  OCR1B = ICR1 * 0;
                  mode2 = 5;
               }
               else if(adc_regular[0] < 0.1 && adc_regular[1] < 0.1 && adc_regular[2] < 0.1 && adc_regular[3] < 0.1 && adc_regular[4] < 0.1 && adc_regular[5] < 0.1)
               {
                  PORTB = (PORTB & 0xF0) | 0x0A;
                  OCR1A = ICR1 * 0.75;
                  OCR1B = ICR1 * 0.65;
               }
            }
    }
          else if(nmode == 3)//nmode 4하기
          {
             if(adc_regular[5] > 0.2)
             {
				 PORTB = (PORTB & 0xF0) | 0x05;
				 OCR1A = ICR1 * 0;
				 OCR1B = ICR1 * 0;
				 _delay_ms(200);
                PORTB = (PORTB & 0xF0) | 0x05;
                OCR1A = ICR1 * 0.7;
                OCR1B = ICR1 * 0.7;
                _delay_ms(600);
				PORTB = (PORTB & 0xF0) | 0x05;
				OCR1A = ICR1 * 0;
				OCR1B = ICR1 * 0;
				_delay_ms(200);
                PORTB = (PORTB & 0xF0) | 0x09;
                OCR1A = ICR1 * 0.65;
                OCR1B = ICR1 * 0.65;
                _delay_ms(850);
				nmode = 50;
				
             }

             else if(adc_regular[0] > 0.1)
             {
                PORTB = (PORTB & 0xF0) | 0x05;
                OCR1A = ICR1 * 0;
                OCR1B = ICR1 * 0.7;
             }
             else if(adc_regular[1] > 0.1)
             {
                PORTB = (PORTB & 0xF0) | 0x05;
                OCR1A = ICR1 * 0;
                OCR1B = ICR1 * 0.65;
             }
             else
             {
                PORTB = (PORTB & 0xF0) | 0x05;
                OCR1A = ICR1 * 0.7;
                OCR1B = ICR1 * 0;
             }
          }
		  else if(nmode == 4)
		  {
			  if(adc_regular[5] > 0.2)
			  {
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0;
				  OCR1B = ICR1 * 0;
				  _delay_ms(200);
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0.7;
				  OCR1B = ICR1 * 0.7;
				  _delay_ms(520);
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0;
				  OCR1B = ICR1 * 0;
				  _delay_ms(200);
				  PORTB = (PORTB & 0xF0) | 0x09;
				  OCR1A = ICR1 * 0.65;
				  OCR1B = ICR1 * 0.65;
				  _delay_ms(1000);
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0;
				  OCR1B = ICR1 * 0;
				  _delay_ms(200);
				  if(adc_regular[5] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.60;
					  OCR1B = ICR1 * 0;
					  _delay_ms(200);
				  }
				  nmode = 5;
			  }
			  else if(adc_regular[0] > 0.1)
			  {
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0;
				  OCR1B = ICR1 * 0.7;
			  }
			  else if(adc_regular[1] > 0.1)
			  {
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0;
				  OCR1B = ICR1 * 0.65;
			  }
			  else
			  {
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0.7;
				  OCR1B = ICR1 * 0;
			  }
		  }
		  else if(nmode == 5)
		  {
			  if(adc_regular[5] > 0.2)
			  {
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0;
				  OCR1B = ICR1 * 0;
				  _delay_ms(200);
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0.7;
				  OCR1B = ICR1 * 0.7;
				  _delay_ms(600);
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0;
				  OCR1B = ICR1 * 0;
				  _delay_ms(200);
				  PORTB = (PORTB & 0xF0) | 0x09;
				  OCR1A = ICR1 * 0.65;
				  OCR1B = ICR1 * 0.65;
				  _delay_ms(830);
				  
				  nmode = 52;
			  }

			  else if(adc_regular[0] > 0.1)
			  {
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0;
				  OCR1B = ICR1 * 0.7;
			  }
			  else if(adc_regular[1] > 0.1)
			  {
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0;
				  OCR1B = ICR1 * 0.65;
			  }
			  else
			  {
				  PORTB = (PORTB & 0xF0) | 0x05;
				  OCR1A = ICR1 * 0.7;
				  OCR1B = ICR1 * 0;
			  }
		  }
			  else if(nmode == 50)
			  {
				  if(adc_regular[0] > 0.1 && adc_regular[5] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0;
					  _delay_ms(200);
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.7;
					  OCR1B = ICR1 * 0.7;
					  _delay_ms(550);
					  PORTB = (PORTB & 0xF0) | 0x06;
					  OCR1A = ICR1 * 0;//85
					  OCR1B = ICR1 * 0;
					  _delay_ms(200);
					  PORTB = (PORTB & 0xF0) | 0x06;
					  OCR1A = ICR1 * 0.65;//85
					  OCR1B = ICR1 * 0.65;
					  _delay_ms(1700);
					   PORTB = (PORTB & 0xF0) | 0x05;
					   OCR1A = ICR1 * 0;
					   OCR1B = ICR1 * 0;
					   _delay_ms(200);
					  nmode = 51;
				  }
				  else if(adc_regular[5] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.85;//85
					  OCR1B = ICR1 * 0;
				  }
				  else if(adc_regular[0] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0.85;//85
					  
				  }
				  else if(adc_regular[4] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.80;
					  OCR1B = ICR1 * 0;
				  }
				  else if(adc_regular[1] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0.90;
				  }
			  }
			  else if(nmode == 51)
			  {
				  if(adc_regular[0] > 0.1 && adc_regular[5] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0;
					  _delay_ms(200);
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.7;
					  OCR1B = ICR1 * 0.7;
					  _delay_ms(400);
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0;
					  _delay_ms(200);
					  PORTB = (PORTB & 0xF0) | 0x09;
					  OCR1A = ICR1 * 0.65;
					  OCR1B = ICR1 * 0.65;
					  _delay_ms(900);
					   PORTB = (PORTB & 0xF0) | 0x05;
					   OCR1A = ICR1 * 0;
					   OCR1B = ICR1 * 0;
					   _delay_ms(200);
					  nmode = 4;
				  }
				  else if(adc_regular[5] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.85;//85
					  OCR1B = ICR1 * 0;
				  }
				  else if(adc_regular[0] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0.85;//85
					  
				  }
				  else if(adc_regular[4] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.80;
					  OCR1B = ICR1 * 0;
				  }
				  else if(adc_regular[1] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0.90;
				  }
			  }
			  else if(nmode == 52)
			  {
				  if(adc_regular[0] > 0.1 && adc_regular[5] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0;
					  _delay_ms(200);
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.7;
					  OCR1B = ICR1 * 0.7;
					  _delay_ms(600);
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0;
					  _delay_ms(200);
					  PORTB = (PORTB & 0xF0) | 0x06;
					  OCR1A = ICR1 * 0.65;//85
					  OCR1B = ICR1 * 0.65;
					  _delay_ms(1700);
					   PORTB = (PORTB & 0xF0) | 0x05;
					   OCR1A = ICR1 * 0;
					   OCR1B = ICR1 * 0;
					   _delay_ms(200);
					  nmode = 53;
				  }
				  else if(adc_regular[5] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.85;//85
					  OCR1B = ICR1 * 0;
				  }
				  else if(adc_regular[0] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0.85;//85
					  
				  }
				  else if(adc_regular[4] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.80;
					  OCR1B = ICR1 * 0;
				  }
				  else if(adc_regular[1] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0.90;
				  }
			  }
			  else if(nmode == 53)
			  {
				  if(adc_regular[0] > 0.1 && adc_regular[5] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0;
					  _delay_ms(200);
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.7;
					  OCR1B = ICR1 * 0.7;
					  _delay_ms(500);
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0;
					  _delay_ms(200);
					  PORTB = (PORTB & 0xF0) | 0x09;
					  OCR1A = ICR1 * 0.65;
					  OCR1B = ICR1 * 0.65;
					  _delay_ms(900);
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0;
					  _delay_ms(200);
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 1.2;
					  OCR1B = ICR1 * 1.2;
					  _delay_ms(500);
					  
					  phase = 2;
				  }
				  else if(adc_regular[5] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.85;//85
					  OCR1B = ICR1 * 0;
				  }
				  else if(adc_regular[0] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0.85;//85
					  
				  }
				  else if(adc_regular[4] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0.80;
					  OCR1B = ICR1 * 0;
				  }
				  else if(adc_regular[1] > 0.1)
				  {
					  PORTB = (PORTB & 0xF0) | 0x05;
					  OCR1A = ICR1 * 0;
					  OCR1B = ICR1 * 0.90;
				  }
			  }
			  
       else
       {
       if(mode2 == 0)
       {
          if(adc_regular[1] < 0.1 && adc_regular[5] < 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0;
             OCR1B = ICR1 * 0.85;
          }
          mode2 = 100;
       }
       else if(mode2 == 5)
       {
          if(adc_regular[0] < 0.1 && adc_regular[4] < 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0.85;//1
             OCR1B = ICR1 * 0;
          }
          mode2 = 100;
       }
       
       else
       {
          if(adc_regular[1] > 0.1 && adc_regular[4] > 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0.8;//85
             OCR1B = ICR1 * 0.7;
          }
          else if(adc_regular[5] > 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0.85;//85
             OCR1B = ICR1 * 0;
             mode2 = 5;
          }
          else if(adc_regular[0] > 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0;
             OCR1B = ICR1 * 0.85;//85
             mode2 = 0;
             
          }
          else if(adc_regular[4] > 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0.80;
             OCR1B = ICR1 * 0;
             mode2 = 5;
          }
          else if(adc_regular[1] > 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0;
             OCR1B = ICR1 * 0.90;
             mode2 = 0;
          }
          //고정
          else if(adc_regular[2] > 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0;
             OCR1B = ICR1 * 0.60;
             mode2 = 0;
          }
          //고정
          else if(adc_regular[3] > 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x05;
             OCR1A = ICR1 * 0.60;
             OCR1B = ICR1 * 0;
             mode2 = 5;
          }
          else if(adc_regular[0] < 0.1 && adc_regular[1] < 0.1 && adc_regular[2] < 0.1 && adc_regular[3] < 0.1 && adc_regular[4] < 0.1 && adc_regular[5] < 0.1)
          {
             PORTB = (PORTB & 0xF0) | 0x0A;
             OCR1A = ICR1 * 0.75;
             OCR1B = ICR1 * 0.65;
          }
       }
      }
       

     }//phase 1
	 else if(phase == 2)
	 {
		 if(front_distance > 300 && ultra_value > 400)
		 {
			 PORTB = (PORTB & 0xF0) | 0x05;
			 OCR1A = ICR1 * 0;
			 OCR1B = ICR1 * 1.2;
		 }
		else if(ultra_value > 400)
		{
			PORTB = (PORTB & 0xF0) | 0x05;
			OCR1A = ICR1 * 0;
			OCR1B = ICR1 * 0.8;
		}
		else if(front_distance > 300)
		{
			PORTB = (PORTB & 0xF0) | 0x05;
			OCR1A = ICR1 * 0;
			OCR1B = ICR1 * 0.8;
		}
		else
		{
			PORTB = (PORTB & 0xF0) | 0x05;
			OCR1A = ICR1 * 0.8;
			OCR1B = ICR1 * 0;
		}
	 }
	 ultra_value = 0;
	 front_distance = 0;
	 }//혹시 안되면 괄호 위치 확인하자
	 
   }



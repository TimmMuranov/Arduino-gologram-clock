//------------ декларирую распиновку --------------------
#define button 2
#define  led_1 3
#define  led_2 4
#define  led_3 5
#define  led_4 6
#define  led_5 7
//---------- включаю библиотеки -------------------------
#include<TimeLib.h>//для работы со временем
#include "numbers.h"
//---- объявляю глобальные переменные--------
bool leds[5];
//диодоы изменяются на этот массив
//------объявляю цифры в нужном формате----
//первый элемент  (- 1) - цифра
//Второй элемент - высоту (начиная с верху)
//Третий элемент - столбец (начиная слева)

//======= Функция возвращает время =====
long getTime() {
  static unsigned long startTime = millis(); // время запуска микроконтроллера
  unsigned long currentTime = millis() - startTime; // текущее прошедшее время
 
  int hours = currentTime / 3600000 % 24; // вычисление часов
  int minutes = (currentTime % 3600000) / 60000; // вычисление минут
 
  long formattedTime = hours * 100 + minutes; // форматирование времени в формат "АБСД"
 
  if (hours >= 24) { // сброс времени после 24 часов
	startTime = millis();
	formattedTime = 0;
  }
  return 10000 + formattedTime;
}
//== Функция дробления числа на разряды ==
int getDigit(long number, int index) {
  long digit = 0;
  long count = 0;
  while (number > 0)
  {
	digit = number % 10;
	number /= 10;
	if (count == index)
	{
  	return digit;
	}
	count++;
  }
  return -1; // Если индекс больше, чем количество разрядов числа
}

void led_write(){
digitalWrite(led_1,leds[0]);
digitalWrite(led_2,leds[1]);
digitalWrite(led_3,leds[2]);
digitalWrite(led_4,leds[3]);
digitalWrite(led_5,leds[4]);
}

void led_include(int stolb, int digit){
	for(int x=0; x<5; ++x){
	    leds[x] = numbers [digit][x][stolb];
	}
  }
 
void setup(){
  Serial.begin(9600);
 	pinMode(button, INPUT_PULLUP);
 	pinMode(led_1, OUTPUT);
 	pinMode(led_2, OUTPUT);
 	pinMode(led_3, OUTPUT);
 	pinMode(led_4, OUTPUT);
 	pinMode(led_5, OUTPUT);
  }

void loop(){
   if(digitalRead(button) == 0){
        for (int segment = 0; segment < 3; ++segment) {
            for (int digit = 0; digit <= segment; ++digit) {
                led_include(digit, getDigit(getTime(), 3 - segment + digit));
                led_write();
                delay(20);
            }
            led_include(0, 11);
            led_write();
            delay((segment == 1 ? 500 : 300));
        }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 	 
   }
   else {led_include(0, 11); led_write();}
   Serial.println(getTime());
}

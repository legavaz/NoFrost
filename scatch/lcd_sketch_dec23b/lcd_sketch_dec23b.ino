/*
питание:
gnd - земля
vcc - 5V 
порты i2c:
SCL - пин A5
SDA - пин A4
*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // Подключение библиотеки
//#include <LiquidCrystal_PCF8574.h> // Подключение альтернативной библиотеки

LiquidCrystal_I2C lcd(0x27,16,2); // Указываем I2C адрес (наиболее распространенное значение), а также параметры экрана (в случае LCD 1602 - 2 строки по 16 символов в каждой 
//LiquidCrystal_PCF8574 lcd(0x27); // Вариант для библиотеки PCF8574 

void setup()
{
  lcd.init();                      // Инициализация дисплея  
  lcd.backlight();                 // Подключение подсветки
  lcd.setCursor(0,0);              // Установка курсора в начало первой строки
  lcd.print("Hello");       // Набор текста на первой строке
  lcd.setCursor(0,1);              // Установка курсора в начало второй строки
  lcd.print("ArduinoMaster");       // Набор текста на второй строке
}
void loop()
{
}
